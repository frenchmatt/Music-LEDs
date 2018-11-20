#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
#define SOUNDPIN A0

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(SOUNDPIN, INPUT);
  Serial.begin (9600);
}

int count = 0;
int maxVal = 0;
double m1 = 0, m2 = 0, m3 = 0, m4 = 0;
int r, g, b;
int maxReset = 5000;
int wait = 1;
int d = 7;
int previous = 0;


void loop() {
  double sensorValue = pow(analogRead (SOUNDPIN), 1.5);
  Serial.println (sensorValue, DEC);
  
  count++;
  //reset max to be specific per each song
  if(count > maxReset) {
    count = 0;
    maxVal = 0;
  }
  
  if(sensorValue > maxVal) {
    maxVal = sensorValue;
    m1 = 0.25 * maxVal;
    m2 = 0.45 * maxVal;
    m3 = 0.55 * maxVal;
    m4 = 0.7 * maxVal; 
  }

  

  if(previous <= m1) {
    if(sensorValue <= m1) {
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
  
  if (r > 255) {r = 255;}
  if (r < 0) {r = 0;}
  if (g > 255) {g = 255;}
  if (g < 0) {g = 0;}
  if (b > 255) {b = 255;}
  if (b < 0) {b = 0;}
  
  
  analogWrite(REDPIN,r);
  analogWrite(GREENPIN,g);
  analogWrite(BLUEPIN,b);
  previous = sensorValue;
  delay(wait);
}
