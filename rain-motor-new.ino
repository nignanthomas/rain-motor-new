//Small Stepper Motor and Driver


/*-----( Import needed libraries )-----*/
#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
#define STEPS  100   //Number of steps per revolution


/*-----( Declare objects )-----*/
/* create an instance of the stepper class, specifying
 the number of steps of the motor and the pins it's
 attached to. The pin connections need to be 4 pins connected
 to Motor Driver In1, In2, In3, In4  and then the pins entered
 here in the sequence 1-3-2-4 for proper sequencing*/

Stepper small_stepper(STEPS, 8, 10, 9, 11);

int  Steps2Take = 0;
int relayPin1 = 12;

//rain sensor settings
int nRainIn = A1;
int nRainDigitalIn = 2;
int nRainVal;
boolean bIsRaining = false;
String strRaining;
int count = 1;
boolean deployed = false;
//


void setup(){  
 Serial.begin(9600);
 pinMode(relayPin1, OUTPUT); 

 pinMode(2,INPUT); //setting digitalRead pin
}
void loop()   
{

  //reading rain sensor
  nRainVal = analogRead(nRainIn);
  bIsRaining = !(digitalRead(nRainDigitalIn));
  //

  Serial.println(count);
  count++;

  if(nRainVal<800){
    strRaining = "YES";
  }
  else{
    strRaining = "NO";
  }

  if(nRainVal<800 && deployed==false){
    deployed = true;
    strRaining = "YES";
    small_stepper.setSpeed(320);
    digitalWrite (relayPin1, LOW);
    Steps2Take  = -4096; // Rotate CW steps = 2048
    Serial.println("CW");
    small_stepper.step(Steps2Take);
    digitalWrite (relayPin1, HIGH);
  }
  else if (nRainVal>=800 && deployed==true){
    deployed=false;
    strRaining = "NO";
    small_stepper.setSpeed(320);
    digitalWrite (relayPin1, LOW);
    Steps2Take = 4096; // Rotate CCW steps =2048
    Serial.println("CCW");
    small_stepper.step(Steps2Take);
    digitalWrite (relayPin1, HIGH);
  }
  
  Serial.print("Raining?: ");
  Serial.print(strRaining);
//  Serial.print(bIsRaining);
  Serial.print("\t Moisture Level: ");
  Serial.println(nRainVal);
  Serial.print("Deployed:  ");
  Serial.println(deployed);
  Serial.println("==========================");
  delay(2000);
} /* --(end main loop )-- */
