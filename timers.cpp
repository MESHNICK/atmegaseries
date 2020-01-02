#include<avr/io.h>


int extraTime;

int main()
{
    DDRB|=0x01;
    TCCR0A=(1<<WGM01);//set CTC
    OCR0A=195;// number of ticks
    TIMSK0=(1<<OCIE0A);//set interrupt

    sei();


    TCCT0B=(1<<CS02) | (1<<CS00); //set prescaler (1024 )

    while(1)
    {

    }

}


ISR(TIMER0_COMPA_vect)
{ 
    extraTime++;
    if(extraTime>100)
    {
        PORTB=^(1<<PORTB0);
        extraTime=0;
    }

}