#include <Arduino.h>

const int pinBotao = 3;

// PROTOTIPOS DAS FUNCOES
void ligaLed(int);
void desligaLed(int);
void piscaLed(int , unsigned long);
int somaDeDoisNumeros(int , int);

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  piscaLed(2, 1000); //pisca o led do pino 2 e fica piscando e desligando em 1 segundo.
  int resultadoDaSoma = somaDeDoisNumeros(4, 8);// criando a variavel resultadoDaSoma recebendo a somaDeDoisNumeros, numeros 4 + 8.
  Serial.println(resultadoDaSoma);// vai mostrar o resultadoDaSoma no monitor serial
}

void ligaLed(int pin) // funcao vazia, que retorna o led ligado numa variavel inteira
{
  digitalWrite(pin, HIGH);//liga o led no pino definido 
}

void desligaLed(int pin)// funcao vazia, que retorna o led desligado numa variavel inteira 
{
  digitalWrite(pin, LOW);// desliga o led no pino definido 
}

void piscaLed(int pin, unsigned long tempo)//funcao vazia, que retorna o led declarado piscando numa variavel inteira, e piscando num  tempo declarado na variavel unsigned long tempo 
{
  ligaLed(pin);//retorna o led ligado numa variavel inteira
  delay(tempo);//da um delay sobre tempo declarado na variavel unsigned long tempo 
  desligaLed(pin);//retorna o led desligado numa variavel inteira 
  delay(tempo);//da um delay sobre tempo declarado na variavel unsigned long tempo 
}

int somaDeDoisNumeros(int numeroA, int numeroB)//variavel inteira que soma dois numeros, que ambos tem a variavel inteira 
{
  int resultado = numeroA + numeroB;// viariavel inteira soma o valor dos dois resultados
  return resultado;// variavel que retorna o valor do resultado
}