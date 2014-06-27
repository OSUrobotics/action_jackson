//Servo Angle Tester

#include <Servo.h> 

 
Servo servo_1;  // create servo object to control a servo 
Servo servo_2;

 
void setup() 
{ 
  Serial.begin(9600);
  servo_1.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo_2.attach(10);
} 
 
void loop() 
{ 
  int servo_1_angle = 0;
  int servo_2_angle = 0;
  int angles[2];
  servo_1_angle = servo_1.read(); 
  servo_2_angle = servo_2.read();
  angles[0] = servo_1_angle;
  angles[1] = servo_2_angle;
  int n;
  for (n=0; n<2; n++){
    Serial.print(angles[n]);
    
  }
  delay(1000);
} 
