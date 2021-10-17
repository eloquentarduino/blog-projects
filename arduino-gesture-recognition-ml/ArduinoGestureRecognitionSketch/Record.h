#include "IMU.h"


bool isRecording = false;
float ax = 0, ay = 0, az = 0;
float gx = 0, gy = 0, gz = 0;


void setup() {
  Serial.begin(115200);
  delay(3000);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1) delay(1000);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");

  Serial.print("Gyroscope sample rate = ");  
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println("Hz");
  
  Serial.println("Send 'record' to start recording, anything else to stop");
  delay(3000);
}


void loop() {
  // await for serial commands
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    Serial.print("Command: ");
    Serial.println(command);

    // if user sent "record", start recording
    if (command.equals("record")) {
      Serial.println("Start recording...");
      isRecording = true;
    }
    // otherwise stop recording
    else {
      Serial.println("Stop recording...");
      isRecording = false;
    }
  }

  if (!isRecording)
    return;


  // await for IMU
  if (!isIMUReady())
    return;

  readIMU(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print(ax);
  Serial.print(',');
  Serial.print(ay);
  Serial.print(',');
  Serial.print(az);
  Serial.print(',');
  Serial.print(gx);
  Serial.print(',');
  Serial.print(gy);
  Serial.print(',');
  Serial.print(gz);
  Serial.print('\n');
}
