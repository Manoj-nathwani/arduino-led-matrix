#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            1
#define NUMPIXELS      600
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  Serial.begin(9600);
  Serial.setTimeout(50);
  pixels.begin();
  pixels.show();
  Serial.println("Ready to party!");
}

void loop() { 
  while (Serial.available() > 0) {

    String message = Serial.readString();
    if (message == "clear"){
      Serial.println("Clearing...");
      for (int i=0; i <= NUMPIXELS-1; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      }
      pixels.show();
    }else{
        //convert 1222333444 to led=1 red=222 green=333 blue=444
        int led = message.substring(0,3).toInt();
        int red = message.substring(3,6).toInt();
        int green = message.substring(6,9).toInt();
        int blue = message.substring(9,12).toInt();
        
        // sent pixels
        red = constrain(red, 0, 255); // safety first
        green = constrain(green, 0, 255); // second
        blue = constrain(blue, 0, 255); // and third
        pixels.setPixelColor(led, pixels.Color(red, green, blue));
        pixels.show();
    }
    /*
    }else if (message.length() % 9){
      Serial.println("ERROR: Input not divisible by 9");
    }else{
      Serial.println("Instructions received");
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
    */
        
  }  
}
