//Configurações do Display
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*---------------------------------------------*/

int var_control = 1, min_umid = 20, max_umid = 55;

/*Criando o Simbolo da Mecajun pro Display*/

byte Triangulo_Baixo[8] = {
0b00000,
0b00000,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000,
0b00000
};


byte Triangulo_Cima[8] = {
0b00000,
0b00000,
0b00100,
0b01110,
0b11111,
0b11111,
0b00000,
0b00000
};

/*-------------------------------------*/

/*--Criando o Símbolo de Torneira--*/


byte Torneira[8] =
{
0b00000,
0b01010,
0b00100,
0b11110,
0b11110,
0b00110,
0b00000,
0b00010
};

/*---------------------------------*/

/*--Função Para Mostrar a Tela Inicial--*/

void TelaInicial(){

  lcd.clear();
  delay(500);

  lcd.setCursor(0, 0);
  lcd.print("Projeto Automate");
  delay(500);

  lcd.setCursor(6, 1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(7, 1);
  lcd.write(byte(1));
  delay(500);
  lcd.setCursor(8, 1);
  lcd.write(byte(0));
  delay(3000);

}
/*-------------------------------------*/

/*--Função que Exibe os Dados Na Tela--*/
void TelaDeDados(int umidade1, int umidade2, int rele_ligado){
  
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("S1=  % & S2=  %");

  //Atualiza no display os dados dos sensores
  if((umidade1 > 9) && (umidade1 < 100)){
    lcd.setCursor(3, 0);
    lcd.print(umidade1);
  } else {
    lcd.setCursor(3, 0);
    lcd.print("0");
    lcd.setCursor(4, 0);
    lcd.print(umidade1);
  }
  if((umidade2 > 9) && (umidade2 < 100)){
    lcd.setCursor(12, 0);
    lcd.print(umidade2);
  } else {
    lcd.setCursor(12, 0);
    lcd.print("0");
    lcd.setCursor(13, 0);
    lcd.print(umidade2);
  }

  if (rele_ligado == 0){
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Bomba = Desl.");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Irrig. = Lig.");
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  }
  
  delay(5000);

}
/*-------------------------------------*/


#define Sensor1 A0
#define Sensor2 A1

int umidade1 = 0, umidade2 = 0;

#define rele_bomba 8

int rele_ligado = 0;

void setup() {

  //Coloca o número de coluna e linhas do display 
  lcd.begin(16, 2);

  //Configurações do Relé da Bomba
  pinMode(rele_bomba, OUTPUT);
  digitalWrite(rele_bomba, LOW);

  //Cria os caracteres especiais pro display
  lcd.createChar(0, Triangulo_Baixo);
  lcd.createChar(1, Triangulo_Cima);
  lcd.createChar(2, Torneira);
  
  //Escreve a mensagem inicial no Display
  TelaInicial();

  //Inicia o monitor serial
  Serial.begin(9600);


}

void loop() {

  //Lê o primeiro sensor
  umidade1 = analogRead(Sensor1);
  umidade1 = map(umidade1, 400, 1023, 100, 0);

  //Lê o segundo sensor
  umidade2 = analogRead(Sensor2);
  umidade2 = map(umidade2, 400, 1023, 100, 0);

  while (var_control == 1){
    
    TelaDeDados(umidade1, umidade2, rele_ligado);
    TelaInicial();

    //Lê o primeiro sensor
    umidade1 = analogRead(Sensor1);
    umidade1 = map(umidade1, 400, 1023, 100, 0);

    //Lê o segundo sensor
    umidade2 = analogRead(Sensor2);
    umidade2 = map(umidade2, 400, 1023, 100, 0);

    if((umidade1 <= min_umid) || (umidade2 <= min_umid)){
      var_control = 0;
      rele_ligado = 1;
      digitalWrite(rele_bomba, HIGH);
    }
  }

  while (var_control == 0){

    //Lê o primeiro sensor
    umidade1 = analogRead(Sensor1);
    umidade1 = map(umidade1, 400, 1023, 100, 0);
  
    //Lê o segundo sensor
    umidade2 = analogRead(Sensor2);
    umidade2 = map(umidade2, 400, 1023, 100, 0);

    TelaDeDados(umidade1, umidade2, rele_ligado);

    if((umidade1 >= max_umid) || (umidade2 >= max_umid)){
      var_control = 1;
      rele_ligado = 0;
      digitalWrite(rele_bomba, LOW);
    }

    delay(1000);
  }

}
