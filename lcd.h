#define data_line PORTD
#define RS PORTCbits.RC1
#define RW PORTCbits.RC0
#define EN PORTCbits.RC2

void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void delay(int);


void lcd_init(void)
{
TRISC = 0X00;
TRISD = 0X00;
lcd_cmd(0X30);
lcd_cmd(0X38);
lcd_cmd(0X01);
lcd_cmd(0X80);
lcd_cmd(0X0C);
}

void lcd_cmd(unsigned char c)
{
data_line = c;
RS = 0;
RW = 0;
EN = 1;
delay(200);
EN = 0;
}

void lcd_data(unsigned char d)
{
data_line = d;
RS = 1;
RW = 0;
EN = 1;
delay(200);
EN = 0;
}

void lcd_string(unsigned char *p)
{
while(*p != '\0')
{
lcd_data(*p);
p++;
}
}

void delay(int t)
{
int i,j;
for (i=0;i<t;i++)
{
for (j=0;j<200;j++);
}
}
