#include <Arduino.h>
#include <WiFi.h>
#include "internet.h"
#include "senhas.h"

// -------------- Configuracao do WiFi --------------------

const unsigned long tempoEsperaConexao = 20000;
const unsigned long tempoEsperaReconexao = 5000;

void conectaWiFi()
{
  Serial.printf("conectando ao wiFi: %s", SSID);

  WiFi.begin(SSID, SENHA);

  unsigned long tempoInicialWiFi = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - tempoInicialWiFi < tempoEsperaConexao)
  {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\nWiFi conectado com suceddo! ");
    Serial.print("endereco IP: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("\n falha ao conectar no WiFi. verifique o nome da sete e a senha");
  }
}

void checkWiFi()
{
  unsigned long tempoAtual = millis();
  static unsigned long tempoUltimaConexao = 0;
  if (tempoAtual - tempoUltimaConexao > tempoEsperaReconexao)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("\n conexao perdida! tentando reconectar... ");
      conectaWiFi();
    }
    tempoUltimaConexao = tempoAtual;
  }
}