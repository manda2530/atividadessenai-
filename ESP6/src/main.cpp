#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "internet.h"
#include "certificados.h"
#include <Bounce2.h>



WiFiClientSecure espClient;
PubSubClient client(espClient);
Bounce botao = Bounce();

const int mqtt_port = 8883;
const char *mqtt_id = "espamandaalertamesa04";
const char *mqttTopic = "senai134/alerta";

const int botaoPin = 0;

void conectarMQTT() 
{
  while (!client.connected()) 
  {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(mqtt_id)) 
    {
      Serial.println("Conectado!");
    } else 
    {
      Serial.print("Erro: ");
      Serial.print(client.state());
      Serial.println(" tentando em 2s...");
      delay(2000);
    }
  }
}

void enviarAlerta() 
{
  JsonDocument doc;
  doc["tipo"] = "alerta";
  doc["mensagem"] = "preciso de ajuda!";
  doc["dispositivo"] = "relogio";

   String msm;
  serializeJson(doc, msm);  

 

  client.publish(mqttTopic, msm.c_str());
  Serial.println(" Alerta enviado via MQTT:");
  Serial.println(msm);
}

void Callback(char *topic, byte *payLoad, unsigned int Length)
{
  String msg((char *)payLoad, Length);
  Serial.print("..........................");
  Serial.printf("mensagem recebida (topico: [%s]): %s\n\r", topic, msg.c_str());
}



void setup()
{
  Serial.begin(9600);
 
  pinMode(botaoPin, INPUT_PULLUP);
  botao.attach(botaoPin);
  botao.interval(10); 

  conectaWiFi();


  espClient.setCACert(AWS_ROOT_CA);
  espClient.setCertificate(AWS_CERT);
  espClient.setPrivateKey(AWS_KEY);

  client.setServer(AWS_BROKER, mqtt_port);
  client.setCallback(Callback);
  

  
}

void loop()
{
  botao.update();
  checkWiFi();

  if (!client.connected())
    conectarMQTT();


  client.loop();


  if (botao.fell()) 
  {
    enviarAlerta(); 
  }

}
