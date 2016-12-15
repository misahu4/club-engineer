//Libraries
#include <EVs_NXTLight.h>
#include <EVShield.h>

//Powers
#define CPowerForward 50
#define CPowerReverse 20

//Rotations
#define CRotation 1

//Inputs
#define CMotorL SH_Motor_1
#define CMotorR SH_Motor_2
#define CRLS GRLightSensor
#define CCLS GCLightSensor
#define CLLS GLLightSensor

//Directions
#define CDirectionForward SH_Direction_Reverse
#define CDirectionReverse SH_Direction_Forward

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
    GRLightSensor.init(&GEVShield, SH_BAS1);
    GRLightSensor.setReflected();
    GCLightSensor.init(&GEVShield, SH_BBS2);
    GCLightSensor.setReflected();
    GLLightSensor.init(&GEVShield, SH_BBS1);
    GLLightSensor.setReflected();


    Serial.println ("Press GO button to continue");
    while (GEVShield.getButtonState(BTN_GO) != true)
    {
      delay(50);
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

void RightSensorLineFollow()
{
    int LLightValue;
    int LThreshold = 650; // You will have to set this value after calibration
    // int LMotorPowerInside  =  1; // This value will depend on the battery level. Uncomment for sharper turns. 

    LLightValue = CRLS.readRaw();


      if (LLightValue < LThreshold){
        RunMotor(CMotorL, CDirectionForward, CPowerForward);
        RunMotor(CMotorR, CDirectionReverse, CPowerReverse);
        // GEVShield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, LMotorPowerInside); // Comment the line above, and uncomment this line for sharper turns
    } else {
       RunMotor(CMotorL, CDirectionReverse, CPowerReverse);
       RunMotor(CMotorR, CDirectionForward, CPowerForward);
    }
        Serial.println (LLightValue);
      
}


void LeftSensorLineFollow()
{
    int LLightValue;
    int LThreshold = 650; // You will have to set this value after calibration
    // int LMotorPowerInside  =  1; // This value will depend on the battery level. Uncomment for sharper turns. 

    LLightValue = CLLS.readRaw();


      if (LLightValue < LThreshold){
        RunMotor(CMotorR, CDirectionForward, CPowerForward);
        RunMotor(CMotorL, CDirectionReverse, CPowerReverse);
        // GEVShield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, LMotorPowerInside); // Comment the line above, and uncomment this line for sharper turns
    } else {
       RunMotor(CMotorR, CDirectionReverse, CPowerReverse);
       RunMotor(CMotorL, CDirectionForward, CPowerForward);
    }
        Serial.println (LLightValue);
      
}

void TwoSensorLineFollow()
{
    int LLightValueLeft;
    int LLightValueRight;
    int LThreshold = 650; // You will have to set this value after calibration
    // int LMotorPowerInside  =  1; // This value will depend on the battery level. Uncomment for sharper turns. 

    LLightValueLeft = CLLS.readRaw();
    LLightValueRight = CRLS.readRaw();

    if (LLightValueLeft < LThreshold & LLightValueRight < LThreshold)
    {
      RunMotor(CMotorR, CDirectionForward, CPowerForward);
      RunMotor(CMotorL, CDirectionForward, CPowerForward);
    }
    else if (LLightValueLeft > LThreshold & LLightValueRight < LThreshold)
    {
      RunMotor(CMotorL, CDirectionForward, CPowerForward);
      RunMotor(CMotorR, CDirectionReverse, CPowerReverse);
    }
    else if (LLightValueLeft < LThreshold & LLightValueRight > LThreshold)
    {
      RunMotor(CMotorR, CDirectionForward, CPowerForward);
      RunMotor(CMotorL, CDirectionReverse, CPowerReverse);
    }
    else
    {
     OffMotor(CMotorL);
     OffMotor(CMotorR);
    }

}
void loop()
{
 TwoSensorLineFollow();
}

