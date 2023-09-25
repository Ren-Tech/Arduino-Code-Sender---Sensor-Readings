
//UPLOAD THIS CODE FIRST THEN UPLOAD NODEMCU CODE THEN CONNECT TX, RX TO SEND THE DATA TO NODEMCU REAL-TIME
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize the LCD with its I2C address

const int turbidityPin = A0;  // Analog input pin for turbidity sensor
#define SensorPin A1  // pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  // Store the average value of the sensor feedback
int buf[20], temp;  // Increase the buffer size to capture more samples

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready");  // Test the serial monitor

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();  // Initialize the LCD
}

void loop() {
  // pH sensor code
  for (int i = 0; i < 20; i++) {
    buf[i] = analogRead(SensorPin);
    delay(5);  // Decrease the delay between samples
  }
  for (int i = 0; i < 19; i++) {
    for (int j = i + 1; j < 20; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 18; i++) {
    avgValue += buf[i];
  }
  float pHValue = (float)avgValue * 5.0 / 1024 / 16;
  pHValue = 3.5 * pHValue;

  // Turbidity sensor code
  int sensorValue = analogRead(turbidityPin);
  int turbidity = map(sensorValue, 0, 750, 100, 0);  // Corrected map() function

  // Display values on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Turbidity: ");
  lcd.print(turbidity);
  
  lcd.setCursor(0, 1);
  lcd.print("pH: ");
  lcd.print(pHValue, 2);

  // Send pH and turbidity values to NodeMCU
  Serial.print("pH: ");
  Serial.println(pHValue);
  Serial.print("Turbidity: ");
  Serial.println(turbidity);

  digitalWrite(13, HIGH);
  delay(800);
  digitalWrite(13, LOW);

  delay(1000);
}











//THIS WORKS DO NOT DELETE
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>

// LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize the LCD with its I2C address

// const int turbidityPin = A0;  // Analog input pin for turbidity sensor
// #define SensorPin A1  // pH meter Analog output is connected with the Arduino’s Analog
// unsigned long int avgValue;  // Store the average value of the sensor feedback
// int buf[20], temp;  // Increase the buffer size to capture more samples

// void setup() {
//   pinMode(13, OUTPUT);
//   Serial.begin(9600);
//   Serial.println("Ready");  // Test the serial monitor

//   lcd.begin(16, 2);
//   lcd.backlight();
//   lcd.clear();  // Initialize the LCD
// }

// void loop() {
//   // pH sensor code
//   for (int i = 0; i < 20; i++) {
//     buf[i] = analogRead(SensorPin);
//     delay(5);  // Decrease the delay between samples
//   }
//   for (int i = 0; i < 19; i++) {
//     for (int j = i + 1; j < 20; j++) {
//       if (buf[i] > buf[j]) {
//         temp = buf[i];
//         buf[i] = buf[j];
//         buf[j] = temp;
//       }
//     }
//   }
//   avgValue = 0;
//   for (int i = 2; i < 18; i++) {
//     avgValue += buf[i];
//   }
//   float pHValue = (float)avgValue * 5.0 / 1024 / 16;
//   pHValue = 3.5 * pHValue;
//   Serial.println(pHValue);

//   // Display pH value on the top row of the LCD
//   lcd.setCursor(0, 0);
//   lcd.print("pH: ");
//   lcd.print(pHValue, 2);

//   // Turbidity sensor code
//   int sensorValue = analogRead(turbidityPin);
//   int turbidity = map(sensorValue, 0, 750, 100, 0);  // Corrected map() function
//   Serial.println(turbidity);

//   // Display turbidity value on the bottom row of the LCD
//   lcd.setCursor(0, 1);
//   lcd.print("Turbidity: ");
//   lcd.print(turbidity);

//   digitalWrite(13, HIGH);
//   delay(800);
//   digitalWrite(13, LOW);

//   delay(1000);
// }


// #include <Wire.h>
// #include <ESP8266WiFi.h>  // Add the WiFi library

// const char *ssid = "SmartBro_5EE7";
// const char *pass = "soriano/wifiPSS";

// const int turbidityPin = A0;  // Analog input pin for turbidity sensor
// #define SensorPin A0  // pH meter Analog output is connected with the Arduino’s Analog
// unsigned long int avgValue;  // Store the average value of the sensor feedback
// int buf[20], temp;  // Increase the buffer size to capture more samples

// void setup() {
//   pinMode(13, OUTPUT);
//   Serial.begin(9600);
//   Serial.println("Ready");  // Test the serial monitor

//   // WiFi setup
//   Serial.println("Connecting to ");
//   Serial.println(ssid);
//   WiFi.begin(ssid, pass);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println(WiFi.SSID());
//   Serial.println(WiFi.localIP());
//   Serial.println('\n');
//   Serial.println("Connection established!");
//   Serial.print("IP address:\t");
//   Serial.println(WiFi.localIP());

//   // No LCD initialization needed
// }

// void loop() {
//   // pH sensor code
//   for (int i = 0; i < 20; i++) {
//     buf[i] = analogRead(SensorPin);
//     delay(5);  // Decrease the delay between samples
//   }
//   for (int i = 0; i < 19; i++) {
//     for (int j = i + 1; j < 20; j++) {
//       if (buf[i] > buf[j]) {
//         temp = buf[i];
//         buf[i] = buf[j];
//         buf[j] = temp;
//       }
//     }
//   }
//   avgValue = 0;
//   for (int i = 2; i < 18; i++) {
//     avgValue += buf[i];
//   }
//   float pHValue = (float)avgValue * 5.0 / 1024 / 16;
//   pHValue = 3.5 * pHValue;

//   // Turbidity sensor code
//   int sensorValue = analogRead(turbidityPin);
//   int turbidity = map(sensorValue, 0, 750, 100, 0);  // Corrected map() function

//   // You can print the pH and turbidity values here if needed
//   // For now, we'll just delay for 1 second
//   delay(1000);
// }
