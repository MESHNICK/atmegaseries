#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>


double dutyCycle=0;

#define F_CPU 16000000UL

int main(void)
{

    DDRB |=(1<<PORTD6);
    TCCR0A= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);//set fast PWM and clear OC0A
    TIMSK0=(1<<TOIE0);//set timer interrupt

    OCR0A=(dutyCycle/100)*255;//duty cycle

    sei();//set external interrupt


    TCCR0B=(1<<CS00);//set prescaler
    while(1)
    {
        _delay_ms(100);
        dutyCycle +=10;
        if(dutyCycle>100)
        { 
            dutyCycle=0;
        }

    }



}
ISR(TIMER0_OVF_vect)
{
    OCR0A=(dutyCycle/100)*255;//duty cycle

}