# Seat_Belt_ELR
## Abstract/ Problem Statement

An Emergency Locking Retractor (ELR) is a seat belt retractor that locks only in response to the rapid deceleration of a vehicle or rapid spooling out of the seat belt webbing from the retractor and increases the comfort of the seat belt assembly compared to an ALR. The ELR was designed to allow the seat belt webbing to move freely once the seat belt is in place but locking the webbing instantly in the event of a crash. The locking sensitivity of the device has been an important issue given the need to assure that the retractor would lock very early during a collision, but not be so sensitive as to cause nuisance locking during normal driving conditions.
Instead of traditional Mechanical Sensors are trying to have some electronic sensing and actuating system.
For detection of sudden deceleration IMU (inertial measurement unit) is being used, in case of accidents sudden deceleration is detected by sensor and data is sent to Microcontroller unit which actuates the actuator mechanism to lock the belt. Similar sensing is done for sudden/ rapid spooling of seat belt using encoder sensors along with webbing. Encoder sensors help to detect speed of rotation of webbing and if it exceeds a certain value lock is actuated by the microcontroller unit.
Actuator is a servo motor which initially is unlocked and if rotated to 90 degrees locks the seat belt. Servo motor is controlled by microcontroller unit.


## Software Used
Proteus design Suite 8.10
Arduino Ide

## Components Required
- Microcontroller Unit – Arduino Uno
- Sensors – Hall Sensor based Encoder
	IMU Sensor (Acclerometer)
	Encoder for seat angle detection
- Actuator – Servo Motor

## Working:
For sake of understanding working is divided in 3 parts – Sensing, Processing, Actuating.
Sensing – In this part we try to collect RAW data from the sensors in the system and send it to microcontroller unit. We have 2 categories of sensors in the system, first one being interrupt to MCU unit and second one to collect ambiance details.
Interrupting sensors include accelerometer and Encoder attached to spool of web, whenever sudden deceleration is detected, or rapid spooling is detected the interrupt is activated in mcu which actuates the servo motor and stops spooling immediately.
Sensors which collet ambiance details are like an encoder to detect seat angle of passenger so they don’t activate any interrupt but in case of accident helps in determining at what exact moment the actuator should be actuated.
Processing – Once data is collected from the sensors, we must convert it to understandable form and use that readable data to make decisions like locking or unlocking the seat belt. Processing is being done in AT Mega 328p as of now which is sufficient for out purpose as of now. Both the interrupt pins are being used to detect and actuate the servo in case of accident.
Actuating – Once sensing and processing is done, if microcontroller unit senses an accident, it actuates servo motor at pin 12, this servo moves a plastic bit and locks the seat belt.




Basic Structure of Hardware

![image](https://user-images.githubusercontent.com/49076977/127124378-24d0ecc4-7b35-4c85-a74f-d3482661c709.png)
