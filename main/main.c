#include <stdio.h>
#include <string.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_sntp.h"
#include "esp_system.h"
#include "esp_sleep.h"
#include "esp_attr.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "esp_netif.h"
#include "sdkconfig.h"

// Configuration for Wi-Fi credentials and blink delays at menuConfig

#define LED_GPIO GPIO_NUM_2
#define TAG "MAIN"
#define TEST_MODE 0  // Set to 1 for test mode

RTC_DATA_ATTR static int wake_count = 0;

static void connect_wifi() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));

    wifi_config_t sta_config = {
        .sta = {
            .ssid = CONFIG_WIFI_SSID,
            .password = CONFIG_WIFI_PASS,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        }
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "Connecting to Wi-Fi...");

    ESP_ERROR_CHECK(esp_wifi_connect());

    vTaskDelay(pdMS_TO_TICKS(5000));
}

static void obtain_time() {
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_init();

    time_t now = 0;
    struct tm timeinfo = { 0 };

    while (timeinfo.tm_year < (2020 - 1900)) {
        ESP_LOGI(TAG, "Waiting for time...");
        time(&now);
        localtime_r(&now, &timeinfo);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(TAG, "Time obtained.");
}

static void blink_led(int times, int delay_ms) {
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    for (int i = 0; i < times; ++i) {
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);
    }
}

void app_main() {
    ESP_ERROR_CHECK(nvs_flash_init());

    // Set Singapore timezone (UTC+8)
    setenv("TZ", "SGT-8", 1);
    tzset();

#if TEST_MODE
    // Simulate 12:00 noon for testing
    struct tm test_time = {
        .tm_year = 2025 - 1900,
        .tm_mon  = 5 - 1,
        .tm_mday = 29,
        .tm_hour = 12,
        .tm_min  = 0,
        .tm_sec  = 0
    };
    time_t fake_time = mktime(&test_time);
    struct timeval now_val = { .tv_sec = fake_time };
    settimeofday(&now_val, NULL);
    ESP_LOGI(TAG, "Test mode: Simulated time set to 12:00");
#endif

    wake_count++;
    ESP_LOGI(TAG, "Wake count: %d", wake_count);

    if (wake_count % 24 == 0 || !esp_sleep_get_wakeup_cause()) {
        connect_wifi();
        obtain_time();
        esp_wifi_stop();
    }

    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    int minute = timeinfo.tm_min;
    int hour = timeinfo.tm_hour;

    if (minute % 15 == 0) {
        blink_led(1, 300);  // Quarter-hour chime
        // printf(">>>>>>>>>>> Chime at %02d:%02d, wake_count: %02d  <<<<<<<<<<\n", hour, minute, wake_count);
    }

    if (minute == 0) {
        if (hour == 12) {
            blink_led(12, CONFIG_NOON_BLINK_DELAY);  // Noon chime - slower, more distine
        } else {
            blink_led(hour % 24 == 0 ? 24 : hour % 24, CONFIG_HOURLY_BLINK_DELAY);  // Hourly blink - faster
        }
    }

#if !TEST_MODE
    ESP_LOGI(TAG, "Sleeping...");
    esp_sleep_enable_timer_wakeup(60 * 1000000ULL);
    esp_deep_sleep_start();
#endif
}