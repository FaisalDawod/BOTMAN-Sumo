//Motors pins
const int motorR[]={5,6},motorL[]={10,11};
//IR sensors
//0= they are seeing || 1=not seeing
const int irL=4,irC=7,irR=12;
//color sensor
// 0=white || 1=black
const int clrF=8,clrB=2;
//start button
const int startButton=13;
unsigned long buttonPressedTime = 0;
//speed and 
const int speedMax=230,speedHalf=110;
char state='p';
int speedCrnt=0;
bool seeing=false;

void forward(int s);
void notFound(int s);
void backWord(int s);
void rotateRight(int s);
void rotateLeft(int s);
void stop();
bool edgeDetected();
char see();
void imOnTheLine();

void setup() {
  pinMode(motorL[0],OUTPUT);
  pinMode(motorL[1],OUTPUT);
  pinMode(motorR[0],OUTPUT);
  pinMode(motorR[1],OUTPUT);
  pinMode(irL,INPUT);
  pinMode(irC,INPUT);
  pinMode(irR,INPUT);
  pinMode(clrB,INPUT);
  pinMode(clrF,INPUT);
  pinMode(startButton, INPUT_PULLUP);
// motors are set to 0  for saftey 
  digitalWrite(motorR[0],0);
  digitalWrite(motorR[1],0);
  digitalWrite(motorL[0],0);
  digitalWrite(motorL[1],0);
// Waiting for the button to be pressed
  while (digitalRead(buttonPin) == 1) {}
//waiting to release the button 
  while (digitalRead(buttonPin) == 0) {}
  buttonPressedTime = millis();
// Wait for 5 seconds after button to start
  while (millis() - buttonPressedTime < 5000) {}

  while(see()=='f'){
   forward(speedMax);
   delay(10);
  }
  imOnTheLine();
  //test motors
  //f(140);delay(3000);
  //b(140);delay(3000);
  //r(140);delay(3000);
  //l(140);delay(3000);
  //p();delay(5000);

  while(speedCrnt<150&&(see()=='s')){
  speedCrnt+=3;
    analogWrite(motorR[0],0);
    analogWrite(motorR[1],speedCrnt);
    analogWrite(motorL[0],0);
    analogWrite(motorL[1],0);
    delay(10);
    }
    while(speedCrnt>0){
  speedCrnt-=6;
    analogWrite(motorR[0],0);
    analogWrite(motorR[1],speedCrnt);
    analogWrite(motorL[0],0);
    analogWrite(motorL[1],0);
    delay(8);
    }
    speedCrnt=0;
    analogWrite(motorR[0],0);
    analogWrite(motorR[1],0);
    analogWrite(motorL[0],0);
    analogWrite(motorL[1],0);
}
void loop(){
 switch(see()){
    case 'f':
      forwad(maxSpeed,10);
    break;
    /////
    case 'r':
      rotateRight(speedHalf);
    break;
    /////
    case 'l':
      rotateLeft(speedHalf);
    break;
    /////
    case 'n':
      notFound(speedHalf);
    break;
    }
  
}
// s for speed and t for time 
void forward(int s,int t){
  if(state!='f') p(); state='f';
  
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
    analogWrite(RM[1],speedCrnt);
    analogWrite(RM[0],0);
    analogWrite(LM[1],speedCrnt);
    analogWrite(LM[0],0);
    delay(t);
    }
      speedCrnt=s;
    analogWrite(RM[1],s);
    analogWrite(RM[0],0);
    analogWrite(LM[1],s);
    analogWrite(LM[0],0);
}
void b(int s){
  if(state!='b') p(); state='b';
  for(currentSpeed;currentSpeed<s;currentSpeed+=2){
    analogWrite(RM[1],0);analogWrite(RM[0],currentSpeed);
    analogWrite(LM[1],0);analogWrite(LM[0],currentSpeed);
    delay(10);
    }
    analogWrite(RM[1],0);analogWrite(RM[0],s);
    analogWrite(LM[1],0);analogWrite(LM[0],s);
}
void notFound(int s){
 rotateRight(s);
 stop(7);
 see();
 if(seeing==true)
 break;
 rotateLeft((s);
 see();
 if(seeing==true)
 break;
 stop(14);
}
char see(){
  if(!digitalRead(df)){seeing=true;return 'f';}
  if(!digitalRead(dl)&&digitalRead(df)&&digitalRead(dr)){seeing=true;return 'l';}
  if(digitalRead(dl)&&digitalRead(df)&&!digitalRead(dr)){seeing=true;return 'r';}
  if(digitalRead(dl)&&digitalRead(df)&&digitalRead(dr)){seeing=false;return 'n';}
}
void imOnTheLine(){
  if(!clrF){
     backWord(100);
     RotateLeft(120);
     p();}
  
  if(!clrB){
     forward(100);
     rotateLeft(120);
     p();
  }
}
void rotateRight(int s){
  if(state!='r') p(); state='r';
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
        if(see()!='r')return;
    analogWrite(RM[0],0);
    analogWrite(RM[1],speedCrnt);
    analogWrite(LM[0],speedCrnt);
    analogWrite(LM[1],0);
    delay(10);
    }
    analogWrite(RM[0],0);
    analogWrite(RM[1],s);
    analogWrite(LM[0],s);
    analogWrite(LM[1],0);
}
void RotateLeft(int s){
  if(state!='l') p(); state='l';
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
        if(see()!='l')return;
    analogWrite(RM[0],speedCrnt);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],speedCrnt);
    delay(10);
    }
     // }
    analogWrite(RM[0],s);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],s);
}
//t: stands for every time i need to do this procees in t time 
void stop(int t){
  switch(state){
    case 'p':
    break;
    ////
    case 'f':
    while(speedCrnt > 6) {
    speedCrnt -= 3;
    analogWrite(RM[1],speedCrnt);
    analogWrite(RM[0],0);
    analogWrite(LM[1],speedCrnt);
    analogWrite(LM[0],0);
    delay(t);
    }
    speedCrnt=0;
    break;
    ////
    case 'b':
    while(speedCrnt > 6) {
    speedCrnt -= 3;
    analogWrite(RM[1],0);
    analogWrite(RM[0],speedCrnt);
    analogWrite(LM[1],0);
    analogWrite(LM[0],speedCrnt);
    delay(t);
    }
    speedCrnt=0;
    break;
    ////
    case 'l':
    while(speedCrnt > 6) {
    speedCrnt -= 3;
    analogWrite(RM[0],speedCrnt);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],speedCrnt);
    delay(t);
    }
    speedCrnt=0;
    break;
    case 'r':
    while(speedCrnt > 6) {
    speedCrnt -= 3;
    analogWrite(RM[0],0);
    analogWrite(RM[1],speedCrnt);
    analogWrite(LM[0],speedCrnt);
    analogWrite(LM[1],0);
    delay(t);
    }
    speedCrnt=0;
    break;
    }
    state='p';
    analogWrite(RM[0],0);analogWrite(RM[1],0);
    analogWrite(LM[0],0);analogWrite(LM[1],0);
}
