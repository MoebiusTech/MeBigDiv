//主控芯片MEGA2560芯片 
//Main control chip MEGA2560 chip download chip CH340 needs to install CH340 driver
//MeBigDiv黑色控制器和DWS300黑色电机驱动蓝牙程序 
//MeBigDiv black controller and DWS300 black motor driver Bluetooth program


//电机引脚
//Motor pin
#define PWMA 4     //A电机转速 A Motor speed
#define DIRA1 A4    
#define DIRA2 A5    //A电机方向 A Motor direction
#define PWMB 6      //B电机转速   B Motor speed
#define DIRB1 43 
#define DIRB2 42    //B电机方向 Motor direction
#define PWMC 11     //C电机转速  C Motor speed
#define DIRC1 34 
#define DIRC2 35   //C电机方向  C Motor direction
#define PWMD 7     //D电机转速  D Motor speed
#define DIRD1 37 
#define DIRD2 36   //D电机方向 D Motor direction

#define MOTORA_FORWARD(pwm)    do{digitalWrite(DIRA1,HIGH); digitalWrite(DIRA2,LOW);analogWrite(PWMA,pwm);}while(0)
#define MOTORA_STOP(x)         do{digitalWrite(DIRA1,LOW); digitalWrite(DIRA2,LOW); analogWrite(PWMA,0);}while(0)
#define MOTORA_BACKOFF(pwm)    do{digitalWrite(DIRA1,LOW);digitalWrite(DIRA2,HIGH); analogWrite(PWMA,pwm);}while(0) 

#define MOTORB_FORWARD(pwm)    do{digitalWrite(DIRB1,LOW); digitalWrite(DIRB2,HIGH);analogWrite(PWMB,pwm);}while(0)
#define MOTORB_STOP(x)         do{digitalWrite(DIRB1,LOW); digitalWrite(DIRB2,LOW); analogWrite(PWMB,0);}while(0)
#define MOTORB_BACKOFF(pwm)    do{digitalWrite(DIRB1,HIGH);digitalWrite(DIRB2,LOW); analogWrite(PWMB,pwm);}while(0)

#define MOTORC_FORWARD(pwm)    do{digitalWrite(DIRC1,HIGH); digitalWrite(DIRC2,LOW);analogWrite(PWMC,pwm);}while(0)
#define MOTORC_STOP(x)         do{digitalWrite(DIRC1,LOW); digitalWrite(DIRC2,LOW); analogWrite(PWMC,0);}while(0)
#define MOTORC_BACKOFF(pwm)    do{digitalWrite(DIRC1,LOW);digitalWrite(DIRC2,HIGH); analogWrite(PWMC,pwm);}while(0)

#define MOTORD_FORWARD(pwm)    do{digitalWrite(DIRD1,LOW); digitalWrite(DIRD2,HIGH);analogWrite(PWMD,pwm);}while(0)
#define MOTORD_STOP(x)         do{digitalWrite(DIRD1,LOW); digitalWrite(DIRD2,LOW); analogWrite(PWMD,0);}while(0)
#define MOTORD_BACKOFF(pwm)    do{digitalWrite(DIRD1,HIGH);digitalWrite(DIRD2,LOW); analogWrite(PWMD,pwm);}while(0)

#define SERIAL Serial
#define HC06 Serial3
//#define LOG_DEBUG

//#ifdef LOG_DEBUG
//#define M_LOG SERIAL.print
//#define M_LOG Serial.print
//#else
//#define M_LOG 
//#endif

#define MAX_PWM   200
#define MIN_PWM   20
int Motor_PWM = 150;

//控制电机运动    宏定义


//    ↑A-----B↑   
//     |  ↑  |
//     |  |  |
//    ↑C-----D↑
void ADVANCE()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_FORWARD(Motor_PWM);    
  MOTORC_FORWARD(Motor_PWM);MOTORD_FORWARD(Motor_PWM);    
}

//    ↓A-----B↓   
//     |  |  |
//     |  ↓  |
//    ↓C-----D↓
void BACK()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    =A-----B↑   
//     |   ↖ |
//     | ↖   |
//    ↑C-----D=
void LEFT_1()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}

//    ↓A-----B↑   
//     |  ←  |
//     |  ←  |
//    ↑C-----D↓
void LEFT_2()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    ↓A-----B=   
//     | ↙   |
//     |   ↙ |
//    =C-----D↓
void LEFT_3()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    ↑A-----B=   
//     | ↗   |
//     |   ↗ |
//    =C-----D↑
void RIGHT_1()
{
  MOTORA_STOP(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_STOP(Motor_PWM);
}
//    ↑A-----B↓   
//     |  →  |
//     |  →  |
//    ↓C-----D↑
void RIGHT_2()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}
//    =A-----B↓   
//     |   ↘ |
//     | ↘   |
//    ↓C-----D=
void RIGHT_3()
{
  MOTORA_STOP(Motor_PWM);MOTORB_BACKOFF (Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_STOP(Motor_PWM);
}
//    =A-----B=  
//     |  =  |
//     |  =  |
//    =C-----D=
void Right_spin()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);  
 }
void Left_spin()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_FORWARD(Motor_PWM); 
 }
void STOP()
{
  MOTORA_STOP(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_STOP(Motor_PWM);
}
void UART_Control() {
    char Uart_Date;
    if (Serial.available()) {
        Uart_Date = Serial.read();
    } else if (HC06.available()) {
        Uart_Date = HC06.read();
        Serial.println(Uart_Date);
    }

  switch(Uart_Date)
  {
     case 'A':  ADVANCE();        break;
     case 'B':  RIGHT_1();        break;
     case 'G':  RIGHT_2();        break;
     case 'D':  LEFT_3();         break;
     case 'E':  BACK();           break;
     case 'F':  RIGHT_3();        break;
     case 'C':  LEFT_2();         break;
     case 'b': Right_spin();      break;
     case 'd': Left_spin();       break;
     case 'H':  LEFT_1();         break;
     case 'Z':  STOP();           break;
     case 'z':  STOP();           break;
     case 'L':  Motor_PWM = 70;  break;
     case 'M':  Motor_PWM = 30;   break;
   }
     
}
/*
void UART_Control()
{
  char Uart_Date;
 if(SERIAL.available())
  {
   
   Uart_Date = SERIAL.read();
   delay(100);
  }

  switch(Uart_Date)
  {
     case 'A':  ADVANCE();    M_LOG("Run!\r\n");          break;
     case 'B':  RIGHT_1();    M_LOG("Right up!\r\n");     break;
     case 'C':  RIGHT_2();    M_LOG("Right!\r\n");        break;
     case 'D':  RIGHT_3();    M_LOG("Right down!\r\n");   break;
     case 'E':  BACK();       M_LOG("Run!\r\n");          break;
     case 'F':  LEFT_3();     M_LOG("Left down!\r\n");    break;
     case 'G':  LEFT_2();     M_LOG("Left!\r\n");         break;
     case 'H':  LEFT_1();     M_LOG("Left up!\r\n");      break;
     case 'Z':  STOP();       M_LOG("Stop!\r\n");         break;
     case 'L':  Motor_PWM = 240;                          break;
     case 'M':  Motor_PWM = 130;                          break;
   }
     
}
*/
/*

void UART_Control()
{
  char Uart_Date = 0;
  if(Serial.available())
  {
    Uart_Date = Serial.read();
  }
  if(Uart_Date=='A')
  {
    ADVANCE();
  }
  if(Uart_Date=='B')
  {
   RIGHT_1();
  }
  if(Uart_Date=='C')
  {
    RIGHT_2();
  }
  if(Uart_Date=='D')
  {
    RIGHT_3();
  }
  if(Uart_Date == 'E')
  {
    BACK(); 
   }
  if(Uart_Date=='F')
  {
    LEFT_3();
  }
  if(Uart_Date=='G')
  {
     LEFT_2();
  }
  if(Uart_Date=='H')
  {
    LEFT_1();
  }
//  if(Uart_Date=='E')
//  {
//    BACK();
//  }
  if(Uart_Date=='Z')
  {
    STOP();
  }
}
*/

void IO_init()
{
	pinMode(PWMA, OUTPUT);
	pinMode(DIRA1, OUTPUT);pinMode(DIRA2, OUTPUT);
	pinMode(PWMB, OUTPUT);
	pinMode(DIRB1, OUTPUT);pinMode(DIRB2, OUTPUT);
  pinMode(PWMC, OUTPUT);
	pinMode(DIRC1, OUTPUT);pinMode(DIRC2, OUTPUT);
	pinMode(PWMD, OUTPUT);
	pinMode(DIRD1, OUTPUT);pinMode(DIRD2, OUTPUT);
	STOP();
}
void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  HC06.begin(9600);
  IO_init();
  SERIAL.print("Start");
  STOP(); 
  delay(1500);

}

void loop()
{
	UART_Control();//串口接收处理 
	//CAR_Control();//小车控制
  
}
