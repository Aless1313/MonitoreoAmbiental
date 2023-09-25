#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <DHT.h>
#include <MQ135.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

MQ135 gasSensor = MQ135(A0);

void setup() {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();



  display.display();
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  MQ135 gasSensor = MQ135(A0);
  float ppm = gasSensor.getPPM();

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperatura: ");
  display.print(String(temperature));
  display.println(" C");
  display.print(F("Humedad: "));
  display.print(humidity);
  display.println(F("%"));
  display.print(F("PPM: "));
  display.print(String(ppm));
  display.println(F(" ppm"));
  Serial.println(ppm);

  display.display();
  delay(2000);

}
