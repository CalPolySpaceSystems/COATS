/* Each struct requires an ID at the start 
 * ID designations should be as follows:
 * AD7606 : 5
 * A3G5250D : N/A
 * MS5611: 4
 * UBLOX-M8N: 2
 * LSM9DS1: 3
 * RTC : 1
 */ 

/* Analog Devices AD7606 16-bit ADC (pressure board) */
struct ad7606_adc {
    uint8_t id; // 5
    uint16_t ch1;
    uint16_t ch2;
    uint16_t ch3;
    uint16_t ch4;
    uint16_t ch5;
    uint16_t ch6;
}__attribute__((packed));


/* STM A3G5250D 3-axis gyro */
struct a3g4250d_gyro {
    uint8_t id; //?
    float x;
    float y;
    float z;
}__attribute__((packed));

/* MS5611 barometric pressure sensor */
struct ms5611 {
    uint8_t id; // 4
    float temp;
    float pressure;
    float altitude;
}__attribute__((packed));

/* Ublox M8N GPS */
struct ubloxM8N {
    uint8_t id; // 2
    float time;
    float latitude;
    float longitude;
}__attribute__((packed));

/* LSM9DS1 9-axis mems device */
struct lsm9ds1 {
    uint8_t id; // 3
    float temp;
    float acc_x;
    float acc_y;
    float acc_z;
    float gyro_x;
    float gyro_y;
    float gyor_z;
    float mag_x;
    float mag_y;
    float mag_z;
}__attribute__((packed));

/* RTC */
struct rtc_data {
    uint8_t id; // 1
    uint16_t rtc_val;
}__attribute__((packed));
