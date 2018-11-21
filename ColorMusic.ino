#define REDPIN 5                                            //r
#define GREENPIN 6                                          //g
#define BLUEPIN 3                                           //b
#define SOUNDPIN A0                                         //pin for reading voltage level in

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(SOUNDPIN, INPUT);
  Serial.begin (9600);  
}

int maxVal = 0;                                             //used to determine each song's unique max

double m1 = 0, m2 = 0, m3 = 0, m4 = 0;                      //used to split input range into 5 levels
int d = 7;                                                  //(delta) value to make colors more reactive
int previous = 0;                                           //level previously read in

int r, g, b;                                                //red, green, and blue values to be output
int wait = 1;                                               //delay between each loop

double power = 1.5;                                         

void loop() {
  double sensorValue = pow(analogRead (SOUNDPIN), power);   //reads in signal and spreads values according to power
  Serial.println (sensorValue, DEC);                        //prints input to consol for dev use
  
  maxVal -= 1;                                              //decrements local max to keep range updated
  
  if(sensorValue > maxVal) {                                //resets max and interval values
    maxVal = sensorValue;
    m1 = 0.25 * maxVal;
    m2 = 0.45 * maxVal;
    m3 = 0.55 * maxVal;
    m4 = 0.7 * maxVal; 
  }
                                                            
  if(previous <= m1) {                                      //compares previous range to current range
    if(sensorValue <= m1) {                                 //and changes rgb values accordingly
      r += d;
      g -= d;
      b -= d;
    }
    else if (sensorValue <= m2) {
      r -= d;
      g += 2*d;
      b -= 3*d;
    }
    else if (sensorValue <= m3) {
      r -= 3*d;
      g += d;
      b += 2*d;
    }
    else if (sensorValue <= m4) {
      r -= 3*d;
      g -= 2*d;
      b += 3*d;
    }
    else {
      r += d;
      g -= 3*d;
      b += 4*d;
    }
  }
  else if(previous <= m2) {
    if(sensorValue <= m1) {
      r += d;
      g -= d;
      b -= d;
    }
    else if (sensorValue <= m2) {
      r -= d;
      g += d;
      b -= d;
    }
    else if (sensorValue <= m3) {
      r -= d;
      g += d;
      b += d;
    }
    else if (sensorValue <= m4) {
      r -= d;
      g -= 2*d;
      b += 2*d;
    }
    else {
      r += 3*d;
      g -= 3*d;
      b += 3*d;
    }
  }
  else if(previous <= m3) {
    if(sensorValue <= m1) {
      r += 2*d;
      g -= 2*d;
      b -= 3*d;
    }
    else if (sensorValue <= m2) {
      r += d;
      g -= d;
      b -= d;
    }
    else if (sensorValue <= m3) {
      r -= d;
      g += d;
      b += d;
    }
    else if (sensorValue <= m4) {
      r -= d;
      g -= d;
      b += d;
    }
    else {
      r += 2*d;
      g -= 3*d;
      b += 3*d;
    }
  }
  else if(previous <= m4) {
    if(sensorValue <= m1) {
      r += 3*d;
      g -= d;
      b -= 3*d;
    }
    else if (sensorValue <= m2) {
      r += d;
      g += d;
      b -= 2*d;
    }
    else if (sensorValue <= m3) {
      r -= d;
      g += d;
      b -= d;
    }
    else if (sensorValue <= m4) {
      r -= d;
      g -= d;
      b += d;
    }
    else {
      r += d;
      g -= d;
      b += d;
    }
  }
  else {
    if(sensorValue <= m1) {
      r += d;
      g += d;
      b -= 3*d;
    }
    else if (sensorValue <= m2) {
      r -= d;
      g += d;
      b -= 3*d;
    }
    else if (sensorValue <= m3) {
      r -= 3*d;
      g += 3*d;
      b -= d;
    }
    else if (sensorValue <= m4) {
      r -= 2*d;
      g += d;
      b += d;
    }
    else {
      r += d;
      g -= 3*d;
      b += d;
    }
  }
                                                             
  if (r > 255) {r = 255;}                                   //resets r, g, and b values if they become too small or too large
  if (r < 0) {r = 0;}
  if (g > 255) {g = 255;}
  if (g < 0) {g = 0;}
  if (b > 255) {b = 255;}
  if (b < 0) {b = 0;}
  
  
  analogWrite(REDPIN,r);                                    //writes r, g, and b values to red, green, and blue, pins
  analogWrite(GREENPIN,g);
  analogWrite(BLUEPIN,b);
  previous = sensorValue;                                   //updates the previous value
  delay(wait);                                              //delays the wait amount specified
}
