#include <Braccio.h>
#include <Servo.h>

#include "./header/GeneratedCode.h"

#include <InverseK.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

// Quick conversion from the Braccio angle system to radians
float b2a(float b){
  return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a) {
  return (a + HALF_PI) * 180 / PI;
}


void moveToXYZ(int xIn, int yIn, int zIn,int aIn=90, int bIn=73){

	float a0, a1, a2, a3; //These variables are passed to the solver as pointers and their values are modified by the solver

	if(InverseK.solve(xIn, yIn, zIn, a0, a1, a2, a3)) {
		Serial.print(a2b(a0)); Serial.print(',');
		Serial.print(a2b(a1)); Serial.print(',');
		Serial.print(a2b(a2)); Serial.print(',');
		Serial.println(a2b(a3));
	} else {
		Serial.println("No solution found!");
	}
	
        Braccio.ServoMovement(30,a2b(a0),a2b(a1),a2b(a2),a2b(a3),aIn,bIn);
}


void pickThingUp(){
        //x distance from center
        //y is the height
        //z is the rotation axis and is an angle

        moveToXYZ(GOTOXB,GOTOYB,50,80,10);
        delay(1000);
        moveToXYZ(GOTOXB,GOTOYB,-120,80,10);
        delay(1000);
        moveToXYZ(GOTOXB,GOTOYB,-120,80,85);
        delay(1000);
        moveToXYZ(GOTOXB,GOTOYB,0,80,85);
        delay(1000);
        moveToXYZ(GOTOXL,GOTOYL,100,90,85);
        delay(1000);
        moveToXYZ(GOTOXL,GOTOYL,-30,90,85);
        delay(1000);
        moveToXYZ(GOTOXL,GOTOYL,-30,90,10);
        delay(1000);      
	return;
}


void setup() {  

  Braccio.begin();

  Link base, upperarm, forearm, hand;

  base.init(0, b2a(0.0), b2a(180.0));
  upperarm.init(200, b2a(15.0), b2a(165.0));
  forearm.init(200, b2a(0.0), b2a(180.0));
  hand.init(270, b2a(0.0), b2a(180.0));

  // Attach the links to the inverse kinematic model
  InverseK.attach(base, upperarm, forearm, hand);

  pickThingUp();
  delay(3000);
}


void loop() {
  Braccio.begin();
  while (1)
  {
    /* Infinite loop */
  }
  
}