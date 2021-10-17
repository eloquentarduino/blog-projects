#include "IMU.h"
#include "Window.h"
#include "Classifier.h"


float ax = 0, ay = 0, az = 0;
float gx = 0, gy = 0, gz = 0;

Window window;
Eloquent::ML::Port::Classifier clf;


void setup() {
  Serial.begin(115200);
  delay(3000);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1) delay(1000);
  }
  
  delay(3000);

}

void loop() {
  if (!isIMUReady())
    return;

  readIMU(&ax, &ay, &az, &gx, &gy, &gz);

  float sample[] = {ax, ay, az, gx, gy, gz};

  // if gesture started, feed the window to make a prediction
  if (!window.transform(sample))
      return;
  
  Serial.print("Gesture: ");
  Serial.println(clf.predictLabel(window.features));
}
