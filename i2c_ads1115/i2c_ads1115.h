#ifndef __i2c_ads1115_H__
#define __i2c_ads1115_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define ADS1115_POLLING_MS  500

#define Wait_time    1000
/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define ADS1115_ADDRESS_ADDR_GND    (0x48) // address pin low (GND)
#define ADS1115_ADDRESS_ADDR_VDD    (0x49) // address pin high (VCC)
#define ADS1115_ADDRESS_ADDR_SDA    (0x4A) // address pin tied to SDA pin
#define ADS1115_ADDRESS_ADDR_SCL    (0x4B) // address pin tied to SCL pin
/*=========================================================================*/

/*=========================================================================
    CONVERSION DELAY (in mS)
    -----------------------------------------------------------------------*/
    #define ADS1115_CONVERSIONDELAY         (8)
/*=========================================================================*/


/*=========================================================================
    POINTER REGISTER
    -----------------------------------------------------------------------*/
    #define ADS1115_REG_POINTER_CONVERT     (0x00)
    #define ADS1115_REG_POINTER_CONFIG      (0x01)
    #define ADS1115_REG_POINTER_LOWTHRESH   (0x02)
    #define ADS1115_REG_POINTER_HITHRESH    (0x03)

/*=========================================================================
    CONFIG REGISTER
    -----------------------------------------------------------------------*/
	
	//Bit 15 Operational status or single-shot conversion start
	//When writing
    #define ADS1115_REG_CONFIG_OS_NA      (0x0000)	// No Effect
    #define ADS1115_REG_CONFIG_OS_SINGLE    (0x8000)  // Write: Set to start a single-conversion   
	//When reading
    #define ADS1115_REG_CONFIG_OS_BUSY      (0x0000)  // Read: Bit = 0 when conversion is in progress
    #define ADS1115_REG_CONFIG_OS_NOTBUSY   (0x8000)  // Read: Bit = 1 when device is not performing a conversion


	//Bit 14:12 Input multiplexer configuration
    #define ADS1115_REG_CONFIG_MUX_DIFF_0_1 (0x0000)  // Differential P = AIN0, N = AIN1 (default)
    #define ADS1115_REG_CONFIG_MUX_DIFF_0_3 (0x1000)  // Differential P = AIN0, N = AIN3
    #define ADS1115_REG_CONFIG_MUX_DIFF_1_3 (0x2000)  // Differential P = AIN1, N = AIN3
    #define ADS1115_REG_CONFIG_MUX_DIFF_2_3 (0x3000)  // Differential P = AIN2, N = AIN3
    #define ADS1115_REG_CONFIG_MUX_SINGLE_0 (0x4000)  // Single-ended AIN0  
    #define ADS1115_REG_CONFIG_MUX_SINGLE_1 (0x5000)  // Single-ended AIN1  
    #define ADS1115_REG_CONFIG_MUX_SINGLE_2 (0x6000)  // Single-ended AIN2  
    #define ADS1115_REG_CONFIG_MUX_SINGLE_3 (0x7000)  // Single-ended AIN3  

	//Bit 11 : 9 Programmable gain amplifier configuration
    #define ADS1115_REG_CONFIG_PGA_6_144V   (0x0000)  // +/-6.144V range = Gain 2/3
    #define ADS1115_REG_CONFIG_PGA_4_096V   (0x0200)  // +/-4.096V range = Gain 1
    #define ADS1115_REG_CONFIG_PGA_2_048V   (0x0400)  // +/-2.048V range = Gain 2 (default)
    #define ADS1115_REG_CONFIG_PGA_1_024V   (0x0600)  // +/-1.024V range = Gain 4
    #define ADS1115_REG_CONFIG_PGA_0_512V   (0x0800)  // +/-0.512V range = Gain 8
    #define ADS1115_REG_CONFIG_PGA_0_256V   (0x0A00)  // +/-0.256V range = Gain 16

	//Bit 8 Device operating mode
    #define ADS1115_REG_CONFIG_MODE_CONTIN  (0x0000)  // Continuous conversion mode
    #define ADS1115_REG_CONFIG_MODE_SINGLE  (0x0100)  // Power-down single-shot mode (default)

	//Bit 7:5 Data rate
    #define ADS1115_REG_CONFIG_DR_8SPS    (0x0000)  // 8 samples per second
    #define ADS1115_REG_CONFIG_DR_16SPS    (0x0020)  // 16 samples per second
    #define ADS1115_REG_CONFIG_DR_32SPS    (0x0040)  // 32 samples per second
    #define ADS1115_REG_CONFIG_DR_64SPS    (0x0060)  // 64 samples per second
    #define ADS1115_REG_CONFIG_DR_128SPS   (0x0080)  // 128 samples per second (default)
    #define ADS1115_REG_CONFIG_DR_250SPS   (0x00A0)  // 250 samples per second
    #define ADS1115_REG_CONFIG_DR_475SPS   (0x00C0)  // 475 samples per second
    #define ADS1115_REG_CONFIG_DR_860SPS   (0x00E0)  // 860 samples per second
	
	//Bit 4 Comparator mode
    #define ADS1115_REG_CONFIG_CMODE_TRAD   (0x0000)  // Traditional comparator with hysteresis (default)
    #define ADS1115_REG_CONFIG_CMODE_WINDOW (0x0010)  // Window comparator

	//Bit 3 Comparator polarity
    #define ADS1115_REG_CONFIG_CPOL_ACTVLOW (0x0000)  // ALERT/RDY pin is low when active (default)
    #define ADS1115_REG_CONFIG_CPOL_ACTVHI  (0x0008)  // ALERT/RDY pin is high when active

	//Bit 2 Latching comparator
    #define ADS1115_REG_CONFIG_CLAT_NONLAT  (0x0000)  // Non-latching comparator (default)
    #define ADS1115_REG_CONFIG_CLAT_LATCH   (0x0004)  // Latching comparator

	//Bit 1:0 Comparator queue and disable
    #define ADS1115_REG_CONFIG_CQUE_1CONV   (0x0000)  // Assert ALERT/RDY after one conversions
    #define ADS1115_REG_CONFIG_CQUE_2CONV   (0x0001)  // Assert ALERT/RDY after two conversions
    #define ADS1115_REG_CONFIG_CQUE_4CONV   (0x0002)  // Assert ALERT/RDY after four conversions
    #define ADS1115_REG_CONFIG_CQUE_NONE    (0x0003)  // Disable the comparator and put ALERT/RDY in high state (default)
/*=========================================================================*/

class I2C_ADS1115 : public Device {
	private:
		enum {
			 s_detect, s_config, s_read, s_error, s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt;
		double read_value[4];
		uint8_t analog_input;
	//	int channel;
	//	int address;

	public:
		// constructor
		I2C_ADS1115(int bus_ch, int dev_addr);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		// method
		double getValue(int i2c_io);
};

#endif