
//Motors PWM
  const int RM[]={11,10}; const int LM[]={5,6};
//Digital Obstacle Sensors
  const int dl=4; const int df=7; const int dr=12;
  //(LOW= they are seeing, HIGH=not seeing)
//Digital light Sensors
  const int cl=2,cr=3,cb=8;
  //(Low=white, HIGH=black)
  const int buttonPin = 9;
//vars
  unsigned long buttonPressedTime = 0;
  const int maxSpeed=180;
  int halfSpeed=100;
  char state='p';
  int currentSpeed=0;
  bool seeing=false;
// delay
const int d=7;
//functions
void f(int s);
void sf(int s);
void b(int s);
void r(int s);
void l(int s);
void p();
bool lineDetected();
char see();
void imOnTheLine();
void stopReverse();

void setup() {
  Serial.begin(9600);
  pinMode(RM[0],OUTPUT);
  pinMode(RM[1],OUTPUT);
  pinMode(LM[0],OUTPUT);
  pinMode(LM[1],OUTPUT);
  pinMode(dl,INPUT);
  pinMode(df,INPUT);
  pinMode(dr,INPUT);
  pinMode(cl,INPUT);
  pinMode(cr,INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
//make sure motors are off
  digitalWrite(RM[0],LOW);
  digitalWrite(RM[1],LOW);
  digitalWrite(LM[0],LOW);
  digitalWrite(LM[1],LOW);

// Wait for button press to start
  while (digitalRead(buttonPin) == HIGH) {
    // Wait for button press
  }
  while (digitalRead(buttonPin) == LOW) {
    // Wait for button press
  }
  buttonPressedTime = millis();

  // Wait for 5 seconds after button release before starting
  while (millis() - buttonPressedTime < 5000) {
    // Wait for 5 seconds
  }

  //attacking techniques just after the five seconds
 // not allways well be implemented
//  f(240);delay(100);l(240);delay(100);
//  f(240);delay(100);r(240);delay(100);
//  r(100);f(100);l(100);
  //see();
  
  //test motors
//  f(220);
//  delay(7000);
//  b(80);
//  delay(2000);
//  r(80);
//  delay(2000);
//  l(80);
//  delay(2000);
//  
  p();
  delay(2000);
// 
  
  

 

//  while(currentSpeed<150&&(see()=='s')){
//  currentSpeed+=3;
//    analogWrite(RM[0],0);
//    analogWrite(RM[1],currentSpeed);
//    analogWrite(LM[0],0);
//    analogWrite(LM[1],0);
//    delay(10);
//    }

// to check if the motors are stopped

    while(currentSpeed>0){
  currentSpeed-=6;
    analogWrite(RM[0],0);
    analogWrite(RM[1],currentSpeed);
    analogWrite(LM[0],0);
    analogWrite(LM[1],0);
    delay(d);
    }
    currentSpeed=0;
    analogWrite(RM[0],0);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],0);
}

void loop() {
  if(lineDetected()){
    imOnTheLine();
    }else
  switch(see()){
    case 'f':
      
      f(maxSpeed);
    break;
    /////
    case 'r':
      
      r(80);
    break;
    /////
    case 'l':
      
      l(80);
    break;
    /////
    case 's':
      
      sf(38);///////////finding the enemy
    break;
    }
}

void f(int s){
  if(state!='f') p(); state='f';
  
  for(currentSpeed;currentSpeed<s;currentSpeed+=2){
    analogWrite(RM[1],currentSpeed);
    analogWrite(RM[0],0);
    analogWrite(LM[1],currentSpeed);
    analogWrite(LM[0],0);
    delay(d);
    }
      currentSpeed=s;
    analogWrite(RM[1],s);
    analogWrite(RM[0],0);
    analogWrite(LM[1],s);
    analogWrite(LM[0],0);
  }

  void sf(int s){
    if(state!='f') p(); state='f';
    if(!seeing&&lineDetected()){imOnTheLine();}
    for(currentSpeed;currentSpeed<s;currentSpeed+=2){
     ///////////////////////////////////////////////////////////////////////////////
    analogWrite(RM[1],currentSpeed);
    analogWrite(RM[0],0);
    analogWrite(LM[1],currentSpeed);
    analogWrite(LM[0],0);
    delay(d);
    }
    currentSpeed=s;
    analogWrite(RM[1],s);
    analogWrite(RM[0],0);
    analogWrite(LM[1],s);
    analogWrite(LM[0],0);
  }
void b(int s){
  if(state!='b') p(); state='b';
  for(currentSpeed;currentSpeed<s;currentSpeed+=2){
    analogWrite(RM[1],0);
    analogWrite(RM[0],currentSpeed);
    analogWrite(LM[1],0);
    analogWrite(LM[0],currentSpeed);
    delay(d);
    }
    analogWrite(RM[1],0);
    analogWrite(RM[0],s);
    analogWrite(LM[1],0);
    analogWrite(LM[0],s);
  }

void l(int s){
  if(state!='l') p(); state='l';

      for(currentSpeed;currentSpeed<s;currentSpeed+=2){
    analogWrite(RM[0],currentSpeed);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],currentSpeed);
    delay(d);
    }
     
    analogWrite(RM[0],s);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],s);
  }

void r(int s){
  if(state!='r') p(); state='r';
  
      for(currentSpeed;currentSpeed<s;currentSpeed+=2){  
    analogWrite(RM[0],0);
    analogWrite(RM[1],currentSpeed);
    analogWrite(LM[0],currentSpeed);
    analogWrite(LM[1],0);
    delay(d);
    }
     
    analogWrite(RM[0],0);
    analogWrite(RM[1],s);
    analogWrite(LM[0],s);
    analogWrite(LM[1],0);
  }

void p(){
  switch(state){
    case 'p':
    break;
    ////
    case 'f':
    while(currentSpeed > 6) {
    currentSpeed -= 3;
    analogWrite(RM[1],currentSpeed);
    analogWrite(RM[0],0);
    analogWrite(LM[1],currentSpeed);
    analogWrite(LM[0],0);
    delay(d);
    }
    currentSpeed=0;
    break;
    ////
    case 'b':
    while(currentSpeed > 6) {/////////////////////////////////////////test
//    if(digitalRead(cb)==0){
//       stopReverse();
//      break;
//      }
    currentSpeed -= 3;
    analogWrite(RM[1],0);
    analogWrite(RM[0],currentSpeed);
    analogWrite(LM[1],0);
    analogWrite(LM[0],currentSpeed);
    delay(d);
    }
    currentSpeed=0;
    break;
    ////
    case 'l':
    while(currentSpeed > 6) {
    currentSpeed -= 3;
    analogWrite(RM[0],currentSpeed);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],currentSpeed);
    delay(d);
    }
    currentSpeed=0;
    break;
    case 'r':
    while(currentSpeed > 6) {
    currentSpeed -= 3;
    analogWrite(RM[0],0);
    analogWrite(RM[1],currentSpeed);
    analogWrite(LM[0],currentSpeed);
    analogWrite(LM[1],0);
    delay(d);
    }
    currentSpeed=0;
    break;
    }
    state='p';
    analogWrite(RM[0],0);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],0);
  }

void pp(){
  switch(state){
    case 'p':
    break;
    ////
    case 'f':
    while(currentSpeed > 12) {
    currentSpeed -= 6;
    analogWrite(RM[1],currentSpeed);
    analogWrite(RM[0],0);
    analogWrite(LM[1],currentSpeed);
    analogWrite(LM[0],0);
    delay(d);
    }
    currentSpeed=0;
    break;
    ////
    case 'b':
    while(currentSpeed > 12) {/////////////////////////////////test
//      if(digitalRead(cb)==0){
//       stopReverse();
//      break;
//      }
    currentSpeed -= 6;
    analogWrite(RM[1],0);
    analogWrite(RM[0],currentSpeed);
    analogWrite(LM[1],0);
    analogWrite(LM[0],currentSpeed);
    delay(d);
    }
    currentSpeed=0;
    break;
    ////
    case 'l':
    while(currentSpeed > 12) {
    currentSpeed -=6;
    analogWrite(RM[0],currentSpeed);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],currentSpeed);
    delay(d);
    }
    currentSpeed=0;
    break;
    case 'r':
    while(currentSpeed > 12) {
    currentSpeed -= 6;
    analogWrite(RM[0],0);
    analogWrite(RM[1],currentSpeed);
    analogWrite(LM[0],currentSpeed);
    analogWrite(LM[1],0);
    delay(d);
    }
    currentSpeed=0;
    break;
    }
    state='p';
    analogWrite(RM[0],0);
    analogWrite(RM[1],0);
    analogWrite(LM[0],0);
    analogWrite(LM[1],0);
  }
  
  char see(){////////////////////////////////////////////////////////////////////////low seeing high not seeing
  if(!digitalRead(df)){seeing=true;return 'f';}
  if(!digitalRead(dl)&&digitalRead(df)&&digitalRead(dr)){seeing=true;return 'r';}
  if(digitalRead(dl)&&digitalRead(df)&&!digitalRead(dr)){seeing=true;return 'l';}
  if(digitalRead(dl)&&digitalRead(df)&&digitalRead(dr)){seeing=false;return 's';}
  }




  

//  bool lineDetected(){
//    if(!digitalRead(cl)||!digitalRead(cr)){
//      return true;
//      }
//      else return false;
//    }


  
//  bool lineDetected(){
//    if(!digitalRead(cl)||!digitalRead(cr)){
//      return true;
//      }
//      else return false;
//    }


  bool lineDetected(){////////////////////////////////////////////////////////////////this is to test in Rami's house 
    if(!digitalRead(cl)||!digitalRead(cr)||!digitalRead(cb)){
      return true;
      }
      else return false;
    }



    
  void stopReverse(){
    if(see()=='f'){
      f(maxSpeed);
    }else{
      f(halfSpeed);
    }
  }



//  void imOnTheLine(){
//    pp();
//    if(!digitalRead(cl)&& digitalRead(cr)){
//    r(100);p();}
//    
//    if(digitalRead(cl)&& !digitalRead(cr)){
//    l(100);p();}
//
//    if(!digitalRead(cl)&& !digitalRead(cr)){
//    b(100);r(120);p();}
//    }  

  void imOnTheLine(){ ////////////////////////////////////////////////////////////////this is to test in Rami's house 
    pp();

    if(!digitalRead(cb)){
      if(see()=='f'){
      f(maxSpeed);
      delay(1500);
      p();
      }
      f(100);
      delay(250);
      p();
      }
    
    if(!digitalRead(cl)&& digitalRead(cr)){  
    b(100);
    delay(250);
    l(80);
    delay(70);
    p();}
    
    if(digitalRead(cl)&& !digitalRead(cr)){
    b(100);
    delay(250);
    r(80);
    delay(70);
    p();}

    if(!digitalRead(cl)&& !digitalRead(cr)){
    r(80);
    delay(70);  
    b(100);
    delay(500);
    p();
    }
    } 





    
