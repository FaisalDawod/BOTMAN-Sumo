//Motors pins
const int motorR[]={5,6},motorL[]={11,10};
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
const int speedMax=220,speedHalf=120;
char state='s';
int speedCrnt=0;
bool seeing=false;
void forW(int s, int t);
void back(int s);
void rL(int s);
void forward(int s,int t);
void notFound(int s);
void backword(int s);
void rotateR(int s);
void rotateL(int s);
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
  digitalWrite(motorL[1],0);
// Waiting for the button to be pressed
  digitalWrite(motorL[0],0);
  while (digitalRead(startButton) == 1) {}
//waiting to release the button 
  while (digitalRead(startButton) == 0) {}
  buttonPressedTime = millis();
// Wait for 5 seconds after button to start
  while (millis() - buttonPressedTime < 5000) {}

Serial.begin(9600);

   while(see()=='f'){
    forward(speedMax,10);
    delay(10);
   }
//   imOnTheLine();
//  //test motors
////  forward(140,5);
////  delay(1000);
////  backward(140);
////  delay(1000);
////  rotateR(140);
//  
//  rotateL(140);
//  
//  stop(10);delay(1000);
//
////   while(speedCrnt<150&&(see()=='s')){
////   speedCrnt+=3;
////     analogWrite(motorR[0],0);
////     analogWrite(motorR[1],speedCrnt);
////     analogWrite(motorL[0],0);
////     analogWrite(motorL[1],0);
////     delay(10);
////     }
     stop(5);
}
 void loop(){

//    Serial.print(digitalRead(clrF));
//    Serial.print("l");
//    Serial.println(digitalRead(clrB));
  switch(see()){
     case 'f':
       forward(speedMax,7);
     break;
     /////
     case 'r':
       rotateR(speedHalf);
     break;
     /////
     case 'l':
       rotateL(speedHalf);
     break;
     /////
     case 'n':
       notFound(speedHalf);
     break;
     }

 }

// s for speed and t for time 
void forward(int s,int t){
  if(state!='f') stop(5); state='f';
  
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
    imOnTheLine();
    analogWrite(motorR[1],speedCrnt);
    analogWrite(motorR[0],0);
    analogWrite(motorL[1],speedCrnt);
    analogWrite(motorL[0],0);
    delay(t);
    }
      speedCrnt=s;
    analogWrite(motorR[1],s);
    analogWrite(motorR[0],0);
    analogWrite(motorL[1],s);
    analogWrite(motorL[0],0);
}
void forW(int s,int t){
  if(state!='f') stop(10); state='f';
  
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
    analogWrite(motorR[1],speedCrnt);
    analogWrite(motorR[0],0);
    analogWrite(motorL[1],speedCrnt);
    analogWrite(motorL[0],0);
    delay(t);
    }
    speedCrnt=s;
    analogWrite(motorR[1],s);
    analogWrite(motorR[0],0);
    analogWrite(motorL[1],s);
    analogWrite(motorL[0],0);
}
void backward(int s){
  if(state!='b') stop(10); state='b';
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
    imOnTheLine();
    analogWrite(motorR[1],0);
    analogWrite(motorR[0],speedCrnt);
    analogWrite(motorL[1],0);
    analogWrite(motorL[0],speedCrnt);
    delay(7);
    }
    speedCrnt=s;
    analogWrite(motorR[1],0);
    analogWrite(motorR[0],s);
    analogWrite(motorL[1],0);
    analogWrite(motorL[0],s);
}

void back(int s){//backward for white color
  if(state!='b') stop(5); state='b';
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
    analogWrite(motorR[1],0);
    analogWrite(motorR[0],speedCrnt);
    analogWrite(motorL[1],0);
    analogWrite(motorL[0],speedCrnt);
    delay(7);
    }
    speedCrnt=s;
    analogWrite(motorR[1],0);
    analogWrite(motorR[0],s);
    analogWrite(motorL[1],0);
    analogWrite(motorL[0],s);
}
void rotateR(int s){
  if(state!='r')stop(10); state='r';
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
    if(see()=='r')return;
    imOnTheLine();
    analogWrite(motorR[0],0);
    analogWrite(motorR[1],speedCrnt);
    analogWrite(motorL[0],speedCrnt);
    analogWrite(motorL[1],0);
    delay(7);
    }
    speedCrnt=s;
    analogWrite(motorR[0],0);
    analogWrite(motorR[1],s);
    analogWrite(motorL[0],s);
    analogWrite(motorL[1],0);
}
void rotateL(int s){
  if(state!='l') stop(10); state='l';
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
    if(see()=='l')return;
    imOnTheLine();
    analogWrite(motorR[0],speedCrnt);
    analogWrite(motorR[1],0);
    analogWrite(motorL[0],0);
    analogWrite(motorL[1],speedCrnt);
    delay(7);
    }
    speedCrnt=s;
    analogWrite(motorR[0],s);
    analogWrite(motorR[1],0);
    analogWrite(motorL[0],0);
    analogWrite(motorL[1],s);
}
void rL(int s){// rL for color white
  if(state!='l') 
    stop(5); 
  state='l';
  for(speedCrnt;speedCrnt<s;speedCrnt+=2){
     if(see()!='l') return;
    analogWrite(motorR[0],speedCrnt);
    analogWrite(motorR[1],0);
    analogWrite(motorL[0],0);
    analogWrite(motorL[1],speedCrnt);
    delay(5);
    }
    speedCrnt=s;
    analogWrite(motorR[0],s);
    analogWrite(motorR[1],0);
    analogWrite(motorL[0],0);
    analogWrite(motorL[1],s);
}
void notFound(int s){
 rotateL(speedHalf);
 while(see()=='n'){
  imOnTheLine();
 }
 
}
char see(){
  imOnTheLine();
  if(!digitalRead(irC)){seeing=true;return 'f';}
  if(!digitalRead(irL)&&digitalRead(irC)&&digitalRead(irR))
  {
    seeing=true;return 'l';
    }
  if(digitalRead(irL)&&digitalRead(irC)&&!digitalRead(irR))
  {
    seeing=true;return 'r';
    }
  if(digitalRead(irL)&&digitalRead(irC)&&digitalRead(irR))
  {
    seeing=false;return 'n';
    }
}
void imOnTheLine(){
  if(!digitalRead(clrB)){
    stop(5);
    delay(2000);
    
//     forW(100,7);
//     rL(120);
//     
//     stop(5);
  }
  
//  if(!clrF){
//     back(100);
//     rL(120);
//     stop(5);
//     }
}

//t: stands for every time i need to do this procees in t time 
void stop(int t){
  
  switch(state){
    case 's':
    break;
    ////
    case 'f':
        while(speedCrnt > 6) {
    speedCrnt -= 3;
    imOnTheLine();
    analogWrite(motorR[1],speedCrnt);
    analogWrite(motorR[0],0);
    analogWrite(motorL[1],speedCrnt);
    analogWrite(motorL[0],0);
    delay(t);
    }
    speedCrnt=0;
    break;
    ////
    case 'b':
    while(speedCrnt > 6) {
    speedCrnt -= 3;
    imOnTheLine();
    analogWrite(motorR[1],0);
    analogWrite(motorR[0],speedCrnt);
    analogWrite(motorL[1],0);
    analogWrite(motorL[0],speedCrnt);
    delay(t);
    }
    speedCrnt=0;
    break;
    ////
    case 'l':
    while(speedCrnt > 6) {
    speedCrnt -= 3;
    imOnTheLine();
    analogWrite(motorR[0],speedCrnt);
    analogWrite(motorR[1],0);
    analogWrite(motorL[0],0);
    analogWrite(motorL[1],speedCrnt);
    delay(t);
    }
    speedCrnt=0;
    break;
    case 'r':
    imOnTheLine();
    while(speedCrnt > 6) {
    speedCrnt -= 3;
    analogWrite(motorR[0],0);
    analogWrite(motorR[1],speedCrnt);
    analogWrite(motorL[0],speedCrnt);
    analogWrite(motorL[1],0);
    delay(t);
    }
    speedCrnt=0;
    break;
    }
    state='s';
    analogWrite(motorR[0],0);
    analogWrite(motorR[1],0);
    analogWrite(motorL[0],0);
    analogWrite(motorL[1],0);
}