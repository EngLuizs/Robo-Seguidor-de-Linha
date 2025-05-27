//INCLUINDO AS BIBLIOTECAS 
#include "BluetoothSerial.h" 
//ADICIONANDO FUNCOES 
void estadoIR(); 
void leiturasIR(); 
void mostrarIR(); 
//DEFINICÃO DOS PINOS 
#define IREE 5 
#define IRE 15 
#define IRC 19 
#define IRD 4 
#define IRDD 18 
#define LED 23 

//DEFINICÃO DOS MOTORES 
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
 
//CONFIGURANDO COMUNICACAO BLUETOOTH 
  BluetoothSerial serialBLE; 
 
//ADICIONANDO VARIAVEIS 
  char dados; 
  bool conexao; 
  int estadoEE, estadoE, estadoC, estadoD, estadoDD; 
 
void setup() { 
  
  //IDENTIFICACAO BLUETOOTH 
    Serial.begin(9600); 
    serialBLE.begin("EngRobots"); 
  //CONFIGURACAO SENSORES IR 
    pinMode(IREE, INPUT); 
    pinMode(IRE, INPUT); 
    pinMode(IRC, INPUT); 
    pinMode(IRD, INPUT); 
    pinMode(IRDD, INPUT); 
 
  //CONFIGURANDO LED 
    pinMode(LED, OUTPUT); 
 
  //CONFIGURACAO MOTORES 
    pinMode(MotorDP, OUTPUT); 
    pinMode(MotorDN, OUTPUT); 
    pinMode(MotorEP, OUTPUT); 
    pinMode(MotorEN, OUTPUT); 
    pinMode(Vpadrao, OUTPUT); 
    pinMode(Verro1, OUTPUT); 
    pinMode(Verro2, OUTPUT); 
 
 
    //analogWrite(Vpadrao, 255); 
} 
 
void loop() { 
 
  //INICIANDO MOTORES DESLIGADOS 
    analogWrite(MotorDP, 0); 
    analogWrite(MotorDN, 0); 
    analogWrite(MotorEP, 0); 
    analogWrite(MotorEN, 0); 
 
  //LIGANDO LED 
    digitalWrite(LED, HIGH); 
 
  //LENDO SENSORES IR 
    leiturasIR(); 
    //mostrarIR(); 
 
  //COMANDOS BLUETOOTH 
    conexao = serialBLE.available(); 
    if (conexao == true) 
    { 
      dados = serialBLE.read(); 
      if (dados == 'L') 
      { 
        while (dados != 'D') 
        { 
          leiturasIR(); 
          estadoIR(); 
          dados = serialBLE.read(); 
        } 
      } 
    } 
} 
 
void leiturasIR() 
{ 
  //NOMEANDO E LENDO ESTADOS DOS SENSORES 
    estadoEE = digitalRead(IREE); 
    estadoE = digitalRead(IRE); 
    estadoC = digitalRead(IRC); 
    estadoD = digitalRead(IRD); 
    estadoDD = digitalRead(IRDD); 
} 
 
void estadoIR() 
{ 
 
  //00100 
  if ((estadoEE == branco) && (estadoE == branco) && (estadoC 
== preto) && (estadoD == branco) && (estadoDD == branco)) 
  { 
    analogWrite(MotorDP, Vpadrao); 
    analogWrite(MotorDN, 0); 
    analogWrite(MotorEP, Vpadrao); 
    analogWrite(MotorEN, 0); 
    leiturasIR(); 
  } 
 
  //01000 
  if ((estadoEE == branco) && (estadoE == preto) && (estadoC 
== branco) && (estadoD == branco) && (estadoDD == branco)) 
  { 
      analogWrite(MotorDP, Vpadrao); 
      analogWrite(MotorDN, 0); 
      analogWrite(MotorEP, Verro1); 
      analogWrite(MotorEN, 0); 
      leiturasIR(); 
  } 
 
  // 00010 
  if ((estadoEE == branco) && (estadoE == branco) && (estadoC 
== branco) && (estadoD == preto) && (estadoDD == branco)) 
  { 
      analogWrite(MotorDP, Verro1); 
      analogWrite(MotorDN, 0); 
      analogWrite(MotorEP, Vpadrao); 
      analogWrite(MotorEN, 0); 
      leiturasIR(); 
  } 
 
  //10000 
  if ((estadoEE == preto) && (estadoE == branco) && (estadoC 
== branco) && (estadoD == branco) && (estadoDD == branco)) 
  { 
      analogWrite(MotorDP, Vpadrao); 
      analogWrite(MotorDN, 0); 
      analogWrite(MotorEP, Verro2); 
      analogWrite(MotorEN, 0); 
      leiturasIR(); 
  } 
 
  //00001 
  if ((estadoEE == branco) && (estadoE == branco) && (estadoC 
== branco) && (estadoD == branco) && (estadoDD == preto)) 
  { 
      analogWrite(MotorDP, Verro2); 
      analogWrite(MotorDN, 0); 
      analogWrite(MotorEP, Vpadrao); 
      analogWrite(MotorEN, 0); 
      leiturasIR(); 
  } 
 
  //11111 
  if ((estadoEE == preto) && (estadoE == preto) && (estadoC 
== preto) && (estadoD == preto) && (estadoDD == preto)) 
  { 
      analogWrite(MotorDP, Vpadrao); 
      analogWrite(MotorDN, 0); 
      analogWrite(MotorEP, Vpadrao); 
      analogWrite(MotorEN, 0); 
      leiturasIR(); 
  } 
} 
 
void mostrarIR() 
{ 
  Serial.print("EstadoEE"); 
  Serial.println(estadoEE); 
  delay(1000); 
  Serial.print("EstadoE"); 
  Serial.println(estadoE); 
  delay(1000); 
  Serial.print("EstadoC"); 
  Serial.println(estadoC); 
  delay(1000); 
  Serial.print("EstadoD"); 
  Serial.println(estadoD); 
  delay(1000); 
  Serial.print("EstadoDD"); 
  Serial.println(estadoDD); 
  delay(1000); 
} 
