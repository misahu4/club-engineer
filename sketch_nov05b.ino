#include <EVShield.h>
#include <EVs_NXTLight.h>

EVShield     GEVShield(0x34,0x36); //  Create shield object
EVs_NXTLight GLightSensor; //  Create our sensor for use in this program

void setup()
{

    Serial.begin(9600);
    Serial.println ("--------------------------------------");
    Serial.println ("Starting NXT Light Sensor Test Program");
    Serial.println ("--------------------------------------");

    GEVShield.init( SH_HardwareI2C );
    GLightSensor.init(&GEVShield, SH_BAS2);
    GLightSensor.setReflected();

    Serial.println ("Press GO button to continue");
    GEVShield.waitForButtonPress(BTN_GO);

}

void
loop()
{
    int LLightValue;

    LLightValue = GLightSensor.readRaw();
    Serial.print("Reflected Light: "); Serial.print(LLightValue); Serial.println(" (High = dark, Low = light)");
    delay(200);
}

