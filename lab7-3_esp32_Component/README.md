# Lab 7-3: Custom ESP32 Components (Sensor + Display)

## คำอธิบาย
การทดลองนี้แสดงการสร้าง component ใหม่ด้วยคำสั่ง `idf.py create-component`
สร้าง 2 components:
1. **Sensor Component** - อ่านค่า temperature, humidity และคำนวณ heat index
2. **Display Component** - แสดงผลข้อมูลในรูปแบบตาราง

## โครงสร้างโฟลเดอร์หลังใช้ create-component
lab7-3_esp32_Component/
├── CMakeLists.txt
├── components/
│   ├── sensor/
│   │   ├── CMakeLists.txt
│   │   ├── include/
│   │   │   └── sensor.h
│   │   └── sensor.c
│   └── display/
│       ├── CMakeLists.txt
│       ├── include/
│       │   └── display.h
│       └── display.c
├── main/
│   ├── CMakeLists.txt
│   └── lab7-3.c
├── build/
└── README.md

~~~
I (23488) LAB7-3: 📋 Reading #2
I (23488) DISPLAY: 🧹 Display cleared
I (23488) DISPLAY: 
I (23488) ENHANCED_SENSOR: 🌡️  Temperature: 28.80°C
I (23488) ENHANCED_SENSOR: 💧 Humidity: 67.90%
I (23488) LAB7-3: 🔥 Heat Index: 62.75
I (23488) DISPLAY: ┌─────────────────────────────────┐
I (23488) DISPLAY: │        SENSOR DATA DISPLAY      │
I (23488) DISPLAY: ├─────────────────────────────────┤
I (23488) DISPLAY: │ 🌡️  Temperature:  28.80°C      │
I (23488) DISPLAY: │ 💧 Humidity:     67.90%       │
I (23488) DISPLAY: │ 🔥 Heat Index:   62.75        │
I (23488) DISPLAY: └─────────────────────────────────┘
I (23488) DISPLAY: ┌─────────────────────────────────┐
I (23488) DISPLAY: │         SYSTEM STATUS           │
I (23488) DISPLAY: ├─────────────────────────────────┤
I (23488) DISPLAY: │ Status: ✅ Comfortable         │
I (23488) DISPLAY: └─────────────────────────────────┘
I (23488) LAB7-3: ==========================================
I (29488) LAB7-3: 📋 Reading #3
I (29488) DISPLAY: 🧹 Display cleared
I (29488) DISPLAY: 
I (29488) ENHANCED_SENSOR: 🌡️  Temperature: 21.20°C
I (29488) ENHANCED_SENSOR: 💧 Humidity: 62.90%
I (29488) LAB7-3: 🔥 Heat Index: 52.65
I (29488) DISPLAY: ┌─────────────────────────────────┐
I (29488) DISPLAY: │        SENSOR DATA DISPLAY      │
I (29488) DISPLAY: ├─────────────────────────────────┤
I (29488) DISPLAY: │ 🌡️  Temperature:  21.20°C      │
I (29488) DISPLAY: │ 💧 Humidity:     62.90%       │
I (29488) DISPLAY: │ 🔥 Heat Index:   52.65        │
I (29488) DISPLAY: └─────────────────────────────────┘
I (29488) DISPLAY: ┌─────────────────────────────────┐
I (29498) DISPLAY: │         SYSTEM STATUS           │
I (29498) DISPLAY: ├─────────────────────────────────┤
I (29498) DISPLAY: │ Status: ✅ Comfortable         │
I (29498) DISPLAY: └─────────────────────────────────┘
I (29498) LAB7-3: ==========================================
~~~