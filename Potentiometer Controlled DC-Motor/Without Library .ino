/* 	
	Jash_Jarvis laptop
	Created on : 30/09/2020, 16:25 hrs 
*/

/*
	Control logic for DC motors using L293D, pots and button switch based emergency Stop interrupts.
*/

// Connections for motor 1
// All of these are output pins.
// inp1 and inp2 require Digital output and ENB12 requires analog output.
int ENB12 = 11;
int inp1 = 10;
int inp2 = 9;

// Connections for motor 2
// All of these are output pins.
// inp3 and inp4 require Digital output and ENB34 requires analog output.
int ENB34 = 6;
int inp3 = 5;
int inp4 = 3;

// For the PULL_UP button Switches 
// All of these are input pins.
// Pull-up Voltage is 9V.
int S1 = 7; 
int S2 = 2;

// For pots
// All are analog output pins.
// The max output is 9V and min is 0V with 10K ohm resistance.
int pot1 = A0;
int pot2 = A1;

// Function Declaration.
void setMotor1(int, boolean);
void setMotor2(int, boolean);

// Setup Function
void setup()
{ 
	Serial.begin(9600); 			// Serial Baud Rate

	pinMode(inp1, OUTPUT);
	pinMode(inp2, OUTPUT);
	pinMode(ENB12, OUTPUT);
	pinMode(S1, INPUT_PULLUP);

	pinMode(inp3, OUTPUT);
	pinMode(inp4, OUTPUT);
	pinMode(ENB34, OUTPUT);
	pinMode(S2, INPUT_PULLUP);
}

// Main Loop Function.
void loop()
{
	// Potentiometer Inputs for speed regulation.
	int potvalue1 = analogRead(pot1);
  	int potvalue2 = analogRead(pot2);
  	
  	// Mapping them to corresponding Enable output pins.
  	// 142.51 is taken by mapping the motor's rpm with full scale reading (255 -> 5368).
  	int enb_out1 = map(potvalue1,0,1023,-142.51,142.51);
  	int enb_out2 = map(potvalue2,0,1023,-142.51,142.51);
	
  	// PushButton Inputs for direction control.
  	boolean reverse1 = digitalRead(S1); 	
  	boolean reverse2 = digitalRead(S2);
  
  	// If the button is pressed, the motors will stop working.
	if(reverse1 == 0)
		enb_out1 = 0;
	if(reverse2 == 0)
		enb_out2 = 0;

	// Calliing the functions.
 	setMotor1(enb_out1);
  	setMotor2(enb_out2);

 	// Mapping the control signal to actual Motor RPM ( Motor's full scale rpm is 5368, as per observation ).
 	int motorspeed1 = map(enb_out1,-142.51,142.51,3000,-3000);
  	int motorspeed2 = map(enb_out2,-142.51,142.51,3000,-3000);
	
  	
  	// Printing the motor speed to Serial monitor.  
  	Serial.print("Speed of Motor 1 : ");
  	Serial.print(motorspeed1);
  	Serial.print(", Speed of Motor 2 : ");
  	Serial.println(motorspeed2);   			// println() to move the cursor to new line after printing.
  	delay(10);

}

// Control Function for setting the Motor1's speed and direction.
void setMotor1(int speed_inp)
{ 
	analogWrite(ENB12, abs(speed_inp));
	if(speed_inp < 0)
    {
    	digitalWrite(inp1, LOW);
		digitalWrite(inp2, HIGH);
    }
  	else
    {
    	digitalWrite(inp1, HIGH);
		digitalWrite(inp2, LOW);
    }
}

// Control Function for setting the Motor2's speed and direction.
void setMotor2(int speed_inp)
{ 
	analogWrite(ENB34, abs(speed_inp));
	if(speed_inp<0)
    {
    	digitalWrite(inp3, LOW);
		digitalWrite(inp4, HIGH);
    }
  	else
    {
    	digitalWrite(inp3, HIGH);
		digitalWrite(inp4, LOW);
    }
}
