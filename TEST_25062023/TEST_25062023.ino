#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include <LiquidCrystal.h>
#include <DHT.h>
#include <WiFiManager.h>
#include <Button2.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <EEPROM.h>
#include <BlynkSimpleEsp32.h> // Thêm thư viện Blynk

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6l-vlcK7W"
#define BLYNK_TEMPLATE_NAME "DoAn2"
#define BLYNK_AUTH_TOKEN "ZYkdM9D7GR6fcplqione0iFsbWopARjq"



#define DHT_PIN 4
#define DHT_TYPE DHT11
#define bt 33
#define MQ_PIN 5
#define FLAME_PIN 6
#define LED_PIN 2 // Chân điều khiển đèn màu xanh
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
DHT dht(DHT_PIN, DHT_TYPE);

TaskHandle_t Task1;
TaskHandle_t Task2;
SemaphoreHandle_t lcdSemaphore;

volatile bool switchPage = false;
volatile int currentPage = 1;
unsigned long lastDebounceTime = 0;

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 25200;
const int daylightOffset_sec = 0;


WiFiManager wifiManager;
Button2 resetButton(bt);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  EEPROM.begin(512);
  Serial.begin(9600);
  delay(3000);
  resetButton.setLongClickHandler([](Button2 & btn) {
    wifiManager.resetSettings();
    delay(1000);
    ESP.restart();
  });

  wifiManager.autoConnect("Hệ thống nhà kho");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Đang kết nối WiFi...");
  }
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  while (!time(nullptr)) {
    delay(1000);
    Serial.println("Đang đồng bộ thời gian...");
  }

  lcdSemaphore = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(
    task1,
    "Task1",
    10000,
    NULL,
    1,
    &Task1,
    1
  );

  xTaskCreatePinnedToCore(
    task2,
    "Task2",
    10000,
    NULL,
    1,
    &Task2,
    0
  );

  attachInterrupt(
    digitalPinToInterrupt(2),
    switchPageButtonInterrupt,
    RISING
  );

    Blynk.begin(BLYNK_AUTH_TOKEN, WiFi.SSID().c_str(), WiFi.psk().c_str());
    pinMode(LED_PIN, OUTPUT);
}

BLYNK_WRITE(V1){
  int btn = param.asInt();
  if(btn == 1){
    digitalWrite(LED_PIN, HIGH);
  }
  else{
    digitalWrite(LED_PIN,LOW);
  }
}

void loop() {
  resetButton.loop();
  
  Blynk.run();
}

void task1(void* parameter) {
  for (;;) {
    if (currentPage == 1) {
      display1();
    }

    delay(1000);
  }
}

void task2(void* parameter) {
  for (;;) {
    if (currentPage == 2) {
      display2();
    }
    delay(1000);
  }
}

void switchPageButtonInterrupt() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime > 200) {
    switchPage = true;
  }
  lastDebounceTime = currentMillis;

  currentPage = (currentPage == 1) ? 2 : 1;
}

void display1() {
  time_t now = time(nullptr);
  struct tm* timeinfo;
  timeinfo = localtime(&now);

  xSemaphoreTake(lcdSemaphore, portMAX_DELAY);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ngay: ");
  lcd.print(getFormattedDate(timeinfo));

  lcd.setCursor(0, 1);
  lcd.print("Gio: ");
  lcd.print(getFormattedTime(timeinfo));

  xSemaphoreGive(lcdSemaphore);
}

void display2() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int mqValue = analogRead(MQ_PIN);
  int flameValue = digitalRead(FLAME_PIN);

  xSemaphoreTake(lcdSemaphore, portMAX_DELAY);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(8, 0);
  lcd.print("H:");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("G:");
  lcd.print(mqValue);

  lcd.setCursor(8, 1);
  lcd.print("F:");
  lcd.print(flameValue);

  xSemaphoreGive(lcdSemaphore);
}

String getFormattedDate(struct tm* timeinfo) {
  char buffer[20];
  sprintf(buffer, "%02d/%02d/%04d",
          timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);

  return String(buffer);
}

String getFormattedTime(struct tm* timeinfo) {
  char buffer[20];
  sprintf(buffer, "%02d:%02d:%02d",
          timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  return String(buffer);
}
