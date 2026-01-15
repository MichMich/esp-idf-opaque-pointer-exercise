#pragma once
#include "esp_err.h"

typedef struct scheduled_logger_t *scheduled_logger_handle_t;

scheduled_logger_handle_t scheduled_logger_create(const char *message, int interval_ms);

void scheduled_logger_set_message(scheduled_logger_handle_t logger, const char *message);
void scheduled_logger_set_interval(scheduled_logger_handle_t logger, int interval_ms);

esp_err_t scheduled_logger_start(scheduled_logger_handle_t logger);
void scheduled_logger_stop(scheduled_logger_handle_t logger);
void scheduled_logger_destroy(scheduled_logger_handle_t logger);