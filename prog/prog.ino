#include <SPI.h>
#include <Wire.h>
#include <ServoTimer2.h>
#include <AltSoftSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 

AltSoftSerial muSerial;

DFRobotDFPlayerMini muPlayer;

ServoTimer2 servoBrow;

int pos = 0; 

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
const int micPin = A0;
const int volPot = A1;

const int redPin= 3;
const int greenPin = 5;
const int bluePin = 6;

char msg1[] = "Ok";

char msg2[] = "Te luid";

char msg3[] = "Stop";

void setColor(int,int,int);

void draw(char*);

void setup() {
  muSerial.begin(9600);
  Serial.begin(9600);
  
  servoBrow.attach(11);

  muPlayer.begin(muSerial);

  //if (!muPlayer.begin(muSerial)) {  //Use AltSoftSerial to communicate with mp3 and check it
  //  Serial.println(F("Unable to begin:"));
  //  Serial.println(F("1.Please recheck the connection!"));
  //  Serial.println(F("2.Please insert the SD card!"));
  //  while(true);
  //}
}

void loop() {
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  muPlayer.pause();
  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(micPin);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
  int vol = analogRead(volPot) / 34;
  muPlayer.volume(vol);
  
  //Serial.println(vol);
  //Serial.println(volts);
  if(volts <= 1) {
    setColor(0,255,0);
    servoBrow.write(0);
    draw(msg1);
    delay(2000);
  } else if(volts > 1 && volts <= 2) {
    setColor(255,255,0);
    servoBrow.write(1300);
    draw(msg2);
    muPlayer.play(1);
    delay(2000);
  } else {
    setColor(255,0,0);
    servoBrow.write(2000);
    draw(msg3);
    muPlayer.play(2);
    delay(2000);
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
      analogWrite(redPin, redValue);
      analogWrite(greenPin, greenValue);
      analogWrite(bluePin, blueValue);
}

void draw(char* msg) {
  u8g.setPrintPos(10, 44);
  u8g.print(msg);
}

