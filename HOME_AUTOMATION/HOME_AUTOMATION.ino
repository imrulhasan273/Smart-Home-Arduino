//variables for temparature sensing and Motor________________________________________________________
const int tSensor=A0; 
float tempC;
float tempF; 
float output;
int count=0;
int controlPin = 9;
int posDir = 8;
int negDir = 7;
//_____________________________________________________________________________________________________
//_____________________Visitor COuting___________________________________________________________
#define LDRpin A8 // pin where we connected the LDR and the resistor
int LDRValue = 0;     // result of reading the analog pin
int LED = 40;
int in = A1;
int out = A2;
float x;
float y;
int countLDR=0;
//____________________________________________________________________________________________________
//_________Vibration Sensor_____________________________________
int led = 6;
int vs = A15; // vibration sensor
int measurement;
//_____________________________________________________________

//_____________________Visitor COuting___________________________________________________________

//Smoke
int smokeA5 = A5;
//

void LEDS()
{
  Serial.println("Light On");
  digitalWrite(LED,HIGH);
}
void NotLEDS()
{
  digitalWrite(LED,LOW);
}
void checkLDR()
{
  LDRValue = analogRead(LDRpin); // read the value from the LDR
  Serial.println("LDR Value:");
  Serial.println(LDRValue);      // print the value to the serial port
  if(LDRValue<60)
  {
    LEDS();
  }
  else
  {
    NotLEDS();
  }
}
//___________________________________________
void light()
{
  x=digitalRead(in);
  y=digitalRead(out);
  Serial.println(x);
  Serial.println(y);
  Serial.println("Total Members: ");
  Serial.println(countLDR);

  
  
  if(x==0)
  {
    countLDR=countLDR+1;
    delay(2000);
  }
  else if(y==0)
  {
    
    countLDR=countLDR-1;
//    if(digitalRead(34)==HIGH)
//    {
//      countLDR=countLDR+1;
//    }
//    digitalWrite(34,LOW);
    delay(2000);
  }
  delay(100);

  if(countLDR>0)
  {
    checkLDR();
  }
  else
  {
    Serial.println("Light Off");
  }
}
void temparature()
{
  //Temparature measurement
  output=analogRead(tSensor); 
  output=(output*500)/1023;
  tempC=output;
  tempF=(output*1.8)+32; 
  Serial.print("Degree C =>");
  Serial.print(" ");
  Serial.print(tempC);
  Serial.print("\t");
  Serial.println();
//  delay(500);
//  output = 30;
  //Motor speed measurement
  Serial.print(output);
  Serial.print("\n");
  if(output<=48 || countLDR<=0)
  {
    digitalWrite(posDir,HIGH);
    digitalWrite(negDir,LOW);
    analogWrite(controlPin,0);
  }
  else if(output>48 && output<=80 && countLDR>0)
  {
    digitalWrite(posDir,HIGH);
    digitalWrite(negDir,LOW);
    analogWrite(controlPin,70);
  }
  else if(output>80 && output<=200 && countLDR>0)
  {
    digitalWrite(posDir,HIGH);
    digitalWrite(negDir,LOW);
    analogWrite(controlPin,255);
  }
}
void smokes()
{
  int smokesensor = analogRead(smokeA5);
//  delay(1000);
  Serial.println("Smoke Value");
  Serial.println(smokesensor);
  if(smokesensor>300)
  {
    digitalWrite(6,HIGH);
    delay(2000);
    digitalWrite(6,LOW);
  }
}
void servo()
{
  
}
///Imrul Hasan_______________set Up files.
void setup() 
{
  pinMode(34,INPUT);
  pinMode(smokeA5,INPUT);
  pinMode(in,INPUT);
  pinMode(out,INPUT);
  
  pinMode(tSensor,INPUT);   
  pinMode(posDir,OUTPUT);
  pinMode(negDir,OUTPUT);
  pinMode(controlPin,OUTPUT);

  pinMode(led, OUTPUT);
  pinMode(vs, INPUT); 
  Serial.begin(9600);
}
void loop() 
{
//  digitalWrite(34,LOW);
  temparature();
  
//    if(digitalRead(34)==HIGH)
//    {
//      countLDR=countLDR+1;
//    }
    
  light();
   
 
  smokes();

  
  
//  long measurement =pulseIn (vs, HIGH);
  measurement = analogRead(vs);
  Serial.println("Earthquake: ");
  Serial.println(measurement);
  if (measurement > 100)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW); 
  }
  
}
