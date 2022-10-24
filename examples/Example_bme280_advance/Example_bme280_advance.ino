/***********************************************************************
 * Project      :     Example_bme280_advance
 * Description  :     tiny32 interface with BME280 Temperature, Humidity and Pressure Sensor
 * Hardware     :     tiny32_v3
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-308-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

/**************************************/
/*          Firmware Version          */
/**************************************/
String version = "0.1";

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;
Adafruit_BME280 bme; // I2C

/**************************************/
/*            GPIO define             */
/**************************************/

/**************************************/
/*       Constand define value        */
/**************************************/
#define SEALEVELPRESSURE_HPA (1013.25)

/**************************************/
/*       eeprom address define        */
/**************************************/

/**************************************/
/*        define global variable      */
/**************************************/
unsigned long delayTime;

/**************************************/
/*           define function          */
/**************************************/

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    Serial.println("*** Example_bme280_advance ***");

    if (! bme.begin(0x76)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }


    Serial.println("-- Default Test --");
    Serial.println("normal mode, 16x oversampling for all, filter off,");
    Serial.println("0.5ms standby period");
    delayTime = 5000;

    // For more details on the following scenarious, see chapter
    // 3.5 "Recommended modes of operation" in the datasheet

    /*
        // weather monitoring
        Serial.println("-- Weather Station Scenario --");
        Serial.println("forced mode, 1x temperature / 1x humidity / 1x pressure oversampling,");
        Serial.println("filter off");
        bme.setSampling(Adafruit_BME280::MODE_FORCED,
                        Adafruit_BME280::SAMPLING_X1, // temperature
                        Adafruit_BME280::SAMPLING_X1, // pressure
                        Adafruit_BME280::SAMPLING_X1, // humidity
                        Adafruit_BME280::FILTER_OFF   );

        // suggested rate is 1/60Hz (1m)
        delayTime = 60000; // in milliseconds
    */

    /*
        // humidity sensing
        Serial.println("-- Humidity Sensing Scenario --");
        Serial.println("forced mode, 1x temperature / 1x humidity / 0x pressure oversampling");
        Serial.println("= pressure off, filter off");
        bme.setSampling(Adafruit_BME280::MODE_FORCED,
                        Adafruit_BME280::SAMPLING_X1,   // temperature
                        Adafruit_BME280::SAMPLING_NONE, // pressure
                        Adafruit_BME280::SAMPLING_X1,   // humidity
                        Adafruit_BME280::FILTER_OFF );

        // suggested rate is 1Hz (1s)
        delayTime = 1000;  // in milliseconds
    */

    /*
        // indoor navigation
        Serial.println("-- Indoor Navigation Scenario --");
        Serial.println("normal mode, 16x pressure / 2x temperature / 1x humidity oversampling,");
        Serial.println("0.5ms standby period, filter 16x");
        bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                        Adafruit_BME280::SAMPLING_X2,  // temperature
                        Adafruit_BME280::SAMPLING_X16, // pressure
                        Adafruit_BME280::SAMPLING_X1,  // humidity
                        Adafruit_BME280::FILTER_X16,
                        Adafruit_BME280::STANDBY_MS_0_5 );

        // suggested rate is 25Hz
        // 1 + (2 * T_ovs) + (2 * P_ovs + 0.5) + (2 * H_ovs + 0.5)
        // T_ovs = 2
        // P_ovs = 16
        // H_ovs = 1
        // = 40ms (25Hz)
        // with standby time that should really be 24.16913... Hz
        delayTime = 41;
        */

    /*
    // gaming
    Serial.println("-- Gaming Scenario --");
    Serial.println("normal mode, 4x pressure / 1x temperature / 0x humidity oversampling,");
    Serial.println("= humidity off, 0.5ms standby period, filter 16x");
    bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X1,   // temperature
                    Adafruit_BME280::SAMPLING_X4,   // pressure
                    Adafruit_BME280::SAMPLING_NONE, // humidity
                    Adafruit_BME280::FILTER_X16,
                    Adafruit_BME280::STANDBY_MS_0_5 );

    // Suggested rate is 83Hz
    // 1 + (2 * T_ovs) + (2 * P_ovs + 0.5)
    // T_ovs = 1
    // P_ovs = 4
    // = 11.5ms + 0.5ms standby
    delayTime = 12;
*/

    mcu.buzzer_beep(2);
}

/***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{

    // Only needed in forced mode! In normal mode, you can remove the next line.
    bme.takeForcedMeasurement(); // has no effect in normal mode

    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println("-----------------------\r\n");
    vTaskDelay(delayTime);
}
