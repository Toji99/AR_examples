/* Part: SRF08 Ultrasonic Sensor
 * Voltage: 5v
 * Current: 15mA Typical; 3mA Standby
 * Frequency: 40 KHz
 * Range: 3cm-6m
 * Max Analogue Gain: Variable 94 to 1025 in 32 steps
 * Connection: I2C bus
 * Size: 43mm x 20mm x 17mm
 */

 /* Pinout
  * 5v--------------5v
  *     1kohm 1kohm
  * SDA--|--4  |
  * SCL--------|--5
  * Do Not Connect
  * 0v GND----GND
  */

#include <wire.h>
#define srfAddress 0x70                           // Address of the SRF08
#define cmdByte 0x00                              // Command byte
#define lightByte 0x01                            // Byte to read light sensor
#define rangeByte 0x02                            // Byte for start of ranging data
 
byte highByte = 0x00;                             // Stores high byte from ranging
byte lowByte = 0x00;                              // Stored low byte from ranging
 
void setup(){
  Wire.begin();                                   // Waits to make sure everything is powered up before sending or receiving data
  Serial.begin(9600);
  delay(100);
}
 
void loop(){
  int rangeData = getRange();                     // Calls a function to get range
  Serial.print("Range:");
  Serial.print(rangeData);
  Serial.print("\n\n");
 
  int lightData = getLight();                     // Calls a function to get range
  Serial.print("Light:");
  Serial.print(lightData);
  Serial.println();
  delay(70);                                      // Wait before looping
}
 
int getRange(){                                   // This function gets a ranging from the SRF08
 
  int range = 0; 
 
  Wire.beginTransmission(srfAddress);             // Start communticating with SRF08
  Wire.send(cmdByte);                             // Send Command Byte
  Wire.send(0x51);                                // Send 0x51 to start a ranging
  Wire.endTransmission();
 
  delay(100);                                     // Wait for ranging to be complete
 
  Wire.beginTransmission(srfAddress);             // start communicating with SRFmodule
  Wire.send(rangeByte);                           // Call the register for start of ranging data
  Wire.endTransmission();
 
  Wire.requestFrom(srfAddress, 2);                // Request 2 bytes from SRF module
  while(Wire.available() &lt; 2);                    // Wait for data to arrive
  highByte = Wire.receive();                      // Get high byte
  lowByte = Wire.receive();                       // Get low byte
 
  range = (highByte &lt;&lt; 8) + lowByte;              // Put them together
 
  return(range);                                  // Returns Range
}
 
int getLight(){                                   // Function to get light reading
 
  Wire.beginTransmission(srfAddress);
  Wire.send(lightByte);                           // Call register to get light reading
  Wire.endTransmission();
 
  Wire.requestFrom(srfAddress, 1);                // Request 1 byte
  while(Wire.available() &lt; 0);                    // While byte available
  int lightRead = Wire.receive();                 // Get light reading
 
  return(lightRead);                              // Returns lightRead 
}</wire.h>
