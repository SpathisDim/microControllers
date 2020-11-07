
 char  my_read_keypad()
{
   char var, key;
   int i,j;

   PORTD = 0xFF;      //initialize all pins in PORT D as 1
   TRISD = 0xFF;      //configure PORTD is inpout

   TRISB = 0x00;     //configure PORT B as outpout
   PORTB = 0xFF;     //set all pins of PORT B to 1;

   key =0;

   do {     //scan continuously until a key is pressed on the keypad.

           // scan first column   by setting RB0 to 0 and reading from DR0,RD1, RD2, RD3.
           PORTB.F0 = 0;
           delay_ms(1);
           var = PORTD;
           if (var.F0 == 0)      key = '<';
           else if (var.F1 == 0) key = '7';
           else if (var.F2 == 0) key = '4';
           else if (var.F3 == 0) key = '1';
           PORTB.F0 =1;    //restore RB0 to 1.

           // scan second column    by setting RB1 to 0 and reading from DR0,RD1, RD2, RD3.
           PORTB.F1 = 0;
           delay_ms(1);
           var = PORTD;
           if (var.F0 == 0)      key = '0';
           else if (var.F1 == 0) key = '8';
           else if (var.F2 == 0) key = '5';
           else if (var.F3 == 0) key = '2';
           PORTB.F1 =1;   //restore RB1 to 1

           // scan third column   by setting RB2 to 0 and reading from DR0,RD1, RD2, RD3.
           PORTB.F2 =0;
           delay_ms(1);
           var = PORTD;
           if (var.F0 == 0)      key = '>';
           else if (var.F1 == 0) key = '9';
           else if (var.F2 == 0) key = '6';
           else if (var.F3 == 0) key = '3';
           PORTB.F2 =1;  //restore RB2 to 1
   } while (key == 0);

   return key;
}
 
 
unsigned char data[11];
void main() {
      char i, *text ,*text1;
      char keypressed;
      
      Lcd8_Config(&PORTE, &PORTD, 2,1,0,7,6, 5, 4, 3, 2, 1, 0); // Lcd_Init_EP5, see Autocomplete
      LCD8_Cmd(LCD_CURSOR_OFF);                                 // send command to LCD (cursor off)
      LCD8_Cmd(LCD_CLEAR);
      text="Patiste to 4 " ;
      text1="Gia na xekinisei";
      LCD8_Out(1,1,text);
      LCD8_Out(2,1,text1);
      
      keypressed=my_read_keypad();
      
      //pataw to 4 apo to keypad kai xekinaei
      if(keypressed='4'){
         Soft_I2C_Config(&PORTC, 4, 3);                           //arxikopoiw
         Soft_I2C_Start();                                        // Issue I2C start signal
         Soft_I2C_Write(0xA2);                                    // stelnw tin dieuthunsh tis EEPROM + W
         Soft_I2C_Write(2);                                       // Stelnw tin thesi mnimis tis eeprom pou thelw na grapsw
         Soft_I2C_Write('S');                                     // Send data (data to be written)
         Soft_I2C_Write('P');                                     // Send data (data to be written)
         Soft_I2C_Write('A');                                     // Send data (data to be written)
         Soft_I2C_Write('T');                                     // Send data (data to be written)
         Soft_I2C_Write('H');                                     // Send data (data to be written)
         Soft_I2C_Write('I');                                     // Send data (data to be written)
         Soft_I2C_Write('S');                                     // Send data (data to be written)

         Soft_I2C_Write('J');                                     // Send data (data to be written)
         Soft_I2C_Write('I');                                     // Send data (data to be written)
         Soft_I2C_Write('M');                                     // Send data (data to be written)
         Soft_I2C_Stop();


         Soft_I2C_Config(&PORTC, 4, 3);                           //Use Port C pins 4 and 3
         Soft_I2C_Start();                                        // Issue I2C start signal
         Soft_I2C_Write(0xA2);                                    // stelnw tin dieuthunsh tis EEPROM + W
         Soft_I2C_Write(2);                                       // Stelnw tin thesi mnimis tis eeprom pou thelw na grapsw

         Soft_I2C_Start();                                        // Issue I2C start signal
         Soft_I2C_Write(0xA3);                                    // twra exw tin dieuthinsh ths suskeuhs alla gia read
         data[0] = Soft_I2C_Read(1);                              // Read data (send ACK)
         data[1] = Soft_I2C_Read(1);                              // Read data (send ACK)
         data[2] = Soft_I2C_Read(1);                              // Read data (send ACK)
         data[3] = Soft_I2C_Read(1);                              // Read data (send ACK)
         data[4] = Soft_I2C_Read(1);                              // Read data (send ACK)
         data[5] = Soft_I2C_Read(1);                              // Read data (send ACK)
         data[6] = Soft_I2C_Read(1);                              // Read data (send ACK)
         data[7] = Soft_I2C_Read(1);                              // Read data (send ACK)
         data[8] = Soft_I2C_Read(1);                              // Read data (send ACK)
         data[9] = Soft_I2C_Read(0);                              // Read data (NO ACK)
         Soft_I2C_Stop();


        Usart_Init(9600);

           /*  LCD8_Chr(1,2,data[0]);         //kati testara me to lcd tis plaketas
             LCD8_Chr(1,3,data[1]);
             LCD8_Chr(1,4,data[2]);
             LCD8_Chr(1,5,data[3]);
             LCD8_Chr(1,6,data[4]);
             LCD8_Chr(1,7,data[5]);
             LCD8_Chr(1,8,data[6]);
             LCD8_Chr(1,9,data[7]);
             LCD8_Chr(1,10,data[8]);
             LCD8_Chr(1,11,data[9]);  */

          //tupwnw to onoma moy sto seiriako terminal

          Usart_Write(data[0]);                                  //tupwnei to S
          Usart_Write(data[1]);                                  //tupwnei to P
          Usart_Write(data[2]);                                  //tupwnei to A
          Usart_Write(data[3]);                                  //tupwnei to T
          Usart_Write(data[4]);
          Usart_Write(data[5]);
          Usart_Write(data[6]);
          Usart_Write(' ');
          Usart_Write(data[7]);
          Usart_Write(data[8]);
          Usart_Write(data[9]);
     }
}
