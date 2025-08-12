# Week 07: ESP32 Components - เนื้อหาประกอบการทดลอง
## การพัฒนาซอฟต์แวร์ด้วย Component-Based Architecture

**ระยะเวลาการบรรยาย:** 60 นาที  
**วัตถุประสงค์:** เข้าใจแนวคิด Component-Based Development ใน ESP-IDF และการประยุกต์ใช้ในการพัฒนา IoT Applications

---

## 📚 หัวข้อการบรรยาย

### ตอนที่ 1: Component-Based Architecture Fundamentals 
1. [แนวคิด Component-Based Development](#1-แนวคิด-component-based-development)
2. [ข้อดีของการใช้ Components](#2-ข้อดีของการใช้-components)
3. [ESP-IDF Component Model](#3-esp-idf-component-model)

### ตอนที่ 2: ESP-IDF Components Deep Dive 
4. [โครงสร้าง Component](#4-โครงสร้าง-component)
5. [CMake Build System](#5-cmake-build-system)
6. [Component Dependencies](#6-component-dependencies)

### ตอนที่ 3: Component Management Strategies 
7. [Local vs Managed Components](#7-local-vs-managed-components)
8. [Component Registry และ Version Control](#8-component-registry-และ-version-control)
9. [Team Development Workflow](#9-team-development-workflow)

### ตอนที่ 4: Best Practices และ Case Studies 
10. [Component Design Patterns](#10-component-design-patterns)
11. [Testing และ Documentation](#11-testing-และ-documentation)
12. [สรุปและเตรียมตัวสำหรับการทดลอง](#12-สรุปและเตรียมตัวสำหรับการทดลอง)

---

## 1. แนวคิด Component-Based Development

### 1.1 ความหมายของ Component

**Component** คือหน่วยซอฟต์แวร์ที่:
- มีความเป็นอิสระ (Independent)
- สามารถนำไปใช้ซ้ำได้ (Reusable)
- มี Interface ที่ชัดเจน
- ซ่อนรายละเอียดการทำงานภายใน (Encapsulation)

> เทียบได้กับการประกอบรถยนต์ ซึ่ง Component ก็เหมือนชิ้นส่วนต่าง ๆ ของรถยนต์
> - แต่ละชิ้นทำงานได้ด้วยตัวเอง (เช่น เครื่องยนต์, เบรก, ระบบไฟฟ้า)
> - นำไปใช้กับรถรุ่นอื่นที่ใช้พาร์ทเดียวกันได้
> - มีจุดต่อ (interface) มาตรฐาน เช่น ขนาดน็อต ขั้วไฟ ที่แน่นอน
> - ไม่จำเป็นต้องรู้ว่าข้างในเครื่องยนต์ทำงานยังไง แค่รู้วิธีใช้และบำรุงรักษา

```mermaid
graph TB
    subgraph "Traditional Monolithic Approach"
        A[Main Application] --> B[Sensor Code]
        A --> C[Display Code]
        A --> D[Network Code]
        A --> E[Storage Code]
        B -.-> C
        C -.-> D
        D -.-> E
    end
    
    subgraph "Component-Based Approach"
        F[Main Application] --> G[Sensor Component]
        F --> H[Display Component]
        F --> I[Network Component]
        F --> J[Storage Component]
    end
    
    style A fill:#ffcccc
    style F fill:#ccffcc
    style G fill:#cceeff
    style H fill:#cceeff
    style I fill:#cceeff
    style J fill:#cceeff
```

### 1.2 Software Engineering Principles

Component-Based Development อิงตามหลักการ Software Engineering

> ** หลักการสำคัญ 4 ข้อที่ควรจำ **
> 1. **Modularity** = แยกเป็นส่วนๆ เหมือนโรงงานรถยนต์ที่แยกประกอบชิ้นส่วนแต่ละส่วน
> 2. **Reusability** = ใช้ซ้ำได้ เหมือนเครื่องยนต์รุ่นเดียวกันที่ใช้ได้กับรถหลายรุ่น
> 3. **Abstraction** = ซ่อนความซับซ้อน เหมือนการขับรถที่เราแค่เหยียบคันเร่ง ไม่ต้องรู้ว่าข้างในเครื่องยนต์ทำงานยังไง หรือคนที่เป็นช่างที่รู้ทุกรายละเอียด มาขับรถก็ย่อมได้
> 4. **Separation of Concerns** = แยกหน้าที่ให้ชัดเจน เหมือนในศูนย์บริการรถยนต์ที่มีช่างเครื่อง ช่างไฟฟ้า ช่างแอร์ แยกความเชี่ยวชาญกัน

```mermaid
mindmap
  root((Component-Based<br/>Development))
    (Modularity)
      ::icon(fa fa-cube)
      แยกความรับผิดชอบ
      ง่ายต่อการดูแล
    (Reusability)
      ::icon(fa fa-recycle)
      ใช้ซ้ำได้
      ลดเวลาพัฒนา
    (Abstraction)
      ::icon(fa fa-eye-slash)
      ซ่อนรายละเอียด
      Interface ชัดเจน
    (Separation of Concerns)
      ::icon(fa fa-layer-group)
      แยกหน้าที่
      ลดการพึ่งพาซึ่งกันและกัน
```

## 2. ข้อดีของการใช้ Components

### 2.1 ประโยชน์ในการพัฒนา

> - **Code Reusability** = เหมือนการใช้อะไหล่มาตรฐาน สามารถใช้กับรถหลายรุ่นได้
> - **Modularity** = แยกเป็นระบบย่อยๆ ถ้าเบรกมีปัญหา ก็เปลี่ยนแค่ระบบเบรก ไม่ต้องเปลี่ยนทั้งคัน
> - **Team Collaboration** = ทีมช่างแต่ละคนรับผิดชอบคนละระบบ เช่น ช่างเครื่อง ช่างไฟฟ้า ช่างแอร์
> - **Testing** = ทดสอบแต่ละระบบได้แยกกัน เช่น เช็คระบบเบรก ระบบไฟ ก่อนส่งมอบรถ

```mermaid
graph LR
    subgraph "Development Benefits"
        A[Code Reusability] --> B[Faster Development]
        C[Modularity] --> D[Easier Maintenance]
        E[Team Collaboration] --> F[Parallel Development]
        G[Testing] --> H[Quality Assurance]
    end
    
    subgraph "Business Benefits"
        B --> I[Reduced Time-to-Market]
        D --> J[Lower Maintenance Cost]
        F --> K[Increased Productivity]
        H --> L[Higher Product Quality]
    end
    
    style I fill:#90EE90
    style J fill:#90EE90
    style K fill:#90EE90
    style L fill:#90EE90
```

### 2.2 Component Lifecycle Management

**วงจรชีวิตของ Component เหมือนการทำการบ้าน**
> 1. **Design** = วางแผนว่าจะทำอะไร เหมือนอ่านโจทย์การบ้าน
> 2. **Development** = เริ่มเขียนโค้ด เหมือนลงมือทำการบ้าน
> 3. **Testing** = ทดสอบว่าทำงานถูกไหม เหมือนตรวจทานการบ้าน
> 4. **Documentation** = เขียนอธิบายวิธีใช้ เหมือนจดวิธีทำไว้ให้เพื่อนดู
> 5. **Publication** = ปล่อยให้คนอื่นใช้ เหมือนส่งการบ้าน
> 6. **Maintenance** = คอยดูแลแก้ไขถ้ามีปัญหา เหมือนแก้การบ้านหลังครูตรวจ

```mermaid
stateDiagram-v2
    [*] --> Design
    Design --> Development
    Development --> Testing
    Testing --> Documentation
    Documentation --> Publication
    Publication --> Usage
    Usage --> Maintenance
    Maintenance --> Updates
    Updates --> Testing
    Testing --> Deprecation
    Deprecation --> [*]
    
    Usage --> Issues
    Issues --> Maintenance
```

## 3. ESP-IDF Component Model

### 3.1 ESP-IDF Architecture Overview

```mermaid
graph TB
    subgraph "ESP-IDF Ecosystem"
        subgraph "Application Layer"
            APP[Your Application]
            MAIN[main component]
        end
        
        subgraph "ESP-IDF Components"
            FREERTOS[FreeRTOS]
            LWIP[lwIP]
            WIFI[WiFi]
            BT[Bluetooth]
            NVFLASH[NVS Flash]
            DRIVER[Driver]
            LOG[Logging]
        end
        
        subgraph "Custom Components"
            SENSOR[Sensor Component]
            DISPLAY[Display Component]
            COMM[Communication Component]
        end
        
        subgraph "Hardware Abstraction Layer"
            HAL[HAL Components]
            SOC[SoC Components]
        end
        
        subgraph "Hardware"
            ESP32[ESP32 Chip]
        end
    end
    
    APP --> MAIN
    MAIN --> SENSOR
    MAIN --> DISPLAY
    MAIN --> COMM
    
    SENSOR --> DRIVER
    DISPLAY --> DRIVER
    COMM --> WIFI
    COMM --> BT
    
    WIFI --> FREERTOS
    BT --> FREERTOS
    DRIVER --> HAL
    HAL --> SOC
    SOC --> ESP32
    
    style APP fill:#FFE4B5
    style SENSOR fill:#E0E0FF
    style DISPLAY fill:#E0E0FF
    style COMM fill:#E0E0FF
```

### 3.2 Component Registration Process

```mermaid
sequenceDiagram
    participant CMake as CMake Build System
    participant Component as Component Directory
    participant Registry as Component Registry
    participant Linker as Linker
    participant Binary as Final Binary
    
    CMake->>Component: Scan for CMakeLists.txt
    Component->>Registry: idf_component_register()
    Registry->>Registry: Validate dependencies
    Registry->>CMake: Return component info
    CMake->>Linker: Generate link libraries
    Linker->>Binary: Create final executable
    
    Note over CMake,Binary: Build Process Flow
```

## 4. โครงสร้าง Component

### 4.1 Component Directory Structure

```mermaid
graph TD
    subgraph "Component Directory"
        A[my_component/] --> B[CMakeLists.txt]
        A --> C[include/]
        A --> D[src/ หรือ *.c files]
        A --> E[test/ optional]
        A --> F[README.md optional]
        A --> G[Kconfig optional]
        
        C --> C1[my_component.h]
        C --> C2[internal.h]
        
        D --> D1[my_component.c]
        D --> D2[helper.c]
        
        E --> E1[test_my_component.c]
    end
    
    style B fill:#FFB6C1
    style C fill:#98FB98
    style D fill:#87CEEB
```

### 4.2 Component Interface Design (APIs)

```mermaid
classDiagram
    class SensorComponent {
        -sensor_handle_t handle
        -sensor_config_t config
        +sensor_init(config) esp_err_t
        +sensor_read_data() sensor_data_t
        +sensor_deinit() esp_err_t
        +sensor_set_callback(callback) esp_err_t
    }
    
    class DisplayComponent {
        -display_handle_t handle
        -display_config_t config
        +display_init(config) esp_err_t
        +display_show(data) esp_err_t
        +display_clear() esp_err_t
        +display_set_brightness(level) esp_err_t
    }
    
    class MainApplication {
        +app_main() void
        -sensor_callback(data) void
        -display_update_task() void
    }
    
    MainApplication --> SensorComponent : uses
    MainApplication --> DisplayComponent : uses
    SensorComponent ..> DisplayComponent : data flow
```

## 5. CMake Build System

### 5.1 CMake Component Registration

```cmake
# CMakeLists.txt ใน component
idf_component_register(
    SRCS "src/sensor.c" "src/helper.c"
    INCLUDE_DIRS "include"
    REQUIRES "driver" "log" "esp_timer"
    PRIV_REQUIRES "nvs_flash"
    PRIV_INCLUDE_DIRS "src"
)
```

**SRCS "src/sensor.c" "src/helper.c"**

ระบุไฟล์ซอร์ส (.c) ที่จะถูกคอมไพล์เป็นส่วนหนึ่งของคอมโพเนนต์นี้ เช่น sensor.c และ helper.c ในโฟลเดอร์ src

**INCLUDE_DIRS "include"**

ระบุโฟลเดอร์ที่มีไฟล์ header (.h) ที่จะถูกเพิ่มเข้าไปใน include path ของคอมโพเนนต์นี้ (เช่น include/)

**REQUIRES "driver" "log" "esp_timer"**

ระบุว่าคอมโพเนนต์นี้ต้องใช้คอมโพเนนต์อื่นๆ (dependencies) เช่น driver, log, esp_timer ซึ่งเป็น library ของ ESP-IDF

**PRIV_REQUIRES "nvs_flash"**

ระบุ dependencies ที่ใช้เฉพาะภายในคอมโพเนนต์นี้ (private) เช่น nvs_flash

**PRIV_INCLUDE_DIRS "src"**

ระบุโฟลเดอร์ header (.h) ที่ใช้เฉพาะภายในคอมโพเนนต์นี้ (private) เช่น src/

- แต่ละบรรทัดใช้กำหนดไฟล์ซอร์ส, ไฟล์ header, และ dependencies ที่จำเป็นสำหรับการ build คอมโพเนนต์ในโปรเจกต์ ESP-IDF ช่วยให้ build system รู้ว่าจะต้องคอมไพล์ไฟล์ไหนและต้องใช้ library อะไรบ้าง


- ไฟล์ header ใน INCLUDE_DIRS จะถูกมองเห็นจากคอมโพเนนต์อื่นด้วย

- ไฟล์ header ใน PRIV_INCLUDE_DIRS จะถูกมองเห็นเฉพาะในคอมโพเนนต์นี้เท่านั้น



### 5.2 Build Dependency Graph

```mermaid
graph TD
    A[Project CMakeLists.txt] --> B[Component Scanning]
    B --> C[Dependency Resolution]
    C --> D[Source Compilation]
    D --> E[Static Libraries]
    E --> F[Final Linking]
    F --> G[Executable Binary]
    
    H[my_sensor] --> I[driver]
    H --> J[log]
    H --> K[esp_timer]
    
    L[my_display] --> I
    L --> J
    L --> M[spi_flash]
    
    N[main] --> H
    N --> L
    
    C -.-> H
    C -.-> L
    
    style A fill:#FFE4E1
    style G fill:#90EE90
    style H fill:#E0E0FF
    style L fill:#E0E0FF
    style N fill:#FFB6C1
```

### 5.3 Component Configuration with Kconfig

```mermaid
graph LR
    subgraph "Configuration Flow"
        A[Kconfig Files] --> B[menuconfig]
        B --> C[sdkconfig]
        C --> D[sdkconfig.h]
        D --> E[Compilation]
    end
    
    subgraph "Configuration Sources"
        F[ESP-IDF Kconfig] --> A
        G[Component Kconfig] --> A
        H[Project Kconfig] --> A
    end
    
    style C fill:#FFB6C1
    style D fill:#98FB98
```

## 6. Component Dependencies

### 6.1 Dependency Types

```mermaid
graph TB
    subgraph "Component Dependency Types"
        A[Public Dependencies<br/>REQUIRES] --> A1[Headers exported to users]
        A --> A2[Link libraries propagated]
        
        B[Private Dependencies<br/>PRIV_REQUIRES] --> B1[Internal use only]
        B --> B2[Not exported to users]
        
        C[Interface Dependencies<br/>REQUIRES only headers] --> C1[Headers only]
        C --> C2[No link libraries]
    end
    
    style A fill:#FFE4B5
    style B fill:#E0E0FF
    style C fill:#98FB98
```

### 6.2 Circular Dependency Resolution

> **🎓 ปัญหาวงจรนรก**
> 
> **ตัวอย่างในชีวิตประจำวัน:**
> - **ปัญหา:** ลืมกุญแจรถไว้ในบ้าน แต่กุญแจบ้านก็ดันอยู่ในรถ = ไม่สามารถเข้าถึงทั้งสองอย่างได้!
> 
> **วิธีแก้:**
> 1. **แบบมีคนกลาง (Interface Component):**
>    - ฝากกุญแจสำรองไว้กับเพื่อนบ้าน
>    - เพื่อนบ้านเป็น "ตัวกลาง" ที่ช่วยแก้ปัญหาการพึ่งพากันแบบวงกลม
> 
> 2. **แบบระบบอัตโนมัติ (Event System):**
>    - ติดตั้งระบบรีโมทไร้กุญแจที่รถ
>    - ติดตั้งระบบล็อคอัตโนมัติที่บ้าน
>    - ทั้งสองระบบทำงานแยกกัน ไม่ต้องพึ่งพากุญแจอีกต่อไป

```mermaid
graph TD
    subgraph "Problematic: Circular Dependency"
        A1[Component A] --> B1[Component B]
        B1 --> A1
        style A1 fill:#FFB6B6
        style B1 fill:#FFB6B6
    end
    
    subgraph "Solution: Interface Component"
        A2[Component A] --> I[Interface Component]
        B2[Component B] --> I
        I --> C2[Common Dependencies]
        style I fill:#90EE90
    end
    
    subgraph "Solution: Event-Driven"
        A3[Component A] --> E[Event System]
        E --> B3[Component B]
        B3 --> E
        E --> A3
        style E fill:#87CEEB
    end
```

## 7. Local vs Managed Components

### 7.1 Component Sources Comparison

```mermaid
graph TB
    subgraph "Component Sources"
        subgraph "Local Components"
            A[components/ folder] --> A1[Project-specific]
            A --> A2[Full control]
            A --> A3[Immediate changes]
        end
        
        subgraph "Managed Components"
            B[Component Registry] --> B1[ESP Component Registry]
            C[Git Repositories] --> C1[GitHub/GitLab]
            D[HTTP Archives] --> D1[ZIP/TAR files]
        end
        
        subgraph "Project Integration"
            E[idf_component.yml] --> B
            E --> C
            E --> D
            F[EXTRA_COMPONENT_DIRS] --> A
        end
    end
    
    style A fill:#E0E0FF
    style B fill:#FFE4B5
    style C fill:#98FB98
    style D fill:#DDA0DD
```

### 7.2 Component Lifecycle and Management

```mermaid
graph TD
    A[Initial Release v1.0.0] --> B[Feature Branch:<br/>Sensor Upgrade]
    B --> C[Add new API]
    C --> D[Update Docs]
    D --> E[Merge to Main<br/>v1.1.0]
    
    E --> F[Bugfix Branch:<br/>Memory Leak]
    F --> G[Fix Issue]
    G --> H[Merge to Main<br/>v1.1.1]
    
    H --> I[Feature Branch:<br/>Low Power]
    I --> J[Add Power Mode]
    J --> K[Merge to Main<br/>v1.2.0]
    
    style A fill:#FFE4B5
    style E fill:#98FB98
    style H fill:#98FB98
    style K fill:#98FB98
```

### 7.3 idf_component.yml Configuration

```mermaid
graph TD
    A[idf_component.yml] --> B[dependencies]
    B --> C[component_name_1]
    B --> D[component_name_2]
    
    C --> C1[version: ^1.0.0]
    C --> C2[git: repo_url]
    C --> C3[path: subdir]
    
    D --> D1[version: ~2.0.0]
    D --> D2[git: other_repo]
    
    A --> E[targets]
    E --> E1[esp32]
    E --> E2[esp32s3]
    
    style A fill:#FFE4B5
    style B fill:#98FB98
    style E fill:#E0E0FF
```

## 8. Component Registry และ Version Control

### 8.1 Semantic Versioning in Components

```mermaid
graph TB
    subgraph "Semantic Versioning"
        A[MAJOR.MINOR.PATCH] --> B[1.2.3]
        
        C[MAJOR] --> C1[Breaking changes<br/>API incompatible]
        D[MINOR] --> D1[New features<br/>Backward compatible]
        E[PATCH] --> E1[Bug fixes<br/>Backward compatible]
    end
    
    subgraph "Version Constraints"
        F["^1.2.3"] --> F1[>=1.2.3, <2.0.0]
        G["~1.2.3"] --> G1[>=1.2.3, <1.3.0]
        H["1.2.*"] --> H1[>=1.2.0, <1.3.0]
        I["*"] --> I1[Latest version]
    end
    
    style C1 fill:#FFB6B6
    style D1 fill:#FFE4B5
    style E1 fill:#90EE90
```

### 8.2 Component Registry Workflow

```mermaid
sequenceDiagram
    participant Dev as Developer
    participant Local as Local Registry
    participant Remote as Component Registry
    participant Build as Build System
    participant Cache as Component Cache
    
    Dev->>Build: idf.py build
    Build->>Local: Check idf_component.yml
    Local->>Cache: Check local cache
    alt Component not in cache
        Cache->>Remote: Download component
        Remote-->>Cache: Component files
    end
    Cache->>Build: Provide component
    Build->>Build: Compile project
    Build-->>Dev: Build complete
```

## 9. Team Development Workflow

### 9.1 Component Development Team Structure

```mermaid
graph TB
    subgraph "Team Organization"
        TL[Team Lead] --> SM[Sensor Module Team]
        TL --> DM[Display Module Team]
        TL --> NM[Network Module Team]
        TL --> IM[Integration Team]
        
        SM --> S1[Sensor Developer 1]
        SM --> S2[Sensor Developer 2]
        
        DM --> D1[Display Developer]
        
        NM --> N1[Network Developer 1]
        NM --> N2[Network Developer 2]
        
        IM --> I1[Integration Engineer]
        IM --> I2[Test Engineer]
    end
    
    subgraph "Component Ownership"
        S1 -.-> C1[sensor_temp component]
        S2 -.-> C2[sensor_humidity component]
        D1 -.-> C3[display_oled component]
        N1 -.-> C4[wifi_manager component]
        N2 -.-> C5[mqtt_client component]
    end
    
    style TL fill:#FFB6C1
    style C1 fill:#E0E0FF
    style C2 fill:#E0E0FF
    style C3 fill:#E0E0FF
    style C4 fill:#E0E0FF
    style C5 fill:#E0E0FF
```

### 9.2 Git Workflow for Component Development

> **🎓 Git Workflow เหมือนการทำโปรเจคกลุ่ม**
> 
> 1. **Initial Project** = เริ่มต้นโปรเจค เหมือนอาจารย์แจกโจทย์
> 2. **แตก Branch** = แบ่งงานกัน เช่น คนนึงทำ Sensor อีกคนทำ Display
> 3. **พัฒนาแต่ละส่วน** = ต่างคนต่างทำงานที่ได้รับมอบหมาย
> 4. **Merge to Main** = เอางานแต่ละส่วนมารวมกัน
> 5. **Integration** = ทดสอบว่าทุกส่วนทำงานร่วมกันได้ดี
> 6. **Release** = ส่งงานอาจารย์

```mermaid
graph TD
    Init[Initial Project] --> S1[Sensor Branch:<br/>Component Scaffold]
    Init --> D1[Display Branch:<br/>Component Scaffold]
    
    subgraph "Sensor Component"
        S1 --> S2[Basic Implementation]
        S2 --> S3[Add Unit Tests]
        S3 --> SM[Merge to Main]
    end
    
    subgraph "Display Component"
        D1 --> D2[Basic Implementation]
        D2 --> D3[Add Display Tests]
        D3 --> DM[Merge to Main]
    end
    
    SM --> I1[Integration Branch]
    DM --> I1
    
    subgraph "Integration"
        I1 --> I2[Integrate Components]
        I2 --> I3[Add Demo App]
        I3 --> IM[Merge to Main]
    end
    
    IM --> Rel[Release v1.0.0]
    
    style Init fill:#FFE4B5
    style SM fill:#98FB98
    style DM fill:#98FB98
    style IM fill:#98FB98
    style Rel fill:#FFB6C1
    
    classDef branch fill:#E0E0FF,stroke:#333,stroke-width:2px
    class S1,S2,S3 branch
    class D1,D2,D3 branch
    class I1,I2,I3 branch
```

### 9.3 Component Testing Strategy

```mermaid
graph TB
    subgraph "Testing Pyramid"
        A[Unit Tests] --> A1[Individual functions]
        A --> A2[Mock dependencies]
        A --> A3[Fast execution]
        
        B[Integration Tests] --> B1[Component interaction]
        B --> B2[Real dependencies]
        B --> B3[Medium execution time]
        
        C[System Tests] --> C1[End-to-end scenarios]
        C --> C2[Real hardware]
        C --> C3[Slow execution]
    end
    
    subgraph "Test Tools"
        D[Unity] --> A
        E[CMock] --> A
        F[ESP-IDF Test Framework] --> B
        G[Hardware-in-the-Loop] --> C
    end
    
    style A fill:#90EE90
    style B fill:#FFE4B5
    style C fill:#FFB6B6
```

## 10. Component Design Patterns

### 10.1 Common Component Patterns

> **🎓 4 รูปแบบการออกแบบ Component ที่พบบ่อย:**
> 
> **1. Singleton Pattern - เหมือนผู้จัดการคนเดียว**
> - มีตัวจัดการแค่ตัวเดียว (เหมือนร้านที่มีผู้จัดการคนเดียว)
> - เข้าถึงได้จากทุกที่ในระบบ (ทุกแผนกติดต่อผู้จัดการคนนี้ได้)
> - สร้างเมื่อจำเป็นต้องใช้ (ถ้าไม่มีใครเรียกหา ก็ไม่ต้องมี)

```mermaid
flowchart TD
    subgraph Singleton[Singleton Pattern]
        PM[ผู้จัดการ] --> |มีได้<br>1 คน| W1[พนักงาน 1]
        PM --> |ติดต่อ| W2[พนักงาน 2]
        PM --> |สั่งงาน| W3[พนักงาน 3]
    end
    style PM fill:#FFE4B5,stroke-width:3px
    style W1 fill:#fff,stroke-width:2px
    style W2 fill:#fff,stroke-width:2px
    style W3 fill:#fff,stroke-width:2px
```

```mermaid
flowchart TD
    subgraph Factory[Factory Pattern]
        F[โรงงานผลิตเซนเซอร์] --> S1[เซนเซอร์วัดอุณหภูมิ]
        F --> S2[เซนเซอร์วัดความชื้น]
        F --> S3[เซนเซอร์วัดแสง]
        F --> S4[เพิ่มชนิดใหม่ได้...]
    end
    style F fill:#E0E0FF,stroke-width:3px
    style S1 fill:#fff,stroke-width:2px
    style S2 fill:#fff,stroke-width:2px
    style S3 fill:#fff,stroke-width:2px
    style S4 fill:#fff,stroke-width:2px
```

```mermaid
flowchart TD
    subgraph Observer[Observer Pattern - เหมือนกลุ่ม LINE]
        L[กลุ่ม LINE] --> |ส่งข่าว| M1[สมาชิก 1]
        L --> |แจ้งเตือน| M2[สมาชิก 2]
        L --> |อัพเดท| M3[สมาชิก 3]
        M4[สมาชิกใหม่] -.-> |เข้ากลุ่ม| L
        M5[ออกกลุ่ม] -.-> |ออก| L
    end
    style L  fill:#98FB98,stroke-width:3px
    style M1 fill:#fff,stroke-width:2px
    style M2 fill:#fff,stroke-width:2px
    style M3 fill:#fff,stroke-width:2px
    style M4 fill:#fff,stroke-width:2px
    style M5 fill:#fff,stroke-width:2px
```

```mermaid
flowchart TD
    subgraph Strategy[Strategy Pattern - เหมือนเลือกวิธีส่งของ]
        D[ระบบส่งของ] --> |ด่วนพิเศษ| D1[Kerry]
        D --> |ราคาประหยัด| D2[ไปรษณีย์]
        D --> |ส่งในกรุงเทพ| D3[Grab]
        D -.-> |เพิ่มตัวเลือก| D4[วิธีใหม่ๆ]
    end
    style D fill:#DDA0DD,stroke-width:3px
    style D1 fill:#fff,stroke-width:2px
    style D2 fill:#fff,stroke-width:2px
    style D3 fill:#fff,stroke-width:2px
    style D4 fill:#fff,stroke-width:2px
```

### 10.2 Component Communication Patterns

```mermaid
sequenceDiagram
    participant App as Application
    participant SM as Sensor Manager
    participant Sensor as Sensor Component
    participant Queue as Event Queue
    participant Display as Display Component
    
    App->>SM: Initialize
    SM->>Sensor: sensor_init()
    Sensor-->>SM: Success
    
    loop Every 1 second
        SM->>Sensor: sensor_read()
        Sensor-->>SM: data
        SM->>Queue: publish_event(data)
        Queue->>Display: sensor_data_event
        Display->>Display: update_display(data)
    end
```

### 10.3 Error Handling in Components

> **🎓 การจัดการความผิดพลาดเหมือนการแก้ปัญหาในชีวิตประจำวัน**
> 
> 1. **Error Detection** = จับได้ว่ามีปัญหา เช่น โทรศัพท์ไม่ติด
> 2. **Error Classification** = ระบุว่าเป็นปัญหาอะไร เช่น แบตหมด/เครื่องค้าง
> 3. **Error Reporting** = แจ้งปัญหา เช่น บอกว่า "แบตหมด กรุณาชาร์จ"
> 4. **Error Recovery** = แก้ปัญหา เช่น เสียบชาร์จ/รีสตาร์ทเครื่อง
> 5. **Error Logging** = จดไว้เป็นประวัติ เผื่อเกิดปัญหาซ้ำ

```mermaid
graph TB
    subgraph "Error Handling Strategy"
        A[Error Detection] --> B[Error Classification]
        B --> C[Error Reporting]
        C --> D[Error Recovery]
        D --> E[Error Logging]
    end
    
    subgraph "Error Types"
        F[Hardware Errors] --> F1[Sensor disconnected]
        F --> F2[Communication timeout]
        
        G[Software Errors] --> G1[Invalid parameters]
        G --> G2[Memory allocation failure]
        
        H[Configuration Errors] --> H1[Missing config]
        H --> H2[Invalid settings]
    end
    
    subgraph "Recovery Strategies"
        I[Retry Mechanism] --> I1[Exponential backoff]
        J[Fallback Mode] --> J1[Safe defaults]
        K[Reset/Restart] --> K1[Component reinit]
    end
    
    B --> F
    B --> G
    B --> H
    
    D --> I
    D --> J
    D --> K
    
    style A fill:#FFB6B6
    style D fill:#90EE90
```

## 11. Testing และ Documentation

### 11.1 Component Documentation Structure

```mermaid
graph TB
    subgraph "Documentation Types"
        A[API Reference] --> A1[Function signatures]
        A --> A2[Parameter descriptions]
        A --> A3[Return values]
        A --> A4[Code examples]
        
        B[User Guide] --> B1[Getting started]
        B --> B2[Configuration guide]
        B --> B3[Troubleshooting]
        
        C[Developer Guide] --> C1[Architecture overview]
        C --> C2[Extending the component]
        C --> C3[Contributing guidelines]
        
        D[Changelog] --> D1[Version history]
        D --> D2[Breaking changes]
        D --> D3[Migration guides]
    end
    
    style A fill:#E0E0FF
    style B fill:#FFE4B5
    style C fill:#98FB98
    style D fill:#DDA0DD
```

### 11.2 Continuous Integration Pipeline

> **🎓 CI/CD Pipeline เหมือนการส่งการบ้านออนไลน์:**
> 
> 1. **Code Push** = ส่งการบ้าน
> 2. **Static Analysis** = ระบบตรวจรูปแบบการเขียน
> 3. **Unit Tests** = ตรวจว่าแต่ละข้อถูกไหม
> 4. **Integration Tests** = ตรวจว่าทุกข้อทำงานร่วมกันได้
> 5. **Build Verification** = ตรวจว่าคอมไพล์ผ่านไหม
> 6. **Documentation** = ตรวจว่าเขียนอธิบายครบไหม
> 7. **Package & Publish** = ให้คะแนนและบันทึกผล

```mermaid
graph LR
    subgraph "CI/CD Pipeline"
        A[Code Push] --> B[Static Analysis]
        B --> C[Unit Tests]
        C --> D[Integration Tests]
        D --> E[Build Verification]
        E --> F[Documentation Generation]
        F --> G[Package & Publish]
    end
    
    subgraph "Quality Gates"
        H[Code Coverage > 80%]
        I[No Critical Issues]
        J[All Tests Pass]
        K[Documentation Complete]
    end
    
    C -.-> H
    B -.-> I
    D -.-> J
    F -.-> K
    
    style A fill:#87CEEB
    style G fill:#90EE90
```

## 12. สรุปและเตรียมตัวสำหรับการทดลอง

### 12.1 สรุปแนวคิดสำคัญ

```mermaid
mindmap
  root((ESP32 Components))
    (Architecture)
      Component-based design
      Modular development
      Clear interfaces
    (Management)
      Local components
      Managed components
      Version control
    (Development)
      CMake build system
      Dependency management
      Testing strategies
    (Collaboration)
      Team workflows
      Git strategies
      Documentation
```

### 12.2 Lab Roadmap

```mermaid
journey
    title Component Development Journey
    section Lab 7.1
      Setup Environment: 3: Student
      Create Local Component: 4: Student
      Build & Test: 5: Student
    section Lab 7.2
      Configure Managed Component: 4: Student
      Download from GitHub: 5: Student
      Integration Testing: 4: Student
    section Lab 7.3
      Create Custom Components: 5: Student
      Multi-component Project: 5: Student
      Team Workflow: 4: Student
```

### 12.3 การเตรียมตัวสำหรับการทดลอง

#### สิ่งที่ควรจำ:
1. **Component Structure** - CMakeLists.txt, include/, source files
2. **Dependency Management** - REQUIRES vs PRIV_REQUIRES
3. **Build Process** - idf.py commands และ CMake integration
4. **Version Control** - Git workflow สำหรับ components

#### เครื่องมือที่ต้องใช้:
- Docker และ ESP-IDF environment
- Git สำหรับ version control
- Text editor หรือ IDE
- Terminal/Command line

#### ทักษะที่จะได้รับ:
- ✅ การออกแบบ component architecture
- ✅ การจัดการ dependencies
- ✅ การใช้งาน managed components
- ✅ การทำงานเป็นทีมด้วย Git
- ✅ การทดสอบและ documentation

---

## 🎯 คำถามท้าทาย (สำหรับการอภิปราย)

1. **เมื่อไหร่ควรสร้าง component ใหม่** แทนที่จะเขียนโค้ดใน main application?

2. **ความแตกต่างระหว่าง REQUIRES และ PRIV_REQUIRES** ส่งผลต่อการ compile อย่างไร?

3. **การเลือกใช้ local component vs managed component** ขึ้นอยู่กับปัจจัยใดบ้าง?

4. **ในทีมงานขนาดใหญ่** จะจัดการ component dependencies อย่างไรให้มีประสิทธิภาพ?

5. **การทดสอบ component** ที่มีการพึ่งพา hardware ทำได้อย่างไร?

---

**หมายเหตุ:** เนื้อหานี้เป็นการเตรียมความพร้อมสำหรับการทดลอง หลังจากการบรรยายนี้ นักศึกษาจะได้ลงมือปฏิบัติจริงใน Lab 7.1-7.3 เพื่อประยุกต์ใช้ความรู้ที่ได้เรียน
