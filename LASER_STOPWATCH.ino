#include <SD.h> //include the sd card library

unsigned long start, finished, elapsed;
int photocellAPin = 1; //tell arduino which pin the start photocell is attached to 
int photocellBPin = 3; //tell arduino which pin the end photocell is attached to 
int photocellAReading; //record the photocell's value
int photocellBReading; //record the photocell's value

const int chipSelect = 10;  //attach sd

void setup () {
  Serial.begin (9600);//start communication with the serial port
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);
if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}

void displayResult () {

File dataFile = SD.open("SDTEST1.txt", FILE_WRITE); //opens the text file that will be written on

  float h, m, s, ms;
  unsigned long over;
  elapsed = finished - start;
  h = int (elapsed/3600000);
  over = elapsed % 3600000;
  m = int (over/60000);
  over = over % 60000;
  s = int (over/1000);
  ms = over % 1000;

  //write to serial monitor
  Serial.print ("Raw elapsed time: ");
  Serial.println (elapsed);
  Serial.print ("Elapsed time: ");
  Serial.print (h, 0);
  Serial.print ("h ");
  Serial.print (m, 0);
  Serial.print ("m ");
  Serial.print (s, 0);
  Serial.print ("s ");
  Serial.print (ms, 0);
  Serial.println ("ms ");
  Serial.println ();

  //write to sd card
  dataFile.print ("Raw elapsed time: ");
  dataFile.println (elapsed);
  dataFile.print ("Elapsed time: ");
  dataFile.print (h, 0);
  dataFile.print ("h ");
  dataFile.print (m, 0);
  dataFile.print ("m ");
  dataFile.print (s, 0);
  dataFile.print ("s ");
  dataFile.print (ms, 0);
  dataFile.println ("ms ");
  dataFile.println ();
  dataFile.close(); 
}

void loop () {
File dataFile = SD.open("SDTEST1.txt", FILE_WRITE);
 photocellAReading = analogRead(photocellAPin);//reads values of photocell A
 photocellBReading = analogRead(photocellBPin);//reads value of photocell B
 
  Serial.print("Analog A reading = ");
  Serial.println(photocellAReading);

  dataFile.print("Analog A reading = ");
  dataFile.println(photocellAReading);

  Serial.print("Analog B reading = ");
  Serial.println(photocellBReading);
  
  dataFile.print("Analog B reading = ");
  dataFile.println(photocellBReading);

  if (photocellAReading < 650 && photocellBReading > 650 ) {
    start = millis ();//records start time (when an object has passed thru the first photocell and laser)
    Serial.println ("Started...");
  }
  
  if (photocellBReading < 650) {
    finished = millis ();//records stop time (when an object has passed thru the first photocell and laser)
    displayResult ();
   while(1);
  } 
   dataFile.close(); 
}
