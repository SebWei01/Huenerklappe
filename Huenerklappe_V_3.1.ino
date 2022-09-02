#include <LiquidCrystal_I2C.h>       //https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
#include <Wire.h>
#include <Servo.h>
#include <DS3231.h>                  // https://github.com/NorthernWidget/DS3231


LiquidCrystal_I2C lcd(0x27,16,2);
RTClib RTC;
DS3231 setRTC;
Servo myServo;

//1 LCD GND --> GND
//2 LCD VCC --> 5V
//3 LCD SDA --> A4
//4 LCD SCL --> A5

//1 UpButton --> 10
//2 selectButton --> 11
//3 downButton --> 12
//4 GND --> GND

//1 RTC 32K --> None
//2 RTC SQW --> None
//3 RTC SCL --> A5
//4 RTC SDA --> A4
//5 RTC VCC --> 3.3V
//6 RTC GNG --> GND

//1 servo Vcc --> 5V
//2 servo GND --> GND
//3 servo PWM --> 9

int upButton = 10;
int selectButton = 11;  
int downButton = 12;
int servopin = 9 ;

int menu = 1;

int offnenstunde = 6;                  //Öffnen zeit      
int schliessenstunde = 18;             //schlißen zeit

int offnenminute = 10;                  //Öffnen zeit      
int schliessenminute = 30;             //schlißen zeit

int neutralwinkel = 90;            // Servo winkel H-brücke
int offnenwinkel =45;
int schliessenwinkel = 135;

void setup() {
  
  myServo.attach(servopin);
  Serial.begin(9600);
  Wire.begin();
  delay(500);
  
  lcd.init(); 
  lcd.backlight();

  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);

  updateMenu();                          // Grafischeraufbau des Menüs
}
void updateMenu() {                       // Grafischeraufbau des Menüs
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">Aktuelle Zeit");
      lcd.setCursor(0,1);
      lcd.print(" Zeit einstellen");
      break;
    case 2:
      lcd.clear();
      lcd.print(" Aktuelle Zeit");
      lcd.setCursor(0,1);
      lcd.print(">Zeit einstellen");
      break;


    case 3:
      lcd.clear();
      lcd.print(">Offnen andern");
      lcd.setCursor(0,1);
      lcd.print(" Schliess andern");
      break;
    case 4:
      lcd.clear();
      lcd.print(" Offnen andern");
      lcd.setCursor(0,1);
      lcd.print(">Schliess andern");
      break;


    case 5:
      lcd.clear();
      lcd.print(">Offnen");
      lcd.setCursor(0,1);
      lcd.print(" Schliessen ");
      break;
    case 6:
      lcd.clear();
      lcd.print(" Offnen");
      lcd.setCursor(0,1);
      lcd.print(">Schliessen");
      break;
    case 7:
      menu = 6;
      break;  
      
  }
}
void aktuelleZeitanzeigen(){              
  for(int i=0;i<=5;i++){                  //i = Anzeigezeit in sec                     
    
    DateTime now = RTC.now();
    byte hour = now.hour();
    byte min = now.minute();
    byte sec = now.second();

    delay(990);

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aktuelle Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(hour);
    lcd.setCursor(6, 1);
    lcd.print(":");

    lcd.setCursor(7, 1);
    lcd.print(min);
    lcd.setCursor(9, 1);
    lcd.print(":");

    lcd.setCursor(10, 1);
    lcd.print(sec); 
}}

void zeiteinstellen() {
  menu = 8;
  DateTime now = RTC.now();

  byte hour = now.hour();
  byte min = now.minute();
  byte sec = now.second();

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aktuelle Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(hour);
    lcd.setCursor(6, 1);
    lcd.print(":");

    lcd.setCursor(7, 1);
    lcd.print(min);
    lcd.setCursor(9, 1);
    lcd.print(":");

    lcd.setCursor(10, 1);
    lcd.print(sec); 

    byte state=1; 
    delay(1000);

  while (menu==8) {

    switch (state) {
    case 1:                           //stunde einstellen            
    while(state==1){
       if (!digitalRead(downButton)){
        hour--;
        delay(500);}                             //scrollzeit
        // while (!digitalRead(downButton));    // anti scrolling

       if(!digitalRead(upButton)){
        hour++;                                 
        delay(500);}                           //scrollzeit
        //while(!digitalRead(upButton));       // anti scrolling
      if (!digitalRead(selectButton)){
        state++;
        while(!digitalRead(selectButton)){ 
        delay(10);
        }} 

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aktuelle Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(hour);
    lcd.setCursor(6, 1);
    lcd.print(":");

    lcd.setCursor(7, 1);
    lcd.print(min);
    lcd.setCursor(9, 1);
    lcd.print(":");

    lcd.setCursor(10, 1);
    lcd.print(sec);   

    delay(500);

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aktuelle Zeit:");
    lcd.setCursor(4, 1);
    lcd.print("--");
    lcd.setCursor(6, 1);
    lcd.print(":");

    lcd.setCursor(7, 1);
    lcd.print(min);
    lcd.setCursor(9, 1);
    lcd.print(":");

    lcd.setCursor(10, 1);
    lcd.print(sec);  } 

    case 2:                           //Minuten einstellen            
     while(state==2){
       if (!digitalRead(downButton)){
        min--;
        delay(100);}                             //scrollzeit
        // while (!digitalRead(downButton));    // anti scrolling

       if(!digitalRead(upButton)){
        min++;                                 
        delay(100);}                           //scrollzeit
        //while(!digitalRead(upButton));       // anti scrolling
      if (!digitalRead(selectButton)){
        state++;
        while(!digitalRead(selectButton)){ 
        delay(10);
        }} 
        
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aktuelle Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(hour);
    lcd.setCursor(6, 1);
    lcd.print(":");

    lcd.setCursor(7, 1);
    lcd.print(min);
    lcd.setCursor(9, 1);
    lcd.print(":");

    lcd.setCursor(10, 1);
    lcd.print(sec);   

    delay(100);

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aktuelle Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(hour);
    lcd.setCursor(6, 1);
    lcd.print(":");

    lcd.setCursor(7, 1);
    lcd.print("--");
    lcd.setCursor(9, 1);
    lcd.print(":");

    lcd.setCursor(10, 1);
    lcd.print(sec);  } 


    case 3:                           //Sekunden einstellen            
     while(state==3){
       if (!digitalRead(downButton)){
        sec--;
        delay(100);}                             //scrollzeit
        // while (!digitalRead(downButton));    // anti scrolling

       if(!digitalRead(upButton)){
        sec++;                                 
        delay(100);}                           //scrollzeit
        //while(!digitalRead(upButton));    // anti scrolling
      
      if (!digitalRead(selectButton)){
        state++;
        while(!digitalRead(selectButton)){ 
        delay(10);
        }} 
        
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aktuelle Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(hour);
    lcd.setCursor(6, 1);
    lcd.print(":");

    lcd.setCursor(7, 1);
    lcd.print(min);
    lcd.setCursor(9, 1);
    lcd.print(":");

    lcd.setCursor(10, 1);
    lcd.print(sec);   

    delay(100);

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aktuelle Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(hour);
    lcd.setCursor(6, 1);
    lcd.print(":");

    lcd.setCursor(7, 1);
    lcd.print(min);
    lcd.setCursor(9, 1);
    lcd.print(":");

    lcd.setCursor(10, 1);
    lcd.print("--");  } 

      case 4: 

      setRTC.setSecond(sec);
      setRTC.setMinute(min);
      setRTC.setHour(hour);

      menu=1;
      updateMenu();                        
      break;

     }}
    

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aktuelle Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(hour);
    lcd.setCursor(6, 1);
    lcd.print(":");

    lcd.setCursor(7, 1);
    lcd.print(min);
    lcd.setCursor(9, 1);
    lcd.print(":");

    lcd.setCursor(10, 1);
    lcd.print(sec); 
  }


void offneneinstellen(){
    menu = 9;

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("offnen Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(offnenstunde);
    lcd.setCursor(6, 1);
    lcd.print(":");
    lcd.setCursor(7, 1);
    lcd.print(offnenminute);

    byte state=1; 
    delay(1000);

  while (menu==9) {

    switch (state) {
    case 1:                           //stunde einstellen            
    while(state==1){

       if (!digitalRead(downButton)){
        offnenstunde--;
       lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(offnenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(offnenminute);
      delay(350);}                             //scrollzeit
        // while (!digitalRead(downButton));    // anti scrolling

       if(!digitalRead(upButton)){
        offnenstunde++;                                 
       lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(offnenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(offnenminute);
      delay(350);}                           //scrollzeit
        //while(!digitalRead(upButton));       // anti scrolling
      if (!digitalRead(selectButton)){
        state++;
        while(!digitalRead(selectButton)){ 
        delay(10);
        }}

        
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print("--");
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(offnenminute);}
        delay(150);
    
    case 2:                           //Minuten einstellen            
     while(state==2){
       if (!digitalRead(downButton)){
        offnenminute--;
         lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(offnenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(offnenminute);
        delay(250);}                            
        // while (!digitalRead(downButton));    // anti scrolling

       if(!digitalRead(upButton)){
        offnenminute++; 
         lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(offnenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(offnenminute);                                
        delay(250);}                           
        //while(!digitalRead(upButton));       // anti scrolling
      if (!digitalRead(selectButton)){
        state++;
        while(!digitalRead(selectButton)){ 
        delay(10);
        }}

        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(offnenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print("--");}
        delay(150);
    case 3:
      menu=1;
      updateMenu();      
}}}

void schlisseneinstellen(){
  menu = 10;

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("offnen Zeit:");
    lcd.setCursor(4, 1);
    lcd.print(schliessenstunde);
    lcd.setCursor(6, 1);
    lcd.print(":");
    lcd.setCursor(7, 1);
    lcd.print(schliessenminute);

    byte state=1; 
    delay(1000);

  while (menu==10) {

    switch (state) {
    case 1:                           //stunde einstellen            
    while(state==1){

       if (!digitalRead(downButton)){
        schliessenstunde--;
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(schliessenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(schliessenminute);
        delay(350);}                             //scrollzeit
        // while (!digitalRead(downButton));    // anti scrolling

       if(!digitalRead(upButton)){
        schliessenstunde++; 
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(schliessenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(schliessenminute);                                
        delay(350);}                           //scrollzeit
        //while(!digitalRead(upButton));       // anti scrolling
      if (!digitalRead(selectButton)){
        state++;
        while(!digitalRead(selectButton)){ 
        delay(10);
        }}
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print("--");
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(schliessenminute);}
        delay(150);
    
    case 2:                           //Minuten einstellen            
     while(state==2){
       if (!digitalRead(downButton)){
        schliessenminute--;
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(schliessenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(schliessenminute);
        delay(250);}                             //scrollzeit
        // while (!digitalRead(downButton));    // anti scrolling

       if(!digitalRead(upButton)){
        schliessenminute++; 
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(schliessenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(schliessenminute);                                
        delay(250);}                           //scrollzeit
        //while(!digitalRead(upButton));       // anti scrolling
      if (!digitalRead(selectButton)){
        state++;
        while(!digitalRead(selectButton)){ 
        delay(10);
        }}

        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("offnen Zeit:");
        lcd.setCursor(4, 1);
        lcd.print(schliessenstunde);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print("--");}
          delay(150);
    case 3:
      menu=1;
      updateMenu();      
}}}


void  offnen() {
  myServo.write(offnenwinkel);
  delay(5000);
  myServo.write(neutralwinkel);
}
void schliessen() {
  myServo.write(schliessenwinkel);
  delay(5000);
  myServo.write(neutralwinkel);
}

void loop() {
  DateTime now = RTC.now();

  byte hour = now.hour();
  byte min = now.minute();
  byte sec = now.second();

 if (hour == offnenstunde){
  if (min == offnenminute){
     offnen();
     delay(60000);
     }}
     


 if (hour == schliessenstunde){
  if (min == schliessenminute){
    schliessen();
    delay(60000);
    }}
 

  if (!digitalRead(downButton)){
    menu++;
    updateMenu();                        // Grafischeraufbau des Menüs
    delay(500);                          // Scrollzeit
  //while (!digitalRead(downButton));    // anti scrolling
  }
  if (!digitalRead(upButton)){
    menu--;
    updateMenu();                        // Grafischeraufbau des Menüs
    delay(500);                          // Scrollzeit
  //while(!digitalRead(upButton));       // anti scrolling
  }
  if (!digitalRead(selectButton)){
    executeAction();                     // Aktion auswählen
    updateMenu();                        // Grafischeraufbau des Menüs
    delay(500);                          // Scrollzeit
  //while (!digitalRead(selectButton));  // anti scrolling
}}

void executeAction() {                    // Aktion auswählen
  switch (menu) {
    case 1:
      aktuelleZeitanzeigen();                           
      break;
      
    case 2:
      zeiteinstellen();
      break;

    case 3:
      offneneinstellen();
      break;

    case 4:
      schlisseneinstellen();
      break;

    case 5:
      offnen();;
      break;
    case 6:
      schliessen();
      break;    
  }
}