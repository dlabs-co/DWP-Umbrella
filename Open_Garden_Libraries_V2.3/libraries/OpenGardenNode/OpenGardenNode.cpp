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

#include "OpenGardenNode.h" 
#include "DHT22.h" 
#include "RF12.h" 
#include "Ports.h" 


DHT22 myDHT22(DHT22_PIN); // Setup the DHT
ISR(WDT_vect) {  Sleepy::watchdogEvent(); }

OpenGardenNodeClass::OpenGardenNodeClass() 
{
	 	
}

//Sensor initializing functions:
void OpenGardenNodeClass::initSensors(void){
   pinMode(sensorPowerPin, OUTPUT);
}

void OpenGardenNodeClass::sensorPowerON(void){
   digitalWrite(sensorPowerPin, HIGH);
   bitClear(PRR, PRADC); ADCSRA |= bit(ADEN);
}
 
void OpenGardenNodeClass::sensorPowerOFF(void){
   digitalWrite(sensorPowerPin, LOW);
   ADCSRA &= ~ bit(ADEN); bitSet(PRR, PRADC);
   
}


//Sensors function:
void OpenGardenNodeClass::readSensors(void){
	
  DHT22_ERROR_t errorCode;
  Sleepy::loseSomeTime(2000); // Sensor requires minimum 2s warm-up after power-on.
  errorCode = myDHT22.readData(); // read data from sensor
  if (errorCode == DHT_ERROR_NONE) { // data is good
    
    airPacket.temperature = (myDHT22.getTemperatureC()); // Get temperature reading and convert to integer, reversed at receiving end
    airPacket.humidity = (myDHT22.getHumidity()); // Get humidity reading and convert to integer, reversed at receiving end
   }
   
    airPacket.moisture = (analogRead(soilMoisturePin));

    float luminosity = analogRead(luminosityPin);
    airPacket.light = ((luminosity/1023)*100);

    digitalWrite(sensorPowerPin, LOW);  // Disable sensor power to read Vcc
    delay(500);
    airPacket.supplyV = readVcc();   
    digitalWrite(sensorPowerPin, HIGH);
}


//Transceiver functions:
void OpenGardenNodeClass::initRF(uint8_t _myNode){ 
	myNodeID = _myNode;
    rf12_initialize(myNodeID,RF12_433MHZ,100); // (NodeID,freq,network)
}

void OpenGardenNodeClass::sendPackage(void){
   for (byte i = 0; i <= RETRY_LIMIT; ++i) {  // tx and wait for ack up to RETRY_LIMIT times
     rf12_sleep(-1);              // Wake up RF module
      while (!rf12_canSend())
      rf12_recvDone();
      rf12_sendStart(RF12_HDR_ACK, &airPacket, sizeof airPacket); 
      rf12_sendWait(RF12_NORMAL_SENDWAIT);   // Wait for RF to finish sending while in standby mode
	  acked = waitForAck();
      rf12_sleep(0);              // Put RF module to sleep
      if (acked) { return; }      // Return if ACK received
  
   Sleepy::loseSomeTime(RETRY_PERIOD * 1000);     // If no ack received wait and try again
}
}


//Node function:
void OpenGardenNodeClass::nodeWait(uint16_t seconds){
	
	 Sleepy::loseSomeTime(seconds*1000);
}


//Private node functions:
long OpenGardenNodeClass::readVcc(void){
   long result;
   // Read 1.1V reference against Vcc
   #if defined(__AVR_ATtiny84__) 
    ADMUX = _BV(MUX5) | _BV(MUX0); // For ATtiny84
   #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);  // For ATmega328
   #endif 
   delay(2); // Wait for Vref to settle
   ADCSRA |= _BV(ADSC); // Convert
   while (bit_is_set(ADCSRA,ADSC));
   result = ADCL;
   result |= ADCH<<8;
   result = 1126400L / result; // Back-calculate Vcc in mV
   return result;
}

byte OpenGardenNodeClass::waitForAck() {   MilliTimer ackTimer;
   while (!ackTimer.poll(ACK_TIME)) {
     if (rf12_recvDone() && rf12_crc == 0 &&
        rf12_hdr == (RF12_HDR_DST | RF12_HDR_CTL | myNodeID))
        return 1;
     }
   return 0;
 }
   

OpenGardenNodeClass OpenGardenNode;
