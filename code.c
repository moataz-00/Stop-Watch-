
#define  F_CPU   8000000
#include <util/delay.h>

//  REGISTERS

#define  PINA (*(volatile unsigned char *)0x39)
#define  DDRA (*(volatile unsigned char *)0x3A)
#define  PORTA (*(volatile unsigned char *)0x3B)


#define PINB    (*(volatile unsigned char *)0x36)
#define DDRB     (*(volatile unsigned char *)0x37)
#define PORTB     (*(volatile unsigned char *)0x38)

#define PINC    (*(volatile unsigned char *)0x33)
#define DDRC     (*(volatile unsigned char *)0x34)
#define PORTC     (*(volatile unsigned char *)0x35)

#define PIND    (*(volatile unsigned char *)0x30)
#define DDRD     (*(volatile unsigned char *)0x31)
#define PORTD     (*(volatile unsigned char *)0x32)


// set , clear , read bit


#define SET_BIT(reg,bit)   (reg|=(1<<bit))
#define CLR_BIT(reg,bit)   (reg&=~(1<<bit))
#define READ_BIT(reg,bit)   ((reg>>bit)&1)  //give me 1 or 0 not number


#define SEGMENT_PORT  PORTA
void segment_display_mlx(char n){
	const char arr[10]={0x3f<<1,0x06<<1,0x5b<<1,0x4f<<1,0x66<<1,0x6d<<1,0x7d<<1,0x07<<1,0x7f<<1,0x4f<<1};
	SET_BIT(PORTC,6);
	PORTA=arr[n%10];
	CLR_BIT(PORTC,7);
	_delay_ms(10);
	SET_BIT(PORTC,7);
	PORTA = arr[n/10];
	
	CLR_BIT(PORTC,6);
	_delay_ms(10);
}

void segment_display_bcd(char n){
	char d0=n%10;
	char d1=n/10;
	PORTC =d1<<4|d0 ;
}

void segment_display_hex(char n){
	char d0=n;
	PORTC=d0;
}



int main(void)
{
   
  DDRD=0x00;
  PORTD=0xff;
  DDRC=0xff;
  DDRA=0xff;
  
  
  SET_BIT(PORTD,0);
  int i=10;
  int flag=0;
  int mode=0;
  int x;
  while (1)
  {
  segment_display_bcd(i);
		
if (!READ_BIT(PIND,0))
		{
			flag^=1;

		}
		
  if (flag==1)
		   {
		   i--;
		  segment_display_bcd(i);
	
		  if(i==0){
						   
		for (int x=0;x<=2;x++)
		 {
		 SET_BIT(PORTA,0);
		_delay_ms(300);
		 CLR_BIT(PORTA,0);
		 _delay_ms(300);
		 }
						   
	 main();
	}
	 }else{
						   
	 segment_display_bcd(i);
	 }
					   
					  
	  for (x=0;x<100;x++)
	  {
		
	  if(!READ_BIT(PIND,2)){
		i++;
		segment_display_bcd(i);
		while(!READ_BIT(PIND,2));
		}
						  
		if (!READ_BIT(PIND,2))
		{
			 mode^1;
		 }
						  
		 if (!READ_BIT(PIND,1))
		 {
		     main();
		}
						   
		 if (!READ_BIT(PIND,0))
		 {
			flag^=1;
							  
			while(!READ_BIT(PIND,0));
		 }
	        _delay_ms(10);
		 }
  }
 }
	 
