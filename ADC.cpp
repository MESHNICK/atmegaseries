#include<avr/io.h>
#include<avr/interrupt.h>

double dutyCycle=0;

#define F_CPU 16000000UL

int main(void)
{

    DDRB |=(1<<PORTD6);
    TCCR0A= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);//set fast PWM and clear OC0A
    TIMSK0=(1<<TOIE0);//set timer interrupt
    setupADC();


    sei();//set external interrupt


    TCCR0B=(1<<CS00);//set prescaler
    while(1)
    {
    }



}
void setupADC()
{
    ADMUX=(1<<REFS0) | (1<<MUX0) | (1<<MUX2);//set ADC pin as ADC 5 and set REf voltage
    ADCSRA=(1<<ADEN) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);//enable ADC, set interrupt and set prescaler
    DIDR0 = (1<<ADC5D);// disable digital input buffer
    startConversion();

}


void startConversion()
{
    ADCSRA |=(1<<ADSC);
}


ISR(TIMER0_OVF_vect)
{
    OCR0A=dutyCycle;//duty cycle

}

ISR(ADC_vect)
{
    dutyCycle=ADC;
    startConversion();
}