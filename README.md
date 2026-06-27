# ⚡ Smart Energy Monitoring with Generator Load Protection and Adaptive Control

## 📌 Overview
This project presents an IoT-based smart energy monitoring and protection system designed for residential environments. 
It ensures safe and efficient power usage by preventing generator overload through adaptive multi-stage protection and real-time monitoring.
The system integrates embedded hardware with a web-based interface to provide both user-level and authority-level control.

## 🎯 Objectives
- Monitor real-time electrical parameters (Voltage, Current, Power, Energy)
- Prevent generator overload using adaptive protection techniques
- Implement dual operation modes (Normal & Generator Mode)
- Provide remote monitoring and control via web dashboards

## 🧠 System Architecture

The system consists of multiple ESP32-based nodes deployed across different units (e.g., apartments), connected to a central server.

- ESP32 nodes → Collect electrical data  
- Server → Processes and stores data  
- Dashboards → Display data and allow control  

## 🛠️ Hardware Components

| Component      | Function |

| ESP32          | Main controller for sensing and communication |
| PZEM-004T      | Measures voltage, current, power, and energy |
| Relay Module   | Disconnects load during overload |
| Buzzer         | Provides warning alerts |
| 16x2 LCD (I2C) | Displays real-time data |
| Power Supply   | Provides regulated voltage |


## 💻 Software & Communication

- Embedded C (Arduino IDE)
- HTTP-based communication
- Web server for data handling and control
- Dashboard interface for users and administrators


## ⚙️ Working Principle

The system operates in two modes:

### 🔹 Normal Mode
- Only monitoring is active  
- No automatic load cutoff  
- Optional warning alerts  

### 🔹 Generator Mode
- Threshold-based protection enabled  
- Adaptive multi-stage cutoff active  
- Prevents generator overload  

---

## ⚠️ Adaptive Protection Mechanism

The system implements a **multi-stage protection strategy**:

- **Stage 1:** Warning + short-duration cutoff  
- **Stage 2:** Warning + medium-duration cutoff  
- **Stage 3:** Warning + long-duration cutoff  

If the user reduces load during the warning period, the cutoff is cancelled.

---

## 🌐 Data Communication

- ESP32 sends real-time data to the server using HTTP protocol  
- Server stores and processes data  
- Dashboards retrieve data and send control commands  

---

## 📊 Dashboard Features

### 👤 User Dashboard
- Real-time monitoring of electrical parameters  
- Threshold configuration  
- Mode indication  
- System reset control  

### 🏢 Authority Dashboard
- Monitor all connected units  
- Activate generator mode  
- Set global thresholds  
- View system activity  

## 📊 Results

- Real-time monitoring with fast response  
- Reliable overload detection and protection  
- Stable operation in both normal and generator modes  
- Efficient load management across multiple users  

  ## Code Structure
  -'code/main.ino'-ESP32 Ardinuo IDE Code

## ▶️ How to Run

1. Connect ESP32 with PZEM-004T module  
2. Connect relay and buzzer  
3. Upload code using Arduino IDE  
4. Start the server (if applicable)  
5. Open dashboard or Serial Monitor  
6. Test system under load conditions  

## 🔧 Applications
- Residential apartment systems  
- Hostels and shared accommodations  
- Commercial buildings  
- Smart grid and energy management systems  

## 🚀 Future Scope
- Automatic generator detection using ATS  
- Mobile app integration  
- Cloud-based monitoring  
- AI-based load prediction and optimization  

## 👩‍💻 Author
**Sreelakshmi S S**  
Electronics and Communication Engineering  
Focus: Embedded Systems | IoT | VLSI  

## 📌 Conclusion

This system provides a scalable and efficient solution for energy monitoring and generator protection by combining IoT, embedded systems, and adaptive control strategies.
It ensures safety, fairness, and optimized energy usage in shared environments.


