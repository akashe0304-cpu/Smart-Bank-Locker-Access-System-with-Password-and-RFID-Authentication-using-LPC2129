#include"lcdheader.h"
#define c0 (IOPIN1&(1<<23))
#define c1 (IOPIN1&(1<<24))
#define c2 (IOPIN1&(1<<25))
#define c3 (IOPIN1&(1<<26))

#define r0 1<<27
#define r1 1<<28
#define r2 1<<29
#define r3 1<<30

unsigned int key_lut[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
unsigned int keyscan(void);

unsigned int keyscan(void)//KEY SCAN DEFINITION
{
unsigned char row_val,col_val;
IODIR1=r0|r1|r2|r3;

while(1)
{
IOCLR1=r0|r1|r2|r3;
IOSET1=c0|c1|c2|c3;
while((c0&&c1&&c2&&c3)==1);//waiting for key press
IOCLR1=r0;
IOSET1=r1|r2|r3;
if((c0&&c1&&c2&&c3)==0)
{
row_val=0;
break;
}
IOCLR1=r1;
IOSET1=r0|r2|r3;
if((c0&&c1&&c2&&c3)==0)
{
row_val=1;
break;
}
IOCLR1=r2;
IOSET1=r1|r0|r3;
if((c0&&c1&&c2&&c3)==0)
{
row_val=2;
break;
}
IOCLR1=r3;
IOSET1=r1|r2|r0;
if((c0&&c1&&c2&&c3)==0)
{
row_val=3;
break;
}
}
if(c0==0)
col_val=0;
else if(c1==0)
col_val=1;
else if(c2==0)
col_val=2;
else
col_val=3;
delayms(150);
while((c0&&c1&&c2&&c3)==0);
return key_lut[row_val][col_val];
}
