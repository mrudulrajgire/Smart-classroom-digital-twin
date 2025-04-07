const int tempPin = A0;  // TMP36 Sensor
const int ldrPin = A1;   // LDR Sensor
const int pirPin = 2;    // PIR Sensor

const int acRelayPin = 7;     // Relay control for AC
const int lightRelayPin = 8;  // Relay control for Light

void setup() {
    Serial.begin(9600);  
    pinMode(pirPin, INPUT); 

    pinMode(acRelayPin, OUTPUT);
    pinMode(lightRelayPin, OUTPUT);

    // Start with everything ON
    digitalWrite(acRelayPin, HIGH);     // HIGH = ON (depending on relay logic)
    digitalWrite(lightRelayPin, HIGH);
}

void loop() {
    // Read Temperature (TMP36)
    int tempValue = analogRead(tempPin);
    float voltage = tempValue * (5.0 / 1023.0);
    float temperatureC = (voltage - 0.5) * 100.0;

    // Read Light (LDR)
    int lightLevel = analogRead(ldrPin);

    // Read Motion (PIR)
    int motionDetected = digitalRead(pirPin);

    // Display Data
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.print(" °C | Light Level: ");
    Serial.print(lightLevel);
    Serial.print(" | Motion: ");
    Serial.println(motionDetected == 1 ? "Detected" : "No Motion");

    // Control AC and Light
    if (motionDetected == 0) {
        digitalWrite(acRelayPin, LOW);       // Turn OFF AC
        digitalWrite(lightRelayPin, LOW);    // Turn OFF Light
        Serial.println("AC & Light turned OFF (No motion)");
    } else {
        digitalWrite(acRelayPin, HIGH);      // Turn ON AC
        digitalWrite(lightRelayPin, HIGH);   // Turn ON Light
        Serial.println("AC & Light turned ON (Motion detected)");
    }

    delay(1000);
}
