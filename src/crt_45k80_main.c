
#include    <pic18.h>

#include 		"crt_45k80_main.h"
#include        "cpu18f45k80.h"
#include		"45k80_SPI.h"


unsigned    int		msec=0;

bit bVirt_RxGood = 0;
unsigned int Virt_RxGoodTimer = 0;


void    PortInit(void)
{
	TRISA=0;
	TRISB=0;
	TRISC=0;
	TRISD=0;
	TRISE=0;

  	LATA=0xff;	
  	LATB=0xff;	
  	LATC=0xff;	
  	LATD=0xff;	
  	LATE=0xff;	

	TRISC0 = 0;
	LATC0 = 1;
}


/*
// Timer 기능 구현 	 
*/
void main(void)
{
	unsigned char i;	
    
    di();
    Initial();
    PortInit();
    Timer0Init(); 
	InitSPI();
	TRISE0 = 0;
	LATE = 0;
    ei();

	msec=0;
	

    while (1)
	{ 		
        CLRWDT();

		
    }
}

	

void interrupt isr(void)
{   
    if( TMR0IF )		
    {    
        TMR0IF = 0;
        TMR0L=MSEC_L;
        TMR0H=MSEC_H;    

        msec++;

        if(msec>1000){
            msec=0;
			_RELAY_OUT = !_RELAY_OUT;
			SPI_Play(DINGDONG_MENT); // 도착 알림 딩동 !
        } 
    }
}




