#define BLYNK_TEMPLATE_ID "TMPL7IkhBa3z"
#define BLYNK_DEVICE_NAME "Weather Monitor"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define USE_NODE_MCU_BOARD

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>

char auth[] = "q7BSrmhfaFQJIXQZ--RBew9-mvKppFPa";//Enter your Auth token
char ssid[] = "Gamma Ray";//Enter your WIFI name
char pass[] = "Galaxy123@";//Enter your WIFI password


#define DHTPIN D4 
#define DHTTYPE DHT11
#define I2C_SCL 04
#define I2C_SDA 05

BlynkTimer timer;
Adafruit_BMP085 bmp;



DHT dht(DHTPIN, DHTTYPE);
float h;

void humidity()
{
  h = dht.readHumidity();  
  Blynk.virtualWrite(V1, h);
}

void pressure()
{
  float temp = bmp.readTemperature();
  float p = bmp.readPressure();
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V2, p);
}

void airQuality()
{
  float mq = analogRead(A0);
  Blynk.virtualWrite(V4, mq);
  if (mq > 500)
  {
    Blynk.logEvent("air_quality", "Harmful gas Detected");
  }
  else if (mq > 400)
  {
    Blynk.logEvent("air_quality", "Smoke Detected");
  }
}

void rainSensor()
{
  float rs = analogRead(D5);
  Blynk.virtualWrite(V5, rs);
  if (rs = 0)
  {
    Blynk.logEvent("water_alert", "Rain/Water Detected!");
  }
}

void setup()
{
  Serial.begin(9600);
  dht.begin();
  Wire.begin(I2C_SDA, I2C_SCL);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  delay(2000); 

  if (!bmp.begin())
  {
    Serial.println(" Could Not find a valid BMP180 sensor ");
  }
  timer.setInterval(1000L, humidity);
  timer.setInterval(1000L, pressure);
  timer.setInterval(1000L, airQuality);
  timer.setInterval(1000L, rainSensor);
}

void loop() 
{
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
