/*
This is the aduino code for AJ 2.0, for electrical designs and documentation
check the GIT Hub located at ...
 */

// constants won't change. They're used here to 
// set pin numbers:
const int button_pin_1 = 2;     // the number of the pushbutton pin
const int button_pin_2 = 3;

const int pwm_1 = 4;	//setting pins for motor controller
const int in_a = 5;
const int in_b = 6;
const int en = 7;

const int servo_1 = 8;	//setting servo pins 
const int servo_2 = 9;
 
const int led_pin = 13;      // the number of the LED pin

// variables will change:
int button_state_1 = 0;         // variable for reading the pushbutton status
int button_state_2 = 0;         // variable for reading the pushbutton status

boolean enable_1_bool = true;	//Motor controller enable pin set

//direction set a = 0,b = 0, no movement, a = 1, b = 0, Clockwise, a = 0, b = 1, Counterclockwise, 
boolean in_a_bool = true;
boolean	in_b_bool = false;

int pwm_motor_1 = 0;
int servo_1_angle;
int servo_2_angle;



void setup(){
	// initialize the LED pin as an output:
	pinMode(led_pin, OUTPUT);      
	// initialize the pushbutton pin as an input:
	pinMode(button_pin_1, INPUT);     
	pinMode(button_pin_2, INPUT);
	// initialize motor pins
	pinMode(pwm_1, OUTPUT);
	pinMode(in_a, OUTPUT);
	pinMode(in_b, OUTPUT);
	pinMode(en, OUTPUT);

	pinMode(servo_1, OUTPUT);
	pinMode(servo_2, OUTPUT);	
	}

void loop(){
	//set motor enable
	if(enable_1_bool == true){
		digitalWrite(en, HIGH);	
	}
	if(enable_1_bool == false){
		digitalWrite(en, LOW);
	}	


	if(in_a_bool == true){
		digitalWrite(in_a, HIGH);
	}
	if(in_a_bool == false){
		digitalWrite(in_a, LOW);
	}


	if(in_b_bool == true){
		digitalWrite(in_b, HIGH);
	}
	if(in_b_bool == false){
		digitalWrite(in_b, LOW);
	}

	analogWrite(pwm_1, 176);
	

	// read the state of the pushbutton value:
	button_state_1 = digitalRead(button_pin_1);
	button_state_2 = digitalRead(button_pin_2);

	// check if the pushbutton is pressed.
	// if it is, the buttonState is HIGH:
	if (button_state_1 == HIGH) {     
		// turn LED on:    
		digitalWrite(led_pin, HIGH);  
		in_a_bool = false;
		in_b_bool = true;
	} 
	else {
		// turn LED off:
		digitalWrite(led_pin, LOW); 
	}

	if (button_state_2 == HIGH) {     
		// turn LED on:    
		digitalWrite(led_pin, HIGH);
		in_a_bool = true;
		in_b_bool = false;
	} 
	else {
		// turn LED off:
		digitalWrite(led_pin, LOW); 
	}
}
