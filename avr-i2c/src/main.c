#include <avr/io.h>
#include "Rtc.h"
#include "Usart.h"
#include "Std_Types.h"

#define CHAR(x) ((x) + '0')

void SendTimeToUsart(uint8 h, uint8 m, uint8 s) {
	Usart_Transmit(CHAR(h >> 4));
	Usart_Transmit(CHAR(h & 0x0F));
	Usart_Transmit(':');
	Usart_Transmit(CHAR(m >> 4));
	Usart_Transmit(CHAR(m & 0x0F));
	Usart_Transmit(':');
	Usart_Transmit(CHAR(s >> 4));
	Usart_Transmit(CHAR(s & 0x0F));
	Usart_Transmit('\r');
	Usart_Transmit('\n');

}

int main() {

	Usart_Init();
	Rtc_Init();
	uint8 s, m, h;
	while (1) {
		Rtc_GetTime(&h, &m, &s);
		SendTimeToUsart(h, m, s);
	}

	return 0;
}

