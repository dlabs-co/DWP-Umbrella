/*  
 *  OpenGarden sensor platform for Arduino from Cooking-hacks.
 *  
 *  Copyright (C) Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version. 
 *  
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see http://www.gnu.org/licenses/. 
 *  
 *  Version:           2.2
 *  Design:            David Gascón 
 *  Implementation:    Victor Boria, Luis Martin & Jorge Casanova
 */

// Ensure this library description is only included once
#ifndef OpenGardenNode_included
#define	OpenGardenNode_included

#include <Arduino.h>
#include "DHT22.h" 
#include "RF12.h"
#include "Ports.h" 


#define DHT22_PIN 10 
#define luminosityPin 7
#define sensorPowerPin 0
#define soilMoisturePin A2
#define RETRY_PERIOD 2    // How soon to retry (in seconds) if ACK didn't come in
#define RETRY_LIMIT 5     // Maximum number of times to retry
#define ACK_TIME 100      // Number of milliseconds to wait for an ack
#define USE_ACK    
#define RF12_NORMAL_SENDWAIT 2


typedef struct MyStruct {
		float humidity;	
		float temperature;	
		int moisture;        
		int light;
		int supplyV;	      
} Payload;

typedef MyStruct Payload; 

// Library interface description
class OpenGardenNodeClass  {

  public:
  
    //***************************************************************
	// Constructor of the class										*
	//***************************************************************
  
		//! Class constructor.
    OpenGardenNodeClass();
    
	//***************************************************************
	// Public Methods												*
	//***************************************************************
	
	//Sensor initializing functions:
	void initSensors(void);  //Initializing necessary for all the sensors
	void sensorPowerON(void); //Turns on the sensor power supply
	void sensorPowerOFF(void); //Turns off the sensor power supply
	
	//Sensor function:
	void readSensors(void); //Get data from all the sensors and store it in a internal buffer
	
	//Transceiver functions:
	void initRF(uint8_t _myNode);
	void sendPackage(); 
 
	//Node function:
	void nodeWait(uint16_t seconds);
	
	
	private:
	
	uint8_t myNodeID;
	long readVcc();	
	byte waitForAck();
	byte acked;
	Payload airPacket;

}; 

extern OpenGardenNodeClass OpenGardenNode;

#endif
