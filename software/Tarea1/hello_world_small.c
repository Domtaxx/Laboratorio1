#include "sys/alt_stdio.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

#include "system.h"

static unsigned segCount = 0;
static unsigned msCount = 0;
static unsigned minCount = 0;
static unsigned mode = 0;
static unsigned start = 0;
static unsigned stop = 0;
volatile int edge_capture;


static void startTimer()
{
	start = 1;
}

static void stopTimer()
{
	stop = 1;
}

static void count()
{
	msCount++;
		if (msCount >= 99)
		{
			msCount = 0;
			segCount++;
		}
		if (segCount >= 60)
		{
			segCount = 0;
			minCount++;
		}
		if(minCount >= 100)
		{
			minCount = 0;
		}
}

static void selectMode()
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

	if(start == 1 && stop == 0)
	{
		count();
		selectMode();
	}


	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
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

  alt_ic_isr_register(
		  PIO_BUTTON_START_IRQ_INTERRUPT_CONTROLLER_ID,
		  PIO_BUTTON_START_IRQ,
		  startTimer,
		  0,
		  0);
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_BUTTON_START_BASE, 0x1);

  //alt_ic_isr_register(
//		  PIO_BUTTON_STOP_IRQ_INTERRUPT_CONTROLLER_ID,
//		  PIO_BUTTON_STOP_IRQ,
//		  stopTimer,
//		  0,
//		  0);
 // IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_BUTTON_STOP_BASE, 0x1);




  while (1);
}
