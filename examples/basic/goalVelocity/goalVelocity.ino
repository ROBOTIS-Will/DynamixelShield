#include <DynamixelShield.h>

#ifdef ARDUINO_AVR_UNO
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(10, 11); //RX,TX
  #define DEBUG_SERIAL soft_serial
#elif ARDUINO_AVR_MEGA2560
  #define DEBUG_SERIAL Serial1
#else
  #define DEBUG_SERIAL Serial
#endif

const uint8_t DXL_ID = 1;
float value;

DynamixelShield dxl;

void setup() {
  // put your setup code here, to run once:
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(2.0);
  dxl.ping(DXL_ID);

  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_VELOCITY);
  dxl.torqueOn(DXL_ID);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Set data to write
  if(value >= 500){
    value = 0;
  }else{
    value += 10;
  }

  //Set goalPosition
  dxl.setGoalVelocity(DXL_ID, value);
  //Print present position
  DEBUG_SERIAL.println(dxl.getPresentVelocity(DXL_ID));
  
  delay(500);
}
