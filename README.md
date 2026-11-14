# CrazyCar (RAT-CrazyCAR)

This is my project for the Crazy Car Competition at FH JOANNEUM in Graz.

The goal is to design and build a small autonomous racing car that drives around a track on its own using time-of-flight distance sensors, active downforce, and a custom STM32 control board.

I made it because I want to win at the Crazy Car competition and because I love designing complicated PCBs.

## Full Assembly

<img width="601" height="716" alt="Full 3D Assembly 1" src="https://github.com/user-attachments/assets/8a919f41-4657-4bd5-854b-9d6c61e813d7" />

<img width="615" height="509" alt="Full 3D Assembly 2" src="https://github.com/user-attachments/assets/f667dabf-061c-428e-81fe-90e22cfd4a59" />

<img width="1016" height="494" alt="Full 3D Assembly 3" src="https://github.com/user-attachments/assets/d11d4e14-f0ae-4c11-94ed-e40ab31c4019" />

## Hardware

- **MCU**: `STM32C092CCT6` (48 MHz ARM Cortex-M0+)
- **Distance Sensors**: Five `VL53L0X` time-of-flight laser distance sensors mounted across the front of the car. Since all five sensors share the same default I2C address (`0x29`), they are routed through a `TCA9548APWR` 8-channel I2C multiplexer (`U4`) with individual `XSHUT` lines for 50 Hz continuous polling.
- **Drive Motors & Current Sensing**: Dual N20 micro metal gearmotors with magnetic quadrature encoders (`M1`, `M2`), driven by two `RZ7889` H-bridge motor drivers (`IC1`, `IC2`) paired with `TMCS1100A3QDR` Hall-effect current sensors (`U2`, `U3`) for stall and torque monitoring.
- **Active Suction / Downforce System**: A centrifugal impeller fan underneath the chassis driven by a `Happymodel RS0802 20000KV` brushless motor (`M3`) and a `Graupner Ultra Control 10A BLHeli_S` ESC (`U7`) to create underbody suction and generate ~1–1.5 kg of downforce for high cornering speeds.
- **IMU & Power**: Onboard `MPU-6500` 6-axis gyroscope/accelerometer (`U5`) over SPI, powered by a `CNHL MiniStar HV 450mAh 2S 70C` LiPo battery (`BT1`) regulated to `+3.3V` via a `TRACO TSR 1-2433E` buck converter (`U6`).

## How to Use It

1. **Flash Firmware**: Connect an ST-Link programmer to the 5-pin SWD header (`J1`) and flash the control firmware onto the `STM32C092CCT6`.
2. **Connect Peripherals**: Plug the five front `VL53L0X` ToF sensors into headers `J4`–`J8`, the two N20 drive motors with encoders into `J2` and `J3`, and the brushless suction-fan ESC into `J11` (power) and `J10` (PWM signal).
3. **Power & Run**: Plug the 2S LiPo battery into the XT30 input connector (`J9`). The MCU initializes the `MPU-6500` IMU and all five `VL53L0X` sensors via the `TCA9548A` multiplexer. Press the onboard user button (`SW2`) to arm the brushless suction fan and start autonomous track driving.

## PCB & Schematic

The custom 2-layer PCB doubles as the main structural chassis plate of the car and was designed in KiCad 10.

**Front Copper:**
<img width="772" height="848" alt="Front Copper" src="https://github.com/user-attachments/assets/c5560d25-a898-46f2-8d61-dfda912b90eb" />

**Back Copper:**
<img width="835" height="834" alt="Back Copper" src="https://github.com/user-attachments/assets/9f960a12-4d7c-4858-b45d-13bfd22bf6b7" />

**3D PCB Render:**
<img width="835" height="905" alt="3D PCB Render" src="https://github.com/user-attachments/assets/f72cee74-0a09-4e82-99b1-26d4261b97a7" />

**Schematic:**
<img width="790" height="635" alt="Schematic" src="https://github.com/user-attachments/assets/e51b72aa-a14e-4b8b-9f49-85ab6f9c7357" />

## Repository Contents

- `carzycar.kicad_pro`, `carzycar.kicad_sch`, `carzycar.kicad_pcb`, `carzycar.kicad_prl` — KiCad 10 project, schematic, and PCB layout source files
- `gerbers.zip` & `production/` — Manufacturing Gerber files (`final.zip`), pick-and-place positions (`final_positions.csv`), and BOMs (`BOM (version 1).xlsx`, `final_bom.csv`)
- `BOM.csv` — Complete Bill of Materials with distributor links, quantities, unit prices, and shipping/import cost breakdown
- `Assembly/` — Full Fusion 360 CAD assembly source files (`crazy car full.f3z`, `gehäuse.f3d`, `impeller.f3d`, `motorhalter.f3d`)
- `3Dmodels/` — `.step` and `.3mf` 3D models for all modeled parts and mechanical components (`carzycar.step`, `carzycarneueplatine2.step`, `Bracket.step`, sensor holders, and impeller housing)
- `firmware/` — Arduino/STM32 firmware (`test_firmware.ino`) for 50 Hz `TCA9548A` + 5× `VL53L0X` continuous ranging
- `Extra Libraries/` — Custom KiCad symbols, footprints, and 3D models (`RZ7889`, `MPU-6500`, `TMCS1100A3QDR`)
