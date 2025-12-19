//base script from this: http://forum.arduino.cc/t/elegoo-smart-car-issues/1158801/13
//Pins for V.4

//Don't need to make lib bc this will run while uno is powered on
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // Orange/RX=10, Brown/TX=11

#define PIN_Motor_STBY 3

// motorA
#define PIN_Motor_PWMA 5
#define PIN_Motor_AIN_1 7

// motorB
#define PIN_Motor_PWMB 6
#define PIN_Motor_BIN_1 8

#define carSpeed 150

const float V_REF = 5.0;                         // Analog reference voltage (e.g., 5V or 3.3V)
const float R_BITS = 10.0;                       // ADC resolution (bits)
const float ADC_STEPS = (1 << int(R_BITS)) - 1;  // Number of steps (2^R_BITS - 1)

const int potentiometerPin = A1;  // Potentiometer wiper connected to analog pin A3

void pin_setup(void)
{

  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
}



void forward(int8_t speed_A, uint8_t speed_B) {
  //enable
  digitalWrite(PIN_Motor_STBY, HIGH);
  // forward
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, speed_A);
  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMB, speed_B);
  //adjust delay to control pace
  delay(3000);
  //disable
  digitalWrite(PIN_Motor_STBY, LOW);
}

void back(int8_t speed_A, uint8_t speed_B) {
  //enable
  digitalWrite(PIN_Motor_STBY, HIGH);  
  digitalWrite(PIN_Motor_AIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, speed_A);
  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMB, speed_B);
  delay(3000);
  //disable
  digitalWrite(PIN_Motor_STBY, LOW);  
}

/*
void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
} */


void setup() {
  Serial.begin(9600);  // Initialize main serial 
  mySerial.begin(9600); //Initialize SW serial to comm with ESP32
  Serial.println(ADC_STEPS);
  pin_setup();
}


void loop() {
  int rawValue = analogRead(potentiometerPin);     // Read the analog input
  float voltage = (rawValue / ADC_STEPS) * V_REF;  // Convert to voltage

  Serial.print("Voltage: ");
  Serial.print(voltage, 3);  // Print voltage with 3 decimal places
  Serial.println(" V");

  if (mySerial.available()) { //Check if SW serial is available
    String msg = mySerial.readStringUntil('\n');
    Serial.println(msg);
    if (msg=="pressed") {
      if (voltage > 3.30) {
        Serial.println("tape");
        //adjust speed with the params
        forward(70,70);
      } else {
        Serial.println("floor");
      }
    delay(50);  // Small delay to avoid flooding the serial monitor
    }

  }
}