// Attach NXT Light Sensor to Port BAS1
// Open the Serial terminal to view results (optional, see commented out code)
// Attach a motors to GBank A, Port M1 and M2
// Perform a calibration of the light sensor to calculate LThreshold
// Set a value for LMotorPower depending on the battery level

#include <EVShield.h>
#include <EVs_NXTLight.h>

EVShield     GEVShield(0x34,0x36); //  Create shield object
EVs_NXTLight GLightSensor;         //  Create our sensor for use in this program

void setup()
{

    Serial.begin(9600);
    //Serial.println ("-------------------------------------");
    //Serial.println ("Starting single sensor line following");
    //Serial.println ("-------------------------------------");

    GEVShield.init( SH_HardwareI2C );
    GLightSensor.init(&GEVShield, SH_BAS1);
    GLightSensor.setReflected();
    GEVShield.bank_b.motorReset();

    Serial.println ("Press GO button to continue");
    // Flash LEDs until the GO button is pressed
    while (GEVShield.getButtonState(BTN_GO) != true){
      GEVShield.bank_a.ledSetRGB(100,0,0);
      GEVShield.bank_b.ledSetRGB(100,0,0);
      delay(500);
      GEVShield.bank_a.ledSetRGB(0,0,0);
      GEVShield.bank_b.ledSetRGB(0,0,0);
      delay(500);
    }
}

void
loop()
{
    int LLightValue;
    int LThreshold = 640; // You will have to set this value after calibration
    int LMotorPowerOutside = 20; // This value will depend on the battery level. 20 for new, 60 for old
    // int LMotorPowerInside  =  1; // This value will depend on the battery level. Uncomment for sharper turns. 

    LLightValue = GLightSensor.readRaw();
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
        Serial.println (LLightValue);
      
}
