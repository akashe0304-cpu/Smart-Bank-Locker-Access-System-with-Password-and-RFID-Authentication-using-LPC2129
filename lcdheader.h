#include<LPC21XX.H>
#define lcd 0x0f<<14
#define RS 1<<12
#define E 1<<13
#define led1 1<<4
#define led2 1<<24
#define DC 1<<18
#define BZ 1<<23
void LCD_COMMAND(unsigned char);
void LCD_INIT(void);
void LCD_DATA(unsigned char);
void LCD_STRING(unsigned char*);
void delayms(unsigned int);
void UART0_CONFIG(void);
unsigned char UART0_RX(void);
void UART0_TX(unsigned char);
void UART0_STRING(unsigned char *);

void LCD_COMMAND(unsigned char ch)
{
IOCLR0=lcd;
IOSET0=(ch&0xf0)<<10;
IOCLR0=RS;
IOSET0=E;
delayms(2);
IOCLR0=E;

IOCLR0=lcd;
IOSET0=(ch&0x0f)<<14;
IOCLR0=RS;
IOSET0=E;
delayms(2);
IOCLR0=E;
}
void LCD_INIT(void)
{
IODIR0=lcd|RS|E|led1|DC|BZ|led2;
IOSET0=led1|BZ|led2;
LCD_COMMAND(0x01);
LCD_COMMAND(0X02);
LCD_COMMAND(0X0C);
LCD_COMMAND(0X28);
}

void LCD_DATA(unsigned char ch)
{
IOCLR0=lcd;
IOSET0=(ch&0xf0)<<10;
IOSET0=RS;
IOSET0=E;
delayms(2);
IOCLR0=E;

IOCLR0=lcd;
IOSET0=(ch&0x0f)<<14;
IOSET0=RS;
IOSET0=E;
delayms(2);
IOCLR0=E;
}
void LCD_STRING(unsigned char *p)
{
int i=0;
LCD_COMMAND(0X01);
while(*p){
LCD_DATA(*p++);
i++;
if(i==16){
LCD_COMMAND(0XC0);
i=0;}
}
}
void delayms(unsigned int ms)
{
T0PR=15000-1;
T0TCR=0X01;
while(T0TC<ms);
T0TCR=0X03;
T0TCR=0X00;
}
void UART0_CONFIG(void)
{
PINSEL0=0X05;
U0LCR=0X83;
U0DLL=97;
U0DLM=0;
U0LCR=0X03;
}
unsigned char UART0_RX(void)
{
while((U0LSR&1)==0);
return U0RBR;
}
void UART0_TX(unsigned char ch)
{
while((U0LSR>>5&1)==0);
U0THR=ch;
}
void UART0_STRING(unsigned char *p)
{
while(*p)
UART0_TX(*p++);
}
