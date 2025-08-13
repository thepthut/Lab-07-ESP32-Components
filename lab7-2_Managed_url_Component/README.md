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
~~~
I (22199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (22199) SENSOR: 🌡️  Temperature: 30.1 °C
I (22199) SENSOR: 💧 Humidity: 86.0%
I (22199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (22199) SENSOR: 📈 All sensors operating normally
I (22199) LAB7-1: ----------------------------
I (25199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (25199) SENSOR: 🌡️  Temperature: 28.9°C
I (25199) SENSOR: 💧 Humidity: 69.9%
I (25199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (25199) SENSOR: 📈 All sensors operating normally
I (25199) LAB7-1: ----------------------------
I (28199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (28199) SENSOR: 🌡️  Temperature: 31.4°C
I (28199) SENSOR: 💧 Humidity: 60.1%
I (28199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (28199) SENSOR: 📈 All sensors operating normally
I (28199) LAB7-1: ----------------------------
I (31199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (31199) SENSOR: 🌡️  Temperature: 34.6°C
I (31199) SENSOR: 💧 Humidity: 89.7%
I (31199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (31199) SENSOR: 📈 All sensors operating normally
I (31199) LAB7-1: ----------------------------
I (34199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (34199) SENSOR: 🌡️  Temperature: 26.7°C
I (34199) SENSOR: 💧 Humidity: 94.3%
I (34199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (34199) SENSOR: 📈 All sensors operating normally
I (34199) LAB7-1: ----------------------------
I (37199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (37199) SENSOR: 🌡 ️  Temperature: 25.6°C
I (37199) SENSOR: 💧 Humidity: 62.4%
I (37199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (37199) SENSOR: 📈 All sensors operating normally
I (37199) LAB7-1: ----------------------------
I (40199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (40199) SENSOR: 🌡️  Tempe rature: 26.3°C
I (40199) SENSOR: 💧 Humidity: 71.9%
I (40199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (40199) SENSOR: 📈 All sensors operating normally
I (40199) LAB7-1: ----------------------------
I (43199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (43199) SENSOR: 🌡️  Temperature: 25.5° C
I (43199) SENSOR: 💧 Humidity: 97.8%
I (43199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (43199) SENSOR: 📈 All sensors operating normally
I (43199) LAB7-1: ----------------------------
I (46199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (46199) SENSOR: 🌡️  Temperature: 33.6°C
I (46199) SENSOR: 💧 Humidity: 80.7%
I (46199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (46199) SENSOR: 📈 All sensors operating normally
I (46199) LAB7-1: ----------------------------
I (49199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (49199) SENSOR: 🌡️  Temperature: 34.5° C
I (49199) SENSOR: 💧 Humidity: 98.3%
I (49199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (49199) SENSOR: 📈 All sensors operating normally
I (49199) LAB7-1: ----------------------------
I (52199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (52199) SENSOR: 🌡️  Temperature: 28.3°C
I (52199) SENSOR: 💧 Humidity: 63.1%
I (52199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (52199) SENSOR: 📈 All sensors operating normally
I (52199) LAB7-1: ----------------------------
I (55199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (55199) SENSOR: 🌡️  Tempera ture: 31.0°C
I (55199) SENSOR: 💧 Humidity: 60.4%
I (55199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (55199) SENSOR: 📈 All sensors operating normally
I (55199) LAB7-1: ----------------------------
I (58199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (58199) SENSOR: 🌡️  Temperature: 33.5°C
I (58199) SENSOR: 💧 Humidity: 97.6%
I (58199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (58199) SENSOR: 📈 All sensors operating normally
I (58199) LAB7-1: ----------------------------
I (61199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (61199) SENSOR: 🌡️  Temperature: 32.5°C
I (61199) SENSOR: 💧 Humidity: 80.8%
I (61199) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (61199) SENSOR: 📈 All sensors operating normally
I (61199) LAB7-1: ----------------------------
I (64199) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (64199) SENSOR: 🌡️  Temperature: 28.4°C
I (64199) SE
~~~