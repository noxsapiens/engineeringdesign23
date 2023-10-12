const int waterSensorPin = A0;   // Analog pin for water sensor
const int lightBulbPin = 13;     // Digital pin for light bulb
const int speakerPin = 9;        // Digital pin for speaker

const int lcdUpdateInterval = 1000;  // Update LCD every 1000 milliseconds
unsigned long previousMillis = 0;
unsigned long totalWater = 0;

const int threshold = 500;       // Set your water consumption threshold

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  pinMode(waterSensorPin, INPUT);
  pinMode(lightBulbPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  
  digitalWrite(lightBulbPin, LOW);  // Turn off light bulb initially
  digitalWrite(speakerPin, LOW);    // Turn off speaker initially
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if it's time to update the LCD
  if (currentMillis - previousMillis >= lcdUpdateInterval) {
    // Save the current time
    previousMillis = currentMillis;

    // Update the LCD with the total water detected
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water: ");
    lcd.print(totalWater);
    lcd.print(" ml");
  }

  int waterLevel = analogRead(waterSensorPin);

  // Check if water consumption exceeds the threshold
  if (waterLevel > threshold) {
    // Turn on light bulb
    digitalWrite(lightBulbPin, HIGH);

    // Beep the speaker
    beep();

    
  } else {
    // Turn off light bulb
    digitalWrite(lightBulbPin, LOW);
  }
  // Update total water
  totalWater += waterLevel;
}

void beep() {
  // Generate a simple beep sound
  tone(speakerPin, 1000, 500);  // Frequency: 1000Hz, Duration: 500ms
  delay(1000);  // Wait for 1 second
  noTone(speakerPin);  // Turn off the tone
}
