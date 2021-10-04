#define BLYNK_PRINT Serial

#include <DHT.h>
#include <ESP8266WiFi.h> // file untuk modul wifi
#include <BlynkSimpleEsp8266.h> // file untuk blynk

char auth[] = "BBFF-0kFPjZRJqbINSZ3Z6F8MV4cWgIIlyB"; // token yang dikirim dari blynk ke email masing2
char ssid[] = "realme3";
char pass[] = "12345678";

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) { //mengecek kondisi apabila suhu dan kelembatan tidak ada
    Serial.println("Failed to read temp and humidity")
    return;
  }

  Blynk.virtualWrite(V1, t); //setting virtual suhu di Blynk
  Blynk.virtualWrite(V2, h); //setting virtual kelembatan di Blynk
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin(); //sensor mulai membaca suhu dan kelembapan
  timer.setInterval(1000L, sendSensor); //waktu untuk mengirimkan data setiap 1 detik

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
