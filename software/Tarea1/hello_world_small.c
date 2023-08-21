#include "sys/alt_stdio.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

#include "system.h"

static unsigned segCount = 0;
static unsigned msCount = 0;
static unsigned minCount = 0;


static unsigned mode = 0;
static unsigned stop = 0;
volatile int start = 0;


static void count()
{
	if (msCount >= 99)
	{
		msCount = 0;
		segCount++;
	}
	else if (segCount >= 60)
	{
		segCount = 0;
		minCount++;
	}
	else if(minCount >= 99)
	{
		minCount = 0;
	}
	msCount++;
}


static void display()
{
	mode = IORD_ALTERA_AVALON_PIO_DATA(PIO_SWITCH_0_BASE);
	if(mode == 0)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_MS_NUM_0_BASE, msCount);
	}
	else if(mode == 1)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_LEDS_0_BASE, segCount);

	}
	else
	{
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_MIN_NUM_0_BASE, minCount);
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_LEDS_0_BASE, segCount);
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_MS_NUM_0_BASE, msCount);
	}
}


static void timer_isr(void *context)
{
	(void) context;
	stop = IORD_ALTERA_AVALON_PIO_DATA(PIO_BUTTON_STOP_BASE);

	if(start == 1 && stop == 0)
	{
		display();
		count();
	}
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}



/* This is the ISR which will be called when the system signals an interrupt. */
static void start_interrupt(void* context)
{
    //Cast context to start's type
    //Volatile to avoid compiler optimization
    //this will point to the start variable.
    volatile int* start_ptr = (volatile int*) context;

    //Read the edge capture register on the PIO and store the value
    //The value will be stored in the start variable and accessible
    //from other parts of the code.
    *start_ptr = 1;

    //Write to edge capture register to reset it
    //IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_BUTTON_START_BASE,0);

}


int main()
{
  alt_ic_isr_register(
		  TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
		  TIMER_0_IRQ,
		  timer_isr,
		  0,
		  0);

  IOWR_ALTERA_AVALON_TIMER_CONTROL(
		  TIMER_0_BASE,
				  ALTERA_AVALON_TIMER_CONTROL_ITO_MSK
				  | ALTERA_AVALON_TIMER_CONTROL_CONT_MSK);



  //Recast the start point to match the
  //alt_irq_register() function prototypo
  void* start_ptr = (void*)&start;

  //Enable a single interrupt input by writing a one to the corresponding interruptmask bit locations
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_BUTTON_START_BASE,0x1);

  //Reset the edge capture register
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_BUTTON_START_BASE,0);

  //Register the interrupt handler in the system
  //The ID and PIO_IRQ number is available from the system.h file.
  alt_ic_isr_register(PIO_BUTTON_START_IRQ_INTERRUPT_CONTROLLER_ID,
		  PIO_BUTTON_START_IRQ, start_interrupt, start_ptr, 0x0);




  while (1);
}
