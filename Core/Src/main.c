#include "system.h"
#include "sx1278.h"
#include <string.h>
#include <stdio.h>

#define TX					//Uncomment for Transmission
//#define RX				//Uncomment for Reception

char buf[20] = {0};
uint8_t ret;

int main(void)
{
  System_Init();
	LoRa_Init();
#ifdef TX
	sprintf(buf, "Smart Grid");
	#else
	uint8_t ret;
	#endif
	
	while(1)
	{
		#ifdef TX
		LoRa_beginPacket();
		LoRa_Transmit((uint8_t*)buf, strlen(buf));
		LoRa_endPacket();
		HAL_Delay(1000);
		#endif
		
		#ifdef RX
		ret = LoRa_parsePacket();
		if(ret)
		{
			uint8_t i = 0;
			while(LoRa_Available())
			{
				buf[i] = LoRa_Read();
				i++;
			}
			buf[i] = '\0';
		}
		#endif	
	}
}


