#include "sys/alt_stdio.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

#include "system.h"

static unsigned counter = 0;
static unsigned segCount = 0;
static unsigned miliCount = 0;
static unsigned minCount = 0;
static unsigned displayCount = 0;
static unsigned mode = 0;


static void count()
{
	counter++;
		if (counter >= 1000)
		{
			counter = 0;
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
		miliCount = counter%100;
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_LEDS_0_BASE, miliCount);
	}
	else if(mode == 1)
	{
		//modo seg
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_MS_NUM_0_BASE, segCount);
	}
	else
	{
		//Modo min, seg, mili
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_MIN_NUM_0_BASE, minCount);
	}
}

static void timer_isr(void *context)
{
	(void) context;

	count();
	selectMode();

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

  while (1);
}
