#include <EVShield.h>

// Attach a NXT motor to M1 on BankA 
// Open the Serial terminal to view.

EVShield          GEVShield(0x34,0x36);

void
setup()
{
    Serial.begin(9600);
    GEVShield.init( SH_HardwareI2C );
}

void
loop()                          
{
    long  LRotation = 2;  
    long  LSpeed    = 50; // Between 0..100

    Serial.println ("Press GO button to run motor");
    GEVShield.waitForButtonPress(BTN_GO);
    GEVShield.bank_b.motorReset();

    delay(1000);
    Serial.print("Bank A, Motor 1 Forward "); Serial.print(LRotation); Serial.println(" rotations");
    GEVShield.bank_b.motorRunRotations(
        SH_Motor_1, 
        SH_Direction_Forward, 
        LSpeed,
        LRotation, 
        SH_Completion_Wait_For,
        SH_Next_Action_BrakeHold);
    delay(1000);
    Serial.print("Bank A, Motor 1 Reverse "); Serial.print(LRotation); Serial.println(" rotations");
    GEVShield.bank_b.motorRunRotations(
        SH_Motor_1, 
        SH_Direction_Reverse, 
        LSpeed,
        LRotation, 
        SH_Completion_Wait_For,
        SH_Next_Action_BrakeHold);
    Serial.println("Program Finished");
    Serial.println("");
}

