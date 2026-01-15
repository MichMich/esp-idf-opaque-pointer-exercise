#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "scheduled_logger.h"   

void app_main(void)
{
    scheduled_logger_handle_t logger1 = scheduled_logger_create("Hello, Scheduled Logger every sec!", 1000);
    scheduled_logger_start(logger1);

    scheduled_logger_handle_t logger2 = scheduled_logger_create("Hello, Scheduled Logger every 300ms!", 300);
    scheduled_logger_start(logger2);

    // we can also change the message and interval later if needed
    scheduled_logger_set_message(logger2, "Updated Message for Logger 2 every 200ms");
    scheduled_logger_set_interval(logger2, 200);
}
