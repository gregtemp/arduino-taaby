// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SimpleRotary.h>

// Pin A, Pin B, Button Pin
SimpleRotary rotary(0,1,7);
SimpleRotary rotary2(2,3,7);
int cw = 100;
int cw2 = 100;
int bo, bn = 0;
byte bstate = false;

int counter = 0;

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("");

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, INPUT_PULLDOWN);
  setRGB(0, 0, 0);
  delay(100);
}

void loop() {
  counter ++;
  /* Get new sensor events with the readings */
  
  if (counter % 100 == 0) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    int sense[7];
    sense[0] = (int)(a.acceleration.x * 100.);
    sense[1] = (int)(a.acceleration.y * 100.);
    sense[2] = (int)(a.acceleration.z * 100.);
    sense[3] = (int)(a.gyro.x*100.);
    sense[4] = (int)(a.gyro.y*100.);
    sense[5] = (int)(a.gyro.z*100.);
    sense[6] = (int)(temp.temperature*10.);
    if (bstate == 1) {
      for (int xy = 0; xy < 7; xy++){
        Serial.print(sense[xy]);
        Serial.print(" ");
      }
      Serial.println("");
      setRGB(255, 0, 0);
    }
  }

  if (counter >= 10000) counter = 0;
  /* Print out the values */
  if (bstate == 1){
    //setRGB(255, 0, 0);  
    }
  else if (bstate == 0) {
    //setRGB(0, 255, 0);
    }

  byte i, i2;
  int bn = analogRead(6) >900;
  if (bn != bo){
    bo = bn;
    if (bn ==1 ) {
      bstate = !bstate;
      Serial.println(bstate);
    }
    
  }

  // get direction
  i = rotary.rotate();
  i2 = rotary2.rotate();
  
  if ( i == 1 ) {
    Serial.print("CW ");
    cw++;
    Serial.println(cw);
    setRGB(0, (cw%127), (cw%127));
  }
  if ( i == 2 ) {
    Serial.print("CCW");
    cw--;
    Serial.println(cw);
    setRGB(0,(cw%127),(cw%127) );
  }

  if ( i2 == 1 ) {
    Serial.print("CW2 ");
    cw2++;
    Serial.println(cw2);
    setRGB((cw2%127), 0, (cw2%127));
  }
  if ( i2 == 2 ) {
    Serial.print("CCW2");
    cw2--;
    Serial.println(cw2);
    setRGB((cw2%127), 0, (cw2%127));
  }

  //delay(10);
}


void setRGB(int r, int g, int b) {
  analogWrite(9, 255-r);
  analogWrite(10, 255-g);
  analogWrite(8, 255-b);
}
