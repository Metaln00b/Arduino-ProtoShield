#include <libad5592r.h>
#include <Wire.h>
#include "SparkFun_MMA8452Q.h"

ad5592r_t ad5592r;
MMA8452Q accel;

void printAccels()
{
    Serial.print(accel.x);
    Serial.print("\t");
    Serial.print(accel.y);
    Serial.print("\t");
    Serial.print(accel.z);
    Serial.print("\t");
}

void printCalculatedAccels()
{
    Serial.print(accel.cx, 3);
    Serial.print("\t");
    Serial.print(accel.cy, 3);
    Serial.print("\t");
    Serial.print(accel.cz, 3);
    Serial.print("\t");
}

void printOrientation()
{
    byte pl = accel.readPL();
    switch (pl)
    {
      case PORTRAIT_U:
        Serial.print("Portrait Up");
        break;
      case PORTRAIT_D:
        Serial.print("Portrait Down");
        break;
      case LANDSCAPE_R:
        Serial.print("Landscape Right");
        break;
      case LANDSCAPE_L:
        Serial.print("Landscape Left");
        break;
      case LOCKOUT:
        Serial.print("Flat");
        break;
    }
}

void printTemperature()
{
    size_t iteration_size = 50;
    double temp[iteration_size];
    double temp_sum = 0;
    double temp_avg;
    for (size_t i = 0; i < iteration_size; i++)
    {
        temp[i] = ad5592r_temperature_get_degC(&ad5592r);
        temp_sum += temp[i];
    }
    temp_avg = temp_sum/iteration_size;
    Serial.print(temp_avg, 2);
    Serial.println(" degC");
    delay(100);
}

void setup() {
    Serial.begin (115200);
    accel.init();
    ad5592r_init(&ad5592r);
    ad5592r_reset(&ad5592r);
    ad5592r_setup_source_ref_set(&ad5592r, AD5592R_VREF_SOURCE_INTERNAL);
    ad5592r_setup_double_vref_set(&ad5592r, true);
    ad5592r_setup_supply_voltage_mV(&ad5592r, 3300);

    ad5592r_setup_dac_all(&ad5592r, AD5592R_IO(0));
    ad5592r_setup_ldac(&ad5592r, AD5592R_LDAC_MODE_IMMEDIATELY);
}

void loop() {
    if (accel.available())
    {
        accel.read();
        printCalculatedAccels();
        printOrientation();
        Serial.println();
    }
    if (Serial.available() > 0) {
        double voltage_mV_set = Serial.parseInt();
    
        Serial.print("You send: ");
        Serial.print(voltage_mV_set);
        Serial.println(" mV");
        if (voltage_mV_set > 2750)
        {
            Serial.println("MAX. 2750mV for TC648BEOA.");
            voltage_mV_set = 2750;
        }
        ad5592r_dac_voltage_set_mV(&ad5592r, AD5592R_IO(0), voltage_mV_set);
        printTemperature();
    }
}
