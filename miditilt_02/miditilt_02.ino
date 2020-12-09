// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SimpleRotary.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, INPUT_PULLDOWN);
  setRGB(0, 0, 0);
  delay(100);

  display.clearDisplay();
} 


void loop() {
  counter ++;
  /* Get new sensor events with the readings */
  
  if (counter % 1000 == 0) {
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
      display.clearDisplay();
      display.setTextSize(1.5);      // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE); // Draw white text
        
      for (int xy = 0; xy < 7; xy++){
        display.setCursor((xy%3)*40, (xy/3)*10);
        Serial.print(sense[xy]);
        Serial.print(" ");
        display.print((sense[xy])); display.print(F(" "));
        if (xy%3==2) display.println(F(" "));
      }
      display.display();
      Serial.println("");
      setRGB(255, 0, 0);
    }
    if (bstate == 0){
//      display.clearDisplay();
//      display.setTextSize(1);      // Normal 1:1 pixel scale
//      display.setTextColor(SSD1306_WHITE); // Draw white text
//      display.print(F("All good!"));
//      display.display();
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
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);      // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE); // Draw white text
      display.print(F("All good!"));
      display.display();
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
    showKnob(cw, cw2);
    
  }
  if ( i == 2 ) {
    Serial.print("CCW");
    cw--;
    Serial.println(cw);
    setRGB(0,(cw%127),(cw%127) );
    showKnob(cw, cw2);
  }

  if ( i2 == 1 ) {
    Serial.print("CW2 ");
    cw2++;
    Serial.println(cw2);
    setRGB((cw2%127), 0, (cw2%127));
    showKnob(cw, cw2);
  }
  if ( i2 == 2 ) {
    Serial.print("CCW2");
    cw2--;
    Serial.println(cw2);
    setRGB((cw2%127), 0, (cw2%127));
    showKnob(cw, cw2);
  }

  //delay(10);
}


void setRGB(int r, int g, int b) {
  analogWrite(9, 255-r);
  analogWrite(10, 255-g);
  analogWrite(8, 255-b);
}

void showKnob(int k1, int k2){
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(20, 0);
    display.print(F("Knob 1:  "));
    display.print(k1);
    display.setCursor(20, 16);
    display.print(F("Knob 2:  "));
    display.print(k2);
    display.display();
}
