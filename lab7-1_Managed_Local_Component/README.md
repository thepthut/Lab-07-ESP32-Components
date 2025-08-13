# Lab 7-1: Local Component Demo

## คำอธิบาย
การทดลองนี้แสดงการใช้งาน component ที่มีอยู่ในโฟลเดอร์ `components/Sensors/` ของ project


## สรุปคำสั่งที่ใช้ และผลลัพธ์ที่ได้
### คำสั่งที่ใช้
~~~
# เริ่มต้น Docker Container
docker-compose up -d

# ตรวจสอบ Docker Container

docker-compose ps -a

# ดูว่ามี NAME เป็น esp32-lab7 หรือไม่

# เข้าใช้งาน Container
docker exec -it esp32-lab7 bash

# เข้าไปใน project directory
cd lab7-1_Managed_Local_Component

#export environment เพื่อให้สามารถเรียกใช้ idf tools ได้
. $IDF_PATH/export.sh

# กำหนด target ESP32
idf.py set-target esp32

# Build project
idf.py build
~~~
### ผลลัพท์ที่ได้
~~~
I (138741) SENSOR: 📈 All sensors operating normally
I (138741) LAB7-1: ----------------------------
I (141741) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (141741) SENSOR: 🌡️  Temperature: 31.8°C
I (141741) SENSOR: 💧 Humidity: 92.5%
I (141741) SENSOR: ✅ Sensor status check from file: /project/compo
nents/Sensors/sensor.c, line: 30
I (141741) SENSOR: 📈 All sensors operating normally
I (141741) LAB7-1: ----------------------------



1. สร้าง component ชื่อ Display โดย นำไฟล์ display.c และ display.h จากใบงานที่ 6 มาใช้
สิ่งที่ต้องมีใน display component

ไฟล์ CMakeLists.txt
ไฟล์ display.h
ไฟล์ display.c
2. นำโค้ดจาก main.c ในใบงานที่ 6 มาใช้ แล้ว build พร้อมทดสอบ



I (14521) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (14521) SENSOR: 🌡️  Temperature: 30.7°C
I (14521) SENSOR: 💧 Humidity: 97.3%
I (14521) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (14521) SENSOR: 📈 All sensors operating normally
I (14521) LAB7-1: ----------------------------
I (17521) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (17521) SENSOR: 🌡 ️  Temperature: 33.8°C
I (17521) SENSOR: 💧 Humidity: 88.2%
I (17521) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (17521) SENSOR: 📈 All sensors operating normally
I (17521) LAB7-1: ----------------------------
I (20521) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (20521) SENSOR: 🌡️  Temperature: 29.4°C
I (20521) SENSOR: 💧 Humidity: 89.5%
I (20521) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (20521) SENSOR: 📈 All sensors operating normally
I (20521) LAB7-1: ----------------------------
I (23521) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (23521) SENSOR: 🌡️  Temperature: 33.6°C
I (23521) SENSOR: 💧 Humidity: 81.7%
I (23521) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (23521) SENSOR: 📈 All sensors operating normally
I (23521) LAB7-1: ----------------------------
I (26521) SENSOR: 📊 Reading sensor data from file: /project/components/Sensors/sensor.c, line: 18
I (26521) SENSOR: 🌡️  Temperature: 34.8°C
I (26521) SENSOR: 💧 Humidity: 97.4%
I (26521) SENSOR: ✅ Sensor status check from file: /project/components/Sensors/sensor.c, line: 30
I (26521) SENSOR: 📈 All sensors operating normally
I (26521) LAB7-1: ----------------------------
~~~
