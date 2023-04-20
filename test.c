/* RFID based attendance system*/

#include<reg51.h>
sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;
sbit buzz=P1^6;
void lcddat(unsigned char);
void lcdcmd(unsigned char);
void lcddis(unsigned char *);
void lcdconv(unsigned char);
void lcd_init();
void ser_dis(unsigned char *);
void serial_init();
void check();
void repeat();
void delay(unsigned int);
unsigned char rfid[12],v1,i;
unsigned char count1,count2,count3,count4,count5,total;
void main()
{
serial_init();
lcd_init();
lcdcmd(0x8c);
lcddis("RFID BASED");
lcdcmd(0xc7);	        //forcing cursor to second line
lcddis("ATTENDANCE SYSTEM");
while(1)
	{
	lcdcmd(0x01);
	lcddis("SWIPE YOUR CARD");
	ser_dis("SWIPE YOUR CARD");
	for(v1=0;v1<12;v1++)
	{
	while(RI==0);
	rfid[v1]=SBUF;
	RI=0;
	SBUF=rfid[v1];	
	while(TI==0);
	TI=0;
	}
	check();
	SBUF=0X0D;
	while(TI==0);
	TI=0;
	}
 }
 void check()
 {

 if(rfid[0]=='E'&& rfid[1]=='E'&& rfid[2]=='E'&& rfid[3]=='R'&& rfid[4]=='E'&& rfid[5]=='G'&& rfid[6]=='1'&& rfid[7]=='9'&& rfid[8]=='E'&& rfid[9]=='1'&& rfid[10]=='2'&& rfid[11]=='0')
 {
	if(count1>=1)
	{
	repeat();
	return;
	}
 lcdcmd(0x01);
	 count1++;
	 total++;
 lcddis("JAMES-PRESENT");	 //EEEREG19E120
 delay(50); 
	lcdconv(total);
	delay(50);  
 }
 
 else if(rfid[0]=='E'&& rfid[1]=='E'&& rfid[2]=='E'&& rfid[3]=='R'&& rfid[4]=='E'&& rfid[5]=='G'&& rfid[6]=='1'&& rfid[7]=='9'&& rfid[8]=='E'&& rfid[9]=='1'&& rfid[10]=='2'&& rfid[11]=='4')
 {
	if(count2>=1)
	{
	repeat();
	return;
	}
	count2++;
	 total++;
 lcdcmd(0x01);
 lcddis("KAVIN-PRESENT");     //EEEREG19E124
	delay(50); 
	lcdconv(total);
	 	delay(50);  
 }
 
 else if(rfid[0]=='E'&& rfid[1]=='E'&& rfid[2]=='E'&& rfid[3]=='R'&& rfid[4]=='E'&& rfid[5]=='G'&& rfid[6]=='1'&& rfid[7]=='9'&& rfid[8]=='E'&& rfid[9]=='1'&& rfid[10]=='3'&& rfid[11]=='4')
 {
	if(count3>=1)
	{
	repeat();
	return;
	}
	 count3++;
	 total++;
 lcdcmd(0x01);
 lcddis("NIRESH-PRESENT");  	 //EEEREG19E134
	delay(50); 
	lcdconv(total);
	 	delay(50);  
 }
 
 else if(rfid[0]=='E'&& rfid[1]=='E'&& rfid[2]=='E'&& rfid[3]=='R'&& rfid[4]=='E'&& rfid[5]=='G'&& rfid[6]=='1'&& rfid[7]=='9'&& rfid[8]=='E'&& rfid[9]=='1'&& rfid[10]=='4'&& rfid[11]=='3')
 {
	if(count4>=1)
	{
	repeat();
	return;
	}
	 count4++;
	 total++;
 lcdcmd(0x01);
 lcddis("SABESH-PRESENT");     //EEEREG19E143
 delay(50);
	lcdconv(total);
	 	delay(50);  
 }
 
  else if(rfid[0]=='E'&& rfid[1]=='E'&& rfid[2]=='E'&& rfid[3]=='R'&& rfid[4]=='E'&& rfid[5]=='G'&& rfid[6]=='1'&& rfid[7]=='9'&& rfid[8]=='E'&& rfid[9]=='1'&& rfid[10]=='5'&& rfid[11]=='3')
 {
	if(count5>=1)
	{
	repeat();
	return;
	}
	 count5++;
	 total++;
 lcdcmd(0x01);
 lcddis("SURESH-PRESENT");              //EEEREG19E153
 delay(50);
	lcdconv(total);
	 	delay(50);  
 }
 
 else
 {
 lcdcmd(0x01);
 lcddis("PERSON");                   //111111111111         
 lcdcmd(0xc0);
 lcddis("NOT REGISTERED");
 delay(50);	 

	buzz=0;
	delay(50);
	buzz=1;
 }
 }
 
 
 void lcd_init()
 {
 lcdcmd(0x38);	//intialises crystal 5x7 matrix
 lcdcmd(0x01);	//clear screen
 lcdcmd(0x0c);	//display on cursor off
 lcdcmd(0x80);	//start display from 1st line
 }
 

 void lcdcmd(unsigned char val)
 {
 P2=val;       //Port 2-Data lines of LCD
 rs=0;         
 rw=0;      
 en=1;    
 delay(500);
 en=0;
 delay(500);
 }
 
 
 void lcddat(unsigned char val)
 {
 P2=val;
 rs=1;
 rw=0;
 en=1;
 delay(500);
 en=0;
 delay(500);
 }
 
 
 void delay(unsigned int ms)
 {
 unsigned int v5,v6;
 for(v5=0;v5<ms;v5++);
 for(v6=0;v6<12000;v6++);
 }
 
 
 void lcddis(unsigned char *s)
 {
 unsigned char w;
 for(w=0;s[w]!='\0';w++)
 {
 lcddat(s[w]);
 }
 }
 
 
 void serial_init()
 {
 SCON=0X50;   //Serial Mode 1
 TMOD=0X20;   //Timer 1 Mode 2, 8 bit auto-reload mode
 TH1=-3;      //baudrate 9600
 TR1=1;       //Run the Timer
 }
 
 void ser_dis(unsigned char *s)
 {
	 unsigned char v3;
	 for(v3=0;s[v3]!='\0';v3++)
	 {
		 SBUF=s[v3];
		 while(TI==0);
		 TI=0;    
		}
		SBUF=0x0d;
		while(TI==0);
		TI=0;
	 
}
 
 void repeat()
{
	lcdcmd(0x01);
	lcddis("ALREADY REGISTERED");
	lcdcmd(0xc0);
	lcddis("FOR TODAY");
	delay(50);
	SBUF=0x0d;
	while(TI==0);
	TI=0;
}

 void lcdconv(unsigned char tot)
{
	unsigned int a1,a2,a3;
	lcdcmd(0xc0);     //Second line of LCD
	lcddis("Total:");
	a1=tot;           // 01
	a2 = a1/10;       // 0
	a3 = a1%10;       // 1
	a2 = a2 + 0x30;
	a3 = a3 + 0x30;
	lcdcmd(0xc7);     //Second line after displaying 6 characters
	lcddat(a2);
	lcddat(a3);
}