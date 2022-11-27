
#include "fw_gpio.h"
#include "fw_timers.h"
#include "fw_uart.h"

volatile uint32_t ticks = 0;
volatile bool send_message = false;
void blink_led()
{
	if (ticks % MS_TO_HW_TICKS(200, HW_TIMER0_PERIOD_MS) == 0)
	{ 
		fw_gpio_set(USER_LEDA, FW_GPIO_TOGGLE);	
	}
	
	if (ticks % MS_TO_HW_TICKS(500, HW_TIMER0_PERIOD_MS) == 0)
	{
		send_message = true;
	}

	ticks++;
	fwprintf("i");
}

/**
 * main.c
 */
int main(void)
{
	PCInit(115200);
	fw_gpio_init();
	fw_timer_init(HW_TIMER_COMPARE0, blink_led);
	fw_timer_counter(HW_TIMER_COUNTER0, true);

	while(1)
	{
		if (send_message)
		{
			fwprintf("e", ticks);
			send_message = false;
		}
	}


	return 0;
}

