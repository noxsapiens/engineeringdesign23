const int waterSensorPin = A0;   //analog pin for water sensor
const int lightBulbPin = 13;     //digital pin for light bulb
const int speakerPin = 9;        //digital pin for speaker

const int lcdUpdateInterval = 1000;  //update LCD every 1000 milliseconds
unsigned long previousMillis = 0;
unsigned long totalWater = 0;

const int threshold = 500;       //water consumption threshold

void setup() {
  lcd.begin(16, 2);  //initialize the LCD with 16 columns and 2 rows
  pinMode(waterSensorPin, INPUT);
  pinMode(lightBulbPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  
  digitalWrite(lightBulbPin, LOW);  //turn off light bulb initially
  digitalWrite(speakerPin, LOW);    //turn off speaker initially
}

void loop() {
  unsigned long currentMillis = millis();

  //check if it's time to update the LCD
  if (currentMillis - previousMillis >= lcdUpdateInterval) {
    //save the current time
    previousMillis = currentMillis;

    //update the LCD with the total water detected
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water: ");
    lcd.print(totalWater);
    lcd.print(" ml");
  }

  int waterLevel = analogRead(waterSensorPin);

  //check if water consumption exceeds the threshold
  if (waterLevel > threshold) {
    //turn on light bulb
    digitalWrite(lightBulbPin, HIGH);

    //beep the speaker, multiple times if we want (bas will telll us)
    beep();

    
  } else {
    //turn off light bulb
    digitalWrite(lightBulbPin, LOW);
  }
  //update total water
  totalWater += waterLevel;
}

void beep() {
  //generate a simple beep sound
  tone(speakerPin, 1000, 500);  //frequency: 1000Hz, Duration: 500ms
  delay(1000);  //wait for 1 second
  noTone(speakerPin);  //turn off the tone
}
