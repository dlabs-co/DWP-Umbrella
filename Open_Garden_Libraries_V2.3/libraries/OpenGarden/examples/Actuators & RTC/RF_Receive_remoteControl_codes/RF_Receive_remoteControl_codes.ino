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

#include <OpenGarden.h>
#include "Wire.h" 


void setup() {
  Serial.begin(9600);
  RemoteReceiver::init(1, 3, readCodes);
}


void loop() {
}


void readCodes(unsigned long receivedCode, unsigned int period) { 
  RemoteReceiver::disable();
  interrupts();
  unsigned long code=receivedCode;
  code = code & 0xFFFFF;
  code |= (unsigned long)period << 23;  
  code |= 3L << 20; 
  Serial.println(code);
  RemoteReceiver::enable();
}

