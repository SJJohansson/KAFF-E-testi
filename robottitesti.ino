// TÄTÄ KOODIA EI OLE TESTATTU VIELÄ, uskon sen toimivan, mutta 100% varmuutta ei ole
const int PWM1 = 3;
const int AIN1 = 4;
const int AIN2 = 5;
const int PWM2 = 6;
const int BIN1 = 7;
const int BIN2 = 8;
const char forward = 'W';
const char back = 'S';
const char left = 'A';
const char right = 'D';
const char off = 'O'; // täysin pois päältä ja poistaa myös valitun suunnan
const char full = 'F'; // 100% teho
const char half = 'H'; // 50% teho
const char kaksviis = 'T'; //~25% teho
int spd = 0;
char dir = 'O';

void setup() {
  Serial.begin(9600);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
}

void motorClockwise(char motor) {
  if (motor == 'A') {
      digitalWrite(AIN1,HIGH);
      digitalWrite(AIN2,LOW);
    }
    else if (motor == 'B') {
      digitalWrite(BIN1,HIGH);
      digitalWrite(BIN2,LOW);
    }
}

void motorCClockwise(char motor) {
  if (motor == 'A') {
      digitalWrite(AIN1,LOW);
      digitalWrite(AIN2,HIGH);
    }
    else if (motor == 'B') {
      digitalWrite(BIN1,LOW);
      digitalWrite(BIN2,HIGH);
    }
}

void motorStop(char motor) {
  if (motor == 'A') {
      digitalWrite(AIN1,LOW);
      digitalWrite(AIN2,LOW);
    }
    else if (motor == 'B') {
      digitalWrite(BIN1,LOW);
      digitalWrite(BIN2,LOW);
    }
}

void move() {
  switch (dir) {
    case forward:
      motorClockwise('A');
      motorClockwise('B');
      break;
    case back:
      motorCClockwise('A');
      motorCClockwise('B');
      break;
    case left:
      motorCClockwise('A');
      motorClockwise('B');
      break;
    case right:
      motorClockwise('A');
      motorCClockwise('B');
      break;
    case off:
      motorStop('A');
      motorStop('B');
      break;
  }
  digitalWrite(PWM1,spd);
  digitalWrite(PWM2,spd);
  printf("Liikutaan, suunta on %d ja nopeus %s",dir,spd);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case forward: 
        dir = forward;
        Serial.print(dir);
        break;
      case back: 
        dir = back;
        Serial.print(dir);
        break;
      case left:
        dir = left;
        Serial.print(dir);
        break;
      case right:
        dir = right;
        Serial.print(dir);
        break;
      case off:
        dir = off;
        spd = 0;
        Serial.print(spd);
        break;
      case full:
        spd = 255;
        Serial.print(spd);
        break;
      case half:
        spd = 127;
        Serial.print(spd);
        break;
      case kaksviis:
        spd = 63;
        Serial.print(spd);
        break;
    }
  }
  move();
}