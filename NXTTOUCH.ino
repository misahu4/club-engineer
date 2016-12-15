#include <EVShield.h>
#include <EVs_NXTTouch.h>

EVShield     GEVShield(0x34,0x36); 
EVs_NXTTouch GTouch; 

void setup()
{
    Serial.begin(9600);
    GEVShield.init( SH_HardwareI2C );
    GTouch.init( &GEVShield, SH_BAS1 );
}

void
loop()
{
    if (GTouch.isPressed()){
      Serial.println("Pressed");
    }
    else
    {
      Serial.println("NOT Pressed");
    }
    delay(10);
}
