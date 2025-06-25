#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "timer.h"

const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char *mqtt_client_id = "amandinha";
const char *mqtt_topic_sub = "senai134/mesa01/amanda/espsub";
const char *mqtt_topic_pud = "senai134/mesa01/thiago/esppub";

WiFiClient espClient;
PubSubClient client(espClient);
Temporizador timer(2000);

bool alterna = false;

unsigned long ultimaTentativaWiFi = 0;
unsigned long ultimaTentativaMQTT = 0;

void setup()
{
  Serial.begin(9600);
  timer.iniciar();
}

void loop()
{
  unsigned long agora = millis();

  if (WiFi.status() != WL_CONNECTED)
  {
    if (agora - ultimaTentativaWiFi > 5000)
    {
      Serial.println("Tentando se conectar ao WiFi...");
      WiFi.begin("SALA 09", "info@134");  
      ultimaTentativaWiFi = agora;
    }
    return;
  }

  if (!client.connected())
  {
    Serial.println("Tentando se conectar ao MQTT...");
    if (client.connect(mqtt_client_id))
    {
      Serial.println("Conectado ao MQTT!");
      client.subscribe(mqtt_topic_sub);
    }
    else
    {
      Serial.print("Falha na conexão MQTT, rc=");
      Serial.println(client.state());
      return;
    }
  }

  client.loop();

  if (timer.estaPronto() && client.connected())
  {
    if (alterna)
    {
      client.publish(mqtt_topic_sub, "estadoTimerA");
    }
    else
    {
      client.publish(mqtt_topic_sub, "estadoTimerB");
    }
    alterna = !alterna;
    timer.reiniciar();
  }
}
