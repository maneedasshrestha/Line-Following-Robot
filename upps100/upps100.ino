const int irlf= A0;//left far IR sensor
const int irln= A1;//left near sensor
const int irc= A2;//center IR sensor
const int irrn= A3;//Right near IR sensor
const int irrf= A4;//Right far IR sensor

int IRLF = 0;
int IRLN = 0;
int IRC = 0;
int IRRN = 0;
int IRRF = 0;

const int motorLeftForward= 7;
const int motorLeftReverse= 6;
const int motorRightForward= 5;
const int motorRightReverse= 4;
const int enRightPin=10;
const int enLeftPin=11;

void setup() {
  pinMode(motorLeftForward, OUTPUT);
  pinMode(irlf, INPUT);
  pinMode(irln, INPUT);
  pinMode(irc, INPUT);
  pinMode(irrn, INPUT);
  pinMode(irrf, INPUT);
  pinMode(enLeftPin, OUTPUT);
  pinMode(enRightPin, OUTPUT);
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftReverse, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightReverse, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  getSensorData();
  processData();
  // moveMotors(100, 100);
  processData();
  debugMode();
}//close loop

void processData(){
  if(IRLF==0 && IRLN ==0 && IRC == 1 && IRRN ==0 && IRRF==0){
    Serial.print("Straight");
    moveMotors(100, 100);
  }
  if(IRLF==0 && IRLN ==1 && IRC == 1 && IRRN ==0 && IRRF==0){
//Go straight even if left near and center light up with slight right
    Serial.print("slight right but mostly straight");

moveMotors(80,100);
  }
  if(IRLF==0 && IRLN ==0 && IRC == 1 && IRRN ==1 && IRRF==0){
//GO straight even if right near and center light up with slight left
    Serial.print("slight left but mostly straight");

moveMotors(100,80);

  }
  if(IRLF==0 && IRLN ==1 && IRC == 0 && IRRN ==0 && IRRF==0){
//go slightly right if left near lights up
    Serial.print("ali right");

moveMotors(100,50);
  }
  if(IRLF==0 && IRLN ==0 && IRC == 0 && IRRN ==1 && IRRF==0){
//go slightly left if right near lights up
    Serial.print("ali left");

moveMotors(50,100);

  }
  if(IRLF==1 && IRLN ==1 && IRC == 0 && IRRN ==0 && IRRF==0){
    //go right moree 
        Serial.print("Rightt morreeee");

    moveMotors(100,20);

  }
  if(IRLF==0 && IRLN ==0 && IRC == 0 && IRRN ==1 && IRRF==1){
    //go left moreeee
        Serial.print("Left Moreeee");

        moveMotors(20,100);

  }
  if(IRLF==1 && IRLN ==0 && IRC == 0 && IRRN ==0 && IRRF==0){
    //goo rightttttt moreeeeeeeeeeeeeeeeeeeeee
    Serial.print("GO right MOREEEEEEEEEE");
    moveMotors(100,100);
  }
  if(IRLF==0 && IRLN ==0 && IRC == 0 && IRRN ==0 && IRRF==1){
    //gooo lefttttttttttttttt moreeeeeeeeeeeeee
        Serial.print("GO LEFT MOREEEEEEE");

    moveMotors(-1,100);
  }
  if(IRLF==0 && IRLN ==0 && IRC == 0 && IRRN ==0 && IRRF==0){
    //rotate right until line is found
    moveMotors(0,0);
        Serial.print("Stop");

  }
  if(IRLF==1 && IRLN ==1 && IRC == 1 && IRRN ==1 && IRRF==1){
    //junction is met, turn left until straight line is found.
  }
  if(IRLF=1 && IRLN ==1 && IRC == 1 && IRRN ==0 && IRRF==0){
    //left path found, steer left.
  }
  if(IRLF==0 && IRLN ==0 && IRC == 1 && IRRN ==1 && IRRF==1){
    //right path found, but continue in straight path.
    moveMotors(100,100);
  }
  // else{
  //   moveMotors(-1, -1);
  // }
}

void moveMotors(int leftMotorSpeed, int rightMotorSpeed)
{
  leftMotorSpeed=constrain(leftMotorSpeed, -100, 100);
  rightMotorSpeed=constrain(rightMotorSpeed, -100, 100);

  int enL=abs(map(leftMotorSpeed, -100, 100, -255, 255));
  int enR=abs(map(rightMotorSpeed, -100, 100, -255, 255));

  analogWrite(enLeftPin,enL);
  analogWrite(enRightPin,enR);

  digitalWrite(motorLeftForward, leftMotorSpeed > 0);
  digitalWrite(motorLeftReverse, leftMotorSpeed < 0);
  digitalWrite(motorRightForward, rightMotorSpeed > 0);
  digitalWrite(motorRightReverse, rightMotorSpeed < 0); 

}


void getSensorData(){
  IRLF=digitalRead(irlf);//LEft far sensor
  IRLN=digitalRead(irln);//left near
  IRC=digitalRead(irc);//center
  IRRN=digitalRead(irrn);//right near
  IRRF=digitalRead(irrf);//right far sensor
  Serial.print(IRLF); Serial.print(", "); 
  Serial.print(IRLN); Serial.print(", "); 
Serial.print(IRC); Serial.print(", "); 
Serial.print(IRRN); Serial.print(", "); 
Serial.print(IRRF); Serial.print("\n");  

}

void debugMode(){
  Serial.print(IRLF); Serial.print(", "); Serial.print(IRLN); Serial.print(", "); Serial.print(IRC); Serial.print(", "); Serial.print(IRRN); Serial.print(", "); Serial.print(IRRF); Serial.print("\n");  
}