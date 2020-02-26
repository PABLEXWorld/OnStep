// -----------------------------------------------------------------------------------------------------------------------------
// Weather related functions

#pragma once

#if WEATHER != OFF
  #include <Adafruit_BME280.h>            // https://github.com/adafruit/Adafruit_BME280_Library/tree/156a0537d6b21aaab1d1f104a7001a38ca1ffce3
                                          // and https://github.com/adafruit/Adafruit_Sensor
  #if WEATHER == BME280 || WEATHER == BME280_0x76
    Adafruit_BME280 bme;
  #elif WEATHER == BME280_SPI
    Adafruit_BME280 bme(BME280_CS_PIN);                                   // hardware SPI
  //Adafruit_BME280 bme(BME280_CS_PIN, SSPI_MOSI, SSPI_MISO, SSPI_SCK);   // software SPI
  #endif
#endif

#ifdef ONEWIRE_DEVICES_PRESENT
  #include <OneWire.h>                    // added via built in Arduino IDE library manager
  #include <DallasTemperature.h>          // added via built in Arduino IDE library manager
  OneWire oneWire(OneWirePin);
  DallasTemperature DS18B20(&oneWire);
#endif

class weather {
  public:
    bool init() {
      bool success = true;
#ifdef ONEWIRE_DEVICES_PRESENT
      _DS1820_found = true;
#endif
#if WEATHER != OFF
  #if WEATHER == BME280
      if (bme.begin(&HAL_Wire)) _BME280_found = true; else success = false;
  #elif WEATHER == BME280_0x76
      if (bme.begin(0x76, &HAL_Wire)) _BME280_found = true; else success = false;
  #else
      if (bme.begin()) _BME280_found = true; else success = false;
  #endif
  #if defined(ESP32) & defined(WIRE_END_SUPPORT)
      HAL_Wire.end();
  #endif
#endif
      return success;
    }

    // designed for a 1s polling interval to refresh readings once a minute
    void poll() {
#if WEATHER != OFF || defined(ONEWIRE_DEVICES_PRESENT)
      if (_DS1820_found || _BME280_found) {
        static int phase = 0;

  #if WEATHER != OFF
        if (_BME280_found) {
    #ifdef ESP32
          if (phase == 3 || phase == 6 || phase == 9) HAL_Wire.begin();
    #endif
          if (phase == 3) {
            _t = bme.readTemperature();
    #if TELESCOPE_TEMPERATURE == OFF
            _tt = _t;
    #endif
          }
          if (phase == 6) _p = bme.readPressure() / 100.0;
          if (phase == 9) _h = bme.readHumidity();
    #if defined(ESP32) & defined(WIRE_END_SUPPORT)
          if (phase == 3 || phase == 6 || phase == 9) HAL_Wire.end();
    #endif
        }
  #endif

  #ifdef ONEWIRE_DEVICES_PRESENT
        if (_DS1820_found) {
          if (phase == 12) _nbDS1820 = DS18B20.getDeviceCount();
          if (phase == 15) DS18B20.requestTemperatures();
    #if TELESCOPE_TEMPERATURE != OFF
          if (phase == 18) {
          _tt = DS18B20.getTempCByIndex(TELESCOPE_TEMPERATURE);
      #if WEATHER == OFF
          _t = _tt;
      #endif
          }
    #endif
    #if DEW_HEATER1_TEMPERATURE != OFF
          if (phase == 21) _tds[0] = DS18B20.getTempCByIndex(DEW_HEATER1_TEMPERATURE);
    #endif
    #if DEW_HEATER2_TEMPERATURE != OFF
          if (phase == 24) _tds[1] = DS18B20.getTempCByIndex(DEW_HEATER2_TEMPERATURE);
    #endif
    #if DEW_HEATER3_TEMPERATURE != OFF
          if (phase == 27) _tds[2] = DS18B20.getTempCByIndex(DEW_HEATER3_TEMPERATURE);
    #endif
    
        }
  #endif
        phase++; if (phase == 30) phase = 0;
      }
#endif
    }
    
    // get temperature in deg. C
    double getTemperature() {
      return _t;
    }
    
    // get telescope temperature in deg. C
    double getTelescopeTemperature() {
      return _tt;
    }
    
    // get DS1820 temperature in deg. C
    double getDS1820Temperature(int ds) {
      return _tds[ds];
    }
    
    // set temperature in deg. C
    void setTemperature(double t) {
      _t = t;
    }
    
    // get barometric pressure in hPa/mb
    double getPressure() {
      return _p;
    }
    
    // get barometric pressure in hPa/mb
    void setPressure(double p) {
      _p = p;
    }
    
    // get relative humidity in %
    double getHumidity() {
      return _h;
    }
    
    // set relative humidity in %
    void setHumidity(double h) {
      _h = h;
    }
    
    // get altitude in meters
    double getAltitude() {
      return _a;
    }
    
    // set altitude in meters
    void setAltitude(double a) {
      _a = a;
    }
    
    // get dew point in deg. C
    // accurate to +/- 1 deg. C for RH above 50%
    double getDewPoint() {
      return _t - ((100.0 - _h) / 5.0);
      // a more accurate formula?
      // return 243.04*(log(_h/100.0)+((17.625*_t)/(243.04+_t)))/(17.625-log(_h/100.0)-((17.625*_t)/(243.04+_t)));
    }

  private:
    bool _DS1820_found = false;
    bool _BME280_found = false;
    double _t = 10.0;
    double _p = 1010.0;
    double _h = 70.0;
    double _a = 200.0;
    int    _nbDS1820 = 0;
    double _tt = 10.0;
    double _tds[3] = {10.0, 10.0, 10.0};
};
