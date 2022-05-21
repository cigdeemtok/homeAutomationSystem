#include <Keypad.h>
#include <LM35.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(22,23,24,25,26,27);    //rs,en,d4,d5,d6,d7

int buzzerPin=30;
int yanginSensoru=A8;
int okunan_deger_yangin;

int lm35pin =A1;

int okunan_deger_termometre=0;
float sicaklik_gerilim=0;
float sicaklik=0;
int yesil_led =6;
int kirmizi_led=5;
const byte satir=4;
const byte sutun=3;
char dogru_sifre[4]={'1','2','3','4'};
char girilen_sifre[4];
char tus;
int i=0;
int girisBasarili=0; 

int hareketSensoru =28;
int hareketVarMi;
int lamba=29;

char tus_takimi[satir][sutun]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'} 
  };

byte satir_pinleri[satir]={13,12,11,10};
byte sutun_pinleri[sutun]={9,8,7};

Keypad keypadd= Keypad(makeKeymap(tus_takimi),satir_pinleri,sutun_pinleri,satir,sutun);



void setup() {

  
pinMode(yesil_led,OUTPUT);
pinMode(kirmizi_led,OUTPUT);
lcd.begin(16,2);
pinMode(hareketSensoru, INPUT);
pinMode(lamba, OUTPUT);

pinMode(yanginSensoru,INPUT);
pinMode(buzzerPin,OUTPUT);
}



void loop() {
    
  //////////////////////////////////////////KEYPAD//////////////////////////////
  digitalWrite(yesil_led,LOW);
  digitalWrite(kirmizi_led,LOW);
  tus=keypadd.getKey();
  if(tus){
    girilen_sifre[i]=tus; 
    i++;
    lcd.print("*");
  }
  if(i == 4)
  {
    lcd.clear();
  
    if((strncmp(dogru_sifre,girilen_sifre,4)==0)){
      digitalWrite(yesil_led,HIGH);
      
      delay(500);
      digitalWrite(yesil_led,LOW);
      lcd.print("HOS GELDINIZ.");
      delay(500);
      lcd.clear();
      i=0;      
      delay(200);
      girisBasarili=1;
    }
    else{
      digitalWrite(kirmizi_led,HIGH);
      delay(500);
      digitalWrite(kirmizi_led,LOW); 
       lcd.print("HATALI PAROLA.");
      delay(500);
      lcd.clear();
      i=0;
    }
  }
//////////////////////////////////////////////////////////////////////////////



if(girisBasarili==1){
//////////////////////////////////////TERMOMETRE//////////////////////////////
  okunan_deger_termometre = analogRead(A1);
  sicaklik_gerilim =(5000.0/1023.0) * okunan_deger_termometre;
  sicaklik = sicaklik_gerilim / 10.0;
    lcd.clear();
    lcd.home();
   
   // lcd.setCursor(0,1);
    if(sicaklik>30){
       lcd.clear();
        lcd.print("Sicaklik: ");
       lcd.print(sicaklik);
        lcd.setCursor(0,1);
    lcd.print("Sicaklik yukseldi.");
    }
    else if(sicaklik<20)
    {   lcd.clear();
        lcd.print("Sicaklik: ");
       lcd.print(sicaklik);
        lcd.setCursor(0,1);
    lcd.print("Sicaklik dustu.");
    }else
    {lcd.clear();
     lcd.print("Sicaklik: ");
      lcd.print(sicaklik);
  lcd.print("  derece");
    }
 
  
    delay(250);


//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////HAREKET//////////////////////////////
  hareketVarMi = digitalRead(hareketSensoru);

  if(hareketVarMi==1){
    digitalWrite(lamba,HIGH);  
  }else{
     digitalWrite(lamba,LOW);  
  }
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////YANGIN SENSORU/////////////////////////
  okunan_deger_yangin = digitalRead(yanginSensoru);

  if(okunan_deger_yangin == HIGH){
    digitalWrite(buzzerPin,HIGH);
  }
  else{
    digitalWrite(buzzerPin,LOW);  
  }

  delay(200);


//////////////////////////////////////////////////////////////////////////////



}
 
 

}
