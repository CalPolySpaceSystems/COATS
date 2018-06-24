// cosmos.cpp

#include "cosmos.h"


cosmos::cosmos(uint16_t ending, bool counterEnable)
{
	endString = ending;
	timerEnable = counterEnable;
}

/*
 *	UART Interface
 */

void cosmos::serialInit(HardwareSerial& serialInst, long baud)
{
	
	SerialCOSMOS = &serialInst;
	SerialCOSMOS->begin(baud);
	
}

void cosmos::serialWriteTlm(uint8_t id){

	if (timerEnable) {
		uint16_t rtc = (uint16_t)(millis());
		SerialCOSMOS->write(id);
		SerialCOSMOS->write(rtc);
		SerialCOSMOS->write(rtc >> 8);
		SerialCOSMOS->write((byte *)packetPointers[id], packetSizes[id]);
		SerialCOSMOS->write(endString >> 8);
		SerialCOSMOS->write(endString); 
	}
	
	else{
		SerialCOSMOS->write(id);
		SerialCOSMOS->write((byte *)packetPointers[id], packetSizes[id]);
		SerialCOSMOS->write(endString >> 8);
		SerialCOSMOS->write(endString); 
	}
	
}

/*
 *	SPI Interface
 */
 
/*
 *	I2C Interface
 */
		 
/*
 *	Other Functions
 */ 

void cosmos::addTlm(uint8_t id, uint32_t * data, size_t dataSize){
	
	packetSizes[id] = dataSize;
	packetPointers[id] = data;

}
		 
void cosmos::buildTlm(uint8_t id, String packet)
{
	size_t dataSize = packetSizes[id];
	
	if (timerEnable) {
		uint16_t rtc = (uint16_t)(millis());
		packet[0] = id;
		packet[1] = rtc;
		packet[2] = (rtc >> 8);
		for (int i=0;i<dataSize;i++)
		{
			packet[i+3] = *(packetPointers[id] + 8*i);
		}

		packet[dataSize+3] = (endString >> 8);
		packet[dataSize+4] = (endString);
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
