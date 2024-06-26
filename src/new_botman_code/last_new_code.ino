
//Motors PWM
  const int RM[]={11,10}; const int LM[]={5,6};
//Digital Obstacle Sensors
  const int dl=4; const int df=7; const int dr=12;
  //(LOW= they are seeing, HIGH=not seeing)
//Digital light Sensors
  const int cl=2,cr=3;
  //(Low=white, HIGH=black)
  const int buttonPin = 9;
//vars
  unsigned long buttonPressedTime = 0;
  const int maxSpeed=250;
  int halfSpeed=80;
  char state='p';
  int currentSpeed=0;
  bool seeing=false;
// delay
const int d=3;
// Stop
const int s=10;
// firstSearchSF
int fsf=0;
int switcher=0;
// Stop pp
const int ss=10;
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
bool str1=false;
bool str2=false;
void setup() {
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
  while(digitalRead(buttonPin)==LOW){
       if(digitalRead(dr)==0){
         str1=true;
      }else{
        str1=false;
        }   

        if(digitalRead(dl)==0){
         str2=true;
      }else{
        str2=false;
        }  
    }
  buttonPressedTime = millis();

  // Wait for 5 seconds after button release before starting
  while (millis() - buttonPressedTime < 5000) {
    // Wait for 5 seconds
  }

  if(str1){
    l(100);
  delay(5);
  f(100);
  delay(750);
  r(120);
  delay(200);
  p();
    }
   if(str2){
    r(100);
  delay(5);
  f(100);
  delay(750);
  l(120);
  delay(200);
  p();
    
    }


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
      
      sf(35);///////////finding the enemy
    break;
    }
}

void f(int s){
  fsf=0;
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
    if(!seeing&&lineDetected()){
      
      imOnTheLine();}
       f(s);
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
    currentSpeed -= s;
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
    currentSpeed -= s;
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
    currentSpeed -= s;
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
    currentSpeed -= s;
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
    currentSpeed -= ss;
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

    currentSpeed -= ss;
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
    currentSpeed -=ss;
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
    currentSpeed -= ss;
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
    if(!digitalRead(cl)||!digitalRead(cr)){
      return true;
      }
      else return false;
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
    if(!digitalRead(cl)&& digitalRead(cr)){  
    
    l(100);
    delay(60);
    p();}
    
    if(digitalRead(cl)&& !digitalRead(cr)){
    
    r(100);
    delay(60);
    p();}

    if(!digitalRead(cl)&& !digitalRead(cr)){
    r(80);
    delay(70);  
    b(80);
    delay(500);
    p();
    }
    } 





    
