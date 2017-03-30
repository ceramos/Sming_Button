/****
 * Sming Framework Project - Open Source framework for high efficiency native ESP8266 development.
 * Created 2015 by Skurydin Alexey
 * http://github.com/anakod/Sming
 * All files of the Sming Core are provided under the LGPL v3 license.
 ****/

// HardwareSerial1 based on Espressif Systems code

#include "../Wiring/WiringFrameworkIncludes.h"
#include <cstdarg>

#include "../SmingCore/Clock.h"
#include "../SmingCore/Interrupts.h"
#include "HardwareSerial1.h"
extern "C" {
	void uart1_tx_one_char(char TxChar);
}

// UartDev is defined and initialized in ROM code.
extern UartDevice UartDev;

//set m_printf callback
extern void setMPrintfPrinterCbc(void (*callback)(char));

// StreamDataAvailableDelegate HardwareSerial1::HWSDelegates[2];

HardwareSerial1::HardwareSerial1(const int uartPort)
	: uart(uartPort)
{
	// Start Serial task
}

void HardwareSerial1::begin(const uint32_t baud/* = 9600*/)
{
	//TODO: Move to params!
	UartDev.baut_rate = (UartBautRate)baud;
	UartDev.parity = NONE_BITS;
	UartDev.exist_parity = STICK_PARITY_DIS;
	UartDev.stop_bits = ONE_STOP_BIT;
	UartDev.data_bits = EIGHT_BITS;

	PIN_PULLUP_DIS(PERIPHS_IO_MUX_GPIO2_U);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_U1TXD_BK);

	uart_div_modify(uart, UART_CLK_FREQ / (UartDev.baut_rate));

	WRITE_PERI_REG(UART_CONF0(uart),    UartDev.exist_parity
													| UartDev.parity
													| (UartDev.stop_bits << UART_STOP_BIT_NUM_S)
													| (UartDev.data_bits << UART_BIT_NUM_S));


	//clear rx and tx fifo,not ready
	SET_PERI_REG_MASK(UART_CONF0(uart), UART_RXFIFO_RST | UART_TXFIFO_RST);
	CLEAR_PERI_REG_MASK(UART_CONF0(uart), UART_RXFIFO_RST | UART_TXFIFO_RST);

	//clear all interrupt
	WRITE_PERI_REG(UART_INT_CLR(uart), 0xffff);

	delay(10);
	DbgSerial.println("\r\n"); // after SPAM :)
}

size_t HardwareSerial1::write(uint8_t oneChar)
{
	//if (oneChar == '\0') return 0;

	// uart_tx_one_char(oneChar);
	// UART1 tx one char
	uart1_tx_one_char(oneChar);

	return 1;
}


int HardwareSerial1::available()
{
	return 0;
}

int HardwareSerial1::read()
{
	return -1;
}

int HardwareSerial1::readMemoryBlock(char* buf, int max_len)
{
	return 0;
}

int HardwareSerial1::peek()
{
	return -1;
}

void HardwareSerial1::flush()
{
}

void HardwareSerial1::systemDebugOutput(bool enabled)
{
	if (uart == UART_ID_0)
		setMPrintfPrinterCbc(enabled ? uart_tx_one_char : NULL);
	else {
		os_install_putc1(enabled ? (void *)uart1_tx_one_char : NULL); //TODO: Debug serial
		setMPrintfPrinterCbc(enabled ? uart1_tx_one_char : NULL);
	}
}

HardwareSerial1 DbgSerial(UART_ID_1);

extern "C" {
	/******************************************************************************
	 * FunctionName : uart1_tx_one_char
	 * Description  : Internal used function
	 *                Use uart1 interface to transfer one char
	 * Parameters   : uint8 TxChar - character to tx
	 * Returns      : OK
	*******************************************************************************/
	void uart1_tx_one_char(char TxChar)
	{
		while (true){
			uint32 fifo_cnt = READ_PERI_REG(UART_STATUS(1)) & (UART_TXFIFO_CNT<<UART_TXFIFO_CNT_S);
			if ((fifo_cnt >> UART_TXFIFO_CNT_S & UART_TXFIFO_CNT) < 126) {
				break;
			}
		}
		WRITE_PERI_REG(UART_FIFO(1) , TxChar);
	}
}
