#line 1 "C:/Users/Nhytu/Desktop/Erwtimata123/ergasia_part1.c"
#line 16 "C:/Users/Nhytu/Desktop/Erwtimata123/ergasia_part1.c"
char my_read_keypad()
{
 char var, key;
 int i,j;

 PORTD = 0xFF;
 TRISD = 0xFF;

 TRISB = 0x00;
 PORTB = 0xFF;

 key =0;

 do {


 PORTB.F0 = 0;
 delay_ms(1);
 var = PORTD;
 if (var.F0 == 0) key = '<';
 else if (var.F1 == 0) key = '7';
 else if (var.F2 == 0) key = '4';
 else if (var.F3 == 0) key = '1';
 PORTB.F0 =1;


 PORTB.F1 = 0;
 delay_ms(1);
 var = PORTD;
 if (var.F0 == 0) key = '0';
 else if (var.F1 == 0) key = '8';
 else if (var.F2 == 0) key = '5';
 else if (var.F3 == 0) key = '2';
 PORTB.F1 =1;


 PORTB.F2 =0;
 delay_ms(1);
 var = PORTD;
 if (var.F0 == 0) key = '>';
 else if (var.F1 == 0) key = '9';
 else if (var.F2 == 0) key = '6';
 else if (var.F3 == 0) key = '3';
 PORTB.F2 =1;
 }while (key == 0);
 return key;
}


void date_Time(){

 unsigned char minutes[2];
 unsigned char seconds[2];
 unsigned char hours[2] , day[2], date[2] , month[2] , year[2];
 unsigned char temp,temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;


 Soft_I2C_Config(&PORTC,4,3);
 Soft_I2C_Start();
 Soft_I2C_Write(0xD0);
 Soft_I2C_Write(0);

 Soft_I2C_Start();
 Soft_I2C_Write(0xD1);
 temp=Soft_I2C_Read(0);
 temp1=Soft_I2C_Read(0);
 temp2=Soft_I2C_Read(0);
 temp3=Soft_I2C_Read(0);
 temp4=Soft_I2C_Read(0);
 temp5=Soft_I2C_Read(0);
 temp6=Soft_I2C_Read(0);
 Soft_I2C_Stop();


 seconds[0]=((temp& 0X70)>>4)+0x30;
 seconds[1]=(temp & 0x0F) + 0x30;



 minutes[0]=((temp1 & 0X70)>>4)+0x30;
 minutes[1]=(temp1 & 0x0F) + 0x30;


 hours[0]=((temp2 & 0x70)>>4)+0x30;

 hours[1]=(temp2 & 0x0F)+0x30;



 day[0]=((temp3 & 0x70)>>4) +0x30;
 day[1]=(temp3 & 0x0F) +0x30;

 date[0]=((temp4 & 0x30)>>4)+0x30;
 date[1]=((temp4 & 0x0F))+0x30;

 month[0]=((temp5 & 0x10)>>4)+0x30;
 month[1]=(temp5 & 0x0F)+0x30;

 year[0]=((temp6 & 0xF0)>>4)+0x30;
 year[1]=(temp6 & 0x0F)+0x30;

 Lcd8_Config(&PORTE, &PORTD, 2,1,0,7,6, 5, 4, 3, 2, 1, 0);
 LCD8_Cmd(LCD_CURSOR_OFF);
 LCD8_Cmd(LCD_CLEAR);

 LCD8_Chr(1,1,hours[0]);
 LCD8_Chr(1,2,hours[1]);

 LCD8_Out(1,3,":");
 LCD8_Chr(1,4,minutes[0]);
 LCD8_Chr(1,5,minutes[1]);

 LCD8_Out(1,6,":");
 LCD8_Chr(1,7,seconds[0]);
 LCD8_Chr(1,8,seconds[1]);


 LCD8_Chr(2,1,date[0]);
 LCD8_Chr(2,2,date[1]);

 LCD8_Out(2,3,"/");
 LCD8_Chr(2,4,month[0]);
 LCD8_Chr(2,5,month[1]);

 LCD8_Out(2,6,"/");
 LCD8_Chr(2,7,year[0]);
 LCD8_Chr(2,8,year[1]);

}

void stepMotor(int taxuthta_peristrofis){

 TRISB = 0b00001111;
 PORTB =0x00;

 while(1){
 PORTB.F4 =0;
 PORTB.F5 =1;
 PORTB.F6 =0;
 PORTB.F7 =1;

 Vdelay_ms(taxuthta_peristrofis);

 PORTB.F4 =1;
 PORTB.F5 =0;
 PORTB.F6 =0;
 PORTB.F7 =1;

 Vdelay_ms(taxuthta_peristrofis);

 PORTB.F4 =1;
 PORTB.F5 =0;
 PORTB.F6 =1;
 PORTB.F7 =0;

 Vdelay_ms(taxuthta_peristrofis);

 PORTB.F4 =0;
 PORTB.F5 =1;
 PORTB.F6 =1;
 PORTB.F7 =0;

 Vdelay_ms(taxuthta_peristrofis);
 }
}

void adc_and_servo(){
 unsigned int speed_tester;
 unsigned char ch;
 unsigned int adc_rd;
 char text[6] ="0000";
 long tlong;

 ADCON0 = 1;
 ADCON1 = 0x01;

 Lcd8_Config(&PORTE, &PORTD, 2,1,0, 7,6,5,4,3,2,1,0);
 Lcd8_Cmd(LCD_CURSOR_OFF);
 Lcd8_Cmd(LCD_CLEAR);
 Lcd8_Out(1, 1, "ADC Value:");

 while (1) {

 adc_rd = ADC_read(0)/4;

 wordToStr(adc_rd, text);
 Lcd8_Out(2,4, text);
 delay_ms(20);

 speed_tester=adc_rd;

 PORTC.F2 = 0xFF;
 TRISC.F2 = 0x00;

 Pwm_Init(500);

 Pwm_Start();
 Pwm_Change_Duty(speed_tester);

 delay_ms(300);
 WordtoStr(speed_tester, text);
 LCD8_Out(1,8,text);
 LCD8_Out(1,13,"/255");
 }
}
void main(){

 char keypressed;
 int taxuthta_peristrofis;
 taxuthta_peristrofis=7;

 keypressed = my_read_keypad();

 TRISD = 0x00;
 TRISA = 0xFB;

 if(keypressed=='1'){
 date_time();
 }
 else if(keypressed=='2'){
 stepMotor(taxuthta_peristrofis);
 }
 else if(keypressed=='3'){
 adc_and_servo();
 }
 }
