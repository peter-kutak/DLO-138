//voci staremu neoficialnemu Core
//http://dan.drown.org/stm32duino/package_STM32duino_index.json
//Arduino 2.3.4
//STM32duino(drown.org) 2022.9.26
//Adafruit_GFX 1.11.11

//Programovat cez SWD je mozne iba so zopnutymi JP1 a JP2
//problem je asi, ze sa prepnu aby mohli fungovat ako digitalny vstup
//lebo original firmware isel preprogramovat aj bez prepinacov

#include <EEPROM.h>

#include <Adafruit_GFX.h> 
// needs to be Adafruit GFX Library v1.1.4, check/change your installed version
// otherwise you will get a black screen or compiler errors

//#include "Adafruit_TFTLCD.h"
//ma niaku vlastnu kopiu
#include "src/TFTLib/Adafruit_TFTLCD_8bit_STM32.h"
#include "global.h"
#include "variables.h"


#define FIRMWARE_VERSION	"1.0p"

// ------------------------
void setup()	{
// ------------------------
  //necham zapnute iba SWD,display funguje a programovanie cez SWD tiez
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
  //SWD moze? kecat do Digitalnych vstupov ale ja ich nepouzivam
  //afio_cfg_debug_ports(AFIO_DEBUG_NONE);
	// see http://www.stm32duino.com/viewtopic.php?t=1130#p13919 for more info
	
	
	DBG_INIT(SERIAL_BAUD_RATE);
	DBG_PRINT("Dual channel O Scope with two logic channels, ver: ");
	DBG_PRINTLN(FIRMWARE_VERSION);

	// set digital and analog stuff
	initIO();
	
	// load scope config or factory reset to defaults
	loadConfig(digitalRead(BTN4) == LOW);
	
	// init the IL9341 display
	initDisplay();
}



// ------------------------
void loop()	{
// ------------------------
	controlLoop();
}


