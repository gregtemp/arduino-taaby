/*
===============================================================================================================
SimpleRotary.h Library CW / CCW Example Sketch
Learn more at [https://github.com/mprograms/SimpleRotary]

This example shows how to get the rotational direction.

===============================================================================================================
Release under the GNU General Public License v3
[https://www.gnu.org/licenses/gpl-3.0.en.html]
===============================================================================================================
*/
#include <SimpleRotary.h>

// Pin A, Pin B, Button Pin
SimpleRotary rotary(0,1,7);
int cw = 100;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  byte i;
  int button = digitalRead(7);
  if (button > 900){
    Serial.println("button stuff");
  }
  

  // 0 = not turning, 1 = CW, 2 = CCW
  i = rotary.rotate();

  if ( i == 1 ) {
    Serial.print("CW ");
    cw++;
    Serial.println(cw);
  }

  if ( i == 2 ) {
    Serial.print("CCW");
    cw--;
    Serial.println(cw);
  }
}
