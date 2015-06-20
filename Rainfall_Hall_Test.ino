/*
Uses Adafruit/158 Hall Effect Sensor (US5881LUA) to measure 
"bucket tips" in a homemade rainfall sensor.  Each tip is
approximately 0.025" rain. Tested on MPS430F5529 LaunchPad.

Credit to msuzuki77, the Lazy Old Geek
http://www.instructables.com/id/Arduino-Weather-Station-Part3-Rain/
for the inspiration for my version

See photographs in github wiki for build.

Frank Milburn 18 June 2015
Released into the public domain

Rain sensor connections for analog pin...
 =========================================
 Hall Rain sensor         Connect to F5529
 -----------------------------------------
 1    Orange              3.3V
 2    Blue                GND   
 3    Orange/Wh           Pin 6 
 ----------------------------------------
 Note: 3.3V is below the minimum voltage from the data sheet
 (3.5V) although I had no problem in my tests.  Should 
 address this in the next version.
*/

const int hallPin = 6;          // Pin that the hall sensor attaches to - analog
const int LEDpin = RED_LED;     // LED pin on the 5529 LaunchPad
boolean lastHall;               // Last hall sensor status (true = magnet is close)
int hallReading;                // Last hall sensor analog reading ( <100, magnet is close)
int bucketCount = 0;            // Number of times the bucket has tipped
float bucketSize = 0.025;       // Size of the buckets (equivalent to inches of water)
float totalRainFall = 0.0;      // Total rainfall measured since beginning of test (inches)

void setup()
{
  pinMode(LEDpin,OUTPUT);
  Serial.begin(9600);
  hallReading = analogRead(hallPin);
  lastHall = false;
  if (hallReading < 100)
  {
    lastHall = true;
  }
  Serial.println("Starting rainfall sensor test...");
}

void loop()
{
  hallReading = analogRead(hallPin);
  // Serial.println(hallReading);
  if (hallReading < 100)
  {
    if (lastHall == false)
    {
      lastHall = true;
      digitalWrite(LEDpin, HIGH);
      bucketCount = bucketCount + 1;
      totalRainFall = totalRainFall + bucketSize;
      Serial.print("Bucket tipped: ");
      Serial.print(bucketCount);
      Serial.print("       Total rainfall: ");
      Serial.print(totalRainFall);
      Serial.println(" inches");
    }
  }
  else
  {
    if (lastHall == true)
    {
      lastHall = false;
      digitalWrite(LEDpin, LOW);
      bucketCount = bucketCount + 1;
      totalRainFall = totalRainFall + bucketSize;
      Serial.print("Bucket tipped: ");
      Serial.print(bucketCount);
      Serial.print("       Total rainfall: ");
      Serial.print(totalRainFall);
      Serial.println(" inches");
    }
  }
}
