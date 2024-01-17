#define BLYNK_TEMPLATE_ID "TMPLXRXcrgiW"
#define BLYNK_DEVICE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "IQz4lfExGijTrwBIVzVSEKTD7oMj-wi-"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <ESP32Servo.h>

Servo myservo;
int ledgreen = 15;
int pirin = 4;
int servoPin = 5;
#define trig 13   // Trig pin
#define echo 12


char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
int depth =20 ;

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
int level;
void sendSensor()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t * 0.034 / 2;
  Serial.println(cm);
  level = map(cm,21,0 ,0,100); //Adjust bin height her
  Blynk.virtualWrite(V1, level);
  Blynk.virtualWrite(V2, cm);
  
}
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pirin, INPUT);
  pinMode(ledgreen, OUTPUT);
  myservo.attach(servoPin);
  lcd.init();
  lcd.clear();  
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME");
  lcd.setCursor(0, 1);
  lcd.print("SMART TRASH BIN");
  delay(2000);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  if (digitalRead(pirin) == HIGH)
  { digitalWrite(ledgreen, LOW);
    myservo.write(180);
    Serial.println("Terbuka");
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(1, 1);
    lcd.print("Terbuka");
    delay(3000);
  }
  else
  { digitalWrite(ledgreen, HIGH);
    myservo.write(0);
    Serial.println("Tertutup"); 
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(1, 1);
    lcd.print("Tertutup");
    delay(1000);
  }
  Blynk.run();
  timer.run(); // Initiates BlynkTimer 
}
