// servo acts as actuator
// mpu 6050 for roll and deaccleration sensor
// encoder for speed of webbing detection
// extra led for tp and testing

// Deacc code init
double kp = 2;
double ki = 5;
double kd = 1000;

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output, setPoint;
double cumError, rateError;




// servo
#include<Servo.h>

Servo myservo; // create servo object to control a servo
volatile int pos; //position of servo
#define servo_int 3

// display
#include <LiquidCrystal.h>
double x, y, z, dr;
LiquidCrystal lcd(8, 12, 9, 5, 6, 7);


// stepper
#include<Stepper.h>
const int spr = 200;
//Stepper steper(spr, 8, 9, 10, 11);

// encoder code initilzation
//these pins can not be changed 2/3 are special pins
//int encoderPin1 = 8;
//int encoderPin2 = 9;

//volatile int lastEncoded = 0;
//volatile long encoderValue = 0;

//long lastencoderValue = 0;

//int lastMSB = 0;
//int lastLSB = 0;

//encoder
#define ENC_COUNT_REV 620

// Encoder output to Arduino Interrupt pin. Tracks the pulse count.
#define ENC_IN_RIGHT_A 2

// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC_IN_RIGHT_B 4

// True = Forward; False = Reverse
boolean Direction_right = true;

// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;

// One-second interval for measurements
int interval = 1000;

// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;

// Variable for RPM measuerment
float rpm_right = 0;

// Variable for angular velocity measurement
float ang_velocity_right = 0;
float ang_velocity_right_deg = 0;

const float rpm_to_radians = 0.10471975512;
const float rad_to_deg = 57.29578;

void setup() {
  //servo
  myservo.attach(3); // attaches the servo on pin 9 to the servo object
  attachInterrupt(digitalPinToInterrupt(servo_int), adjustment, RISING); //creating interrupt on rising edge, pin 2


  //encoder
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);


  //dispaly
  lcd.begin(20, 4);
  lcd.setCursor(4, 1);
  lcd.print("AccVal");
  delay(2000);

  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println(encoderValue);
  //  steper.setSpeed(60);

  //LED
  pinMode(LED_BUILTIN, OUTPUT);


  //servo intrupt
  setPoint = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  x = ((analogRead(A0) * 2.0) / 1024.0) - 1;
  y = ((analogRead(A1) * 2.0) / 1024.0) - 1;
  z = ((analogRead(A2) * 2.0) / 1024.0) - 1;

  dr = Deacc_Rate(x);

  if (x > 0.6)
  {
    digitalWrite(servo_int, HIGH);
  }

  lcd.setCursor(6, 1);
  lcd.print("gX = ");
  lcd.print(x);
  lcd.setCursor(6, 2);
  lcd.print("gY = ");
  lcd.print(y);

  currentMillis = millis();

  // If one second has passed, print the number of pulses
  if (currentMillis - previousMillis > interval) {

    previousMillis = currentMillis;

    // Calculate revolutions per minute
    rpm_right = (float)(right_wheel_pulse_count * 60 / ENC_COUNT_REV);
    ang_velocity_right = rpm_right * rpm_to_radians;
    ang_velocity_right_deg = ang_velocity_right * rad_to_deg;

    Serial.print(" Pulses: ");
    Serial.println(right_wheel_pulse_count);
    Serial.print(" Speed: ");
    Serial.print(rpm_right);
    Serial.println(" RPM");
    Serial.print(" Angular Velocity: ");
    Serial.print(rpm_right);
    Serial.print(" rad per second");
    Serial.print("\t");
    Serial.print(ang_velocity_right_deg);
    Serial.println(" deg per second");
    Serial.println();
    if (right_wheel_pulse_count < -20)
    {
      digitalWrite(servo_int, HIGH);
    }
    lcd.setCursor(6, 3);
    lcd.print("AV = ");
    lcd.print(rpm_right);
    right_wheel_pulse_count = 0;




  }
}

double Deacc_Rate(double inp) {
  currentTime = millis();                //get current time
  elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation

  error = setPoint - inp;                                // determine error
  cumError += error * elapsedTime;                // compute integral
  rateError = (error - lastError) / elapsedTime; // compute derivative

  double out = kp * error + ki * cumError + kd * rateError;          //PID output

  lastError = error;                                //remember current error
  previousTime = currentTime;                        //remember current time

  return rateError;                                        //have function return the PID output
}

void right_wheel_pulse() {

  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_RIGHT_B);

  if (val == LOW) {
    Direction_right = false; // Reverse
  }
  else {
    Direction_right = true; // Forward
  }

  if (Direction_right) {
    right_wheel_pulse_count++;
  }
  else {
    right_wheel_pulse_count--;
  }
}


void adjustment()
{
  pos = 0;
  myservo.write(pos);
}
