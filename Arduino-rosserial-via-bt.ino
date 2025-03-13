#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1);  // RX, TX (for Bluetooth)

// Motor A connections
#define ENA 5
#define IN1 6
#define IN2 7

// Motor B connections
#define ENB 11
#define IN3 8
#define IN4 10

void setup() {
    Serial.begin(57600);  // Debugging via USB Serial Monitor
    BT.begin(9600);       // Bluetooth Module

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    Serial.println("Bluetooth Motor Control Ready");
}

// Function to control motors
void controlMotors(String command) {
    Serial.print("Command: ");
    Serial.println(command);
    
    if (command == "forward") {
        digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
    } 
    else if (command == "backward") {
        digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
    } 
    else if (command == "left") {
        digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
        analogWrite(ENA, 100);
        analogWrite(ENB, 100);
    } 
    else if (command == "right") {
        digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
        analogWrite(ENA, 100);
        analogWrite(ENB, 100);
    } 
    else if (command == "stop") {
        digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
        analogWrite(ENA, 0);
        analogWrite(ENB, 0);
    }
}

void loop() {
    if (BT.available()) {
        String command = BT.readStringUntil('\n');
        command.trim();  // Remove extra spaces/newlines
        controlMotors(command);
    }
}
