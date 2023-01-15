#include <Arduino.h>
#include <BH1750.h>
#include <U8g2lib.h>
#include <WiFi.h>

#include "time.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#endif

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
BH1750 lightMeter(0x23);

const char* ssid = "YOUR WIFI NAME";
const char* password = "YOUR WIFI PASSWORD";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600*11;  //偏离的格林威治时间，11是+11时区
const int daylightOffset_sec = 3600; 

void printLocalTime(U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2, int x, int y) {
  u8g2.setCursor(x, y);
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    u8g2.println("Failed to obtain time");
    return;
  }
  u8g2.println(&timeinfo, "Current Time: %H:%M:%S");
}

void wifi_setup() {
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
}

void setup(void) {
  const int readyLED = 26;
  u8g2.begin();
  Serial.begin(9600);
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }
  wifi_setup();
  pinMode(readyLED, OUTPUT);
  digitalWrite(readyLED, HIGH);
}

void loop(void) {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  u8g2.setFont(u8g2_font_ncenB08_tf);  // 设置屏幕上显示的字体
  u8g2.firstPage();
  do {
    float lux = lightMeter.readLightLevel();
    u8g2.setCursor(0, 20);
    u8g2.print("Light: ");
    u8g2.print(lux);
    u8g2.print(" lx");
    printLocalTime(u8g2, 0, 35);
  } while (u8g2.nextPage());
}
