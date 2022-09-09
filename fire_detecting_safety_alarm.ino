#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sen_val1 = 0; 
int sen_val2 = 0;
int sen_val3 = 0;
int switch_state = LOW;

float voltage = 0.0;
float temp = 0.0;

void setup()
{
  lcd.begin(16, 2);
  
  pinMode(A0,INPUT); //Pin for Temperature Sensor
  pinMode(A1,INPUT); //Pin for Photoresistor
  pinMode(A2,INPUT); //Pin for Gas Sensor
  pinMode(10,INPUT); //Pin for Switch
  
  Serial.begin(9600);
  
  for(int i = 6;i<=9;i++){
  pinMode(i,OUTPUT); //Pin for LCD
  }
}

void loop()
{
  sen_val1 = analogRead(A0); // Temperature Sensor
  sen_val2 = analogRead(A1); // Photoresistor
  sen_val3 = analogRead(A2); // Gas Sensor
  switch_state = digitalRead(10);// Manual Control
 
  lcd.setCursor(0, 0); //Setting the 1st Line of LCD
  
  voltage = 5.0*(sen_val1/1023.0);
  temp = (voltage - 0.5)*100;
  //Serial.println(sen_val2);
  //Serial.println(temp);
  //Serial.println(switch_state);
  if(switch_state == HIGH){ //Manual control is turned on
    tone(9, 300, 100);
    digitalWrite(6,LOW);
    digitalWrite(8,HIGH);
    delay(500);
    lcd.print("There is a fire");
    }
  else{ //Automatic control is turned on
  if(temp > 75 && sen_val2 > 700 && sen_val3 > 200){
    digitalWrite(6,LOW);
    digitalWrite(8,HIGH);
    tone(9, 300, 100);
    delay(500);
    lcd.print("There is a fire!");
  }
  else if((temp > 75 && sen_val3 > 200) || (temp > 75 && sen_val2 > 700)) {
    tone(9, 300, 100);
    digitalWrite(6,LOW);
    digitalWrite(8,HIGH);
    delay(500);
    lcd.print("There is a fire!");
  }
  else if(temp > 75){
    digitalWrite(6,LOW);
    digitalWrite(8,HIGH);
    lcd.print("The temp is too");
    lcd.setCursor(0, 1);
    lcd.print("high");
    delay(1000);
    lcd.clear(); //To clear the LCD
  }
  else{
    digitalWrite(8,LOW);
    digitalWrite(6,HIGH);
    lcd.print("No fire , Safe! :)"); //Safe :)
  }
  }
}