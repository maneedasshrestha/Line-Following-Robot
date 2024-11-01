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
  debugMode();
}//close loop

void processData(){
  if(IRLF==1 && IRLN ==1 && IRC == 0 && IRRN ==1 && IRRF==1){
    //optimum condition, move Straight
    Serial.print("Straight");
    moveMotors(100, 100);
  }
  if(IRLF==1 && IRLN ==0 && IRC == 0 && IRRN ==1 && IRRF==1){
    //Go straight even if left near and center light up with slight left
    Serial.print("slight left but mostly straight");
    moveMotors(100,60);
  }
  if(IRLF==1 && IRLN ==1 && IRC == 0 && IRRN ==0 && IRRF==1){
    //GO straight even if right near and center light up with slight right
    Serial.print("slight right but mostly straight");
    moveMotors(60,100);
  }
  if(IRLF==1 && IRLN ==0 && IRC == 1 && IRRN ==1 && IRRF==1){
    //go slightly left if left near lights up
    Serial.print("ali left");
    moveMotors(30,100);
  }
  if(IRLF==1 && IRLN ==1 && IRC == 1 && IRRN ==0 && IRRF==1){
    //go slightly right if right near lights up
    Serial.print("ali right");
    moveMotors(100,30);
  }
  if(IRLF==0 && IRLN ==0 && IRC == 1 && IRRN ==1 && IRRF==1){
    //go right moree 
    Serial.print("Rightt morreeee");
    moveMotors(11,100);
  }
  if(IRLF==1 && IRLN ==1 && IRC == 1 && IRRN ==0 && IRRF==0){
    //go left moreeee
    Serial.print("Left Moreeee");
    moveMotors(100,11);
  }
  if(IRLF==0 && IRLN ==1 && IRC == 1 && IRRN ==1 && IRRF==1){
    //goo rightttttt moreeeeeeeeeeeeeeeeeeeeee
    Serial.print("GO right MOREEEEEEEEEE");
    moveMotors(-100,100);
  }
  if(IRLF==1 && IRLN ==1 && IRC == 1 && IRRN ==1 && IRRF==0){
    //gooo lefttttttttttttttt moreeeeeeeeeeeeee
    Serial.print("GO LEFT MOREEEEEEE");
    moveMotors(100,-100);
  }
  if(IRLF==1 && IRLN ==1 && IRC == 1 && IRRN ==1 && IRRF==1){
    //white line ahead stop
    moveMotors(0,0);
    Serial.print("Stop");
  }
  if(IRLF==0 && IRLN ==0 && IRC == 0 && IRRN ==1 && IRRF==1){
    //left path found, steer left.
    moveMotors(100,100);
    Serial.print("Left path found, but Go straight");
  }
  if(IRLF==1 && IRLN ==1 && IRC == 0 && IRRN ==0 && IRRF==0){
    //right path found, but continue in straight path.
    moveMotors(100,100);
    Serial.print("Right path found, but Go straight");
  }
  // if(IRLF==0 && IRLN ==0 && IRC == 0 && IRRN ==1 && IRRF==1){
  //   //go right dherai nai
  //   moveMotors(10,100);100
  //   Serial.print("Right Dherai naii")
  // }
  // if(IRLF==1 && IRLN ==1 && IRC == 0 && IRRN ==0 && IRRF==0){
  //   //go left dherai nai
  //   moveMotors(100,10);
  //   Serial.print("Left Path Dherai naii")
  // }
  if(IRLF==0 && IRLN ==0 && IRC == 0 && IRRN ==0 && IRRF==0){
    //all black lines, move straight
    moveMotors(100,100);
    Serial.print("All black line, move Straight");
  }
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
//   Serial.print(IRLF); Serial.print(", "); 
//   Serial.print(IRLN); Serial.print(", "); 
// Serial.print(IRC); Serial.print(", "); 
// Serial.print(IRRN); Serial.print(", "); 
// Serial.print(IRRF); Serial.print("\n");  

}

void debugMode(){
  Serial.print(IRLF); Serial.print(", "); Serial.print(IRLN); Serial.print(", "); Serial.print(IRC); Serial.print(", "); Serial.print(IRRN); Serial.print(", "); Serial.print(IRRF); Serial.print("\n");  
}