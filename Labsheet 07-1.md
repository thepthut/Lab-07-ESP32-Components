# Lab 07 ESP32 Components - การใช้งานและสร้าง Component ด้วยตนเอง

## วัตถุประสงค์การทดลอง
1. เรียนรู้การใช้งาน component ที่มีอยู่แล้ว (local components)
2. เรียนรู้การใช้งาน managed components จาก URL
3. เรียนรู้การสร้าง component ใหม่สำหรับ ESP32
4. เข้าใจโครงสร้างและการจัดการ component ใน ESP-IDF

## อุปกรณ์และเครื่องมือ
- Docker และ Docker Compose
- ESP-IDF Development Environment
- VS Code หรือ Text Editor
- QEMU Emulator (สำหรับการทดสอบ)

## การเตรียมความพร้อม

### ขั้นตอนที่ 1: สร้าง Docker Environment
เตรียมความพร้อมโดยการสร้างไฟล์ `docker-compose.yml`
```yml
services:
  esp32-dev:
    image: espressif/idf:latest
    container_name: esp32-lab7
    volumes:
      - .:/project
    working_dir: /project
    tty: true
    stdin_open: true
    environment:
      - IDF_PATH=/opt/esp/idf
    command: /bin/bash
    networks:
      - esp32-network

networks:
  esp32-network:
    driver: bridge
```

### ขั้นตอนที่ 2: เข้าใช้งาน Docker Container
```bash
# เริ่มต้น Docker Container
docker-compose up -d

# ตรวจสอบ Docker Container

docker-compose ps -a

# ดูว่ามี NAME เป็น esp32-lab7 หรือไม่

# เข้าใช้งาน Container
docker exec -it esp32-lab7 bash
```

---

## Lab 7.1 การใช้ Local Component (การใช้ component ที่มีอยู่บน harddisk)

### ขั้นตอนที่ 1: เตรียม Component Files
ก่อนทดลองให้พิจารณาโครงสร้างของไฟล์ ซึ่งเมื่อทดลองเสร็จแล้วจะมีโครงสร้างโฟลเดอร์และไฟล์ต่างๆ ดังนี้

```bash
Lab7-ESP32-Components/            
├── docker-compose.yml                  # ขั้นการเตรียม 
└── components                          # การทดลอง 7.1
│   └── Sensors/
│   │   ├── CMakeLists.txt        
│   │   ├── sensor.h    
│   │   └── sensor.c    
│   └── Display/
│       ├── CMakeLists.txt        
│       ├── display.h    
│       └── display.c    
└── lab7-1_Managed_Local_Component/    # Lab 7.1           
│   ├── CMakeLists.txt            
│   ├── main/                     
│   │   ├── CMakeLists.txt        
│   │   └── lab7-1.c    
│   ├── build/                    
│   └── README.md                      # <-- ตอบคำถามไว้ในไฟล์นี้ 
└── lab7-2_Managed_url_Component/      # การทดลอง 7.2       
│   ├── CMakeLists.txt            
│   ├── main/                     
│   │   ├── CMakeLists.txt        
│   │   └── lab7-2.c    
│   ├── build/                         # <-- ตอบคำถามไว้ในไฟล์นี้
│   └── README.md                 
└── lab7-3_esp32_Component/            # การทดลอง 7.3
    ├── CMakeLists.txt            
    └── components 
    │   └── Sensors/
    │   │   ├── CMakeLists.txt        
    │   │   ├── sensor.c    
    │   │   └── sensor.h    
    │   └── Display/
    │       ├── CMakeLists.txt        
    │       ├── display.c    
    │       └── display.h    
    ├── main/                     
    │   ├── CMakeLists.txt        
    │   └── lab7-3.c    
    ├── build/                    
    └── README.md                      # <-- ตอบคำถามไว้ในไฟล์นี้
```

### ขั้นตอนที่ 2: สร้างไฟล์ Component

#### สร้างไฟล์ `components/Sensors/CMakeLists.txt`
```cmake
idf_component_register(SRCS "sensor.c"
                       INCLUDE_DIRS "."
                       REQUIRES "log")
```

#### สร้างไฟล์ `components/Sensors/sensor.h`

```c
#ifndef SENSOR_H
#define SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize sensor module
 */
void sensor_init(void);

/**
 * @brief Read data from sensors
 */
void sensor_read_data(void);

/**
 * @brief Check sensor status
 */
void sensor_check_status(void);

#ifdef __cplusplus
}
#endif

#endif // SENSOR_H
```

#### สร้างไฟล์ `components/Sensors/sensor.c`
```c
#include <stdio.h>
#include <stdlib.h>
#include "esp_system.h"
#include "esp_random.h"
#include "esp_log.h"
#include "sensor.h"

static const char *TAG = "SENSOR";

void sensor_init(void)
{
    ESP_LOGI(TAG, "🔧 Sensor initialized from file: %s, line: %d", __FILE__, __LINE__);
    ESP_LOGI(TAG, "📡 Sensor module ready for operation");
}

void sensor_read_data(void)
{
    ESP_LOGI(TAG, "📊 Reading sensor data from file: %s, line: %d", __FILE__, __LINE__);
    
    // จำลองการอ่านข้อมูลจาก sensor
    float temperature = 25.5 + (float)(esp_random() % 100) / 10.0f;
    float humidity = 60.0 + (float)(esp_random() % 400) / 10.0f;
    
    ESP_LOGI(TAG, "🌡️  Temperature: %.1f°C", temperature);
    ESP_LOGI(TAG, "💧 Humidity: %.1f%%", humidity);
}

void sensor_check_status(void)
{
    ESP_LOGI(TAG, "✅ Sensor status check from file: %s, line: %d", __FILE__, __LINE__);
    ESP_LOGI(TAG, "📈 All sensors operating normally");
}
```

### ขั้นตอนที่ 3: สร้าง Project Lab 7-1 (Local Component)

#### สร้างไฟล์ `lab7-1_Managed_Local_Component/CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(lab7-1)
```

#### สร้างไฟล์ `lab7-1_Managed_Local_Component/main/CMakeLists.txt`
```cmake
idf_component_register(SRCS "lab7-1.c"
                       INCLUDE_DIRS ".")
```

#### สร้างไฟล์ `lab7-1_Managed_Local_Component/main/lab7-1.c`
```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sensor.h"

static const char *TAG = "LAB7-1";

void app_main(void)
{
    ESP_LOGI(TAG, "🚀 Lab 7-1: Local Component Demo Started");
    
    // เรียกใช้ฟังก์ชันจาก local component
    sensor_init();
    
    while(1) {
        sensor_read_data();
        sensor_check_status();
        
        ESP_LOGI(TAG, "----------------------------");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
```

#### การ Build และ Flash Lab 7-1
```bash
# เข้าไปใน project directory
cd lab7-1_Managed_Local_Component

#export environment เพื่อให้สามารถเรียกใช้ idf tools ได้
. $IDF_PATH/export.sh

# กำหนด target ESP32
idf.py set-target esp32

# Build project
idf.py build

```

### ขั้นตอนที่ 4: ระบุเส้นทางไปยังโฟลเดอร์ของ Components

ในการ build จะพบ error เนื่องจากระบบ build ยังไม่รู้จัก components ให้แก้ไขดังต่อไปนี้

ในไฟล์ CMakeLists.txt ของ project ให้แก้ไขเป็นดังนี้

```cmake
cmake_minimum_required(VERSION 3.16)

# Add external components directory
set(EXTRA_COMPONENT_DIRS "../components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(lab7-1)
```

การใส่ `EXTRA_COMPONENT_DIRS` ในไฟล์ `CMakeLists.txt` หลักของโปรเจคจะทำให้ระบบ build ค้นหา components จากโฟลเดอร์ที่ระบุโดยอัตโนมัติ

**สำคัญ** ต้องใส่ก่อน `include($ENV{IDF_PATH}/tools/cmake/project.cmake)`


#### สร้างไฟล์ `lab7-1_Managed_Local_Component/README.md`
```markdown
# Lab 7-1: Local Component Demo

## คำอธิบาย
การทดลองนี้แสดงการใช้งาน component ที่มีอยู่ในโฟลเดอร์ `components/Sensors/` ของ project


## สรุปคำสั่งที่ใช้ และผลลัพธ์ที่ได้

<เขียนตอบในนี้>

```

## โจทย์ท้าทาย

### 1. สร้าง  component ชื่อ `Display` โดย นำไฟล์ `display.c` และ `display.h` จากใบงานที่ 6 มาใช้ 

สิ่งที่ต้องมีใน display component
1. ไฟล์ `CMakeLists.txt` 
2. ไฟล์ `display.h`
3. ไฟล์ `display.c`


### 2. นำโค้ดจาก main.c ในใบงานที่ 6 มาใช้ แล้ว build พร้อมทดสอบ


ใส่ผลลัพธ์ทั้งหมดในไฟล์ README.md ของใบงานนี้

---

## Lab 7.2 การใช้ Managed Component จาก URL

### ขั้นตอนที่ 1: สร้าง Project Lab 7-2


#### 1.1 สร้างโฟลเดอร์  `lab7-2_Managed_url_Component`

#### 1.2 สร้างไฟล์ `lab7-2_Managed_url_Component/CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(lab7-2)
```

#### 1.3 สร้างไฟล์ `lab7-2_Managed_url_Component/main/CMakeLists.txt`
```cmake
idf_component_register(SRCS "lab7-2.c"
                       INCLUDE_DIRS ".")
```

#### 1.4 สร้างไฟล์ `lab7-2_Managed_url_Component/main/idf_component.yml`
```yaml
dependencies:
  lab7_components:
    git: https://github.com/APPLICATIONS-OF-MICROCONTROLLERS/Lab7_Components.git
```

#### 1.5 สร้างไฟล์ `lab7-2_Managed_url_Component/main/lab7-2.c`
```c
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
```

#### 1.6 การ Build และ Flash Lab 7-2
```bash
# เข้าไปใน project directory
cd lab7-2_Managed_url_Component

#export environment เพื่อให้สามารถเรียกใช้ idf tools ได้
. $IDF_PATH/export.sh

# กำหนด target ESP32
idf.py set-target esp32

# Build project (จะดาวน์โหลด lab7_components จาก GitHub อัตโนมัติ)
idf.py build

# รัน QEMU (สำหรับการทดสอบ)
idf.py qemu monitor
```

#### 1.7 สร้างไฟล์ `lab7-2_Managed_url_Component/README.md`
```markdown
# Lab 7-2: Managed Component from GitHub URL Demo

## คำอธิบาย
การทดลองนี้แสดงการใช้งาน managed component จาก GitHub Repository
ใช้ `Sensors` component จาก https://github.com/APPLICATIONS-OF-MICROCONTROLLERS/Lab7_Components

## ผลลัพธ์ที่คาดหวัง
- แสดงข้อความการเริ่มต้น sensor จาก GitHub component
- แสดงข้อมูล temperature และ humidity ทุก 4 วินาที
- แสดงสถานะการทำงานของ sensor
- แสดงแหล่งที่มาของ component (GitHub Repository)

## ความแตกต่างจาก Lab 7-1
- Lab 7-1: ใช้ local component (ในเครื่อง)
- Lab 7-2: ใช้ managed component จาก GitHub URL

## การใช้งาน
1. เข้าไปในโฟลเดอร์ lab7-2_Managed_url_Component
2. รันคำสั่ง `idf.py build` (จะดาวน์โหลด component จาก GitHub อัตโนมัติ)
3. ทดสอบด้วย QEMU

---

## โจทย์ท้าทาย

### 1. สร้าง  component ชื่อ `Display` โดย นำไฟล์ `display.c` และ `display.h` จากใบงานที่ 6 มาใช้ 

สิ่งที่ต้องมีใน display component
1. ไฟล์ `CMakeLists.txt` 
2. ไฟล์ `display.h`
3. ไฟล์ `display.c`


### 2. นำโค้ดจาก main.c ในใบงานที่ 6 มาใช้ แล้ว build พร้อมทดสอบ

ให้ผลลักษณะเดียวกับ component แบบ local หรือไม่

ใส่ผลลัพธ์ทั้งหมดในไฟล์ README.md ของใบงานนี้



## Lab 7.3 การสร้าง ESP32 Component ใหม่

### ขั้นตอนที่ 1: สร้าง Component ภายใน Project

#### สร้างไฟล์ `lab7-3_esp32_Component/CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(lab7-3)
```

#### สร้างไฟล์ `lab7-3_esp32_Component/sensor/CMakeLists.txt`
```cmake
idf_component_register(SRCS "sensor.c"
                       INCLUDE_DIRS "."
                       REQUIRES "log" "driver")
```

#### สร้างไฟล์ `lab7-3_esp32_Component/sensor/sensor.h`
```c
#ifndef SENSOR_H
#define SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize sensor module with GPIO
 */
void sensor_init(void);

/**
 * @brief Read temperature data
 */
float sensor_read_temperature(void);

/**
 * @brief Read humidity data
 */
float sensor_read_humidity(void);

/**
 * @brief Read all sensor data and display
 */
void sensor_read_all_data(void);

#ifdef __cplusplus
}
#endif

#endif // SENSOR_H
```

#### สร้างไฟล์ `lab7-3_esp32_Component/sensor/sensor.c`
```c
#include <stdio.h>
#include <stdlib.h>
#include "esp_system.h"
#include "esp_random.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "sensor.h"

static const char *TAG = "ENHANCED_SENSOR";

void sensor_init(void)
{
    ESP_LOGI(TAG, "🔧 Enhanced Sensor Component initialized");
    ESP_LOGI(TAG, "📍 File: %s, Line: %d", __FILE__, __LINE__);
    
    // กำหนด GPIO สำหรับ LED indicator
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_NUM_2),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = 0,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
    
    ESP_LOGI(TAG, "✅ GPIO LED configured on pin 2");
}

float sensor_read_temperature(void)
{
    float temperature = 20.0 + (float)(esp_random() % 200) / 10.0f;
    ESP_LOGI(TAG, "🌡️  Temperature: %.2f°C", temperature);
    return temperature;
}

float sensor_read_humidity(void)
{
    float humidity = 40.0 + (float)(esp_random() % 400) / 10.0f;
    ESP_LOGI(TAG, "💧 Humidity: %.2f%%", humidity);
    return humidity;
}

void sensor_read_all_data(void)
{
    ESP_LOGI(TAG, "📊 Reading all sensor data...");
    
    // เปิด LED เมื่ออ่านข้อมูล
    gpio_set_level(GPIO_NUM_2, 1);
    
    float temp = sensor_read_temperature();
    float hum = sensor_read_humidity();
    
    // คำนวณ Heat Index
    float heat_index = temp + 0.5 * hum;
    ESP_LOGI(TAG, "🔥 Heat Index: %.2f", heat_index);
    
    // แสดงสถานะตามค่า Heat Index
    if (heat_index < 80) {
        ESP_LOGI(TAG, "✅ Comfortable conditions");
    } else if (heat_index < 90) {
        ESP_LOGI(TAG, "⚠️  Caution: Possible fatigue");
    } else {
        ESP_LOGI(TAG, "🚨 Warning: High heat stress");
    }
    
    // ปิด LED หลังอ่านข้อมูลเสร็จ
    gpio_set_level(GPIO_NUM_2, 0);
}
```

#### สร้างไฟล์ `lab7-3_esp32_Component/main/CMakeLists.txt`
```cmake
idf_component_register(SRCS "lab7-3.c"
                       INCLUDE_DIRS ".")
```

#### สร้างไฟล์ `lab7-3_esp32_Component/main/lab7-3.c`
```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sensor.h"

static const char *TAG = "LAB7-3";

void app_main(void)
{
    ESP_LOGI(TAG, "🚀 Lab 7-3: Custom ESP32 Component Demo Started");
    
    // เริ่มต้น enhanced sensor component
    sensor_init();
    
    int reading_count = 0;
    
    while(1) {
        reading_count++;
        ESP_LOGI(TAG, "📋 Reading #%d", reading_count);
        
        // อ่านข้อมูลจาก enhanced sensor
        sensor_read_all_data();
        
        ESP_LOGI(TAG, "==========================================");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
```

#### การ Build และ Flash Lab 7-3
```bash
# เข้าไปใน project directory
cd lab7-3_esp32_Component

# กำหนด target ESP32
idf.py set-target esp32

# Build project
idf.py build

# Flash to ESP32 (หากมี ESP32 ต่ออยู่)
# idf.py -p /dev/ttyUSB0 flash monitor
```

#### สร้างไฟล์ `lab7-3_esp32_Component/README.md`
```markdown
# Lab 7-3: Custom ESP32 Component Demo

## คำอธิบาย
การทดลองนี้แสดงการสร้าง component ใหม่ภายใน project
มีฟีเจอร์ advanced sensor อ่านค่า temperature, humidity และคำนวณ heat index

## ผลลัพธ์ที่คาดหวัง
- แสดงข้อมูล temperature และ humidity
- คำนวณและแสดง heat index
- แสดงสถานะความปลอดภัย
- LED บน GPIO 2 กะพริบเมื่ออ่านข้อมูล

## อุปกรณ์เพิ่มเติม
- LED ต่อกับ GPIO 2 (Built-in LED ของ ESP32)
```

---

## ผลการทดลองที่คาดหวัง

### Lab 7-1: Local Component
```
I (294) LAB7-1: 🚀 Lab 7-1: Local Component Demo Started
I (304) SENSOR: 🔧 Sensor initialized from file: /project/components/Sensors/sensor.c, line: 12
I (314) SENSOR: 📡 Sensor module ready for operation
I (324) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (334) SENSOR: 🌡️  Temperature: 32.4°C
I (334) SENSOR: 💧 Humidity: 67.8%
I (344) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 27
I (354) SENSOR: 📈 All sensors operating normally
```

### Lab 7-2: Managed Component from GitHub URL
```
I (294) LAB7-2: 🚀 Lab 7-2: Managed Component from GitHub URL Demo Started
I (304) LAB7-2: 📥 Using Sensors component from: https://github.com/APPLICATIONS-OF-MICROCONTROLLERS/Lab7_Components
I (314) SENSOR: 🔧 Sensor initialized from file: /managed_components/lab7_components/components/Sensors/sensor.c, line: 11
I (324) SENSOR: 📡 Sensor module ready for operation
I (334) LAB7-2: 📋 Reading #1 from GitHub Component
I (344) SENSOR: 📊 Reading sensor data from file: /managed_components/lab7_components/components/Sensors/sensor.c, line: 17
I (354) SENSOR: 🌡️  Temperature: 28.7°C
I (364) SENSOR: 💧 Humidity: 72.3%
I (374) SENSOR: ✅ Sensor status check from file: /managed_components/lab7_components/components/Sensors/sensor.c, line: 26
I (384) SENSOR: 📈 All sensors operating normally
I (394) LAB7-2: � Component Source: GitHub Repository
I (404) LAB7-2: ==========================================
```

### Lab 7-3: Custom ESP32 Component
```
I (294) LAB7-3: 🚀 Lab 7-3: Custom ESP32 Component Demo Started
I (304) ENHANCED_SENSOR: 🔧 Enhanced Sensor Component initialized
I (314) ENHANCED_SENSOR: 📍 File: /project/sensor/sensor.c, Line: 12
I (324) ENHANCED_SENSOR: ✅ GPIO LED configured on pin 2
I (334) LAB7-3: 📋 Reading #1
I (334) ENHANCED_SENSOR: 📊 Reading all sensor data...
I (344) ENHANCED_SENSOR: 🌡️  Temperature: 28.45°C
I (354) ENHANCED_SENSOR: 💧 Humidity: 72.30%
I (364) ENHANCED_SENSOR: 🔥 Heat Index: 64.60
I (364) ENHANCED_SENSOR: ✅ Comfortable conditions
```

---

## ขั้นตอนการดำเนินการทดลอง

### 1. การเตรียมความพร้อม
```bash
# สร้างโครงสร้างโฟลเดอร์
mkdir -p Lab7-ESP32-Components
cd Lab7-ESP32-Components

# สร้าง docker-compose.yml
# สร้างโฟลเดอร์ components และโฟลเดอร์ lab ต่างๆ
```

### 2. การรัน Docker Container
```bash
# เริ่มต้น container
docker-compose up -d

# เข้าใช้งาน container
docker exec -it esp32-lab7 bash
```

### 3. การทดสอบแต่ละ Lab
```bash
# ทดสอบ Lab 7-1
cd lab7-1_Managed_Local_Component
idf.py set-target esp32
idf.py build

# ทดสอบ Lab 7-2  
cd ../lab7-2_Managed_url_Component
idf.py set-target esp32
idf.py build

# ทดสอบ Lab 7-3
cd ../lab7-3_esp32_Component
idf.py set-target esp32
idf.py build
```

---

## คำถามท้ายการทดลอง

1. **อธิบายความแตกต่างระหว่าง Local Component และ Managed Component**
   - Local Component: component ที่เก็บอยู่ในโฟลเดอร์ project ในเครื่อง
   - Managed Component: component ที่ดาวน์โหลดจาก ESP Component Registry

2. **ข้อดีและข้อเสียของการใช้ Managed Component จาก URL คืออะไร?**
   - ข้อดี: อัพเดทอัตโนมัติ, ได้รับการดูแลจากผู้พัฒนา, มี documentation ครบถ้วน
   - ข้อเสีย: ต้องใช้ internet ในการดาวน์โหลด, อาจมีปัญหา dependency

3. **เมื่อไหร่ควรสร้าง Component ใหม่แทนการใช้ Component ที่มีอยู่?**
   - เมื่อต้องการฟังก์ชันเฉพาะที่ไม่มีใน component ที่มีอยู่
   - เมื่อต้องการปรับแต่งให้เหมาะกับงานเฉพาะ
   - เมื่อต้องการประสิทธิภาพสูงหรือการใช้หน่วยความจำที่เหมาะสม

4. **อธิบายโครงสร้างไฟล์ที่จำเป็นสำหรับการสร้าง ESP32 Component**
   - `CMakeLists.txt`: กำหนดการ compile และ dependency
   - `.h` files: header files สำหรับ function declarations
   - `.c` files: source code ที่ implement ฟังก์ชันต่างๆ

---

## Lab 7.4 (เพิ่มเติม): การใช้ Component Registry Manager

### การค้นหา Component
```bash
# ค้นหา component ที่เกี่ยวกับ sensor
idf.py create-project-from-example "espressif/esp_insights:diagnostics_smoke_test"

# ดู component ที่ติดตั้งแล้ว
idf.py dependency-tree
```

### การจัดการ Dependencies
```bash
# เพิ่ม component ใหม่
idf.py add-dependency "espressif/led_strip^2.0.0"

# อัพเดท component
idf.py update-dependencies
```

---

## สรุปผลการทดลอง

การทดลองนี้ช่วยให้เข้าใจการจัดการ Component ใน ESP-IDF ในรูปแบบต่างๆ:

1. **Local Component** - การใช้ component ที่มีอยู่ในเครื่อง ช่วยให้สามารถนำโค้ดที่เขียนไว้แล้วมาใช้ซ้ำได้

2. **Managed Component** - การใช้ component จากแหล่งภายนอก ช่วยลดเวลาการพัฒนาและได้รับการอัพเดทอย่างสม่ำเสมอ

3. **Custom Component** - การสร้าง component ใหม่ ช่วยให้สามารถพัฒนาฟังก์ชันเฉพาะตามความต้องการได้

ทักษะเหล่านี้จะช่วยในการพัฒนาโปรแกรม ESP32 ที่มีความซับซ้อน มีการจัดระเบียบที่ดี และง่ายต่อการบำรุงรักษา การเข้าใจการใช้งาน component จะทำให้การพัฒนา embedded system มีประสิทธิภาพมากขึ้น

---

## ข้อเสนอแนะเพิ่มเติม

1. **Best Practices**
   - ตั้งชื่อ component ให้สื่อความหมาย
   - เขียน documentation ให้ครบถ้วน
   - ใช้ version control สำหรับ component ที่พัฒนาเอง

2. **การแก้ไขปัญหา**
   - ตรวจสอบ dependency ใน CMakeLists.txt
   - ตรวจสอบ path ของ include files
   - ใช้ `idf.py clean` เมื่อมีปัญหาการ build

3. **การพัฒนาต่อยอด**
   - ศึกษา ESP Component Registry เพิ่มเติม
   - เรียนรู้การสร้าง component แบบ professional
   - ฝึกการใช้ Git สำหรับจัดการ component