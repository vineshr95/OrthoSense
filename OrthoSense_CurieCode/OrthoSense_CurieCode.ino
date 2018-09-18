/*
OrthoSense: OrthoSense is a wearable multi-sensory knee sleeve to monitor the progression of Osteoarthritis.
For Joint Angle measurement the Eeonyx piezo resistive sensor was used, The IMU on the board is also used.
Connections: 
Connect one terminal of eeonyx to 5V and the other to A0, Connect a 6.8kohm resistor and 2.2uF filter cap between A0 and Gnd

  
DISCLAIMER **While I aim to make this more safe, accurate it this is experimental software (and pre-beta) at that.
It is not suitable for any particular purpose. No life-critical devices should be based on this software.**
Work by Vignesh Ravichandran (hello@rvignesh.xyz)
*/
#define BLYNK_USE_DIRECT_CONNECT
#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>

#include "CurieIMU.h"
int ax, ay, az;         // accelerometer values
int gx, gy, gz;         // gyrometer values

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";
BLEPeripheral  blePeripheral;
uint32_t tsLastReport = 0;


void setup() {

        blePeripheral.setLocalName("OrthoSense");
        blePeripheral.setDeviceName("Ortho1");
        blePeripheral.setAppearance(384); 
        Blynk.begin(auth, blePeripheral);
        blePeripheral.begin();
        CurieIMU.begin();
        analogReadResolution(12);
        
}


void loop() {
  Blynk.run();
  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

 if (millis() - tsLastReport > 200) {
   int sensorValue = analogRead(A0);  //Read eeonyx sensor value
   Blynk.virtualWrite(V0,ax); //X-axis accel
   Blynk.virtualWrite(V1,ay); //Y-axis accel
   Blynk.virtualWrite(V2,gx); //X-axis gyro
   Blynk.virtualWrite(V3,gy); //X-axis gyro 
   Blynk.virtualWrite(V4,sensorValue);  //Raw joint strain value
   tsLastReport = millis();
    }
     blePeripheral.poll();

}
