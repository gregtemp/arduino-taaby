
/* 
 DESCRIPTION
 ====================
 Simple example of the Bounce library that switches the debug LED when 
 either of 2 buttons are pressed.
 */
 
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>
#include <Encoder.h>


#define butt1 8
#define butt2 9
#define butt3 10
#define butt4 11

#define LED1 13
#define LED2 14

int newb[4] = {1, 1, 1, 1};
int oldb[4] = {1, 1, 1, 1};

// Instantiate a Bounce object
Bounce deb1 = Bounce(); 
Bounce deb2 = Bounce(); 
Bounce deb3 = Bounce(); 
Bounce deb4 = Bounce(); 

//encoder
Encoder myEnc(22, 23);
long encold  = -999;

void setup() {
  Serial.begin(9600);
  // Setup the first button with an internal pull-up :
  pinMode(butt1,INPUT_PULLUP);
  pinMode(butt2,INPUT_PULLUP);
  pinMode(butt3,INPUT_PULLUP);
  pinMode(butt4,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  deb1.attach(butt1);
  deb1.interval(5); // interval in ms
  deb2.attach(butt2);
  deb2.interval(5); // interval in ms
  deb3.attach(butt3);
  deb3.interval(5); // interval in ms
  deb4.attach(butt4);
  deb4.interval(5); // interval in ms

  //Setup the LED :
  //pinMode(LED1,OUTPUT);
  //pinMode(LED2,OUTPUT);

}

void loop() {
  // Update the Bounce instances :
  deb1.update();
  deb2.update();
  deb3.update();
  deb4.update();

  // Get the updated value :
  newb[0] = deb1.read();
  newb[1] = deb2.read();
  newb[2] = deb3.read();
  newb[3] = deb4.read();

  for (int i = 0; i < 4; i++) {
    if(newb[i] != oldb[i]){
      buttonFunc(i, newb[i]);
      oldb[i] = newb[i];
    }
  }

  long encnew = myEnc.read();
  if (encnew != encold) {
    encold = encnew;
    Serial.println(encnew);
  }
}

void buttonFunc(int id, int state) {
  
  Serial.print("id: ");
  Serial.print(id);
  Serial.print(" was set to ");
  Serial.println(state);

  if (id == 0) {
    if (state == 0) {
      Keyboard.set_modifier(MODIFIERKEY_GUI);
      Keyboard.send_now();
      Keyboard.set_key1(KEY_C);
      Keyboard.send_now();
    }
    if (state == 1) {
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
    }
  }
  else if(id == 1) {
    if (state == 0) {
      Keyboard.set_modifier(MODIFIERKEY_GUI);
      Keyboard.send_now();
      Keyboard.set_key1(KEY_V);
      Keyboard.send_now();
    }
    if (state == 1) {
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
    }
  }
  else if(id == 2){
    if (state == 0) {
      Keyboard.set_modifier(MODIFIERKEY_GUI);
      Keyboard.send_now();
      Keyboard.set_key1(KEY_Z);
      Keyboard.send_now();
    }
    if (state == 1) {
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
    }
  }
  else if(id == 3){
    if (state == 0) {
      Keyboard.println("What do you think of that bobosh??");
    }
    if (state == 1) {
//      Keyboard.release(MODIFIERKEY_CTRL);
//      Keyboard.release(KEY_Z);
    }
  }
}
