/* Analog Read to LED
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13. The amount of time the LED will be on and off depends on
 * the value obtained by analogRead(). In the easiest case we connect
 * a potentiometer to analog pin 2.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */

const int potPin = A1;   // select the pin for the potmeter

void setup() {
  Serial.begin(9600);
}

void loop() {
  int potVal = analogRead(potPin);    // read the value from the sensor
  Serial.println(potVal);
  delay(50);
}
