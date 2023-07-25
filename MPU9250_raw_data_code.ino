#include <Wire.h>

//Magnetometer Registers
#define AK8963_ADDRESS   0x0C
#define AK8963_WHO_AM_I  0x00 // should return 0x48
#define AK8963_INFO      0x01
#define AK8963_ST1       0x02  // data ready status bit 0
#define AK8963_XOUT_L    0x03  // data
#define AK8963_XOUT_H    0x04
#define AK8963_YOUT_L    0x05
#define AK8963_YOUT_H    0x06
#define AK8963_ZOUT_L    0x07
#define AK8963_ZOUT_H    0x08
#define AK8963_ST2       0x09  // Data overflow bit 3 and data read error status bit 2
#define AK8963_CNTL      0x0A  // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define AK8963_ASTC      0x0C  // Self test control
#define AK8963_I2CDIS    0x0F  // I2C disable
#define AK8963_ASAX      0x10  // Fuse ROM x-axis sensitivity adjustment value
#define AK8963_ASAY      0x11  // Fuse ROM y-axis sensitivity adjustment value
#define AK8963_ASAZ      0x12  // Fuse ROM z-axis sensitivity adjustment value

#define SELF_TEST_X_GYRO 0x00                  
#define SELF_TEST_Y_GYRO 0x01                                                                          
#define SELF_TEST_Z_GYRO 0x02

/*#define X_FINE_GAIN      0x03 // [7:0] fine gain
#define Y_FINE_GAIN      0x04
#define Z_FINE_GAIN      0x05
#define XA_OFFSET_H      0x06 // User-defined trim values for accelerometer
#define XA_OFFSET_L_TC   0x07
#define YA_OFFSET_H      0x08
#define YA_OFFSET_L_TC   0x09
#define ZA_OFFSET_H      0x0A
#define ZA_OFFSET_L_TC   0x0B */

#define SELF_TEST_X_ACCEL 0x0D
#define SELF_TEST_Y_ACCEL 0x0E    
#define SELF_TEST_Z_ACCEL 0x0F

#define SELF_TEST_A      0x10

#define XG_OFFSET_H      0x13  // User-defined trim values for gyroscope
#define XG_OFFSET_L      0x14
#define YG_OFFSET_H      0x15
#define YG_OFFSET_L      0x16
#define ZG_OFFSET_H      0x17
#define ZG_OFFSET_L      0x18
#define SMPLRT_DIV       0x19
#define CONFIG           0x1A
#define GYRO_CONFIG      0x1B
#define ACCEL_CONFIG     0x1C
#define ACCEL_CONFIG2    0x1D
#define LP_ACCEL_ODR     0x1E   
#define WOM_THR          0x1F   

#define MOT_DUR          0x20  // Duration counter threshold for motion interrupt generation, 1 kHz rate, LSB = 1 ms
#define ZMOT_THR         0x21  // Zero-motion detection threshold bits [7:0]
#define ZRMOT_DUR        0x22  // Duration counter threshold for zero motion interrupt generation, 16 Hz rate, LSB = 64 ms

#define FIFO_EN          0x23
#define I2C_MST_CTRL     0x24   
#define I2C_SLV0_ADDR    0x25
#define I2C_SLV0_REG     0x26
#define I2C_SLV0_CTRL    0x27
#define I2C_SLV1_ADDR    0x28
#define I2C_SLV1_REG     0x29
#define I2C_SLV1_CTRL    0x2A
#define I2C_SLV2_ADDR    0x2B
#define I2C_SLV2_REG     0x2C
#define I2C_SLV2_CTRL    0x2D
#define I2C_SLV3_ADDR    0x2E
#define I2C_SLV3_REG     0x2F
#define I2C_SLV3_CTRL    0x30
#define I2C_SLV4_ADDR    0x31
#define I2C_SLV4_REG     0x32
#define I2C_SLV4_DO      0x33
#define I2C_SLV4_CTRL    0x34
#define I2C_SLV4_DI      0x35
#define I2C_MST_STATUS   0x36
#define INT_PIN_CFG      0x37
#define INT_ENABLE       0x38
#define DMP_INT_STATUS   0x39  // Check DMP interrupt
#define INT_STATUS       0x3A
#define ACCEL_XOUT_H     0x3B
#define ACCEL_XOUT_L     0x3C
#define ACCEL_YOUT_H     0x3D
#define ACCEL_YOUT_L     0x3E
#define ACCEL_ZOUT_H     0x3F
#define ACCEL_ZOUT_L     0x40
#define TEMP_OUT_H       0x41
#define TEMP_OUT_L       0x42
#define GYRO_XOUT_H      0x43
#define GYRO_XOUT_L      0x44
#define GYRO_YOUT_H      0x45
#define GYRO_YOUT_L      0x46
#define GYRO_ZOUT_H      0x47
#define GYRO_ZOUT_L      0x48
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60
#define MOT_DETECT_STATUS 0x61
#define I2C_SLV0_DO      0x63
#define I2C_SLV1_DO      0x64
#define I2C_SLV2_DO      0x65
#define I2C_SLV3_DO      0x66
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET  0x68
#define MOT_DETECT_CTRL  0x69
#define USER_CTRL        0x6A  // Bit 7 enable DMP, bit 3 reset DMP
#define PWR_MGMT_1       0x6B // Device defaults to the SLEEP mode
#define PWR_MGMT_2       0x6C
#define DMP_BANK         0x6D  // Activates a specific bank in the DMP
#define DMP_RW_PNT       0x6E  // Set read/write pointer to a specific start address in specified DMP bank
#define DMP_REG          0x6F  // Register in DMP from which to read or to which to write
#define DMP_REG_1        0x70
#define DMP_REG_2        0x71 
#define FIFO_COUNTH      0x72
#define FIFO_COUNTL      0x73
#define FIFO_R_W         0x74
#define WHO_AM_I_MPU9250 0x75 // Should return 0x71
#define XA_OFFSET_H      0x77
#define XA_OFFSET_L      0x78
#define YA_OFFSET_H      0x7A
#define YA_OFFSET_L      0x7B
#define ZA_OFFSET_H      0x7D
#define ZA_OFFSET_L      0x7E

// Using the MSENSR-9250 breakout board, ADO is set to 0 
// Seven-bit device address is 110100 for ADO = 0 and 110101 for ADO = 1

#define MPU9250_ADDRESS 0x68  // Device address when ADO = 0
#define AK8963_ADDRESS 0x0C   //  Address of magnetometer

#define AHRS true         // set to false for basic data read
#define SerialDebug true   // set to true to get Serial output for debugging
#define CALIBRATION

// Set initial input parameters
enum Ascale {
  AFS_2G,
  AFS_4G = 0,
  AFS_8G,
  AFS_16G
};

enum Gscale {
  GFS_250DPS,
  GFS_500DPS = 0,
  GFS_1000DPS,
  GFS_2000DPS
};

enum Mscale {
  MFS_14BITS = 0, // 0.6 mG per LSB
  MFS_16BITS      // 0.15 mG per LSB
};

// Specify sensor full scale
uint8_t Gscale = 0; //GFS_500DPS;
uint8_t Ascale = 0; //AFS_4G;
uint8_t Mscale = MFS_16BITS; // Choose either 14-bit or 16-bit magnetometer resolution
uint8_t Mmode = 0x06;        // 2 for 8 Hz, 6 for 100 Hz continuous magnetometer data read

// scale resolutions per LSB for the sensors
float gRes = 500./32767.5*(PI/180.0);
float mRes = 10.*4219./32760.0;
float aRes = 4./32767.5f;

// Pin definitions
int16_t accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
int16_t gyroCount[3];   // Stores the 16-bit signed gyro sensor output
int16_t magCount[3];    // Stores the 16-bit signed magnetometer sensor output
float magCalibration[3] = {0, 0, 0};
float magbias[6] = {0, 0, 0, 0, 0, 0};  // Factory mag calibration and mag bias
float gyroBias[3] = { -310.4, 135.7, 278.0};
float accelBias[6] = {515.0, 279.0, 1500.0, 5.96e-5, 6.26e-5, 6.06e-5};      // Bias corrections for gyro and accelerometer

float ax, ay, az, gx, gy, gz, mx, my, mz; // variables to hold latest sensor data values   
float acc_cal[3] = {0, 0, 0};
int16_t calaX, calaY, calaZ;
float gyro_cal[3] = {0, 0, 0};
int16_t calgX, calgY, calgZ;

uint32_t count = 0;
const unsigned int buttonPin = 7;
const unsigned int ledPin = 3;

int buttonState = 0;
int oldButtonState = LOW;
int ledState = LOW;

void setup()
{
  Wire.begin();
//  TWBR = 12;  // 400 kbit/sec I2C speed
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Read the WHO_AM_I register, this is a good test of communication
  //  identify wwhich decive is being used
  byte c = readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
  // Serial.print("MPU9250 "); Serial.print("I AM "); Serial.print(c, HEX); Serial.print(" I should be "); Serial.println(0x71, HEX);
//  delay(100); 

  if (c == 0x71) // WHO_AM_I should always be 0x68
  {  
    //Serial.println("MPU9250 is online...");
//    delay(100); 
  
    initMPU9250(); 
//    Serial.println("MPU9250 initialized for active data mode...."); // Initialize device for active mode read of acclerometer, gyroscope, and temperature

    // Read the WHO_AM_I register of the magnetometer, this is a good test of communication
    byte d = readByte(AK8963_ADDRESS, AK8963_WHO_AM_I);  // Read WHO_AM_I register for AK8963
    //Serial.print("AK8963 "); Serial.print("I AM "); Serial.print(d, HEX); Serial.print(" I should be "); Serial.println(0x48, HEX);
//    delay(100); 
    
    // Get magnetometer calibration from AK8963 ROM
    initAK8963(magCalibration); // Serial.println("AK8963 initialized for active data mode...."); // Initialize device for active mode read of magnetometer
      
    int8_t rawData[6];
    for (int i=0; i<5000; i++)
    {
        readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
        calaX = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
        calaY = ((int16_t)rawData[2] << 8) | rawData[3] ;  
        calaZ = ((int16_t)rawData[4] << 8) | rawData[5] ; 
        acc_cal[0] += calaX;
        acc_cal[1] += calaY;
        acc_cal[2] += calaZ;
        
        readBytes(MPU9250_ADDRESS,GYRO_XOUT_H , 6, &rawData[0]);  // Read the six raw data registers into data array
        calgX = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
        calgY = ((int16_t)rawData[2] << 8) | rawData[3] ;  
        calgZ = ((int16_t)rawData[4] << 8) | rawData[5] ; 
        gyro_cal[0] += calgX;
        gyro_cal[1] += calgY;
        gyro_cal[2] += calgZ;
    }
    accelBias[0] = (acc_cal[0] / 5000) * aRes * 9.81;
    accelBias[1] = (acc_cal[1] / 5000) * aRes * 9.81;
    accelBias[2] = (acc_cal[2] / 5000) * aRes * 9.81 + 9.81;
    
    gyroBias[0] = gyro_cal[0] / 5000;
    gyroBias[1] = gyro_cal[1] / 5000;
    gyroBias[2] = gyro_cal[2] / 5000;
    /*
    Serial.print("Calibration data  ");
    Serial.print(acc_cal[0] / 1000);
    Serial.print(", ");
    Serial.print(acc_cal[1]/ 1000);
    Serial.print(", ");
    Serial.println(acc_cal[2]/1000);
    
    Serial.print(gyro_cal[0] / 1000);
    Serial.print(", ");
    Serial.print(gyro_cal[1] / 1000);
    Serial.print(", ");
    Serial.println(gyro_cal[2] / 1000);
    */
    #ifdef CALIBRATION
      magcalMPU9250(magbias);
      /*
      Serial.print(magbias[0] );
      Serial.print(", ");
      Serial.print(magbias[1] );
      Serial.print(", ");
      Serial.print(magbias[2] );
      Serial.print(", ");
      Serial.print(magbias[3] );
      Serial.print(", ");
      Serial.print(magbias[4] );
      Serial.print(", ");
      Serial.println(magbias[5] ); 
      Serial.print(magCalibration[0] );
      Serial.print(", ");
      Serial.print(magCalibration[1] );
      Serial.print(", ");
      Serial.println(magCalibration[2] );
      */
    #endif

    #ifndef CALIBRATION
      accelBias[0] = -431;
      accelBias[1] =  -8;
      accelBias[2] = 10943;
      gyroBias[0] = 496; 
      gyroBias[1] = 836; 
      gyroBias[2] = 89;
      magbias[0] = -36.22; 
      magbias[1] = 37.79;
      magbias[2] = 69.19;
      magbias[3] = 2.04;
      magbias[4] = 1.53;
      magbias[5] = 0.54;
      magCalibration[0] = 1.22;
      magCalibration[1] = 1.22;
      magCalibration[2] = 1.17;
    #endif
  }
  else
  {
    Serial.print("Could not connect to MPU9250: 0x");
    Serial.println(c, HEX);
    while(1) ; // Loop forever if communication doesn't happen
  }
}

void loop()
{  
  // If intPin goes high, all data registers have new data
  if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {  // On interrupt, check if data ready interrupt
    readAccelData(accelCount);  // Read the x/y/z adc values
    
    // Now we'll calculate the accleration value into actual g's
    ax = ((float)accelCount[0] * aRes * 9.81 - accelBias[0]);   // * accelBias[3];  // get actual g value, this depends on scale being set
    ay = ((float)accelCount[1] * aRes * 9.81 - accelBias[1]);   // * accelBias[4];   
    az = ((float)accelCount[2] * aRes * 9.81 - accelBias[2]);   // * accelBias[5];  
   
    readGyroData(gyroCount);  // Read the x/y/z adc values

    // Calculate the gyro value into actual degrees per second
    gx = ((float)gyroCount[0] - gyroBias[0]) * gRes;  // get actual gyro value, this depends on scale being set
    gy = ((float)gyroCount[1] - gyroBias[1]) * gRes;  
    gz = ((float)gyroCount[2] - gyroBias[2]) * gRes;   
  
    readMagData(magCount);  // Read the x/y/z adc values

    // Calculate the magnetometer values in milliGauss
    // Include factory calibration per data sheet and user environmental corrections
    mx = ((float)magCount[0] * mRes * magCalibration[0] - magbias[0]) * magbias[3];  // get actual magnetometer value, this depends on scale being set
    my = ((float)magCount[1] * mRes * magCalibration[1] - magbias[1]) * magbias[4];
    mz = ((float)magCount[2] * mRes * magCalibration[2] - magbias[2]) * magbias[5];
    int event = 0;

    Serial.print(ax,6);
    Serial.print("|");
    Serial.print(ay,6);
    Serial.print("|");
    Serial.print(az,6);
    Serial.print("|");
    Serial.print(gx,6);
    Serial.print("|");
    Serial.print(gy,6);
    Serial.print("|");
    Serial.print(gz,6);
    Serial.print("|");
    Serial.print(mx,6);
    Serial.print("|");
    Serial.print(my,6);
    Serial.print("|");
    Serial.print(mz,6);
    Serial.print("|");
    Serial.println(event);
//    Serial.print("|");
  }
 
  delay(25);// delay in ms
  button();
}

void button()
{
  
   buttonState = digitalRead(buttonPin);
  if (buttonState != oldButtonState &&
      buttonState == LOW)
  {
    ledState = (ledState == LOW ? HIGH : LOW);
    digitalWrite(ledPin, ledState);
//    delay(50);
  }
  oldButtonState = buttonState;
  
 if (ledState == HIGH){
     int event = 1;
//     Serial.println(event);
      }
  else if (ledState == LOW){
        int event = 0;
//        Serial.println(event);
      }
  }

//===================================================================================================================
//====== Set of useful function to access acceleration. gyroscope, and magnetometer data
//===================================================================================================================

void readAccelData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z accel register data stored here
  
  readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
  destination[0] = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int16_t)rawData[2] << 8) | rawData[3] ;  
  destination[2] = ((int16_t)rawData[4] << 8) | rawData[5] ; 
}

void readGyroData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z gyro register data stored here
  readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int16_t)rawData[2] << 8) | rawData[3] ;  
  destination[2] = ((int16_t)rawData[4] << 8) | rawData[5] ; 
}

void readMagData(int16_t * destination)
{
  uint8_t rawData[7];  // x/y/z gyro register data, ST2 register stored here, must read ST2 at end of data acquisition
  //read mag
  writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x02); //set i2c bypass enable pin to true to access magnetometer
  delay(5);
  writeByte(AK8963_ADDRESS, 0x0A, 0x01); //enable the magnetometer
  delay(5);
  if(readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01) { // wait for magnetometer data ready bit to be set
  readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 6, &rawData[0]);  // Read the six raw data and ST2 registers sequentially into data array
  uint8_t c = rawData[6]; // End data read by reading ST2 register
    //if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
    destination[0] = ((int16_t)rawData[1] << 8) | rawData[0] ;  // Turn the MSB and LSB into a signed 16-bit value
    destination[1] = ((int16_t)rawData[3] << 8) | rawData[2] ;  // Data stored as little Endian
    destination[2] = ((int16_t)rawData[5] << 8) | rawData[4] ; 
   //}
  }
}

void initAK8963(float * destination)
{
  // First extract the factory calibration for each magnetometer axis
  uint8_t rawData[3];  // x/y/z gyro calibration data stored here
  writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer  
  delay(5);
  writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
  delay(5);
  readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);  // Read the x-, y-, and z-axis calibration values
  destination[0] =  (float)(rawData[0] - 128)/256. + 1.;   // Return x-axis sensitivity adjustment values, etc.
  destination[1] =  (float)(rawData[1] - 128)/256. + 1.;  
  destination[2] =  (float)(rawData[2] - 128)/256. + 1.; 
  writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer  
  delay(5);
  // Configure the magnetometer for continuous read and highest resolution
  // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
  // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
  writeByte(AK8963_ADDRESS, AK8963_CNTL, Mscale << 4 | Mmode); // Set magnetometer data resolution and sample ODR
  delay(5);
}

//mag calibration
 void magcalMPU9250(float * dest1) 
 {
 uint16_t ii = 0, sample_count = 0;
 int32_t mag_bias[3] = {0, 0, 0}, mag_scale[3] = {0, 0, 0};
 int16_t mag_max[10] = {-32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767, -32767};
 int16_t mag_min[10] = {32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767}, mag_temp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Serial.println("Mag Calibration: Wave device in a figure eight until done!");
 delay(5);

// shoot for ~fifteen seconds of mag data
if(Mmode == 0x02) sample_count = 80;  // at 8 Hz ODR, new mag data is available every 125 ms
if(Mmode == 0x06) sample_count = 1000;  // at 100 Hz ODR, new mag data is available every 10 ms
for(ii = 0; ii < sample_count; ii++) {
  readMagData(mag_temp);  // Read the mag data   
  for (int jj = 0; jj < 10; jj++) {
    if(mag_temp[jj] > mag_max[jj]) mag_max[jj] = mag_temp[jj];
    if(mag_temp[jj] < mag_min[jj]) mag_min[jj] = mag_temp[jj];
}
if(Mmode == 0x02) delay(135);  // at 8 Hz ODR, new mag data is available every 125 ms
if(Mmode == 0x06) delay(12);  // at 100 Hz ODR, new mag data is available every 10 ms
}

// Get hard iron correction
 mag_bias[0]  = (mag_max[0] + mag_min[0])/2;  // get average x mag bias in counts
 mag_bias[1]  = (mag_max[1] + mag_min[1])/2;  // get average y mag bias in counts
 mag_bias[2]  = (mag_max[2] + mag_min[2])/2;  // get average z mag bias in counts

 dest1[0] = (float) mag_bias[0]*mRes*magCalibration[0];  // save mag biases in G for main program
 dest1[1] = (float) mag_bias[1]*mRes*magCalibration[1];   
 dest1[2] = (float) mag_bias[2]*mRes*magCalibration[2];  
   
// Get soft iron correction estimate
 mag_scale[0]  = (mag_max[0] - mag_min[0])/2;  // get average x axis max chord length in counts
 mag_scale[1]  = (mag_max[1] - mag_min[1])/2;  // get average y axis max chord length in counts
 mag_scale[2]  = (mag_max[2] - mag_min[2])/2;  // get average z axis max chord length in counts

 float avg_rad = mag_scale[0] + mag_scale[1] + mag_scale[2];
 avg_rad /= 3.0;

 dest1[3] = avg_rad/((float)mag_scale[0]);
 dest1[4] = avg_rad/((float)mag_scale[1]);
 dest1[5] = avg_rad/((float)mag_scale[2]);

// Serial.println("Mag Calibration done!");
 delay(5);
 }

void initMPU9250()
{  
 // wake up device
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80);
  delay(5);
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors 
  delay(5); // Wait for all registers to reset 

 // get stable time source
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);  // Auto select clock source to be PLL gyroscope reference if ready else
  delay(5); 
  
 // Configure Gyro and Thermometer
 // Disable FSYNC and set thermometer and gyro bandwidth to 41 and 42 Hz, respectively; 
 // minimum delay time for this setting is 5.9 ms, which means sensor fusion update rates cannot
 // be higher than 1 / 0.0059 = 170 Hz
 // DLPF_CFG = bits 2:0 = 011; this limits the sample rate to 1000 Hz for both
 // With the MPU9250, it is possible to get gyro sample rates of 32 kHz (!), 8 kHz, or 1 kHz
 // here we have Fs = 1KHz
  writeByte(MPU9250_ADDRESS, CONFIG, 0x03);  

 // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
 // Use a 200 Hz rate; a rate consistent with the filter update rate
 // determined inset in CONFIG above
 writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x04);   
                                   
 // Set gyroscope full scale range
 // Range selects FS_SEL and GFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
  uint8_t c = readByte(MPU9250_ADDRESS, GYRO_CONFIG); // get current GYRO_CONFIG register value
 // c = c & ~0xE0; // Clear self-test bits [7:5] 
  c = c & ~0x03; // Clear Fchoice bits [1:0] 
  c = c & ~0x18; // Clear GFS bits [4:3]
  c = c | Gscale << 3; // Set full scale range for the gyro
 // c =| 0x00; // Set Fchoice for the gyro to 11 by writing its inverse to bits 1:0 of GYRO_CONFIG
  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c ); // Write new GYRO_CONFIG value to register
  
 // Set accelerometer full-scale range configuration
  c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG); // get current ACCEL_CONFIG register value
 // c = c & ~0xE0; // Clear self-test bits [7:5] 
  c = c & ~0x18;  // Clear AFS bits [4:3]
  c = c | Ascale << 3; // Set full scale range for the accelerometer 
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c); // Write new ACCEL_CONFIG register value

 // Set accelerometer sample rate configuration
 // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
 // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
  c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG2); // get current ACCEL_CONFIG2 register value
  c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])  
  c = c | 0x0B;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, c); // Write new ACCEL_CONFIG2 register value
 // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates, 
 // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

  // Configure Interrupts and Bypass Enable
  // Set interrupt pin active high, push-pull, hold interrupt pin level HIGH until interrupt cleared,
  // clear on read of INT_STATUS, and enable I2C_BYPASS_EN so additional chips 
  // can join the I2C bus and all can be controlled by the Arduino as master
   writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x22);    
   writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
   delay(5);
}
       
// Wire.h read and write protocols
void writeByte(uint8_t address, uint8_t subAddress, uint8_t data)
  {
    Wire.beginTransmission(address);  // Initialize the Tx buffer
    Wire.write(subAddress);           // Put slave register address in Tx buffer
    Wire.write(data);                 // Put data in Tx buffer
    Wire.endTransmission();           // Send the Tx buffer
  }

uint8_t readByte(uint8_t address, uint8_t subAddress)
  {
    uint8_t data; // `data` will store the register data   
    Wire.beginTransmission(address);         // Initialize the Tx buffer
    Wire.write(subAddress);                  // Put slave register address in Tx buffer
    Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
    Wire.requestFrom(address, (uint8_t) 1);  // Read one byte from slave register address 
    data = Wire.read();                      // Fill Rx buffer with result
    return data;                             // Return data read from slave register
  }

void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
  {  
    Wire.beginTransmission(address);   // Initialize the Tx buffer
    Wire.write(subAddress);            // Put slave register address in Tx buffer
    Wire.endTransmission(false);       // Send the Tx buffer, but send a restart to keep connection alive
    uint8_t i = 0;
    Wire.requestFrom(address, count);  // Read bytes from slave register address 
    while (Wire.available()) {
          dest[i++] = Wire.read(); }   // Put read results in the Rx buffer
  }
