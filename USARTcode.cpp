#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

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


int main(void)
{
    UBRR0H=(BRC>>8);// set baudrate
    UBRR0L=BRC;

    //set up transmitter and receiver
    UCSR0B=(1<<TXEN0) | (1<<TXCIE0) |(1<<RXEN0) | (1<<RXCIE0);
    UCSR0C=(1<<UCSZ01) | (1<<UCSZ00);//set 8 bits data frame
    sei();
    serialWrite(" My name is Fidel");
 
    while(1)
    {
        //tranmitt data
        UDR0='8';
        _delay_ms(1000);

    }
}

//set up
void setup()
{
    UBRR0H=(BRC>>8);// set baudrate
    UBRR0L=BRC;

    //set up transmitter and receiver
    UCSR0B=(1<<TXEN0) | (1<<TXCIE0) |(1<<RXEN0) | (1<<RXCIE0);
    UCSR0C=(1<<UCSZ01) | (1<<UCSZ00);//set 8 bits data frame
    
    sei();// global interrupt
}

//TX functions

void appendSerial(char c)
{
    serialBuffer[serialWritePos]=c;
    serialWritePos++;
    if(serialWritePos>=TX_BUFFER_SIZE)
    {
        serialWritePos=0;
    }
}
void serialWrite( char c[])
{
    for(uint8_t i=0; i<strlen(c); i++)
    {
        appendSerial(c[i]);
    }
    if(UCSR0A & UDRE0)
    {
        UDR0=0;

    }
}


//RX functions
char peekChar(void)
{
    char ret='\0';
    if(rxReadPos!=rxWritePos)
    {
        ret=rxBuffer[rxReadPos];

    }
    return ret;

}
char getChar(void)
{
    char ret='\0';
    if(rxReadPos!=rxWritePos)
    {
        ret=rxBuffer[rxReadPos];
        rxReadPos++;
        if(rxReadPos>=RX_BUFFER_SIZE)
        {
            rxReadPos=0;
        }
    }
    return ret;
}
ISR(USART_TX_vect)
{
    if(serialReadPos!=serialWritePos)
    {
        UDR0=serialBuffer[serialReadPos];
        serialReadPos++;
        if(serialReadPos>=TX_BUFFER_SIZE)
        {
            serialReadPos=0;
        }
    }

}

ISR(USART_RX_vect)
{
    rxBuffer[rxWritePos]=UDR0;
    rxWritePos++;
    if(rxWritePos>=RX_BUFFER_SIZE)
    {
        rxWritePos=0;
    }
}