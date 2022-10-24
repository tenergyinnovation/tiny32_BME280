/***********************************************************************
 * File         :     tiny32_v3.h
 * Description  :     Class for Hardware config and function for tiny32_v3 module
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     23 Nov 2021
 * Revision     :     3.4
 * Rev1.0       :     Original 
 * Rev1.1       :     Add TimeStamp_minute  
 *                    Add TimeStamp_24hr_minute
 * Rev1.2             Add EC RS485 sensor    
 * Rev1.3             Change define switch to int  
 * Rev1.4       :     Add EC sensor (RS485)    
 * Rev1.5       :     Add PZEM-016 Energy Meter AC    
 *                    Add PZEM-003 Energy Meter DC  
 *                    Add rs485_2.begin(9600, SERIAL_8N2, RXD2, TXD2) for PZEM-003   
 * Rev1.6             Intial board to BuildIN LED = > LOW  
 * Rev1.7       :     Fix bug for PZEM-003 and PZEM-016 were read data error  
 * Rev1.8       :     Add PZEM-003_begin, PZEM-016_begin and ec_modbusRTU_begin for initial set RS485 pin
 * Rev3.0       :     Major change hardware from tiny32_v2.0 to tiny32_v3.0
 *                    Add WTR10_E(SHT20) temperature and humidity sensor (RS485)
 * Rev3.1       :     Add XY-MD02(SHT20) temperature and humidity sensor (RS485)    
 * Rev3.2       :     Add SOIL MOISTURE PR-3000-H-N01 sensor (RS485) fix id = 1, baud rate = 4800  
 * Rev3.3       :     Add RS485 Water Flow Meter RS485 MODBUS output  
 * Rev3.4       :     Add PYR20-Solar Radiation/Pyranometer Sensor, RS485, Modbus   
 * Rev3.5       :     Add tiny32 ModbusRTU communication   
 * Rev3.5.1     :     Fix bug for modbusRTU by relay 300mS after write modbus RTU (complier of some computer problem)  
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@innovation.co.th
 * TEL          :     089-140-7205
 ***********************************************************************/

#ifndef TINY32_H
#define TINY32_H
#include "Ticker.h"


class tiny32_v3
{
private:
#define version_c  "3.5.1"

    /* data */

public:
/**************************************/
/*           GPIO define              */
/**************************************/
#define RXD2    16
#define TXD2    17
#define RXD3    27
#define TXD3    26 
#define SW1     34
#define SW2     35
#define RELAY   25
#define LED_IO4  4
#define LED_IO12  12
#define SLID_SW  36
#define BUZZER  13

tiny32_v3(/* args */);
void Relay(bool state);
void RedLED(bool state);
void BlueLED(bool state);
void BuildinLED(bool state);
void buzzer_beep(int times);
bool Sw1(void);
bool Sw2(void);
bool Slid_sw(void);
void library_version(void);

private:
uint8_t _resolution_bit;
uint16_t crc16_update(uint16_t crc, uint8_t a);


public:
void TickBlueLED(float second);
void TickRedLED(float second);
void TickBuildinLED(float second);
bool PWM_Setup(uint8_t channel, double freq, uint8_t resolution_bit, uint8_t pin);
bool PWM_Drive(uint8_t channel, uint8_t percentage);
uint16_t TimeStamp_minute_encode(uint16_t y, uint8_t m, uint8_t d, uint8_t h, uint8_t mi);
uint16_t TimeStamp_24hr_encode(uint16_t h, uint16_t mi);
void TimeStamp_hour_minute_decode(uint16_t timestemp, uint16_t &h, uint16_t &mi);

private:
uint16_t ec_modbusRTU(uint8_t id);
bool ec_modbusRTU_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);

public:
/* PZEM-016 Modbus RTU AC power meter module */
bool   PZEM_016(uint8_t id, float &volt, float &amp, float &power, uint16_t &engergy, float &freq, float &pf);
float  PZEM_016_Volt(uint8_t id);
float  PZEM_016_Amp(uint8_t id);
float  PZEM_016_Power(uint8_t id);
int16_t  PZEM_016_Energy(uint8_t id);
float  PZEM_016_Freq(uint8_t id);  
float  PZEM_016_PF(uint8_t id);
bool PZEM_016_ResetEnergy(uint8_t id);
int8_t PZEM_016_SetAddress(uint8_t id, uint8_t new_id);
int8_t PZEM_016_SearchAddress(void);
bool PZEM_016_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);



/* PZEM-003 Modbus RTU DC power meter module */
bool   PZEM_003(uint8_t id, float &volt, float &amp, float &power, uint16_t &engergy);
float  PZEM_003_Volt(uint8_t id);
float  PZEM_003_Amp(uint8_t id);
float  PZEM_003_Power(uint8_t id);
int16_t  PZEM_003_Energy(uint8_t id);
bool PZEM_003_ResetEnergy(uint8_t id);
int8_t PZEM_003_SetAddress(uint8_t id, uint8_t new_id);
int8_t PZEM_003_SearchAddress(void);
bool PZEM_003_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);


/* WTR10-E Modbus RTU Temperature and Humidity sensor module */
bool WTR10_E_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
bool WTR10_E(uint8_t id, float &temp, float &humi);
float WTR10_E_tempeature(uint8_t id);
float WTR10_E_humidity(uint8_t id);

/* XY-MD02 Modbus RTU Temperature and Humidity sensor module */
bool XY_MD02_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
bool XY_MD02(uint8_t id, float &temp, float &humi);
float XY_MD02_tempeature(uint8_t id);
float XY_MD02_humidity(uint8_t id);
int8_t XY_MD02_searchAddress(void);
int8_t XY_MD02_SetAddress(uint8_t id, uint8_t new_id);

/* SOIL MOISTURE PR-3000-H-N01 sensor (RS485) module */
bool PR3000_H_N01_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
bool PR3000_H_N01(float &temp, float &humi);
float PR3000_H_N01_tempeature();
float PR3000_H_N01_humidity();

/* RS485 Water Flow Meter RS485 MODBUS output  */
bool WATER_FLOW_METER_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
int8_t WATER_FLOW_METER_searchAddress(void);
int8_t WATER_FLOW_METER_SetAddress(uint8_t id, uint8_t new_id);
float WATER_FLOW_METER_flowrate(uint8_t id);


/* PYR20-Solar Radiation/Pyranometer Sensor, RS485, Modbus */
bool PYR20_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
int8_t PYR20_searchAddress(void);
int8_t PYR20_SetAddress(uint8_t id, uint8_t new_id);
int16_t PYR20_read(uint8_t id);

/* tiny32 ModbusRTU communication*/
bool tiny32_ModbusRTU_begin(uint8_t rx = RXD2, uint8_t tx = TXD2);
int8_t tiny32_ModbusRTU_searchAddress(void);
int8_t tiny32_ModbusRTU_setAddress(uint8_t id, uint8_t new_id);
bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9, float &val10);
bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8, float &val9);
bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7, float &val8);
bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6, float &val7);
bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5, float &val6);
bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4, float &val5);
bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3, float &val4);
bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2, float &val3);
bool tiny32_ModbusRTU(uint8_t id, float &val1, float &val2);
bool tiny32_ModbusRTU(uint8_t id, float &val1);


};
#endif