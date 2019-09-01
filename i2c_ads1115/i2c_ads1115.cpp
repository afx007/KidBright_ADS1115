#ifndef __i2c_ads1115_CPP__
#define __i2c_ads1115_CPP__


#include "i2c_ads1115.h"
#include "esp_system.h"
#include "kidbright32.h"
#include <stdio.h>
#include <string.h>

I2C_ADS1115::I2C_ADS1115(int bus_ch, int dev_addr) {
  channel = bus_ch;
  address = dev_addr;
  polling_ms = ADS1115_POLLING_MS;
}

void I2C_ADS1115::init(void) {
  analog_input = 0;
  for (int i = 0; i < 4; i++) {
    read_value[i] = 0;
  }
  state = s_detect;
  
}

int I2C_ADS1115::prop_count(void) {
  // not supported
  return 0;
}

bool I2C_ADS1115::prop_name(int index, char *name) {
  // not supported
  return false;
}

bool I2C_ADS1115::prop_unit(int index, char *unit) {
  // not supported
  return false;
}

bool I2C_ADS1115::prop_attr(int index, char *attr) {
  // not supported
  return false;
}

bool I2C_ADS1115::prop_read(int index, char *value) {
  // not supported
  return false;
}

bool I2C_ADS1115::prop_write(int index, char *value) {
  // not supported
  return false;
}

void I2C_ADS1115::process(Driver *drv) {
  I2CDev *i2c = (I2CDev *)drv;

  uint8_t data[6];

  switch (state) {
  case s_detect:
    polling_tickcnt = get_tickcnt();
    if (i2c->detect(channel, address) == ESP_OK) {
      state = s_config;
    } else {
      state = s_error;
    }
    break;
  case s_config:
    uint16_t config;
    config = ADS1115_REG_CONFIG_OS_SINGLE;
    config |= ADS1115_REG_CONFIG_PGA_2_048V;
    config |= ADS1115_REG_CONFIG_MODE_SINGLE;
    config |= ADS1115_REG_CONFIG_DR_128SPS;
    config |= ADS1115_REG_CONFIG_CMODE_TRAD;
    config |= ADS1115_REG_CONFIG_CPOL_ACTVLOW;
    config |= ADS1115_REG_CONFIG_CLAT_NONLAT;
    config |= ADS1115_REG_CONFIG_CQUE_NONE;

    if (analog_input == 0) {
      config |= ADS1115_REG_CONFIG_MUX_SINGLE_0;
    } else if (analog_input == 1) {
      config |= ADS1115_REG_CONFIG_MUX_SINGLE_1;
    } else if (analog_input == 2) {
      config |= ADS1115_REG_CONFIG_MUX_SINGLE_2;
    } else if (analog_input == 3) {
      config |= ADS1115_REG_CONFIG_MUX_SINGLE_3;
    }
    if (is_tickcnt_elapsed(tickcnt, 20)) {
      data[0] = ADS1115_REG_POINTER_CONFIG;
      data[1] = config >> 8;   // High Bit in Config
      data[2] = config & 0xff; // Low Bit in Config
      if (i2c->write(channel, address, data, 3) == ESP_OK) {
        state = s_read;
      } else {
        state = s_error;
      }
    }
    break;
  case s_read:
    if (is_tickcnt_elapsed(tickcnt, 20)) {
      data[0] = ADS1115_REG_POINTER_CONVERT;
      if (i2c->write(channel, address, data, 1) == ESP_OK) {
        if (i2c->read(channel, address, NULL, 0, data, 2) == ESP_OK) {
          uint16_t newresult = (data[0] << 8) | data[1];
          read_value[analog_input] = newresult;
          if (analog_input < 3) {
            analog_input++;
            state = s_config;
          } else {
            initialized = true;
            state = s_wait;
          }
        } else {
          state = s_error;
        }
      } else {
        state = s_error;
      }
    }
    break;
  case s_error:

    error = true;
    initialized = false;
    tickcnt = get_tickcnt();
    state = s_wait;
    break;
  case s_wait:

    if (is_tickcnt_elapsed(tickcnt, 200)) {
      state = s_detect;
    }
    break;
  }
}

double I2C_ADS1115::getValue(int i2c_io) {
  analog_input = i2c_io;
  return read_value[i2c_io];
}

#endif