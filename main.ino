/******************************************************************************
  MinimalistExample.ino

  Marshall Taylor @ SparkFun Electronics
  May 20, 2015
  https://github.com/sparkfun/LSM6DS3_Breakout
  https://github.com/sparkfun/SparkFun_LSM6DS3_Arduino_Library

  Description:
  Most basic example of use.

  Example using the LSM6DS3 with basic settings.  This sketch collects Gyro and
  Accelerometer data every second, then presents it on the serial monitor.

  Resources:
  Uses Wire.h for i2c operation
  Uses SPI.h for SPI operation
  Either can be omitted if not used

  Development environment specifics:
  Arduino IDE 1.8.5

  Hardware connections: (esp32)
  Connect I2C SDA line to D21
  Connect I2C SCL line to D22
  Connect GND and 3.3v power to the IMU

  This code is released under the [MIT License](http://opensource.org/licenses/MIT).

  Please review the LICENSE.md file included with this example. If you have any questions
  or concerns with licensing, please contact techsupport@sparkfun.com.

  Distributed as-is; no warranty is given.

  26 avril 2019
  Test gyroscopes pour analyse ML et Tableau

  23 mai 2019
  Test mqtt data publishing

  11 juin 2019
  Portage de arduino vers esp32
  Creation d'un filter pour n'envoyer que les positions

******************************************************************************/
#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "SPI.h"

#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid     = "ssid";
const char* password = "password";
const char* mqtt_server = "192.168.0.1";

WiFiClient espClient;
PubSubClient client(espClient);
void setup_wifi() {
  // Connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect() {
  // Loop until we're reconnected
  Serial.println("In reconnect...");
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Arduino_Accelerometer")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
LSM6DS3 myIMU; //Default constructor is I2C, addr 0x6B
//LSM6DS3 myIMU( SPI_MODE, 10 );
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000); //relax...
  Serial.println("Processor came out of reset.\n");

  //Call .begin() to configure the IMU
  myIMU.begin();
  //setup_wifi();
  //client.setServer(mqtt_server, 1883);

}


void loop()
{
  char msg[30];

  float fx,fy,fz;
  fx = myIMU.readFloatGyroX();
  fy = myIMU.readFloatGyroY();
  fz = myIMU.readFloatGyroZ();

  if(fy < fx || fy < fz){
    Serial.println("Debout");
  }else{
    Serial.println("Couche");
  }

  delay(2000);
}

