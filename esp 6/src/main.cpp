#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>
#include <ArduinoJson.h>

using FalhaJson = DeserializationError;

bool Relogio = true;

uint8_t endSlave[] = {0xD8, 0x3B, 0xDA, 0x4C, 0x76, 0x20};

const int PinBotao = 0;
Bounce botao;
BluetoothSerial SerialBT;

unsigned long ultimaTentativa = 0;
const unsigned long intervaloReconexao = 5000;

void setup()
{
  Serial.begin(9600);

  if (Relogio)
  {
    botao.attach(PinBotao, INPUT_PULLUP);
    botao.interval(25);

    SerialBT.begin("ESP_Relogio");
    Serial.println("tentando conectar ao receptor...");

   if (!SerialBT.connect(endSlave))
    {
      Serial.println("Falha na conexão Bluetooth com o receptor");
    }
    else
    {
      Serial.println("Conectado ao receptor!");
    }
  }
  else
  {
    SerialBT.begin("ESP_Receptor");
    Serial.println("Aguardando conexões via Bluetooth...");
  }
}

void loop()
{
  if (Relogio)
  {
    if (!SerialBT.connected())
    {
      if (millis() - ultimaTentativa >= intervaloReconexao)
      {
        ultimaTentativa = millis();
        Serial.println("Reconectando ao receptor...");
        if (SerialBT.connect(endSlave))
        {
          Serial.println("Reconectado ao receptor!");
        }
        else
        {
          Serial.println("Falha na reconexão. Tentando novamente em 5s...");
        }
      }
      return;
    }

    botao.update();

    if (botao.fell())
    {
      Serial.println("Botão pressionado! Enviando alerta via Bluetooth...");

      StaticJsonDocument<100> doc;

      doc["tipo"] = "alerta";
      doc["mensagem"] = "paciente precisa de ajuda";

      String mensagemJson;
      serializeJson(doc, mensagemJson);

      SerialBT.println(mensagemJson);
    }
  }
  else
  {
    if (SerialBT.available())
    {
      String jsonString = SerialBT.readStringUntil('\n');
      Serial.println("Recebido via Bluetooth: " + jsonString);

      StaticJsonDocument<200> doc;

      FalhaJson erro = deserializeJson(doc, jsonString);


      if (!erro && doc["tipo"] == "alerta")
      {
        Serial.println(" ALERTA RECEBIDO: " + String((const char *)doc["mensagem"]));
      }
      else
      {
        Serial.println("Erro ao interpretar JSON ou mensagem inválida.");
      }
    }
  }
}
