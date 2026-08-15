/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <string.h>
#include "esp_log.h"
#include "esp_check.h"
#include "esp_board_manager_includes.h"
#include "gen_board_device_custom.h"
#include "led_strip.h"
#include "led_strip_rmt.h"
#include "led_strip_types.h"
#include "periph_rmt.h"

static const char *TAG = "ESP32_DEVKITC_SETUP_DEVICE";

/*
 * Status LED (Blue LED on GPIO 2)
 * Uses RMT peripheral for WS2812-style control if needed, but for simple GPIO LED
 * we just use the gpio_led custom device type defined in board_devices.yaml
 *
 * The BOOT button (GPIO 0) and EN button (reset) are also defined in board_devices.yaml
 * and handled by the gpio_button custom device type.
 *
 * No additional setup needed - all devices are configured via YAML.
 */

// This file is kept minimal since the ESP32-DevKitC uses only basic GPIO devices
// that are fully configured through board_devices.yaml and board_peripherals.yaml

// Empty constructor to ensure the board module is linked
__attribute__((constructor)) static void esp32_devkitc_board_init(void)
{
    ESP_LOGI(TAG, "ESP32-DevKitC board initialized");
}