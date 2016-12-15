//Libraries
#include <EVs_NXTLight.h>
#include <EVShield.h>

//Powers
#define CSpeed 50

//Rotations
#define CRotation 1

//Inputs
#define CMotorL SH_Motor_1
#define CMotorR SH_Motor_2
#define CRLS GRLightSensor
#define CCLS GCLightSensor
#define CLLS GLLightSensor

//Directions
#define CForwards SH_Direction_Reverse
#define CBackwards SH_Direction_Forward

//Objects
EVShield          GEVShield(0x34,0x36);
EVs_NXTLight GRLightSensor;
EVs_NXTLight GLLightSensor;
EVs_NXTLight GCLightSensor;

void setup()
{
    Serial.begin(9600);
    
    //initialisations
    GEVShield.init( SH_HardwareI2C );
    GEVShield.bank_b.motorReset();
    GRLightSensor.init(&GEVShield, SH_BAS2);
    GRLightSensor.setReflected();
    GCLightSensor.init(&GEVShield, SH_BBS2);
    GCLightSensor.setReflected();
    GLLightSensor.init(&GEVShield, SH_BBS1);
    GLLightSensor.setReflected();
}

void SingleSensorLineFollow(int APort1, int APort2, int AForwardBack, int ASpeed,  EVs_NXTLight CRLS)
{
    int LLightValue;
    int LThreshold = 960; // NOTE, CALIBRATE THIS LATER

    LLightValue = CRLS.readRaw();
    if (LLightValue < LThreshold){
        GEVShield.bank_b.motorRunUnlimited(APort1,AForwardBack,ASpeed); 
        GEVShield.bank_b.motorStop(APort2,SH_Next_Action_Brake);
    } 
    else {
        GEVShield.bank_b.motorRunUnlimited(APort2,AForwardBack,ASpeed);
        GEVShield.bank_b.motorStop(APort1, SH_Next_Action_Brake);
        
    } 
    delay(50);   
}

void SingleSensorLineFollowTest()
{

    int LLightValue;
    int LThreshold = 497; // You will have to set this value after calibration
    int LMotorPowerOutside = 20; // This value will depend on the battery level. 20 for new, 60 for old
    // int LMotorPowerInside  =  1; // This value will depend on the battery level. Uncomment for sharper turns. 

    LLightValue = GRLightSensor.readRaw();
    //Serial.println(LLightValue);
    if (LLightValue < LThreshold){
        GEVShield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, LMotorPowerOutside);
        GEVShield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
        // GEVShield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, LMotorPowerInside); // Comment the line above, and uncomment this line for sharper turns
    } else {
        GEVShield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse, LMotorPowerOutside);
        GEVShield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
        // GEVShield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, LMotorPowerInside);  // Comment the line above, and uncomment this line for sharper turns
    }

  
}
void OffMotor (int Port)
{
GEVShield.bank_b.motorStop(Port, SH_Next_Action_Brake);
}

void RunMotor(int Port, int ForwardBack , int Speed) {
    GEVShield.bank_b.motorRunUnlimited(
        Port, 
        ForwardBack, 
        Speed);

}

void RunMotorRotation(int Port, int ForwardBack , int Speed, int Rotation) {
    GEVShield.bank_b.motorRunRotations(
        Port, 
        ForwardBack, 
        Speed,
        Rotation, 
        SH_Completion_Wait_For,
        SH_Next_Action_BrakeHold);
}

void RunTwoMotors(int MotorPort1, int MotorPort2, int ForwardBack , int Speed) {
RunMotor(MotorPort1, 
        ForwardBack, 
        Speed);
delay(1);
RunMotor(MotorPort2, 
        ForwardBack, 
        Speed);
}


void loop()
{
//RunTwoMotors(CMotorL, CMotorR, CForwards, CSpeed);
SingleSensorLineFollow(CMotorL, CMotorR, CForwards, CSpeed,GRLightSensor );
}


