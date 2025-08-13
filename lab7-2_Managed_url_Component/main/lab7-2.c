#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sensor.h"

static const char *TAG = "LAB7-2";

void app_main(void)
{
    ESP_LOGI(TAG, "🚀 Lab 7-2: Managed Component from GitHub URL Demo Started");
    ESP_LOGI(TAG, "📥 Using Sensors component from: https://github.com/APPLICATIONS-OF-MICROCONTROLLERS/Lab7_Components");
    
    // เรียกใช้ฟังก์ชันจาก managed component (GitHub)
    sensor_init();
    
    int reading_count = 0;
    
    while(1) {
        reading_count++;
        ESP_LOGI(TAG, "📋 Reading #%d from GitHub Component", reading_count);
        
        sensor_read_data();
        sensor_check_status();
        
        ESP_LOGI(TAG, "� Component Source: GitHub Repository");
        ESP_LOGI(TAG, "==========================================");
        vTaskDelay(pdMS_TO_TICKS(4000));
    }
}
