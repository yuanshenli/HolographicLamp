
const int E1 = 26;
const int E2 = 31;
const int E3 = 8;
const int E4 = 7;
const int E5 = 14;
const int E6 = 15;
const int S1 = 30;
const int S2 = 29;
const int S3 = 27;
const int S4 = 28;
const int S5 = 12;
const int S6 = 11;
const int M[12] = {5, 21, 20, 6, 10, 9, 23, 22, 25, 32, 4, 3};

int Encoder1 = 0;
int Encoder2 = 0;
int Encoder3 = 0;
int Encoder4 = 0;
int Encoder5 = 0;
int Encoder6 = 0;
int switch1 = 0;
int switch2 = 0;
int switch3 = 0;
int switch4 = 0;
int switch5 = 0;
int switch6 = 0;


void setup() {
  // put your setup code here, to run once:
 pinMode(E1, INPUT);
 pinMode(E2, INPUT);
 pinMode(E3, INPUT);
 pinMode(E4, INPUT);
 pinMode(E5, INPUT);
 pinMode(E6, INPUT);
 pinMode(S1, INPUT_PULLUP);
 pinMode(S2, INPUT_PULLUP);
 pinMode(S3, INPUT_PULLUP);
 pinMode(S4, INPUT_PULLUP);
 pinMode(S5, INPUT_PULLUP);
 pinMode(S6, INPUT_PULLUP);

 
 for(int i  = 0; i<12; i++){
  pinMode(M[i], OUTPUT);
 }

}

void loop() {
  Encoder1 = digitalRead(E1);
  Encoder2 = digitalRead(E2);
  Encoder3 = digitalRead(E3);
  Encoder4 = digitalRead(E4);
  Encoder5 = digitalRead(E5);
  Encoder6 = digitalRead(E6);
  switch1 = digitalRead(S1);
  switch2 = digitalRead(S2);
  switch3 = digitalRead(S3);
  switch4 = digitalRead(S4);
  switch5 = digitalRead(S5);
  switch6 = digitalRead(S6);
  // put your main code here, to run repeatedly:
  Serial.print(Encoder6);
  Serial.print(Encoder5);
  Serial.print(Encoder4);
  Serial.print(Encoder3);
  Serial.print(Encoder2);
  Serial.println(Encoder1);
  for(int i  = 0; i < 6; i++) {
    analogWrite(M[2*i], 150);
    analogWrite(M[2*i+1], 0);
  }
  
//  Serial.print(switch6);
//  Serial.print(switch5);
//  Serial.print(switch4);
//  Serial.print(switch3);
//  Serial.print(switch2);
//  Serial.println(switch1);
  
}
