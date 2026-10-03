/*
 * Week 2 - Firmware Development and Implementation
 * Application: Timer-Based LED Controller with UART Communication
 *
 * Target: Generic MCU / simulator
 * UART: 115200 baud, 8 data bits, no parity, 1 stop bit
 *
 * The low-level GPIO, timer and UART functions are kept as hardware
 * abstraction functions so they can be mapped to the selected MCU/SDK.
 */

#include <stdint.h>
#include <stdbool.h>

/* ---------------- Hardware Abstraction ---------------- */
void gpio_init(void);
void led_write(bool state);
void timer_init_1ms(void);
void uart_init_115200(void);
bool uart_read_char(char *c);
void uart_write(const char *text);

/* ---------------- Application State ---------------- */
volatile uint32_t system_tick_ms = 0;
volatile bool timer_event = false;

static bool led_state = false;
static bool auto_mode = true;

/*
 * Timer interrupt service routine.
 * Keep the ISR short and avoid lengthy application processing here.
 */
void timer_isr(void)
{
    system_tick_ms++;
    timer_event = true;
}

/* Send a diagnostic/status message through UART. */
static void send_status(void)
{
    uart_write("STATUS: firmware running\r\n");
}

/*
 * Process one received UART command.
 * 1 = LED ON
 * 0 = LED OFF
 * A = automatic blinking
 * S = status
 */
static void process_command(char c)
{
    if (c == '1') {
        led_state = true;
        auto_mode = false;
        led_write(led_state);
        uart_write("LED ON\r\n");
    }
    else if (c == '0') {
        led_state = false;
        auto_mode = false;
        led_write(led_state);
        uart_write("LED OFF\r\n");
    }
    else if (c == 'A' || c == 'a') {
        auto_mode = true;
        uart_write("AUTO MODE\r\n");
    }
    else if (c == 'S' || c == 's') {
        send_status();
    }
}

int main(void)
{
    /* Initialize all required peripherals. */
    gpio_init();
    timer_init_1ms();
    uart_init_115200();

    /* Safe startup state. */
    led_write(false);
    uart_write("Firmware started\r\n");

    while (1)
    {
        char rx;

        /* Check for a UART command without blocking the main loop. */
        if (uart_read_char(&rx)) {
            process_command(rx);
        }

        /*
         * Handle timer work in the main loop.
         * This keeps the interrupt routine short and predictable.
         */
        if (timer_event) {
            timer_event = false;

            /* Toggle the LED every 500 ms in automatic mode. */
            if (auto_mode && (system_tick_ms % 500U == 0U)) {
                led_state = !led_state;
                led_write(led_state);
            }
        }
    }
}
