//------------------------------------------------LCD Header-----------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
const int trigPin = 11; 
const int echoPin = 10;

float duration, distance; 

int i=16;


//-----------------------------------------------------------


#include <Keypad.h>
#include <Servo.h>             //Servo library
Servo servo_test;        //initialize a servo object for the connected servo  
int angle = 0;  
const byte ROWS = 4; 
const byte COLS = 3; 
char inpass[100]="";
char pass[100]="12349";
char changepass[100];
int index=0;
char customKey;
char ckey;
String hide="";
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup()
{
   Serial.begin(9600);
    servo_test.attach(11);  
    pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT); 
     lcd.init();
    lcd.backlight();
    // lcd.setCursor(2,0);
    //lcd.print(" WELCOME TO");
   // lcd.setCursor(3,1);    
   // lcd.print("JUMPER WIRE");
     lcd.setCursor(1,0);
    lcd.print("Enter Password");
    lcd.setCursor(1,1);
    pinMode(12,OUTPUT);
    digitalWrite(13,LOW);
}

//---------------------------------------------------------LCD Function---------------------------------------


void openclose()
{
  for(angle = 180; angle>=95; angle-=1)     // command to move from 180 degrees to 0 degrees 
    {                                
    servo_test.write(angle);              //command to rotate the servo to the specified angle
    delay(50);                       
    } 
   delay(4000);
   lcd.clear();
   lcd.print("Door is Closing");
     for(angle = 95; angle<=180; angle++)     // command to move from 180 degrees to 0 degrees 
    {                                
    servo_test.write(angle);              //command to rotate the servo to the specified angle
    delay(50);                       
    }
    lcd.clear(); 
    lcd.print("Enter Password");
    digitalWrite(12,HIGH);
}

//------------------------------------------------------------------------------------------------------
void takepassword(){
    
    
    
    customKey = customKeypad.getKey();
    
    //lcd.clear();  
  if(customKey=='1' || customKey=='2' || customKey=='3' || customKey=='4' || customKey=='5' || customKey=='6' || customKey=='7' || customKey=='8' ||customKey=='9' || customKey=='0' ){
     lcd.clear();
    inpass[index]=customKey;
    index++;
    inpass[index]='\0';
   // hide = hide + "*" +customKey;
//    strcat(inpass,customKey);
    lcd.setCursor(2,0);
    lcd.print(inpass);
    Serial.println(inpass);
  }
    }
void loop(){  
  
  takepassword();
  if (customKey=='#')
  {
    inpass[index]='\0';
  if(strcmp(inpass,pass)==0)
    {
      lcd.clear();
      
      lcd.print("Password Matched");
      delay(2000);
      lcd.clear();
      lcd.print("Door is Opening");
      
//      strcpy(inpass,"");
//      inpass=null;
      Serial.println(inpass);
      index=0;
      openclose();
      digitalWrite(13,HIGH);
      delay(1000);
      lcd.clear();
//      strcpy(inpass,"");
//      inpass[0]='\0';
//      memset(0, inpass, sizeof(inpass));
//      char strtokIndx[100]="";
//      strtokIndx = strtok(inpass,",");
//      strcpy(rpiCommand, strtokIndx);
//      strcpy(inpass, tempChars);
        for( int i = 0; i < sizeof(inpass);  ++i)
        {
          inpass[i] = (char)0;
        }
      
      lcd.print("Enter Password");
    } 
    else
    {
      lcd.clear();
      lcd.print("Not Matched");
      delay(5000);
      lcd.clear();
      lcd.print("Enter Password");
//      strcpy(inpass,"");
      Serial.println(inpass);
      index=0;
      lcd.clear();
//      memset(0, inpass, sizeof(inpass));
      for( int i = 0; i < sizeof(inpass);  ++i)
      {
          inpass[i] = (char)0;
      }
//      strcpy(inpass,"");
      lcd.print("Enter Password");
//       lcd.clear();
     }
  }
}
