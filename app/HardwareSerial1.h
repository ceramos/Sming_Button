/****
 * Modified from Sming's HardwareSerial class. This class use for UART1 only.
 * Author: nvl1109@gmail.com
 ****/

#ifndef _HARDWARESERIAL1_H_
#define _HARDWARESERIAL1_H_

#include "../Wiring/WiringFrameworkDependencies.h"
#include "../Wiring/Stream.h"
#include "../SmingCore/Delegate.h"
#include "../Services/CommandProcessing/CommandProcessingIncludes.h"

#define UART_ID_0   0
#define UART_ID_1   1

#define NUMBER_UARTS 2

#define SERIAL_SIGNAL_DELEGATE	0
#define SERIAL_SIGNAL_COMMAND	1
#define SERIAL_QUEUE_LEN		10

class HardwareSerial1 : public Stream
{
public:
	HardwareSerial1(const int uartPort);
	~HardwareSerial1() {}

	void begin(const uint32_t baud = 9600);

	int available();
	int read();
	int readMemoryBlock(char* buf, int max_len);
	int peek();
	void flush();
	size_t write(uint8_t oneChar);

	//void printf(const char *fmt, ...);
	void systemDebugOutput(bool enabled);

private:
	int uart;
	os_event_t * serialQueue;
};

extern HardwareSerial1 DbgSerial;

#endif /* _HARDWARESERIAL1_H_ */
