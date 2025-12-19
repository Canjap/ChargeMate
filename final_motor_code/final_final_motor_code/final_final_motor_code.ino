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

void setup() {
  Serial.begin(9600);      // USB Serial Monitor
  mySerial.begin(9600);    // SoftwareSerial to ESP32
  Serial.println("Uno ready");
  pin_setup();
}

void loop() {
  int rawValue = analogRead(potentiometerPin);     // Read the analog input
  float voltage = (rawValue / ADC_STEPS) * V_REF;  // Convert to voltage

  //Serial.print("Voltage: ");
  //Serial.print(voltage, 3);  // Print voltage with 3 decimal places
  //Serial.println(" V");

  if (voltage > 1.50) {
    if (mySerial.available()) {
      String msg = mySerial.readStringUntil('\n');
      msg.trim();
      Serial.println("Received from ESP32: " + msg);
      if (msg.equals("pressed1")){
        Serial.println("pressed 1");
        forward(50,50);
      }
      else if (msg.equals("pressed2")) {
        Serial.println("pressed 2");
        forward(80,80);
      }
      else {
        Serial.println(msg);
      }
    }
  }
  else {
    Serial.println("floor");
  }
}
