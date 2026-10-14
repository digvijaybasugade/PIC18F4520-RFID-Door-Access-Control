#include<p18f4520.h>
#include "lcd.h"

void UART_init(void);
void trans(unsigned char);
unsigned char receive(void);

#define r0 PORTBbits.RB5
#define r1 PORTBbits.RB6
#define r2 PORTBbits.RB7
#define c0 PORTBbits.RB1
#define c1 PORTBbits.RB2
#define c2 PORTBbits.RB3
#define c3 PORTBbits.RB4
#define led PORTBbits.RB0

unsigned char wel[15] = "WELCOME";
unsigned char scan[15] = "SCAN CARD";
unsigned char valid[15] = "VALID CARD";
unsigned char e_pass[15] = "ENTER PASS";
unsigned char v_pass[15] = "VALID PASS";
unsigned char in_pass[15] = "INCORRECT PASS";
unsigned char a_g[15] = "ACCESS GRANTED";
unsigned char led_msg[15] = "LED IS ON";
unsigned char id[12];
unsigned char id1[13] = "09001595038A";
unsigned char id2[13] = "09001521526F"; 

void main()
{
int i, pass[4];
int match1,match2;
unsigned char x;

TRISB = 0X1E;
PORTB = 0X00;
lcd_init();
ADCON1 = 0X0F;
INTCON2bits.RBPU = 0;
led = 0;
UART_init();
while(1)
{
lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_string(wel);
lcd_cmd(0XC0);
lcd_string(scan);

for(i=0;i<12;i++)
{
x = receive();
trans(x);
id[i] = x;
}

match1 = 1;
match2 = 1;
for(i=0;i<12;i++)
{
if (id[i] != id1[i]) match1 = 0;
if (id[i] != id2[i]) match2 = 0;
}

if (match1 || match2)
{
lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_string(valid);
delay(200);

lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_string(e_pass);
lcd_cmd(0XC0);

i=0;
while(i<4)
{
r0 = 0;
r1=r2=1;
if (c0==0)
{ pass[i]=1;lcd_data('1');i++; }

r1 = 0;
r0=r2=1;
if (c0==0)
{ pass[i]=2;lcd_data('2');i++; }

r2 = 0;
r0=r1=1;
if (c0==0)
{ pass[i]=3;lcd_data('3');i++; }

r0 = 0;
r1=r2=1;
if (c1==0)
{ pass[i]=4;lcd_data('4');i++; }

r1 = 0;
r0=r2=1;
if (c1==0)
{ pass[i]=5;lcd_data('5');i++; }

r2 = 0;
r0=r1=1;
if (c1==0)
{ pass[i]=6;lcd_data('6');i++; }

r0 = 0;
r1=r2=1;
if (c2==0)
{ pass[i]=7;lcd_data('7');i++; }

r1 = 0;
r0=r2=1;
if (c2==0)
{ pass[i]=8;lcd_data('8');i++; }

r2 = 0;
r0=r1=1;
if (c2==0)
{ pass[i]=9;lcd_data('9');i++; }

delay(200);
}

if (match1 == 1)
{
if ((pass[0]==1) && (pass[1]==2) && (pass[2]==3) && (pass[3]==4))
{
lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_string(v_pass);
delay(200);

lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_string(a_g);

lcd_cmd(0XC0);
lcd_string(led_msg);
led = 1;
PORTB = 0XFF;
delay(1000);
led = 0;
PORTB = 0X00;
}
else
{
lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_string(in_pass);
delay(200);
}
}

if(match2 == 1)
{
if ((pass[0]==5) && (pass[1]==6) && (pass[2]==7) && (pass[3]==8))
{
lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_string(v_pass);
delay(200);

lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_string(a_g);

lcd_cmd(0XC0);
lcd_string(led_msg);
led = 1;
PORTB = 0XFF;
delay(2000);
led = 0;
PORTB = 0X00;
}
else
{
lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_string(in_pass);
delay(200);
}
}
}
}
}

void UART_init(void)
{
TRISC = 0X80;
TXSTA = 0X24;
RCSTA = 0X90;
SPBRG = 0X81;
}

void trans(unsigned char ch)
{
TXREG = ch;
while(TXSTAbits.TRMT == 0);
}

unsigned char receive(void)
{
while(PIR1bits.RCIF == 0);
return RCREG;
}
