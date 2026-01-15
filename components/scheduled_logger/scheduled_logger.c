#include "scheduled_logger.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "esp_log.h"

static const char* TAG  = "scheduled_logger";
static int logger_index = 0;

struct scheduled_logger_t {
    int index;
    char message[128];
    int interval_ms;
    TaskHandle_t task_handle; 
};

static void scheduled_logger_task(void *param) {
    scheduled_logger_handle_t logger = (scheduled_logger_handle_t)param;
    while (true) {
        ESP_LOGI(TAG, "Logger %d: %s", logger->index, logger->message);
        vTaskDelay(logger->interval_ms / portTICK_PERIOD_MS);
    }
}

scheduled_logger_handle_t scheduled_logger_create(const char *message, int interval_ms) {
    scheduled_logger_handle_t logger = malloc(sizeof(struct scheduled_logger_t));
    logger->index = logger_index++;
    logger->task_handle = NULL;
    scheduled_logger_set_message(logger, message);
    scheduled_logger_set_interval(logger, interval_ms);
    return logger;
}

void scheduled_logger_set_message(scheduled_logger_handle_t logger, const char *message) {
    strncpy(logger->message, message, sizeof(logger->message) - 1);
    logger->message[sizeof(logger->message) - 1] = '\0';
}

void scheduled_logger_set_interval(scheduled_logger_handle_t logger, int interval_ms) {
    logger->interval_ms = interval_ms;
}

esp_err_t scheduled_logger_start(scheduled_logger_handle_t logger) {
    if (logger->task_handle != NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    xTaskCreate(scheduled_logger_task, "scheduled_logger_task", 2048, (void *)logger, 5, &logger->task_handle);
    return ESP_OK;
}

void scheduled_logger_stop(scheduled_logger_handle_t logger) {
    vTaskDelete(logger->task_handle);
    logger->task_handle = NULL;
}

void scheduled_logger_destroy(scheduled_logger_handle_t logger) {
    free(logger);
}

