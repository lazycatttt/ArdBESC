double ch1_pin = 3;  //PWM pin
double ch2_pin = 5;  //PWM pin

//Right motor driver pins
int R_EN_right = 2; 
int L_EN_right = 4;
int R_PWM_right = 6; //PWM pin
int L_PWM_right = 9; //PWM pin

//Left motor driver pins
int R_EN_left = 7; 
int L_EN_left = 8;
int R_PWM_left = 10; //PWM pin
int L_PWM_left = 11; //PWM pin

//FWD
int Ch1_start_Fwd = 1540;
int Ch1_End_Fwd = 1985;
//BACK
int Ch1_start_Bac = 1470;
int Ch1_End_Bac = 980;
//RIGHT
int Ch2_start_Fwd = 1540;
int Ch2_End_Fwd = 1980;
//LEFT
int Ch2_start_Bac = 1470;
int Ch2_End_Bac = 980;

void setup()
{
  Serial.begin(9600);
  pinMode(3,INPUT);
  pinMode(5,INPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT); 
  pinMode(9,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT); 
  pinMode(11,OUTPUT);
}

void loop()
{
//Receiver signal pins data
double ch1 = pulseIn(3,HIGH);
double ch2 = pulseIn(5,HIGH);

/*Serial.println(ch1);
Serial.print(",");
Serial.println(ch2);*/


//Speed mapping for F/B
int spdFwd = map(ch1, Ch1_start_Fwd, Ch1_End_Fwd, 0, 255);   
int spdBac = map(ch1, Ch1_start_Bac, Ch1_End_Bac, 0, 255); 
//Speed mapping for R/L
int spdRyt = map(ch2, Ch2_start_Fwd, Ch2_End_Fwd, 0, 255);   
int spdLft = map(ch2, Ch2_start_Bac, Ch2_End_Bac, 0, 255);      

/*Serial.println(spdFwd);
Serial.print(",");
Serial.println(spdFwd*1.6);*/

digitalWrite(R_EN_right, HIGH);
digitalWrite(L_EN_right, HIGH);
digitalWrite(R_EN_left, HIGH);
digitalWrite(L_EN_left, HIGH);

if((ch1==0)&&(ch2==0))
{     
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,0);
}
//FWD
else if(ch1>Ch1_start_Fwd)
{    
if(ch2>Ch2_start_Fwd)
{ 
analogWrite(R_PWM_right,spdFwd/2);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,spdFwd);
analogWrite(L_PWM_left,0); 
}
else if(ch2<Ch2_start_Bac)
{
analogWrite(R_PWM_right,spdFwd);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,spdFwd/2);
analogWrite(L_PWM_left,0);  
  }
else{
analogWrite(R_PWM_right,spdFwd);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,spdFwd);
analogWrite(L_PWM_left,0); 
}
}
//BACK
else if(ch1<Ch1_start_Bac)
{        
  if(ch2>Ch2_start_Fwd)
{ 
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,spdBac); 
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,spdBac/2); 
}
else if(ch2<Ch2_start_Bac)
{
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,spdBac/2); 
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,spdBac);
  }
else{
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,spdBac); 
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,spdBac); 
}
}
//RIGHT
else if(ch2>Ch2_start_Fwd)
{ 
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,spdRyt);
analogWrite(R_PWM_left,spdRyt);
analogWrite(L_PWM_left,0);
}
//LEFT
else if(ch2<Ch2_start_Bac)
{     
analogWrite(R_PWM_right,spdLft);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,spdLft);
}
else
{     
analogWrite(R_PWM_right,0);
analogWrite(L_PWM_right,0);
analogWrite(R_PWM_left,0);
analogWrite(L_PWM_left,0);
}
