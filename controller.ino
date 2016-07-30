#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            8
#define NUMPIXELS      50
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ400);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  pixels.begin();
}

void loop() { 
  while (Serial.available() > 0) {

    String message = Serial.readString();
    if (message.length() % 9){
      Serial.println("ERROR: Input not divisible by 9");
    }else{
      for (int i=0; i <= message.length()-9; i+=9){
        
        //convert 111222333 to red=111 green=222 blue=333
        int red = message.substring(i,i+3).toInt();
        int green = message.substring(i+3,i+6).toInt();
        int blue = message.substring(i+6,i+9).toInt();
        
        // sent pixels
        red = constrain(red, 0, 255); // safety first
        green = constrain(green, 0, 255); // second
        blue = constrain(blue, 0, 255); // and third
        pixels.setPixelColor(i/9, pixels.Color(red, green, blue));
        
      }
      //print pixels onto strip
      pixels.show();
    }
    
  }  
}
