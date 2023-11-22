#include <SoftwareSerial.h>

const int trigPin = 7;
const int echoPin = 6;
long duration;
int distance;


SoftwareSerial BT(2,3);



int pizoElectro=8;
long pulso;
int i;

int m1a = 10;
int m1b = 9;
int m2a = 12;
int m2b = 11;
char val;

char Nombre[21] = "HC-06";
char PASS[5] = "1234";

void setup() {
  pinMode(pizoElectro, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // put your setup code here, to run once:
  pinMode(m1a, OUTPUT);  // Digital pin 10 set as output Pin
  pinMode(m1b, OUTPUT);  // Digital pin 9 set as output Pin
  pinMode(m2a, OUTPUT);  // Digital pin 12 set as output Pin
  pinMode(m2b, OUTPUT);  // Digital pin 11 set as output Pin
  BT.begin(9600);       // Inicializamos el puerto serie BT que hemos creado
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  BT.print("AT+NAME");
  BT.print(Nombre);
  delay(1000);
  BT.print("AT+PIN");
  BT.print(PASS);
}

void loop() {
  // put your main code here, to run repeatedly:
    
  if (val != "S" && val != "F" && val != "B" && val != "R" && val != "L") {
  if (distance <= 4) {
    pulso = 200;
    //subo
    tone(pizoElectro, 1000, 2000);
    delay(pulso);
    noTone(pizoElectro);
    delay(pulso);
  } else {
    noTone(pizoElectro);
  }
}
  if (BT.available())  // Si llega un dato por el puerto BT se envía al monitor serial
  {
    Serial.write(BT.read());
  }

  if (Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
    BT.write(Serial.read());
  }
  while (Serial.available() > 0){
  val = Serial.read();
  Serial.println(val);
  }

  if (val == 'F')  // Hacia adelante
  {
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
  } else if (val == 'B')  // Hacia atras
  {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
  }

  else if (val == 'L')  // Izquierda
  {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
  } else if (val == 'R')  //Derecha
  {
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
  } else if (val == 'S')  //Stop - Pare, Carrito detenido
  {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
  }

   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor

}
