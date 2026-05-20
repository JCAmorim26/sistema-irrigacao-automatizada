#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

#define Sensor A0
#define rele_bomba 4
//para testes, usar:
//#define rele_bomba LED_BUILTIN


int umid;
int umid_min = 5;
int umid_desejada = 37;


void setup() {
  Serial.begin(9600);

  pinMode(rele_bomba, OUTPUT);
  digitalWrite(rele_bomba, LOW);

  if (!rtc.begin()) {
    Serial.println("RTC não encontrado!");
    while (1);
  }

  //--AJUSTE DO HORÁRIO DO MÓDULO--
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Horário do computador
  rtc.adjust(DateTime(2025, 12, 23, 7, 40, 0)); //Horário pré-definido

  //Limpa a memória de alarme. Boa prática
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  //Definir um horário fixo (ex: 8:0:0)
  DateTime horaAlarme1 = DateTime(0, 0, 0, 8, 0, 0);
  DateTime horaAlarme2 = DateTime(0, 0, 0, 16, 0, 0); 
  // Nota: Ano/Mês/Dia são ignorados dependendo do modo escolhido abaixo

  // DS3231_A1_Second = Toca quando os SEGUNDOS baterem (toda vez que o relógio marcar XX:XX:0)
  if (!rtc.setAlarm1(horaAlarme1, DS3231_A1_Hour)) { //Trocar para DS3231_A1_Hour para configurar o alarme ser na hora certa.
    Serial.println("Erro ao definir alarme!");
  } else {
    Serial.print("Alarme 1 definido para: ");
    Serial.print(horaAlarme1.hour());
    Serial.print(":");
    Serial.print(horaAlarme1.minute());
    Serial.print(":");
    Serial.println(horaAlarme1.second());
  }

  if (!rtc.setAlarm2(horaAlarme2, DS3231_A2_Hour)) { //Trocar para DS3231_A1_Hour para configurar o alarme ser na hora certa.
    Serial.println("Erro ao definir alarme!");
  } else {
    Serial.print("Alarme 2 definido para: ");
    Serial.print(horaAlarme2.hour());
    Serial.print(":");
    Serial.print(horaAlarme2.minute());
    Serial.print(":");
    Serial.println(horaAlarme2.second());
  }
}

void loop() {
  
  umid = map(analogRead(Sensor), 1023, 0, 0, 100);
  DateTime now = rtc.now();

  
  if (umid < umid_min){
    digitalWrite(rele_bomba, HIGH);
    delay(10000);
    digitalWrite(rele_bomba, LOW);
  }
  

  //Aciona o sistema quando o alarme disparar
  if (rtc.alarmFired(1)) {
    
    //Permanece irrigando a planta enquanto umidade atual não for igual à desejada
    while (umid <= umid_desejada) {
      Serial.println("Umidade Insuficiente. Bomba acionada.");
      umid = map(analogRead(Sensor), 1023, 0, 0, 100);
      DateTime now = rtc.now();
      //Essa parte é somente para análise no monitor serial
      
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);
      Serial.print(" | Valor do Sensor: ");
      Serial.println(umid);
      
      digitalWrite(rele_bomba, HIGH);
      delay(1000);
    } 
    
    Serial.println("Planta Irrigada =). Bomba Desligando");
    DateTime now = rtc.now();
    

    rtc.clearAlarm(1); 
    Serial.println("Alarme rearmado.");
    digitalWrite(rele_bomba, LOW);
  }

  if (rtc.alarmFired(2)) {
    
    //Permanece irrigando a planta enquanto umidade atual não for igual à desejada
    while (umid <= umid_desejada) {
      Serial.println("Umidade Insuficiente. Bomba acionada.");
      umid = map(analogRead(Sensor), 1023, 0, 0, 100);
      DateTime now = rtc.now();
      //Essa parte é somente para análise no monitor serial
      
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);
      Serial.print(" | Valor do Sensor: ");
      Serial.println(umid);
      
      digitalWrite(rele_bomba, HIGH);
      delay(1000);
    } 
    
    Serial.println("Planta Irrigada =). Bomba Desligando");
    DateTime now = rtc.now();
    

    rtc.clearAlarm(2); 
    Serial.println("Alarme rearmado.");
    digitalWrite(rele_bomba, LOW);
  }
  
  
  // Print para confirmar que está contando. Novamente, não necessário para o código final
  
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  Serial.print(" | Valor do Sensor: ");
  Serial.println(umid);
  
  
  delay(1000);
  
}