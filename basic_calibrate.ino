
#include <EVs_NXTLight.h>
#include <EVShield.h>
EVShield          GEVShield(0x34,0x36);
EVs_NXTLight GRLightSensor;
EVs_NXTLight GLLightSensor;
EVs_NXTLight GCLightSensor;
#define CRLS GRLightSensor
#define CCLS GCLightSensor
#define CLLS GLLightSensor

void setup() {
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




void loop() {
   int LLightTH;
   int LWhiteValue;
   int LBlackValue;
/*  Serial.println (" place sensors over white");
while (GEVShield.getButtonState(BTN_GO) != true){
     
       LWhiteValue = GRLightSensor.readRaw() +  GRLightSensor.readRaw() /2 ;
    }
  delay(500);
    
    Serial.println (" place sensors over black");
 while (GEVShield.getButtonState(BTN_GO) != true){
   
       LBlackValue = GRLightSensor.readRaw() +  GRLightSensor.readRaw() /2 ;
    }

    LLightTH = LBlackValue + LWhiteValue / 2;
    delay(1000);
    Serial.println ( LLightTH); */

    Serial.println ( GRLightSensor.readRaw());
    

}
