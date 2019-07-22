/*
Original sketch:
Arduino Hall Effect Sensor Project by Arvind Sanjeev
Please check out  http://diyhacking.com for the tutorial of this project.

Modified By M Kear for debugging hall effect sensors with ArduPilot
*/

//conversion factors
#define MILLIS_TO_SEC 1000.0f
#define SEC_TO_MIN 60.0f

/* 
 If you want to use the hall effect sensor to print 'detect' to the serial monitor when the magnet is
 near and the correct polarity is presented, set this to true.  If you want to output an rpm value 
 set this to false.
*/
bool detect_on = true;


/* Set the number of magnets on autorotation wheel / shaft. */
int n_magnets = 1;


volatile byte n_rev;
float rpm;
float prev_time;


 void setup()
 {
   Serial.begin(9600);
   attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
   n_rev = 0;
   rpm = 0.0f;
   prev_time = 0.0f;
 }

 
 void loop()//Measure RPM
 {
   //Only do rpm calculation after 20 rotations has past.
   if (n_rev >= 20) { 
     rpm = SEC_TO_MIN*MILLIS_TO_SEC/(millis() - prev_time)*n_rev/n_magnets;

     //reset prev_time to now
     prev_time = millis();

     //reset rotation counter
     n_rev = 0;

     //print rpm value to serial console
     Serial.println(rpm,DEC);
   }
 }


 //This function is called whenever a magnet/interrupt is detected by the arduino
 void magnet_detect()
 {
   n_rev++;
   
   if (detect_on == true) {
      Serial.println("detect");
   }

 }
