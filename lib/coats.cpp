// coats.cpp

#include "coats.h"

coats::coats(uint16_t ending, bool statusEnable)
{
	endString = ending;

  // Enable status Tlm
  
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

/* Send a telemetry packet */
void coats::serialWriteTlm(HardwareSerial& serialInst, uint8_t id){
  
  SerialCOATS._hw->write(id);
  SerialCOATS._hw->write((byte *)packetPointers[id], packetSizes[id]);
  SerialCOATS._hw->write(endString >> 8);
  SerialCOATS._hw->write(endString); 
  
}

void coats::serialWriteTlm(Serial_& serialInst, uint8_t id){
  
	SerialCOATS._sw->write(id);
	SerialCOATS._sw->write((byte *)packetPointers[id], packetSizes[id]);
	SerialCOATS._sw->write(endString >> 8);
  SerialCOATS._sw->write(endString); 

}

void coats::serialWriteTlm(HardwareSerial& serialInst, uint8_t id, uint32_t timeStamp){

  SerialCOATS._hw->write(id);
  SerialCOATS._hw->write(timeStamp);
  SerialCOATS._hw->write(timeStamp >> 8);
  SerialCOATS._hw->write(timeStamp >> 16);
  SerialCOATS._hw->write(timeStamp >> 24);
  SerialCOATS._hw->write((byte *)packetPointers[id], packetSizes[id]);
  SerialCOATS._hw->write(endString >> 8);
  SerialCOATS._hw->write(endString); 

}

void coats::serialWriteTlm(Serial_& serialInst, uint8_t id, uint32_t timeStamp){

  SerialCOATS._sw->write(id);
  SerialCOATS._sw->write(timeStamp);
  SerialCOATS._sw->write(timeStamp >> 8);
  SerialCOATS._sw->write(timeStamp >> 16);
  SerialCOATS._sw->write(timeStamp >> 24);
  SerialCOATS._sw->write((byte *)packetPointers[id], packetSizes[id]);
  SerialCOATS._sw->write(endString >> 8);
  SerialCOATS._sw->write(endString); 

}


/* Send a Status Packet */
void coats::serialWriteStat(HardwareSerial& serialInst, uint8_t statMsg){

  SerialCOATS._hw->write(STATUS_ID);
  SerialCOATS._hw->write(statMsg);
  SerialCOATS._hw->write(endString >> 8);
  SerialCOATS._hw->write(endString); 

}

void coats::serialWriteStat(Serial_& serialInst, uint8_t statMsg){

  SerialCOATS._sw->write(STATUS_ID);
  SerialCOATS._sw->write(statMsg);
  SerialCOATS._sw->write(endString >> 8);
  SerialCOATS._sw->write(endString); 

}

/* Reads a command from the serial port given
 * 
 * FORMAT: 
 * | Start | CMD | CMD Value | Checksum | 
 */

void coats::serialParseCmd(HardwareSerial& serialInst){

  // Check for input
  if (SerialCOATS._hw->available()){
    
    uint8_t input[4];

    // Read from buffer
    SerialCOATS._hw->readBytes(input,5);

    
    // Read command checksum (XOR)
    uint8_t cs_calc = input[1]^input[2];

    if(input[3]==cs_calc){

      // Send parameter to callback function
      cmdCallbackPtr[input[1]](input[2]);
        
    }

    else{

      // Inform of packet garbled
        
    }
      
  }
  
}
  
void coats::serialParseCmd(Serial_& serialInst){

  // Check for input
  if (SerialCOATS._sw->available()){
    
    char input[4];

    // Read from buffer
    SerialCOATS._sw->readBytes(input,4);

    
    // Read command checksum (XOR)
    uint8_t cs_calc = input[1]^input[2];

    if(input[3]==cs_calc){

      // Send parameter to callback function
      cmdCallbackPtr[input[1]](input[2]);
        
    }

    else{

      // Inform of packet garbled
        
    }
      
  }

}
  

/* Adds a new telemetry packet */ 
void coats::addTlm(uint8_t id, uint32_t * data){
	
	packetSizes[id] = sizeof(*data);
  //SerialUSB.println(packetSizes[id]);
	packetPointers[id] = data;

}

/* Adds a command */
void coats::addCmd(uint8_t id, cmdCallback callback){
  cmdCallbackPtr[id] = callback;
}


/* Outputs a packet as a string */
void coats::buildTlm(uint8_t id, String packet){
	size_t dataSize = packetSizes[id];

	packet[0] = id;
	for (int i=0;i<dataSize;i++)
	{
		packet[i+1] = *(packetPointers[id] + 8*i);
	}
	packet[dataSize+1] = (endString >> 8);
	packet[dataSize+2] = (endString); 

}

void coats::buildTlm(uint8_t id, String packet, uint32_t timeStamp){
  size_t dataSize = packetSizes[id];
  
  packet[0] = id;
  packet[1] = timeStamp;
  packet[2] = (timeStamp >> 8);
  packet[3] = (timeStamp >> 16);
  packet[4] = (timeStamp >> 24);
  for (int i=0;i<dataSize;i++)
  {
    packet[i+5] = *(packetPointers[id] + 8*i);
  }

  packet[dataSize+5] = (endString >> 8);
  packet[dataSize+6] = (endString);



}
