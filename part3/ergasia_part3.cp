#line 1 "C:/Users/Nhytu/Desktop/final_part3/ergasia_part3.c"

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
 } while (key == 0);

 return key;
}


unsigned char data[11];
void main() {
 char i, *text ,*text1;
 char keypressed;

 Lcd8_Config(&PORTE, &PORTD, 2,1,0,7,6, 5, 4, 3, 2, 1, 0);
 LCD8_Cmd(LCD_CURSOR_OFF);
 LCD8_Cmd(LCD_CLEAR);
 text="Patiste to 4 " ;
 text1="Gia na xekinisei";
 LCD8_Out(1,1,text);
 LCD8_Out(2,1,text1);

 keypressed=my_read_keypad();


 if(keypressed='4'){
 Soft_I2C_Config(&PORTC, 4, 3);
 Soft_I2C_Start();
 Soft_I2C_Write(0xA2);
 Soft_I2C_Write(2);
 Soft_I2C_Write('S');
 Soft_I2C_Write('P');
 Soft_I2C_Write('A');
 Soft_I2C_Write('T');
 Soft_I2C_Write('H');
 Soft_I2C_Write('I');
 Soft_I2C_Write('S');

 Soft_I2C_Write('J');
 Soft_I2C_Write('I');
 Soft_I2C_Write('M');
 Soft_I2C_Stop();


 Soft_I2C_Config(&PORTC, 4, 3);
 Soft_I2C_Start();
 Soft_I2C_Write(0xA2);
 Soft_I2C_Write(2);

 Soft_I2C_Start();
 Soft_I2C_Write(0xA3);
 data[0] = Soft_I2C_Read(1);
 data[1] = Soft_I2C_Read(1);
 data[2] = Soft_I2C_Read(1);
 data[3] = Soft_I2C_Read(1);
 data[4] = Soft_I2C_Read(1);
 data[5] = Soft_I2C_Read(1);
 data[6] = Soft_I2C_Read(1);
 data[7] = Soft_I2C_Read(1);
 data[8] = Soft_I2C_Read(1);
 data[9] = Soft_I2C_Read(0);
 Soft_I2C_Stop();


 Usart_Init(9600);
#line 122 "C:/Users/Nhytu/Desktop/final_part3/ergasia_part3.c"
 Usart_Write(data[0]);
 Usart_Write(data[1]);
 Usart_Write(data[2]);
 Usart_Write(data[3]);
 Usart_Write(data[4]);
 Usart_Write(data[5]);
 Usart_Write(data[6]);
 Usart_Write(' ');
 Usart_Write(data[7]);
 Usart_Write(data[8]);
 Usart_Write(data[9]);
 }
}
