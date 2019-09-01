# KidBright_ADS1115

## ADS1115 16-BIT ADC - 4 CHANNEL WITH PROGRAMMABLE GAIN AMPLIFIER
![1085-02](https://cdn-shop.adafruit.com/970x728/1085-02.jpg)

## แก้ไขกำลังขยาย
ไฟล์ i2c_ads1115.cpp<br />
บรรทัดที่ 73<br />
```
    config |= ADS1115_REG_CONFIG_PGA_2_048V;
```

เปลี่ยน
```
    ADS1115_REG_CONFIG_PGA_2_048V
```

เป็น

```
    ADS1115_REG_CONFIG_PGA_6_144V
    ADS1115_REG_CONFIG_PGA_4_096V
    ADS1115_REG_CONFIG_PGA_2_048V
    ADS1115_REG_CONFIG_PGA_1_024V
    ADS1115_REG_CONFIG_PGA_0_512V
    ADS1115_REG_CONFIG_PGA_0_256V
```

โดยที่
```
    ADS1115_REG_CONFIG_PGA_6_144V   +/-6.144V range = Gain 2/3
    ADS1115_REG_CONFIG_PGA_4_096V   +/-4.096V range = Gain 1
    ADS1115_REG_CONFIG_PGA_2_048V   +/-2.048V range = Gain 2 (default)
    ADS1115_REG_CONFIG_PGA_1_024V   +/-1.024V range = Gain 4
    ADS1115_REG_CONFIG_PGA_0_512V   +/-0.512V range = Gain 8
    ADS1115_REG_CONFIG_PGA_0_256V   +/-0.256V range = Gain 16
```
