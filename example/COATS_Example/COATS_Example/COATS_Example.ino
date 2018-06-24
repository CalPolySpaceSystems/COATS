#include "coats.h"

#define ENDING 0x4350
#define ADC_ID 42

#define ptr_t uint32_t

uint16_t adcData[6];

/* Initialize class for the COATS telemetry */
coats downlink = coats(ENDING,COUNTER_EN);

void setup() {

  /* Add the telemetry object (can be array or struct) for all of the ADC readings
   * - Cast adcData to a pointer (8-bit or 32-bit, depending on architecture)
   * - Input size of the given data.
   */
  downlink.addTlm(ADC_ID,(ptr_t*)adcData,sizeof(adcData));

  /* Initialize the serial interface, which also begins serial communication */
  downlink.serialInit(Serial,9800);

}

void loop() {

  /* Read ADCs */
  for (int i=0;i<6;i++){
    adcData[i] = analogRead(i);
  }

  /* Send Packet */
  downlink.serialWriteTlm(ADC_ID);

  delay(50);

}
