#include <PZEM004Tv30.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RX_PIN 16
#define TX_PIN 17
#define RELAY_PIN 5      
#define RESET_BUTTON_PIN 4  // Add a button to reset the lockout
#define THRESHOLD 14.0   

PZEM004Tv30 pzem(Serial2, RX_PIN, TX_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

enum SystemState {NORMAL, WARNING, CUTOFF, LOCKOUT};
SystemState currentState = NORMAL;

unsigned long stateStartTime = 0;
int tripCount = 0;           
int currentCutoffSecs = 10;  

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP); // Use internal pullup
  
  digitalWrite(RELAY_PIN, HIGH); // Power ON
  
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  Wire.begin(21, 22);
  
  lcd.init();
  lcd.backlight();
  lcd.print("LOAD DETECTOR AND GENERATOR RUNOFF PREVENTION MODULE");
  delay(2000);
  lcd.clear();
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power   = pzem.power();

  if (isnan(voltage)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error    ");
    return;
  }

  unsigned long currentTime = millis();

  switch (currentState) {
    
    case NORMAL:
      digitalWrite(RELAY_PIN, HIGH); 
      displayStats(voltage, current, power);
      if (power > THRESHOLD) {
        currentState = WARNING;
        stateStartTime = currentTime;
        lcd.clear();
      }
      break;

    case WARNING:
      lcd.setCursor(0, 0);
      lcd.print("!!! WARNING !!! ");
      lcd.setCursor(0, 1);
      lcd.print("TRIP "); lcd.print(tripCount + 1);
      lcd.print(" CUT: "); 
      lcd.print(10 - (currentTime - stateStartTime) / 1000);
      lcd.print("s ");

      if (currentTime - stateStartTime >= 10000) { 
        tripCount++;
        stateStartTime = currentTime;
        lcd.clear();
        
        if (tripCount == 1) {
          currentCutoffSecs = 10;
          currentState = CUTOFF;
        } else if (tripCount == 2) {
          currentCutoffSecs = 20;
          currentState = CUTOFF;
        } else {
          currentState = LOCKOUT; 
        }
      }
      if (power < THRESHOLD - 1.0) currentState = NORMAL; 
      break;

    case CUTOFF:
      digitalWrite(RELAY_PIN, LOW); // Power OFF
      lcd.setCursor(0, 0);
      lcd.print("POWER CUTOFF!   ");
      lcd.setCursor(0, 1);
      lcd.print("RESTORE IN: ");
      lcd.print(currentCutoffSecs - (currentTime - stateStartTime) / 1000);
      lcd.print("s ");

      if (currentTime - stateStartTime >= (currentCutoffSecs * 1000)) {
        currentState = NORMAL;
        lcd.clear();
      }
      break;

    case LOCKOUT:
      digitalWrite(RELAY_PIN, LOW); // POWER STAYS OFF
      lcd.setCursor(0, 0);
      lcd.print("GENRATOR PROTECT"); // Message updated
      lcd.setCursor(0, 1);
      lcd.print("PRESS RESET BTN ");

      // Check if button is pressed (LOW because of INPUT_PULLUP)
      if (digitalRead(RESET_BUTTON_PIN) == LOW) {
        lcd.clear();
        lcd.print("System Rebooting");
        delay(2000);
        tripCount = 0; // Reset everything
        currentState = NORMAL;
      }
      break;
  }
}

void displayStats(float v, float i, float p) {
  lcd.setCursor(0, 0);
  lcd.print("V:"); lcd.print(v, 1);
  lcd.print("V I:"); lcd.print(i, 2);
  lcd.setCursor(0, 1);
  lcd.print("P:"); lcd.print(p, 1);
  lcd.print("W  ACTIVE      ");
}
