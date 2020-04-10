# Arduino-ProtoShield
Arduino, MMA8452Q, AD5592R, TC648BEOA, IRLZ34N based prototype

## Introduction

### I2C MMA8452Q Accelerometer Connection

| Display | Arduino |
| ------- | ------- |
| SDA     | ANALOG4 |
| SCL     | ANALOG5 |
| GND     | GND     |
| VCC     | 5V      |

### SPI AD5592R-1 Connection

| AD5592R-1 | Arduino | TC648BEOA |
| --------- | ------- | --------- |
| VDD       | 3V3     | -         |
| IO0       | -       | PIN1      |
| Vref      | 100n    | -         |
| SDO       | D12     | -         |
| GND       | GND     | -         |
| SDI       | D11     | -         |
| SCLK      | D13     | -         |
| Vlogic    | 5V      | -         |
| SYNC#     | D10     | -         |

### TC648BEOA Connection

| TC648BEOA | Arduino | AD5592R-1 | IRLZ34N |
| --------- | ------- | --------- | ------- |
| PIN1      | -       | IO0       | -       |
| PIN2      | 100n    | -         | -       |
| PIN3      | GND     | -         | -       |
| PIN4      | GND     | -         | -       |
| PIN7      | -       | -         | GATE    |
| PIN8      | 3V3     | -         | -       |

### IRLZ34N Connection

| IRLZ34N | TC648BEOA | Arduino | LOAD  |
| ------- | --------- | ------- | ----  |
| GATE    | PIN7      | -       | -     |
| DRAIN   | -         | -       | GND   |
| SOURCE  | -         | GND     | -     |

### Libraries

* https://github.com/Metaln00b/Arduino-libad5592r

* https://github.com/sparkfun/SparkFun_MMA8452Q_Arduino_Library

### Parts

* AD5592R-1
* Arduino Uno
* MMA8452Q
* TC648BEOA
* IRLZ34N (N-CH Mosfet)
* 2x100n Capacitor

## License

This project is licensed under the MIT License - see the [license file](LICENSE) for details.
