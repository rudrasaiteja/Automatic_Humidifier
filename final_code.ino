#include <SimpleDHT.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8,7,6,5,4,3);
int pinDHT11 = A0;
SimpleDHT11 dht11(pinDHT11);
 
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop()
{
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" %");
  lcd.setCursor(1,0);
  lcd.print((int)temperature);
  lcd.setCursor(4,0);
  lcd.print("*C");
  lcd.setCursor(8,0);
  lcd.print((int)humidity);
  lcd.setCursor(11,0);
  lcd.print("%");
  if((int)humidity<40)
  {
    digitalWrite(9,HIGH);
  }
  else
  {
    digitalWrite(9,LOW);
  }
  int aqi=analogRead(A1);
  lcd.setCursor(1,1);
  lcd.print("AQI:");
  lcd.setCursor(5,1);
  lcd.print(aqi);
  lcd.setCursor(9,1);
  lcd.print("PPM");
  delay(1500);
}
