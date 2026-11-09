#include<LPC21XX.H>
#include"keypad.h"
#include<string.h>

void keypad(void);
void DC_MOTOR(void);
int main()
{
int i=0;
unsigned char rx;
unsigned char arr[14];
UART0_CONFIG();
LCD_INIT();
LCD_COMMAND(0X80);
LCD_STRING("SMART BANK       LOCKER SYSTEM");
delayms(1000);
while(1)
{
LCD_COMMAND(0X01);
LCD_STRING("SCAN RFID.....");
UART0_STRING("SCAN RFID\r\n");
for(i=0;i<12;i++)
{
rx=UART0_RX();
arr[i]=rx;
}

if(i==12)
arr[i]='\0';
UART0_STRING(arr);
UART0_STRING("\r\n");
LCD_COMMAND(0X01);
LCD_STRING(arr);
if(i==12)
{
 if(strcmp((char*)arr,"0600680EE989")==0){
LCD_STRING("LEVEL-1            VEREFIED");
UART0_STRING("VEREFIED\r\n");
 delayms(1000);
 keypad();
 }
 else{
 LCD_STRING("NOT VEREFIED");
 UART0_STRING("NOT VEREFIED\r\n");
 delayms(3000);}
 i=0;
}
} 
}
void keypad(void) //KEYPAD OPERATIONS
{
	int res,i;
	static int j=0;
	unsigned char a[5];
	LCD_COMMAND(0X83);
	LCD_STRING("ENTER PASSWORD");
	UART0_STRING("ENTER PASSWORD\r\n");
	LCD_COMMAND(0XC3);
	for(i=0;i<4;i++){
		res=keyscan();
		a[i]=((res%10)+48);
		UART0_STRING("*");
		LCD_DATA('*');}
	a[i]='\0';
	UART0_STRING("\r\n");
		if(strcmp((char*)a,"1234")==0)// PASSWORD CORRECT ON
			{
				delayms(400);
				LCD_COMMAND(0X80);
				LCD_STRING("LOCKER OPENED");
				UART0_STRING("LCOKER OPENED\r\n");
				IOCLR0=led1;
				DC_MOTOR();
				delayms(1000);
				IOSET0=led1;
			}
			else{
				LCD_COMMAND(0X83);
				LCD_STRING("WRONG PASSWORD");
				UART0_STRING("WRONG PASSWORD\r\n");
				IOCLR0=1<<24;
                IOCLR0=BZ;
                delayms(1000);
                IOSET0=led2;
                IOSET0=BZ;
				if(j<3){
					j++;
				keypad();}
				else{
					LCD_COMMAND(0X83);
					LCD_STRING("FAILED TO OPEN");
					UART0_STRING("FAILED TO OPEN\r\n");
					delayms(1000);
					return;
				}
			}
}

void DC_MOTOR(void)
{
	IOSET0=DC;
	delayms(3000);
	IOCLR0=DC;
}
