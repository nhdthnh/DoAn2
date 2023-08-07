#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include <LiquidCrystal.h>

//0x3F or 0x27
LiquidCrystal lcd(19, 23, 18, 17, 16, 15); // Khởi tạo LCD

const char* ssid       = "Tang 2";
const char* password   = "thanhdat16";

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 25200; // GMT+7
const int daylightOffset_sec = 0; 

void setup() {
  lcd.begin(16, 2); // Khởi tạo LCD với 16 cột và 2 hàng

  WiFi.begin(ssid, password); // Kết nối WiFi

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2); // Cấu hình đồng bộ thời gian từ NTP server

  while (!time(nullptr)) {
    delay(1000);
    Serial.println("Waiting for time sync...");
  }
}

void loop() {
  time_t now = time(nullptr); // Lấy thời gian hiện tại
  struct tm* timeinfo;
  timeinfo = localtime(&now); // Chuyển đổi thời gian sang địa phương

  lcd.clear(); // Xóa màn hình LCD
  lcd.setCursor(0, 0); // Đặt con trỏ về vị trí đầu tiên trên dòng 1
  lcd.print("Ngay: ");
  lcd.print(getFormattedDate(timeinfo)); // Hiển thị ngày giờ

  lcd.setCursor(0, 1); // Đặt con trỏ về vị trí đầu tiên trên dòng 2
  lcd.print("Gio: ");
  lcd.print(getFormattedTime(timeinfo)); // Hiển thị giờ phút giây

  delay(1000); // Đợi 1 giây trước khi cập nhật lại
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