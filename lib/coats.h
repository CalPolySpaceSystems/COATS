// cosmos.h

#include "arduino.h"
#include "HardwareSerial.h"

//#define WORD_8BIT

#define CNT_ENABLE (1)
#define CNT_DISABLE (0)


#define STATUS_ID 129

typedef void (*cmdCallback)(uint8_t cmd);

class coats
{
  
	public:
	
		coats(uint16_t ending, bool statusEnable);

    /*
     *  Setup functions
     */ 
     
    void addTlm(uint8_t id, uint32_t* data);

    void addCmd(uint8_t id, cmdCallback callback);
     
    void buildTlm(uint8_t id, String packet);

    void buildTlm(uint8_t id, String packet, uint32_t timeStamp);
  
    /*
     *  UART Interface
     */

    // Initialize a software or hardware serial connection
    void serialInit(HardwareSerial& serialInst,long baud);
    void serialInit(Serial_& serialInst, long baud);

    // Write a status packet to the serial interface
    void serialWriteStat(HardwareSerial& serialInst, uint8_t statMsg);
    void serialWriteStat(Serial_& serialInst, uint8_t statMsg);

    // Write a telemetry without a timestamp
    void serialWriteTlm(HardwareSerial& serialInst, uint8_t id);
    void serialWriteTlm(Serial_& serialInst, uint8_t id);

    // Write a telemetry packet with a given timestamp
    void serialWriteTlm(HardwareSerial& serialInst, uint8_t id, uint32_t timeStamp);
    void serialWriteTlm(Serial_& serialInst, uint8_t id, uint32_t timeStamp); 

    // Parse a command that comes in over the serial monitor
    void serialParseCmd(HardwareSerial& serialInst);
    void serialParseCmd(Serial_& serialInst);
				
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
    cmdCallback   cmdCallbackPtr[256];
		size_t 	packetSizes[256];
		uint16_t endString;
		bool timerEnable;
    bool statEnable;
    

};
