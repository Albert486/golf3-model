#define F_CPU 8000000

#define STACYJKA 20
#define ROZRUCH 13
#define ALTERNATOR 100
#define DLUGIE_MAX 100
#define FAZA1 48
#define FAZA2 20

#include <avr/io.h>
#include <util/delay.h>

void led_br(unsigned char mijania, unsigned char dlugie, unsigned int time)
{
	unsigned int i;
	unsigned int j=0;
	
	while(j < time)
	{
		for(i=0;i<100;i++)
		{              			// PWM 1/0
			if(mijania > i)     //
			PORTB |= 1;         //
			else          		//
			PORTB &= ~1;        // -------
	    
			if(dlugie > i)      //
			PORTB |= 2;         //
			else          		//
			PORTB &= ~2;      	// -------
		}
		
		PORTB &= ~1;      // PWM 0
		PORTB &= ~2;      // 
		
		_delay_us(10);    // -------
		
		j++;
	}
}

main()
{
	DDRB = 15;
	DDRD = 7;
	PORTD = 0;
	PORTB = 12;
	
	unsigned int i, j;
	
	while(1)
	{
	    _delay_ms(200);
	    _delay_ms(200);
	    _delay_ms(200);
	    _delay_ms(200);
	    _delay_ms(200);
	
	    PORTD |= 1;
	    _delay_ms(60);
	    PORTD &= ~1;
	    
	    for(i=0; i < STACYJKA; i++)     // WŁ Światła
	    led_br(i, 0, 40);
	    
	    led_br(STACYJKA,0,9700);        // Czekaj...
	    
	    for(j=0;j<3;j++)                // Rozruch faza 1
	    {
			for(i=STACYJKA;i>ROZRUCH;i--)
			led_br(i, 0, FAZA1);
			for(i=ROZRUCH;i<STACYJKA;i++)
			led_br(i, 0, FAZA1);
	    }
	    
	    for(j=0;j<4;j++)                // Rozruch faza 2
	    {
			for(i=STACYJKA;i>ROZRUCH;i--)
			led_br(i, 0, FAZA2);
			for(i=ROZRUCH;i<STACYJKA;i++)
			led_br(i, 0, FAZA2);
	    }
	    
	    for(i=STACYJKA; i<ALTERNATOR; i++)  // Alternator działa
			led_br(i, 0, 40);
	    
	    led_br(ALTERNATOR, 0, 4000);     // Czekaj...
	    
	    for(i=0;i<DLUGIE_MAX;i++)        // Długie
	    led_br(ALTERNATOR, i, 4);
	    
	    for(i=DLUGIE_MAX;i>10;i--)
	    led_br(ALTERNATOR, i, 4);
	    
	    for(i=10;i<DLUGIE_MAX;i++)
	    led_br(ALTERNATOR, i, 4);
	    
	    for(i=DLUGIE_MAX;i>0;i--)
	    led_br(ALTERNATOR, i, 8);
	
	    led_br(ALTERNATOR,0,4000);       // Czekaj...
	    
	    for(i=0;i<DLUGIE_MAX;i++)        // Długie
	    led_br(ALTERNATOR, i, 4);
	    
	    for(i=DLUGIE_MAX;i>10;i--)
	    led_br(ALTERNATOR, i, 4);
	    
	    for(i=10;i<DLUGIE_MAX;i++)
	    led_br(ALTERNATOR, i, 4);
	    
	    for(i=DLUGIE_MAX;i>0;i--)
	    led_br(ALTERNATOR, i, 8);
	    
	    led_br(ALTERNATOR,0,26000);        // Czekaj...
	    
	    for(i=ALTERNATOR; i > STACYJKA; i--)  // WYŁ SILNIK
	    led_br(i, 0, 30);
	    
	    led_br(STACYJKA, 0, 10000);
	    
	    for(i=STACYJKA; i > 0; i--)        // WYŁ światła
	    led_br(i, 0, 30);
	    
	    led_br(0, 0, 4000);
	}
	
	return 0;
}
