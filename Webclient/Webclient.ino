#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

int PINO_TERMISTOR = A0;
int ID_ESTE_DISPOSITIVO = 101;
float temperatura;

// Executar sudo chmod a+rw /dev/ttyUSB0 no terminal

// Credenciais da rede
char* ssid = "brisa-3608279";
char* password = "denitqdl";

// Informações do servidor
String nomeServidor = "http://192.168.0.4:1880/registrar-temperatura";

void conectarWifi(){
  Serial.begin(115200);
  Serial.print("\nTentando conexão com o SSId: ");
  Serial.println(ssid);
  Serial.println(password);

  WiFi.begin(ssid, password);
  Serial.print("Aguardando");
  uint8_t status = WiFi.waitForConnectResult();
  while( status != WL_CONNECTED){
    delay(8000);
    Serial.print(status);
    status = WiFi.waitForConnectResult();
  }
    
  Serial.println("\n");
  Serial.print  ("Conectado. IP: ");
  Serial.println(WiFi.localIP());
  conexao_ativa();
  Serial.println("\n");
}

uint8_t conexao_ativa(){
  Serial.print("Estado da Conexão: ");
  uint8_t online = WiFi.status() == WL_CONNECTED;
  if (online){
    Serial.println ("Online");
  } else {
    Serial.println ("Offline");
  }
  return online;
}

double ler_temperatura(bool celsius){
  float leitura = analogRead(PINO_TERMISTOR);
  double temp_celsius;
  temp_celsius=log(10000.0*((1024.0/leitura-1)));
  temp_celsius=1/(0.001129148+(0.000234125+(0.0000000876741*temp_celsius*temp_celsius))*temp_celsius);
  temp_celsius=temp_celsius-273.15;

  if (celsius) {
    Serial.print("Temperatura lida: ");
    Serial.print(temp_celsius);
    Serial.println("°C");
    return temp_celsius;
  } else {
    double temp_fahrenheit=(temp_celsius*9.0)/5.0+32.0;
    Serial.print("Temperatura lida: ");
    Serial.print(temp_fahrenheit);
    Serial.println("°F");
    return temp_fahrenheit;
  }
}

String enviar_temperatura_get(double temperatura, String nomeServidor){
  WiFiClient client;
  HTTPClient http;

  String dados = "?idDispositivo=" + String(ID_ESTE_DISPOSITIVO) +
                 "&valor=" + String(temperatura) +
                 "&escala='C'";
  http.begin(client, nomeServidor + dados);
  int httpResponseCode = http.GET();
  String payload = "";
    
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    payload = "ERRO";
  }
  // Free resources
  http.end();
  return payload;
}

String enviar_temperatura_post(double temperatura, String nomeServidor){
    WiFiClient client;
    HTTPClient http;
    http.begin(client, nomeServidor);
    String payload = "";

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST("{\"idDispositivo\":" + String(ID_ESTE_DISPOSITIVO) + "," +
                                     "\"valor\":" + String(temperatura) + "," +
                                     "\"escala\":\"C\"}");
      
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      payload = http.getString();
    }
      // Free resources
    http.end();
    return payload;
}

String enviar_temperatura(float temperatura, String metodo, String nomeServidor){
  Serial.println("Executando Envio de temperatura via " + metodo);
  String retorno = "";
  if(metodo == "GET") {
    retorno = enviar_temperatura_get(temperatura, nomeServidor);
  }
  if(metodo == "POST") {
    retorno = enviar_temperatura_post(temperatura, nomeServidor);
  }
  return retorno;
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  conectarWifi();
}

void loop() {
  if (conexao_ativa()){
    // Enviar temperatura
    temperatura = ler_temperatura(true);
    enviar_temperatura(temperatura, "POST", nomeServidor);
  }
  delay(5000);
}
