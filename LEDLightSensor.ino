/*
   http://www.instructables.com/id/Better-LED-as-light-sensor/
*/


// the pin where you will put the LED
int led = 13;
 // the analog pin where you put your sensorLED
int sensorpin = A3;
// the rest are counters and variables to calculate with
int resetteller = 0;
int sens = 0;
int teller = 0;
int basis = 1024;
int test = 1024;
int test2 = 1024;
int test3 = 1024;

// this are the values to play with to get better (or worse) results
int marge = 5;                         
// the space between a positive and negative reading
int vertraging = 1;                  
// the speed of the readings; a lower number is a higher speed
int samples = 70;                   
// the amount of samples to compare to make one reading
int resetsamples = 30;          
// how many cycles to run the light on before you don't trust the value anymore

void setup() {
  pinMode(led, OUTPUT);
  // no real part of the program, just for debugging
  Serial.begin(9600);
  // remember the lowest value out of many readings
  for(teller =0; teller < samples; teller++) {
   sens = analogRead(sensorpin);
   if (sens < basis) {basis = sens;}
   // the sensor needs a delay here to catch its breath
   delay(vertraging);
  }
}


void loop() {
// remember the lowest value out of many readings              
for(teller =0; teller < samples; teller++) {
   sens = analogRead(sensorpin);
   // the sensor needs a delay here to catch its breath
   delay(vertraging);
   if (sens < test){
   // remember the 3 lowest readings
       test3 = sens;
       test2 = test3;
       test = test2;}
   }
   //all 3 low readings mus be < the basis reading
  if (test < basis-marge && test2 < basis-marge && test3 < basis-marge){
    digitalWrite(led, HIGH);
    // count how long the LED stays on
    resetteller++;
  }
    else{
      digitalWrite(led, LOW);
      // if the lowest test reading is higher than the basis, basis will be reset
      basis = test;
      resetteller = 0;
    }
    //if LED stays on to long, we don't trust it and reset basis
    if (resetteller > resetsamples) {basis = test;}
    //just for debugging
    Serial.print(basis);Serial.print("  ");Serial.print(test);Serial.print("  ");Serial.println(sens);
    test = 1024;
}
