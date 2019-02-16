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
	
	SerialCOATS = &serialInst;
	SerialCOATS->begin(baud);
	
}

void coats::serialWriteTlm(uint8_t id){

	if (timerEnable) {
		uint16_t rtc = (uint32_t)(millis());
		SerialCOATS->write(id);
		SerialCOATS->write(rtc);
		SerialCOATS->write(rtc >> 8);
    	SerialCOATS->write(rtc >> 16);
    	SerialCOATS->write(rtc >> 24);
		SerialCOATS->write((byte *)packetPointers[id], packetSizes[id]);
		SerialCOATS->write(endString >> 8);
		SerialCOATS->write(endString); 
	}
	
	else{
		SerialCOATS->write(id);
		SerialCOATS->write((byte *)packetPointers[id], packetSizes[id]);
		SerialCOATS->write(endString >> 8);
		SerialCOATS->write(endString); 
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

void coats::addTlm(uint8_t id, uint32_t * data, size_t dataSize){
	
	packetSizes[id] = dataSize;
	packetPointers[id] = data;

}
		 
void coats::buildTlm(uint8_t id, String packet)
{
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
