#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#ifndef USART_h
#define USART_h

#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD)-1)  //Baudrate calculator
#define TX_BUFFER_SIZE 128

#define RX_BUFFER_SIZE 128

//transmitter
char serialBuffer[TX_BUFFER_SIZE];
uint8_t serialReadPos=0;
uint8_t serialWritePos=0;

//receiver
char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxReadPos=0;
uint8_t rxWritePos=0;


//functions
void appendSerial(char c);//for appending characters to UDR0
void serialWrite(char c[]);//input function
void setup();// for setting up the environment
char getChar(void);
char peekChar(void);

#endif