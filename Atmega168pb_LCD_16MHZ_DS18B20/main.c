/*
 * Atmega328PB_ds18b20_.c
 *
 * Created: 11/11/2019 9:40:13 PM
 * Author : andrei
 */ 

#include <avr/io.h>
#include "LCD_Code_2x16_serial.h"
#include "therm_ds18b20.h"


unsigned char Caracter_1;
unsigned char Caracter_2;
unsigned char Caracter_3;
unsigned char Caracter_4;
unsigned char Caracter_5;



char x[20] = {0};
//char temp_2[20] = {0};
void math( unsigned int MATH_DATA);
void math2( unsigned int MATH_DATA2);

void math_raw(unsigned char LCD_Adresa, unsigned int data_raw);


int main(void)
{
	
	DDRE= 0xFF ;
	DDRB= 0xFF ;
	DDRC= 0xFF;
	DDRD= 0xFF ;
	
    PORTE=0x00;
	PORTB=0x00;
	PORTC=0x00;
	PORTD=0x00;
	
    init_LCD();
    //write_inst(0x80);
    //print_string("Atmega32 LCD");
	
	therm_read_temperature(x);
    while (1) 
    {
		//delay();
		therm_read_temperature(x);
		if(data_sensor_raw_second_byte > 250)
		{ // temperatura negativa
		  // FFFF - Sensor data +1 = negative value ;
		  int8_t digit;
		  uint16_t decimal;
		  unsigned int local_LSB ;
		  unsigned int local_MSB ;
		  
		 local_LSB=( 0xFF - data_sensor_raw_first_byte )+1 ;
		 local_MSB= 0xFF - data_sensor_raw_second_byte;
		 
		 digit=local_LSB>>4;
		 digit|=(local_MSB & 0x7)<<4;
		 decimal=local_LSB & 0xf;
		 decimal*=THERM_DECIMAL_STEPS_12BIT;
			 math(digit); // TEMPERATURA INTREAGA 
			 math2(decimal); // TEMPERATURA DUPA VIRGULA 
			 write_inst(0xC0);
			 print_char('-');
			 print_char(Caracter_1);
			 print_char(Caracter_2);
			 print_char('.');
			 print_char(Caracter_3);
			 print_char(Caracter_4);
			 print_char(Caracter_5);
			 
			 
			 math_raw(0x89, data_sensor_raw_first_byte);
			   //math_raw(0x89, local_LSB);
			 math_raw(0xc9, data_sensor_raw_second_byte);
			   //math_raw(0xc9, local_MSB);
		}
		else {
		math(Temperatura_MSB_8bit);
		math2(Temperatura_LSB_16bit);
		
		write_inst(0xC0);
		print_char('+');
		print_char(Caracter_1);
		print_char(Caracter_2);
		print_char('.');
		print_char(Caracter_3);
		print_char(Caracter_4);
		print_char(Caracter_5);
		
		
		 math_raw(0x89, data_sensor_raw_first_byte);
		
		 math_raw(0xc9, data_sensor_raw_second_byte);
		 
		}
		
    }
}

void math_raw(unsigned char LCD_Adresa, unsigned int data_raw)
{
  unsigned int mat	  ;
  unsigned int zecemii ;
  unsigned char mii	   ;
  unsigned char sute ;
  unsigned char zeci ;
  unsigned char unitati;
  //unsigned char  rest  ;
  unsigned char  dat_a1	   ;
  unsigned char  dat_b1    ;
  unsigned char  dat_c1    ;
  unsigned char  dat_d1    ;
  unsigned char  dat_e1  ;
  
  
  mat= data_raw ;
  
  
  zecemii=mat/10000 ;
  mat=mat%10000 ;
  mii= mat/1000;
  mat= mat%1000 ;
  sute= mat/100 ;
  mat= mat%100 ;
  zeci=	mat/10  ;
  unitati= mat%10  ;
  //rest   = mat%1 ;
  
  dat_a1 = zecemii + 0x30 ;
  dat_b1 = mii+0x30 ;
  dat_c1 = sute+0x30  ;
  dat_d1 = zeci+0x30 ;
  dat_e1 = unitati+0x30;
  
  write_inst(LCD_Adresa);
  print_char(dat_a1)   ;
  print_char(dat_b1)   ;
  print_char(dat_c1)   ;
  print_char(dat_d1)   ;
  print_char(dat_e1) ;
  
  //write_inst(locatie); //0xc6
  //print_char(b1) ;
  //print_char(c1) ;
  //Caracter_1=d1 ;
  //Caracter_2=e1;	
	
}


void math( unsigned int MATH_DATA)
{
	unsigned int mat	  ;
	unsigned int zecemii ;
	unsigned char mii	   ;
	unsigned char sute ;
	unsigned char zeci ;
	unsigned char unitati;
	//unsigned char  rest  ;

	// unsigned char  a1	   ;
	unsigned char  b1    ;
	unsigned char  c1    ;
	unsigned char  d1    ;
	unsigned char  e1  ;
	
	mat= MATH_DATA ;
	
	
	zecemii=mat/10000 ;
	mat=mat%10000 ;
	mii= mat/1000;
	mat= mat%1000 ;
	sute= mat/100 ;
	mat= mat%100 ;
	zeci=	mat/10  ;
	unitati= mat%10  ;
	//rest   = mat%1 ;
	
	//a1 = zecemii + 0x30 ;
	b1 = mii+0x30 ;
	c1 = sute+0x30  ;
	d1 = zeci+0x30 ;
	e1 = unitati+0x30;
	
	//write_inst(locatie); //0xc6
	//print_char(b1) ;
	//print_char(c1) ;
	Caracter_1=d1 ;
	Caracter_2=e1;
	
}

void math2( unsigned int MATH_DATA2)
{
	unsigned int mat	  ;
	unsigned int zecemii ;
	unsigned char mii	   ;
	unsigned char sute ;
	unsigned char zeci ;
	unsigned char unitati;
	//unsigned char  rest  ;

	// unsigned char  a1	   ;
	unsigned char  b1    ;
	unsigned char  c1    ;
	unsigned char  d1    ;
	unsigned char  e1  ;
	
	mat= MATH_DATA2 ;
	
	
	zecemii=mat/10000 ;
	mat=mat%10000 ;
	mii= mat/1000;
	mat= mat%1000 ;
	sute= mat/100 ;
	mat= mat%100 ;
	zeci=	mat/10  ;
	unitati= mat%10  ;
	//rest   = mat%1 ;
	
	//a1 = zecemii + 0x30 ;
	b1 = mii + 0x30 ;
	c1 = sute + 0x30 ;
	d1 = zeci + 0x30;
	e1 = unitati + 0x30;
	
	//write_inst(locatie); //0xc6
	Caracter_3=b1;
	Caracter_4=c1;
	Caracter_5=d1;
	//print_char(e1) ;
	
}