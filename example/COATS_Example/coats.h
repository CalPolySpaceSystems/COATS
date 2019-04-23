// cosmos.h

#include "arduino.h"
#include "HardwareSerial.h"

//#define WORD_8BIT

#define CNT_ENABLE (1)
#define CNT_DISABLE (0)

class coats
{
  
	public:
	
		coats(uint16_t ending, bool counterEnable);
	
    /*
     *  UART Interface
     */
     
    void serialInit(HardwareSerial& serialInst,long baud);
    
    void serialInit(Serial_& serialInst, long baud);

    void serialWriteTlm(HardwareSerial& serialInst, uint8_t id);
    void serialWriteTlm(Serial_& serialInst, uint8_t id);
		
		/*
		 *	Other Functions
		 */ 
		 
		void addTlm(uint8_t id, uint32_t* data);
		 
		void buildTlm(uint8_t id, String packet);
		
	private:

    /* Interfaces */
    union{
      HardwareSerial *_hw;
      Serial_ *_sw;
    }SerialCOATS;
    
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
