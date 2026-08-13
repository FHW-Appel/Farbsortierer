#include <Servo.h>

Servo Drehrad;
Servo swayer;

// Servo Positionen

const int Load = 17;

const int Scan = 85;

const int Ext = 150;

// Pins
const int LEDrot = 2;

const int LEDblau = 8;

const int LEDgruen = 7;

const int Sensor = A0;

const int anzeigerot = 5;

const int anzeigeblau = 9;

const int anzeigegruen = 6;

// Samples - Entscheidet, wie oft gemessen wird
const int samples = 200;

// Helligkeit der einzelnen LED Farben
// const int ledBrightnessRed = 200;
// const int ledBrightnessBlue = 200;
// const int ledBrightnessGruen = 200;

//Farbwerte mit denen die Messungen verglichen werden um die Farbe zu bestimmen
int red[3] = {850, 600, 630};
int orange[3] = {870, 680, 640};
int yellow[3] = {860, 780, 750};
int green[3] = {780, 800, 750};
int blue[3] = {790, 780, 830};
int pink[3] = {850, 700, 760};
int violet[3] = {770, 700, 760};
int brown[3] = {800, 660, 650};

//erlaubte Abweichung von den oberen Farbwerten
int tolerance = 30;

//Variable in der die bestimmte Farbe gespeichert wird
int color;

int Fach0=0;

int Fach1=35;

int Fach2=75;

int Fach3=115;

int Fach4=150;
  
int Fach5=190;

int Fach6=0;

int Fach7=0;

int Fach8=0;

void setup() {
  // Pins vorbereiten
  pinMode(LEDblau, OUTPUT);

  pinMode(LEDgruen, OUTPUT);

  pinMode(LEDrot, OUTPUT);

  pinMode(anzeigeblau, OUTPUT);

  pinMode(anzeigegruen, OUTPUT);

  pinMode(anzeigerot, OUTPUT);

  Drehrad.attach(4);

  swayer.attach(3);

  Serial.begin(9600);

  pinMode(Sensor, INPUT);
}

int getColor(int ledPin) {
  digitalWrite(ledPin, HIGH);
  long brightnessSum = 0;
  delay(100);
  for (int i = 1; i <= samples; i++) {
    brightnessSum += analogRead(Sensor);
    delay(1);
  }
  digitalWrite(ledPin, 0);
  return brightnessSum / samples;
}

float colorDistance(int color1[3], int color2[3]) {
  return pow(pow(color1[0]-color2[0], 2) + pow(color1[1]-color2[1], 2) + pow(color1[2]-color2[2], 2), 1.0/2.0);
}

int readColor(int redM, int greenM, int blueM ) {
  // if (colorDistance({redM, greenM, blueM}, red)) {
    
  // }
  if (red[0] - tolerance <= redM && redM <= red[0] + tolerance && red[1] - tolerance <= greenM && greenM <= red[1] + tolerance && red[2] - tolerance <= blueM && blueM <= red[2] + tolerance) {
    return 1;
  }
  else if (orange[0] - tolerance <= redM && redM <= orange[0] + tolerance && orange[1] - tolerance <= greenM && greenM <= orange[1] + tolerance && orange[2] - tolerance <= blueM && blueM <= orange[2] + tolerance){
    return 2;
  }
  else if (yellow[0] - tolerance <= redM && redM <= yellow[0] + tolerance && yellow[1] - tolerance <= greenM && greenM <= yellow[1] + tolerance && yellow[2] - tolerance <= blueM && blueM <= yellow[2] + tolerance){
    return 3;
  }
  else if (green[0] - tolerance <= redM && redM <= green[0] + tolerance && green[1] - tolerance <= greenM && greenM <= green[1] + tolerance && green[2] - tolerance <= blueM && blueM <= green[2] + tolerance){
    return 4;
  }
  else if (blue[0] - tolerance <= redM && redM <= blue[0] + tolerance && blue[1] - tolerance <= greenM && greenM <= blue[1] + tolerance && blue[2] - tolerance <= blueM && blueM <= blue[2] + tolerance){
    return 5;
  }
  else if (pink[0] - tolerance <= redM && redM <= pink[0] + tolerance && pink[1] - tolerance <= greenM && greenM <= pink[1] + tolerance && pink[2] - tolerance <= blueM && blueM <= pink[2] + tolerance){
    return 6;
  }
  else if (violet[0] - tolerance <= redM && redM <= violet[0] + tolerance && violet[1] - tolerance <= greenM && greenM <= violet[1] + tolerance && violet[2] - tolerance <= blueM && blueM <= violet[2] + tolerance){
    return 7;
  }
  else if (brown[0] - tolerance <= redM && redM <= brown[0] + tolerance && brown[1] - tolerance <= greenM && greenM <= brown[1] + tolerance && brown[2] - tolerance <= blueM && blueM <= brown[2] + tolerance){
    return 8;
  }
  else {
    return 0;
  }
}


void loop() {
  // Drehradpositionen
  Drehrad.write(Load);
  delay(2000);
  Drehrad.write(Scan);

  delay(2000);

  // Rot
  int valueRed = getColor(LEDrot);

  Serial.print("Rot:");

  Serial.print(valueRed);

  delay(100);

  // Grün
  int valueGreen = getColor(LEDgruen);

  Serial.print(",Gruen:");

  Serial.print(valueGreen);
  
  delay(100);

  // Blau
  int valueBlue = getColor(LEDblau);

  Serial.print(",Blau:");

  Serial.println(valueBlue);

  color = readColor(valueRed, valueGreen, valueBlue);

  switch (color) {
    case 0:
      Serial.println("ohne");
      swayer.write(Fach0);

      analogWrite(anzeigerot, 0);
      analogWrite(anzeigegruen, 0);
      analogWrite(anzeigeblau, 0);
      break;
    case 1:
      Serial.println("rot");
      swayer.write(Fach1);

      analogWrite(anzeigerot, 200);
      analogWrite(anzeigegruen, 0);
      analogWrite(anzeigeblau, 0);
      break;
    case 2:
      Serial.println("orange");
      swayer.write(Fach2);

      analogWrite(anzeigerot, 200);
      analogWrite(anzeigegruen, 40);
      analogWrite(anzeigeblau, 20);
      break;
    case 3:
      Serial.println("gelb");
      swayer.write(Fach3);

      analogWrite(anzeigerot, 200);
      analogWrite(anzeigegruen, 120);
      analogWrite(anzeigeblau, 0);
      break;
    case 4:
      Serial.println("gruen");
      swayer.write(Fach4);

      analogWrite(anzeigerot, 60);
      analogWrite(anzeigegruen, 200);
      analogWrite(anzeigeblau, 20);
      break;
    case 5:
      Serial.println("blau");
      swayer.write(Fach5);

      digitalWrite(anzeigeblau, HIGH);
      break;
    case 6:
      Serial.println("pink");
      swayer.write(Fach6);

      analogWrite(anzeigerot, 200);
      digitalWrite(anzeigeblau, HIGH);
      break;
    case 7:
      Serial.println("lila");
      swayer.write(Fach7);

      analogWrite(anzeigerot, 300);
      analogWrite(anzeigegruen, 0);
      digitalWrite(anzeigeblau, HIGH);
      break;
    case 8:
      Serial.println("braun");
      swayer.write(Fach8);

      analogWrite(anzeigerot, 20);
      analogWrite(anzeigegruen, 10);
      break;
  }

  Drehrad.write(Ext);

  delay(3000);
}