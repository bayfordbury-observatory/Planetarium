#include <NeoPixelBus.h>

#include <IRremote.h>
#include <IRremoteInt.h>


const int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define pinIR 3


uint32_t val =0;

#define LED 13

const uint16_t PixelCount = 150; 
const uint8_t PixelPin = 2; 

uint8_t highL=100;
uint8_t lowL=20;

NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
//red green blue white
RgbwColor off(0,0,0,0);

uint8_t red=0;
uint8_t green=0;
uint8_t blue=0;
uint8_t white=255;

RgbwColor colour(red,green,blue,white);


void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;

  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  Serial.println();
}


void setup() {

    Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(false);
  
   strip.Begin();
   //strip.Show();

/*   for(int i=50; i<70; i++){
      strip.SetPixelColor(i, na);
   }*/

       
    /* for(int i=0; i<150; i++){
      strip.SetPixelColor(i, white);

      
   }*/


    for(int i=0; i<150; i++){
      strip.SetPixelColor(i, colour);
   }
   
  strip.Show();

}

float hue=0;
float hueStart=0;

int start=75; int end=75;

bool change=true;

void loop() {

    if (irrecv.decode(&results)){
    //val = results.value;
        
        switch(results.value){
            case 0xD7E84B1B:
                if(red==0 && green==0 && blue==0 && white==0){
                    red=0; green=0; blue=0; white=255;
                }else{
                     red=0; green=0; blue=0; white=0;
                }
                break;
            case 0xB3D4B87F:
                if(white<=238){
                   white=white+17;
                }
                break;
            case 0x44490A7B:
                if(white>=17){
                   white=white-17;
                }
                break;
            case 0x13549BDF:
                if(red<=238){
                   red=red+17;
                }
                break;
            case 0x45473C1B:
                if(red>=17){
                   red=red-17;
                }
                break;
            case 0xA3C8EDDB:
                if(green<=238){
                   green=green+17;
                }
                break;
            case 0x9EF4941F:
                if(green>=17){
                   green=green-17;
                }
                break;
            case 0xC101E57B:
                if(blue<=238){
                   blue=blue+17;
                }
                break;
            case 0xF377C5B7:
                if(blue>=17){
                   blue=blue-17;
                }
                break;
        }
        
        //dump(&results);
        if(results.value!=0xFFFFFFFF){
          Serial.println(results.value, HEX);
          change=true;
        }
    irrecv.resume();
  }

if(change){
colour =  RgbwColor(red,green,blue,white);
    for(int i=0; i<150; i++){
      strip.SetPixelColor(i, colour);
   }
   
  strip.Show();
  change=false;
  }
  

/*
  //while(1);
  hue=hueStart;
   for(int i=0; i<PixelCount; i++){
    HslColor hsl(hue,  1.0f, 0.5f);
    RgbwColor col(hsl);
      strip.SetPixelColor(i, col);
      hue=hue+(1.0f/100.0);
      if(hue>1){hue=0;}
   }
   
  hueStart=hueStart+0.05f;
  if(hueStart>1){hueStart=0;}
  strip.Show();
  delay(25);*/
/*
     for(int i=start; i<end; i++){
      strip.SetPixelColor(i, na);
   }

    strip.Show();
  start--;
  end++;

  

  if(start==0 || end==150){
    start=75;end=75;
    
     for(int i=0; i<150; i++){
      strip.SetPixelColor(i, off);
   }
  }

  delay(100);
*/

}
