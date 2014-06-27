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
#include <std_msgs/Int16MultiArray.h>
//#include <std_msgs/ByteMultiArray.h>

ros::NodeHandle nh;

//Define all Subscribers


// set pin numbers:
const int button_pin_1 = 2;     // the number of the pushbutton pin
const int button_pin_2 = 3;

const int pwm_1_pin = 4;	//setting pins for motor controller
const int in_a_pin = 5;
const int in_b_pin = 6;
const int en_pin = 7;

const int servo_1_pin = 9;	//setting servo pins 
const int servo_2_pin = 10;

Servo servo_1;
Servo servo_2;
 
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
int servo_1_angle = 90;
int servo_2_angle = 90;

std_msgs::UInt16 press_1;
std_msgs::UInt16 press_2;
std_msgs::UInt16 check_1;
std_msgs::UInt16 check_value;
//std_msgs::ByteMultiArray bool_array;

ros::Publisher limit_1("limit_switch_1", &press_1);
ros::Publisher limit_2("limit_switch_2", &press_2);
ros::Publisher check("check", &check_1);
ros::Publisher check_val("check_val", &check_value);
//ros::Publisher array_update("bool_update", &bool_array);

//char dim_0_label[] = "bool_values";

// void bool_array_update(){
// 	//This function will save all the current bool values in it and publish it
// 	bool_array.data[0] = led_bool;
// 	bool_array.data[1] = enable_1_bool;
// 	bool_array.data[2] = in_a_bool;
// 	bool_array.data[3] = in_b_bool;
// 	bool_array.data[4] = button_state_1;
// 	bool_array.data[5] = button_state_2;
//         array_update.publish( &bool_array );
// }

void pwm_1_callback( const std_msgs::UInt16& pwm_1){
	pwm_motor_1 = pwm_1.data;
	}

void servo_1_callback( const std_msgs::UInt16& servo_1_data){
	servo_1_angle = servo_1_data.data;
}	

void servo_2_callback( const std_msgs::UInt16& servo_2_data){
	servo_2_angle = servo_2_data.data;
}

void bool_callback( const std_msgs::UInt16& bool_value){
	if(bool_value.data == 1){
		led_bool = true;	    
		//bool_array_update();
	
	}

	if(bool_value.data == 2){
		led_bool = false;    
		//bool_array_update();
	
	}

	if(bool_value.data == 3){
	    enable_1_bool = true;
		//bool_array_update();
	
	}

	if(bool_value.data == 4){
	    enable_1_bool = false;
		//bool_array_update();
	
	}

	if(bool_value.data == 5){
	    in_a_bool = true;
		//bool_array_update();
	
	}

	if(bool_value.data == 6){
	    in_a_bool = false;
		//bool_array_update();
	
	}

	if(bool_value.data == 7){
	    in_b_bool = true;
		//bool_array_update();
	
	}

	if(bool_value.data == 8){
		in_b_bool = false;
		//bool_array_update();
	}
	else{
		return; 
	}	    
}

ros::Subscriber<std_msgs::UInt16> sub_1("/pwm_1", pwm_1_callback);
ros::Subscriber<std_msgs::UInt16> sub_2("/bool", bool_callback);
ros::Subscriber<std_msgs::UInt16> sub_3("/servo_1", servo_1_callback);
ros::Subscriber<std_msgs::UInt16> sub_4("/servo_2", servo_2_callback);

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
	
	servo_1.attach(9);
 	servo_2.attach(10);
	
	//Setting up Bool Feedback
	// bool_array.layout.dim = (std_msgs::MultiArrayDimension *)malloc(sizeof(std_msgs::MultiArrayDimension) * 2);
	// bool_array.layout.dim[0].label = dim_0_label;
	// bool_array.layout.dim[0].size = 6;
	// bool_array.layout.dim[0].stride = 1*6;
	// bool_array.layout.dim_length = 1;
 //    bool_array.layout.data_offset = 0;
 //    bool_array.data_length = 1;
	// bool_array.data = (( int8_t*)malloc(sizeof(int8_t)*6));
        	

	//nh.advertise(array_update);
	nh.advertise(limit_1);
	nh.advertise(limit_2);
	nh.advertise(check);
	nh.advertise(check_val);
	
	in_a_bool = false;
	in_b_bool = false;
	enable_1_bool = false;
    pwm_motor_1 = 176;
        

    nh.subscribe(sub_1);
	nh.subscribe(sub_2);
	nh.subscribe(sub_3);
	nh.subscribe(sub_4);
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

	servo_1.write(servo_1_angle);
	servo_2.write(servo_2_angle);

	analogWrite(pwm_1_pin, pwm_motor_1);

	button_state_1 = digitalRead(button_pin_1);
	button_state_2 = digitalRead(button_pin_2);

	// if (button_state_1 == HIGH) {     
	// 	// turn LED on:    
	// 	digitalWrite(led_pin, HIGH);  
	// 	if (switch_1_count = 0){
	// 		in_a_bool = false;
	// 		in_b_bool = false;
	// 		switch_1_count = 1;
	// 	}	
	// 	limit_1.publish( &press_1 );
	// } 
	// else {
	// 	// turn LED off:
	// 	digitalWrite(led_pin, LOW); 
	// 	switch_1_count = 0;
	// }

	// if (button_state_2 == HIGH) {     
	// 	// turn LED on:    
	// 	digitalWrite(led_pin, HIGH);
	// 	if (switch_2_count){
	// 		in_a_bool = false;
	// 		in_b_bool = false;
	// 		switch_2_count = 1;
	// 	}
	// 	limit_2.publish( &press_2 ); 
	// } 
	//else {
	//	// turn LED off:
	//	digitalWrite(led_pin, LOW);
	//	switch_2_count = 0;
	//}
        nh.spinOnce();
}




