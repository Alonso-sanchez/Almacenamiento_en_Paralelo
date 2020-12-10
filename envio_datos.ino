#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>
Servo servoMotor;
int i = 0;
int StadoIzq = 5;
int StadoDch = 4;
int ledIzq = 14;
int ledDer = 12;
int estadoIzquierda = 0;
int estadoDerecha = 0;
float estadoActual = 0;
String server = "";

const char *ssid = "IZZI-68F6";
const char *password = "2C9569AA68F6";

void setup()
{
  //Configuracion de pin's
  pinMode(StadoIzq, INPUT);
  pinMode(StadoDch, INPUT);
  pinMode(ledIzq, OUTPUT);
  pinMode(ledDer, OUTPUT);
  servoMotor.attach(14);

  Serial.begin(9600);

  Serial.println("WiFi connected");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED)
  { //Check WiFi connection status

    HTTPClient http;
    http.begin("http://144.202.34.148:6969/device/");

    int httpCode = http.GET();
    String payload = http.getString();
    if (httpCode > 0) {
      String payload2 = payload;
      char json[500];
      payload2.toCharArray(json, 500);
      //      Serial.println(payload2);
      StaticJsonDocument<256> doc;

      deserializeJson(doc, json);

      String estado = doc["estado"];
      int angulo = doc["angulo"];


      // Serial.println("Imprimiendo el estado del apagador");
      for (i; i < 180; i++)
      {
        servoMotor.write(i);
        estadoIzquierda = digitalRead(StadoIzq);
        estadoDerecha = digitalRead(StadoDch);

        if ((estadoActual != 1) and (estadoIzquierda == HIGH)) {
          estadoActual = 1;
          Serial.println("Izquierda");
          digitalWrite(ledIzq, HIGH);
          digitalWrite(ledDer, LOW);
          post("Izquierda", i);
        }
        if ((estadoActual != 3) and (estadoDerecha == HIGH)) {
          estadoActual = 3;
          Serial.println("Derecha");
          digitalWrite(ledIzq, LOW);
          digitalWrite(ledDer, HIGH);
          post("Derecha", i);
        }
        if ((estadoActual != 2) and (estadoDerecha == LOW ) and (estadoIzquierda == LOW)) {
          estadoActual = 2;
          Serial.println("Centro");
          digitalWrite(ledIzq, LOW);
          digitalWrite(ledDer, LOW);
          post("Centro", i);
        }
        delay(25);
      }
      for (i; i > 0; i--)
      {
        servoMotor.write(i);

      }
      //delay(800);
    }
  }
}

void post(String estado, int angulo) {
  Serial.println("Inicio post");
  HTTPClient http;
  String json;
  server = "http://144.202.34.148:6969/device/";

  StaticJsonDocument<256> doc;
  doc["estado"] = String(estado);
  doc["angulo"] = int(angulo);
  serializeJson(doc, json);

  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println("Termino post");
}
