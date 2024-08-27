#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

class SoundSensor {
private:
  int pin;
  int ledLow;
  int ledMedium;
  int ledHigh;
  int soundMinThreshold;
  int soundMaxThreshold;

public:
  SoundSensor(int pin, int ledLow, int ledMedium, int ledHigh, int soundMinThreshold, int soundMaxThreshold)
    : pin(pin), ledLow(ledLow), ledMedium(ledMedium), ledHigh(ledHigh), soundMinThreshold(soundMinThreshold), soundMaxThreshold(soundMaxThreshold) {}

  void setup() {
    pinMode(pin, INPUT);
    pinMode(ledLow, OUTPUT);
    pinMode(ledMedium, OUTPUT);
    pinMode(ledHigh, OUTPUT);
  }

  void readAndDisplay() {
    long level = analogRead(pin);

    lcd.setCursor(0, 0);
    Serial.print("Sound Level: ");
    lcd.print("Sound Level= ");
    Serial.println(level);
    lcd.print(level);

    lcd.setCursor(0, 1);
    if (level <= soundMinThreshold) {
      lcd.print("Intensity= Low");
      digitalWrite(ledLow, HIGH);
    } else {
      digitalWrite(ledLow, LOW);
    }
    if (level > soundMinThreshold && level <= soundMaxThreshold) {
      lcd.print("Intensity=Medium");
      digitalWrite(ledMedium, HIGH);
    } else {
      digitalWrite(ledMedium, LOW);
    }
    if (level > soundMaxThreshold) {
      lcd.print("Intensity= High");
      digitalWrite(ledHigh, HIGH);
    } else {
      digitalWrite(ledHigh, LOW);
    }
    delay(400);
    lcd.clear();
  }
};

class LCDDisplay {
public:
  void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
  }

  void clear() {
    lcd.clear();
  }
};

SoundSensor soundSensor(A0, 3, 4, 5, 522, 527);
LCDDisplay lcdDisplay;

void setup() {
  soundSensor.setup();
  lcdDisplay.setup();
}

void loop() {
  soundSensor.readAndDisplay();
}
