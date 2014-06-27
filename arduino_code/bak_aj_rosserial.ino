/*
This is the aduino code for AJ 2.0, for electrical designs and documentation
check the GIT Hub located at ...
 */

//include rosserial libaries
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle nh;

//Define all Subscribers


// set pin numbers:
const int button_pin_1 = 2;     // the number of the pushbutton pin
const int button_pin_2 = 3;

const int pwm_1_pin = 4;	//setting pins for motor controller
const int in_a_pin = 5;
const int in_b_pin = 6;
const int en_pin = 7;

const int servo_1_pin = 8;	//setting servo pins 
const int servo_2_pin = 9;
 
const int led_pin = 13;      // the number of the LED pin

int switch_1_count = 0;
int switch_2_count = 0;

// variables will change:
int button_state_1 = 0;         // variable for reading the pushbutton status
int button_state_2 = 0;         // variable for reading the pushbutton status

boolean enable_1_bool = false;	//Motor controller enable pin set

boolean led_bool = false;

//direction set a = 0,b = 0, no movement, a = 1, b = 0, Clockwise, a = 0, b = 1, Counterclockwise, 
boolean in_a_bool = false;
boolean	in_b_bool = false;

int pwm_motor_1 = 0;
int servo_1_angle;
int servo_2_angle;

std_msgs::UInt16 press_1;
std_msgs::UInt16 press_2;
std_msgs::UInt16 check_1;
std_msgs::UInt16 check_value;
//std_msgs::Int16MultiArray bool_array;

ros::Publisher limit_1("limit_switch_1", &press_1);
ros::Publisher limit_2("limit_switch_2", &press_2);
ros::Publisher check("check", &check_1);
ros::Publisher check_val("check_val", &check_value);
//ros::Publisher array_update("bool_update", &bool_array);


//void bool_array_update(){

//}

void pwm_1_callback( const std_msgs::UInt16& pwm_1){
	pwm_motor_1 = pwm_1.data;
	}

// void led_callback( const std_msgs::UInt16& led){
//     led_bool = led.data;
// 	}

// void in_a_callback( const std_msgs::UInt16& in_a){
// 	in_a_bool = in_a.data;
// 	}	

// void in_b_callback( const std_msgs::UInt16& in_b){
// 	in_b_bool = in_b.data;
// 	}

// void en_callback( const std_msgs::UInt16& motor_enable){
// 	enable_1_bool = motor_enable.data;
// 	}

void bool_callback( const std_msgs::UInt16& bool_value){
	if(bool_value.data == 1){
		led_bool = true;	    
	}

	if(bool_value.data == 2){
		led_bool = false;    
	}

	if(bool_value.data == 3){
	    enable_1_bool = true;
	}

	if(bool_value.data == 4){
	    enable_1_bool = false;
	}

	if(bool_value.data == 5){
	    in_a_bool = true;
	}

	if(bool_value.data == 6){
	    in_a_bool = false;
	}

	if(bool_value.data == 7){
	    in_b_bool = true;
	}

	if(bool_value.data == 8){
		in_b_bool = false;
	}

	else{
		return; 
	}	    
}

ros::Subscriber<std_msgs::UInt16> sub_1("/pwm_1", pwm_1_callback);
ros::Subscriber<std_msgs::UInt16> sub_2("/bool", bool_callback);

//ros::Subscriber<std_msgs::UInt16> sub_2("/led", led_callback);
//ros::Subscriber<std_msgs::UInt16> sub_3("/in_a", in_a_callback);
//ros::Subscriber<std_msgs::UInt16> sub_4("/in_b", in_b_callback);
//ros::Subscriber<std_msgs::UInt16> sub_5("/motor_enable", en_callback);

void setup(){
	// initialize the LED pin as an output:
	pinMode(led_pin, OUTPUT);      
	// initialize the pushbutton pin as an input:
	pinMode(button_pin_1, INPUT);     
	pinMode(button_pin_2, INPUT);
	// initialize motor pins
	pinMode(pwm_1_pin, OUTPUT);
	pinMode(in_a_pin, OUTPUT);
	pinMode(in_b_pin, OUTPUT);
	pinMode(en_pin, OUTPUT);
	// initialize servo pins
	pinMode(servo_1_pin, OUTPUT);
	pinMode(servo_2_pin, OUTPUT);	
	//int rosserial stuff
	nh.initNode();
	nh.advertise(limit_1);
	nh.advertise(limit_2);
	nh.advertise(check);
	nh.advertise(check_val);
	
	in_a_bool = true;
	in_b_bool = false;
	enable_1_bool = true;
        pwm_motor_1 = 176;z
        

        nh.subscribe(sub_1);
	nh.subscribe(sub_2);
	// nh.subscribe(sub_3);
	// nh.subscribe(sub_4);
	// nh.subscribe(sub_5);

	}

void loop(){
	if(led_bool == true){
		digitalWrite(led_pin, HIGH);	
	}
	if(led_bool == false){
		digitalWrite(led_pin, LOW);
	}	

	if(enable_1_bool == true){
		digitalWrite(en_pin, HIGH);	
	}
	if(enable_1_bool == false){
		digitalWrite(en_pin, LOW);
	}	

	if(in_a_bool == true){
		digitalWrite(in_a_pin, HIGH);
	}
	if(in_a_bool == false){
		digitalWrite(in_a_pin, LOW);
	}

	if(in_b_bool == true){
		digitalWrite(in_b_pin, HIGH);
	}
	if(in_b_bool == false){
		digitalWrite(in_b_pin, LOW);
	}

	analogWrite(pwm_1_pin, pwm_motor_1);

	button_state_1 = digitalRead(button_pin_1);
	button_state_2 = digitalRead(button_pin_2);

	if (button_state_1 == HIGH) {     
		// turn LED on:    
		digitalWrite(led_pin, HIGH);  
		if (switch_1_count = 0){
			in_a_bool = false;
			in_b_bool = false;
			switch_1_count = 1;
		}	
		limit_1.publish( &press_1 );
	} 
	else {
		// turn LED off:
		digitalWrite(led_pin, LOW); 
		switch_1_count = 0;
	}

	if (button_state_2 == HIGH) {     
		// turn LED on:    
		digitalWrite(led_pin, HIGH);
		if (switch_2_count){
			in_a_bool = false;
			in_b_bool = false;
			switch_2_count = 1;
		}
		limit_2.publish( &press_2 ); 
	} 
	else {
		// turn LED off:
		digitalWrite(led_pin, LOW);
		switch_2_count = 0;
	}
	nh.spinOnce();
}



