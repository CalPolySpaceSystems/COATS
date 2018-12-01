// cosmos.h

#include "arduino.h"
#include "HardwareSerial.h"

//#define WORD_8BIT

#define CNT_ENABLE (1)
#define CNT_DISABLE (0)

class cosmos
{
  
	public:
	
		cosmos(uint16_t ending, bool counterEnable);
	
    /*
     *  UART Interface
     */
     
    void serialInit(HardwareSerial& serialInst,long baud);
    
    void serialWriteTlm(uint8_t id);
		
		/*
		 *	SPI Interface
		 */
		 
		/*
		 *	I2C Interface
		 */
		 
		/*
		 *	Other Functions
		 */ 
		 
		void addTlm(uint8_t id, uint32_t* data, size_t dataSize);
		 
		void buildTlm(uint8_t id, String packet);
		
	private:

    /* Interfaces */
    HardwareSerial* SerialCOSMOS;
  
		/* You can cut the memory space used in an 8-bit processor by defining "WORD_8BIT"*/
		#ifdef WORD_8BIT
		uint8_t 	*packetPointers[256];
		#else
		uint32_t 	*packetPointers[256];
		#endif
		size_t 	packetSizes[256];
		uint16_t endString;
		bool timerEnable;

};
