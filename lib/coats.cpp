// coats.cpp

#include "coats.h"

coats::coats(uint16_t ending, bool counterEnable)
{
	endString = ending;
	timerEnable = counterEnable;
}

/*
 *	UART Interface
 */

void coats::serialInit(HardwareSerial& serialInst, long baud)
{
	SerialCOATS._hw = (HardwareSerial*)&serialInst;
	SerialCOATS._hw->begin(baud);
	
}

void coats::serialInit(Serial_& serialInst, long baud)
{
  SerialCOATS._sw = (Serial_*)&serialInst;
  SerialCOATS._sw->begin(baud);
  
}

void coats::serialWriteTlm(HardwareSerial& serialInst, uint8_t id){

  if (timerEnable) {
    uint16_t rtc = (uint32_t)(millis());
    SerialCOATS._hw->write(id);
    SerialCOATS._hw->write(rtc);
    SerialCOATS._hw->write(rtc >> 8);
    SerialCOATS._hw->write(rtc >> 16);
    SerialCOATS._hw->write(rtc >> 24);
    SerialCOATS._hw->write((byte *)packetPointers[id], packetSizes[id]);
    SerialCOATS._hw->write(endString >> 8);
    SerialCOATS._hw->write(endString); 
  }
  
  else{
    SerialCOATS._hw->write(id);
    SerialCOATS._hw->write((byte *)packetPointers[id], packetSizes[id]);
    SerialCOATS._hw->write(endString >> 8);
    SerialCOATS._hw->write(endString); 
  }
  
}


void coats::serialWriteTlm(Serial_& serialInst, uint8_t id){

	if (timerEnable) {
		uint16_t rtc = (uint32_t)(millis());
		SerialCOATS._sw->write(id);
		SerialCOATS._sw->write(rtc);
		SerialCOATS._sw->write(rtc >> 8);
    SerialCOATS._sw->write(rtc >> 16);
    SerialCOATS._sw->write(rtc >> 24);
		SerialCOATS._sw->write((byte *)packetPointers[id], packetSizes[id]);
		SerialCOATS._sw->write(endString >> 8);
		SerialCOATS._sw->write(endString); 
	}
	
	else{
		SerialCOATS._sw->write(id);
		SerialCOATS._sw->write((byte *)packetPointers[id], packetSizes[id]);
		SerialCOATS._sw->write(endString >> 8);
		SerialCOATS._sw->write(endString); 
	}
	
}

/* Adds a data structure */ 
void coats::addTlm(uint8_t id, uint32_t * data){
	
	packetSizes[id] = sizeof(*data);
  SerialUSB.println(packetSizes[id]);
	packetPointers[id] = data;

}

/* Outputs a packet as a string */
void coats::buildTlm(uint8_t id, String packet){
	size_t dataSize = packetSizes[id];
	
	if (timerEnable) {
		uint16_t rtc = (uint16_t)(millis());
		packet[0] = id;
		packet[1] = rtc;
		packet[2] = (rtc >> 8);
    packet[3] = (rtc >> 16);
    packet[4] = (rtc >> 24);
		for (int i=0;i<dataSize;i++)
		{
			packet[i+5] = *(packetPointers[id] + 8*i);
		}

		packet[dataSize+5] = (endString >> 8);
		packet[dataSize+6] = (endString);
	}
	
	else{
		packet[0] = id;
		for (int i=0;i<dataSize;i++)
		{
			packet[i+1] = *(packetPointers[id] + 8*i);
		}

		packet[dataSize+1] = (endString >> 8);
		packet[dataSize+2] = (endString); 
	}

}

/* Generate checksum */
uint8_t coats::xor_checksum(){
}
