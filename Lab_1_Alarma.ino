

/*Revelo Byron
 *Laboratorio 1 Modificar Alarma de Reloj
 *Modificar la hora de Alarma del Reloj por medio de pulsadores
 *Modificar la hora, minutos 
*/

#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int Pulsa_Menu=7;
const int Pulsa_Mas=8;
const int Pulsa_Menos=9;
const int Led = 12;
const int Apagar = 11;

int horas =0;
int minutos=0;
volatile int segundos=0;
volatile boolean actualizar=true;

int alarma_hora=0;
int alarma_minutos=0;
boolean alarmaOn = false;

char texto[10];
int menu=0;
const int N=6;


void setup() {
  Wire.begin();
  lcd.begin(16,2);
  lcd.clear();
  lcd.backlight();
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(11,INPUT);
  pinMode(12,OUTPUT);
  
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(Timer);

}


void Timer(){
   segundos++;
   actualizar = true;  
  }

void actualizarReloj(){
  minutos += segundos / 60;
  segundos = segundos % 60;
  
  horas += minutos / 60;
  minutos = minutos % 60;

  horas = horas % 24;
  
  }

 void subeHoras(){
    horas++;
    horas = horas % 24;
    actualizar = true;
 }

  void bajaHoras(){
    horas--;
    if (horas<0){
      horas = 23;
      }
      actualizar = true;
    }

     void incrementaAlarmaH(){
    alarma_hora++;
    alarma_hora = alarma_hora % 24;
    actualizar = true;
 }

  void decrementaAlarmaH(){
    alarma_hora--;
    if (alarma_hora<0){
      alarma_hora = 23;
      }
      actualizar = true;
    }

 void subeMinutos(){
    minutos++;
    minutos = minutos % 60;
    actualizar = true;
 }

  void bajaMinutos(){
    minutos--;
    if (minutos<0){
      minutos = 59;
      }
      actualizar = true;
    }

    void incrementaAlarmaM(){
    alarma_minutos++;
    alarma_minutos = alarma_minutos % 60;
    actualizar = true;
 }

  void decrementaAlarmaM(){
    alarma_minutos--;
    if (alarma_minutos<0){
      alarma_minutos = 59;
      }
      actualizar = true;
    }

  void fijarMenu(){
    switch(menu){
      case 0:
      lcd.noBlink();
      break;
      case 1:
      lcd.setCursor(0,0);
      lcd.blink();
      break;
      case 2:
      lcd.setCursor(3,0);
      lcd.blink();
      break;
      case 3:
      lcd.setCursor(0,1);
      lcd.blink();
      break;
      case 4:
      lcd.setCursor(3,1);
      lcd.blink();
      break;
       case 5:
        lcd.setCursor(6,1);
        lcd.blink();
      break;
      }
    }
    
void loop() {

  if(digitalRead(Pulsa_Menu)==HIGH){
    menu++;
    menu = menu % N;
    fijarMenu();
    while(digitalRead(Pulsa_Menu)==HIGH); 
    }

    if(digitalRead(Apagar)==HIGH){
    if (digitalRead(Led)==HIGH){
      digitalWrite(Led,LOW);
      }
    }
    switch(menu){
      //MODIFICAR RELOJ
      case 1:
        if (digitalRead(Pulsa_Mas)==HIGH){
          subeHoras();
          while(digitalRead(Pulsa_Mas)==HIGH);
          }
           if (digitalRead(Pulsa_Menos)==HIGH){
          bajaHoras();
          while(digitalRead(Pulsa_Menos)==HIGH);
          }
      break;
      
      case 2:
        if (digitalRead(Pulsa_Mas)==HIGH){
          subeMinutos();
          while(digitalRead(Pulsa_Mas)==HIGH);
        }
        if (digitalRead(Pulsa_Menos)==HIGH){
          bajaMinutos();
          while(digitalRead(Pulsa_Menos)==HIGH);
        }
      break;
      //MODIFICAR ALARMA
      case 3:
        if (digitalRead(Pulsa_Mas)==HIGH){
          incrementaAlarmaH();
          while(digitalRead(Pulsa_Mas)==HIGH);
        }
        if (digitalRead(Pulsa_Menos)==HIGH){
          decrementaAlarmaH();
          while(digitalRead(Pulsa_Menos)==HIGH);
        }
      break;

      case 4:
        if (digitalRead(Pulsa_Mas)==HIGH){
          incrementaAlarmaM();
          while(digitalRead(Pulsa_Mas)==HIGH);
        }
        if (digitalRead(Pulsa_Menos)==HIGH){
          decrementaAlarmaM();
          while(digitalRead(Pulsa_Menos)==HIGH);
        }
      break;

      case 5:
         if (digitalRead(Pulsa_Mas)==HIGH){
          alarmaOn = !alarmaOn;
          actualizar= true;
          while(digitalRead(Pulsa_Mas)==HIGH);
        }
      break;
      }
  
  if(actualizar == true){
  actualizarReloj();
  lcd.clear();
  lcd.noBlink();
  //RELOJ
  lcd.setCursor(0,0);
  sprintf(texto,"%02d:%02d:%02d",horas,minutos,segundos);
  lcd.print(texto);
  //ALARMA
  lcd.setCursor(0,1);
  sprintf(texto,"%02d:%02d",alarma_hora,alarma_minutos);
  lcd.print(texto);

  if (alarmaOn==true){
    if(segundos == 0 && horas == alarma_hora && minutos == alarma_minutos){
      digitalWrite(Led,HIGH);
      }
    lcd.print(" ON");
    }
    else{
      lcd.print(" OFF");
      }
 
  actualizar = false;
  fijarMenu();
  }

}
