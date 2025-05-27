//INCLUINDO AS BIBLIOTECAS
#include "BluetoothSerial.h"

//ADICIONANDO FUNCOES
void estadoIR();
void leiturasIR();
void mostrarIR();

//DEFINICAO DOS PINOS
#define IREE 5
#define IRE 15
#define IRC 19
#define IRD 4
#define IRDD 18
#define LED 23

//DEFINICAO DOS MOTORES
#define MotorDP 13
#define MotorDN 27
#define MotorEP 26
#define MotorEN 25

//VELOCIDADE DO MOTOR
#define Vpadrao 255
#define Verro1 235
#define Verro2 100

//COR DA LEITURA IR
#define branco 1
#define preto 0

BluetoothSerial serialBLE;

char dados;
bool conexao;
int estadoEE, estadoE, estadoC, estadoD, estadoDD;

void setup() {
  Serial.begin(9600);
  serialBLE.begin("EngRobots");

  pinMode(IREE, INPUT);
  pinMode(IRE, INPUT);
  pinMode(IRC, INPUT);
  pinMode(IRD, INPUT);
  pinMode(IRDD, INPUT);
  pinMode(LED, OUTPUT);

  pinMode(MotorDP, OUTPUT);
  pinMode(MotorDN, OUTPUT);
  pinMode(MotorEP, OUTPUT);
  pinMode(MotorEN, OUTPUT);
}

void loop() {
  analogWrite(MotorDP, 0);
  analogWrite(MotorDN, 0);
  analogWrite(MotorEP, 0);
  analogWrite(MotorEN, 0);
  digitalWrite(LED, HIGH);

  leiturasIR();

  conexao = serialBLE.available();
  if (conexao) {
    dados = serialBLE.read();
    if (dados == 'L') {
      while (dados != 'D') {
        leiturasIR();
        estadoIR();
        dados = serialBLE.read();
      }
    }
  }
}

void leiturasIR() {
  estadoEE = digitalRead(IREE);
  estadoE = digitalRead(IRE);
  estadoC = digitalRead(IRC);
  estadoD = digitalRead(IRD);
  estadoDD = digitalRead(IRDD);
}

void estadoIR() {
  if ((estadoEE == branco) && (estadoE == branco) && (estadoC == preto) && (estadoD == branco) && (estadoDD == branco)) {
    analogWrite(MotorDP, Vpadrao);
    analogWrite(MotorEP, Vpadrao);
  } else if ((estadoE == preto)) {
    analogWrite(MotorDP, Vpadrao);
    analogWrite(MotorEP, Verro1);
  } else if ((estadoD == preto)) {
    analogWrite(MotorDP, Verro1);
    analogWrite(MotorEP, Vpadrao);
  } else if ((estadoEE == preto)) {
    analogWrite(MotorDP, Vpadrao);
    analogWrite(MotorEP, Verro2);
  } else if ((estadoDD == preto)) {
    analogWrite(MotorDP, Verro2);
    analogWrite(MotorEP, Vpadrao);
  } else if ((estadoEE == preto) && (estadoE == preto) && (estadoC == preto) && (estadoD == preto) && (estadoDD == preto)) {
    analogWrite(MotorDP, Vpadrao);
    analogWrite(MotorEP, Vpadrao);
  }
}

void mostrarIR() {
  Serial.println(estadoEE);
  Serial.println(estadoE);
  Serial.println(estadoC);
  Serial.println(estadoD);
  Serial.println(estadoDD);
}
