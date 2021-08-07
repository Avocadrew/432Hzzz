#include <Servo.h>
Servo Stepper_m,Servo_m;      // 建立一個 servo 物件，最多可建立 12個 servo

/*
  Serial.print("angle_m : "); 
  Serial.println(angle_m); 
  Serial.print("t : "); 
  Serial.println(t);
 */
 #define Rsev_pin A1           // 可變電阻連接的 pin 腳
 #define Rste_pin A2
 #define Servo_motor_pin 9      // Servo_motor的 pin 腳
 #define Stepper_motor_pin 10   // Stepper_motor的 pin 腳
 #define Led_pin 11             // Led的 pin 腳
 #define Switch_pin 5          // Switch的 pin 腳
 
 #define angle_m_init 63      //初始數值60(外圈)
 #define mf 51                //內圈深度 53                                    //改50應該就可以
  
int add=0,
   // speed_m_init=90,       //初始數值90(停止)
    angle_total,
    angle_m=0;        //初始數值71外-122內
    
unsigned long previousTime= 0,   //初始化previousTime
              interval=950,       //設定每一個副函式的時間950                                     //00
              previousTimeStop= 0,   //初始化previousTime
              intervalStop=950; 
             
int Rsev_val, 
    t=1,i=0,j=0;         // 從可變電阻來的數值  

void setup() {
  //Serial.begin(9600);                                                                                   //00
  //Serial.println("Hello World!");                          
  pinMode(Rsev_pin,INPUT);
  pinMode(Rste_pin,INPUT);
  Servo_m.attach(Servo_motor_pin);      // 將 servo 物件連接到 Servo_motor_pin=9
  Stepper_m.attach(Stepper_motor_pin);  // 將Stepper物件連接到 Stepper_motor_pin=10
  pinMode(Switch_pin, INPUT);
  pinMode(Led_pin, OUTPUT);
  add=0;                  
  angle_m=0;        //初始數值 加角度 0
  digitalWrite(Led_pin,LOW);
  delay(1500);                                                                                 //00
}

void loop() {
  Led_check();
    
}

void Led_check(){
  
   angle_total=angle_m+add;
    if(angle_total<=0){
        angle_total=0;                                                      
    }else if(angle_total>=50)
        angle_total=49;
    
    if( digitalRead(Switch_pin) == HIGH){
      Servo_m.write(angle_m_init+angle_total);
      Stepper_check();
      digitalWrite(Led_pin,HIGH);
      writeToSound();
      readSound();
    }
    else {
 
      writeToStop();
      Stepper_m.writeMicroseconds(1450);
      Servo_m.write(angle_m_init+angle_m);          // 設定 sservo 位置
      digitalWrite(Led_pin,LOW);                            
    }
}

void Stepper_check(){
  if((angle_m>=45)&&(angle_m<=100)){         // if((angle_m>=50)&&(angle_m<=60)){
      Stepper_m.writeMicroseconds(1421);
  }else if((angle_m>=30)&&(angle_m<45)){    //}else if((angle_m>=30)&&(angle_m<50)){
     Stepper_m.writeMicroseconds(1423);
  }else if((angle_m>=0)&&(angle_m<30)){
     Stepper_m.writeMicroseconds(1425);
  }
}

void writeToSound(){
  if(millis() - previousTime > interval) {
     if((angle_m>=50)&&(angle_m<=mf-1)){
       i++;
       if(i==3){
         angle_m += t;
         i=0;
        }
     }
     else if((angle_m>=45)&&(angle_m<50)){
          j++;
       if(j==2){
         angle_m += t;
         j=0;
        }
       }else if(((angle_m>=0)&&(angle_m<45))||(angle_m=mf)){
          angle_m += t;
       }
     
  if ((angle_m <= 0) || (angle_m >=mf)) 
    t = -t ;
  previousTime = millis();         // 記錄更新時間
    
  }
}

void writeToStop(){
  if((millis() - previousTimeStop > intervalStop)&&(angle_m>0)){
    add=0;
     if((angle_m>=50)&&(angle_m<=mf-1)){
       i++;
       if(i==3){
         angle_m += -1;
         i=0;
        }
     }
     else if((angle_m>=45)&&(angle_m<50)){
          j++;
       if(j==2){
         angle_m += -1;
         j=0;
        }
       }else if(((angle_m>=0)&&(angle_m<45))||(angle_m=mf)){
          angle_m += -1;
       }
  previousTime = millis();         // 記錄更新時間
    
  }else
    angle_m=0;
}

void readSound(){
  if(angle_m>=8&&angle_m<=mf-1){
    add = analogRead(Rsev_pin);           // 從可變電阻讀取類比數值 (介於 0 跟 1023) 
    add=add-8;
  }else
    add=0;
}

void readSound(){
  if(angle_m>=8&&angle_m<=25){
    add = analogRead(Rsev_pin);           // 從可變電阻讀取類比數值 (介於 0 跟 1023) 
    add=add-8;
    if(Rsev_val>=500&&Rsev_val<=1000)
    add = map(Rsev_val, 500, 1000, -20, 20);  
    else if(Rsev_val>=300&&Rsev_val<500)
    add = map(Rsev_val, 300,500, -20, 20); 
    else if(Rsev_val>=100&&Rsev_val>300)
    add = map(Rsev_val, 100,300, -20, 20); 
    else if(Rsev_val>=0&&Rsev_val>100)
    add = map(Rsev_val, 0,100, -20, 20);  
  }else if(angle_m>25&&angle_m<=27){
    add = analogRead(Rsev_pin);           // 從可變電阻讀取類比數值 (介於 0 跟 1023) 
    add=add-8;
    if(Rsev_val>=500&&Rsev_val>=1000)
      add = map(Rsev_val, 0, 1000, -20, 20);  
    else if(Rsev_val>=300&&Rsev_val>500)
      add = map(Rsev_val, 300,500, -20,20); 
    else if(Rsev_val>=100&&Rsev_val>300)
      add = map(Rsev_val, 100,300, -20, 20);  
    else if(Rsev_val>=0&&Rsev_val>100)
      add = map(Rsev_val, 0,100, -20,20);  
  }else if(angle_m>27&&angle_m<=45){
    add = analogRead(Rsev_pin);           // 從可變電阻讀取類比數值 (介於 0 跟 1023)
    add=add-8; 
    if(Rsev_val>=500&&Rsev_val>=1000)
      add = map(Rsev_val, 0, 1000, -10,0);  
    else if(Rsev_val>=300&&Rsev_val>500)
      add = map(Rsev_val, 300,500, -10,0);  
    else if(Rsev_val>=100&&Rsev_val>300)
      add = map(Rsev_val, 100,300, -10, 0);  
    else if(Rsev_val>=0&&Rsev_val>100)
      add = map(Rsev_val, 0,100, -10,0); 
  }else
    add=0;
}
