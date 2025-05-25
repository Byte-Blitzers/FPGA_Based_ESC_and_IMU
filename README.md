# FPGA-Based ESC and IMU Integration

This project implements an **FPGA-based Electronic Speed Controller (ESC)** integrated with an **Inertial Measurement Unit (IMU)**. It is designed to offer high-performance, low-latency motor control with real-time feedback from the IMU, making it ideal for robotics, drones, and embedded motion control applications.

---

## 🔧 Project Structure

```
FPGA_Based_ESC_and_IMU/
├── Architectures and Flow Charts/   # System diagrams and flowcharts
├── Constraints FIle/                # FPGA hardware constraints (pin mapping, timing)
├── Docmentation/                    # Project documentation and design explanation
├── SDK Codes/                       # Software (likely C) for controlling FPGA/IMU
├── TCL Script/                      # Scripts for project setup and build automation
└── README.md                        # Project description
```

---

## 🚀 Features

* **Custom ESC on FPGA**: Achieves precise motor control through HDL implementation.
* **IMU Integration**: Real-time orientation and acceleration feedback via sensors.
* **Low-Latency Control Loop**: Suitable for applications requiring fast and accurate response.
* **Automated Project Setup**: TCL scripts streamline synthesis and implementation in FPGA tools.

---

## 🧰 Tools & Technologies

* **HDL (likely VHDL/Verilog)** for hardware design
* **Tcl** for scripting FPGA toolchain processes
* **C** for SDK-based software interaction
* **Vivado/Quartus** (presumed) for FPGA development
* **FPGA Development Board** (e.g., Xilinx or Intel/Altera based)
* **IMU Sensor Module** (e.g., MPU6050 or similar)

---

## 📁 How to Use

1. Clone the repository:

   ```bash
   git clone https://github.com/shardulbhave/FPGA_Based_ESC_and_IMU.git
   ```
2. Open the project in your FPGA IDE (Vivado or Quartus).
3. Review and apply the constraint files under `Constraints FIle/`.
4. Use the `TCL Script/` to set up the build environment.
5. Upload the bitstream to your FPGA.
6. Compile and run the `SDK Codes/` to start communicating with the ESC and IMU.

---

## 📚 Documentation

Full design documentation is available in the `Docmentation/` directory, including system architecture, flow diagrams, and signal explanations. Refer to the "Architectures and Flow Charts/" folder for visual representation of the design and data paths.

---

## 🔍 Applications

* Quadcopters and drones
* Robotics and autonomous vehicles
* Precision motor control systems
* Embedded real-time systems

---
