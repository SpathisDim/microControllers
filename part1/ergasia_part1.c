#define spi_reset  PORTB.F4
#define spi_dta  PORTB.F6
#define spi_clk PORTB.F7
#define spi_cs  PORTB.F5
#define CS0 spi_cs=0;
#define CS1 spi_cs=1;
#define CLK0 spi_clk=0;
#define CLK1 spi_clk=1;
#define SDA0 spi_dta=0;
#define SDA1 spi_dta=1;
#define RESET0 spi_reset=0;
#define RESET1 spi_reset=1;


//ftiaxnw tin sunartisi gia na dinw tis times ap to eikoniko pliktrologio
char  my_read_keypad()
{
   char var, key;
   int i,j;

   PORTD = 0xFF;      //arxikopoiw ola ta podarakia tou D sto 1
   TRISD = 0xFF;      //kanw to portD ws eisodo

   TRISB = 0x00;     //kanw to portB ws eisodo
   PORTB = 0xFF;     //arxikopoiw ola ta podarakia tou B sto 1

   key =0;

   do {    //scan continuously until a key is pressed on the keypad.

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
   }while (key == 0);
    return key;
}

//Synartisi gia to 1o erwthma (diavazw kai emfanizw wra kai hmeromhnia)
void date_Time(){

       unsigned char minutes[2];               //apothikeuw ta dedomena pou diavazw stous pinakes aytous
       unsigned char seconds[2];
       unsigned char hours[2] , day[2], date[2] , month[2] , year[2];
       unsigned char temp,temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
       //unsigned int i,b;

         Soft_I2C_Config(&PORTC,4,3);           //arxikopoiw
         Soft_I2C_Start();
	       Soft_I2C_Write(0xD0);                  //stelnw tin dieuthinsh ths EEPROM+W
         Soft_I2C_Write(0);                     //thesi mnhmhs pou thelw na diavasw ((0)ta seconds diladi)

         Soft_I2C_Start();                      //Issue I2C start signal
         Soft_I2C_Write(0xD1);                  //Send byte(device address +R)
         temp=Soft_I2C_Read(0);                 //Read data (NO ACK)  thesi mnimis 0
         temp1=Soft_I2C_Read(0);                //diavazw thesi mnimis 1
         temp2=Soft_I2C_Read(0);                //diavazw thesi mnimis 2
         temp3=Soft_I2C_Read(0);                //diavazw thesi mnimis 3
         temp4=Soft_I2C_Read(0);                //diavazw thesi mnimis 4
         temp5=Soft_I2C_Read(0);                //diavazw thesi mnimis 5
         temp6=Soft_I2C_Read(0);                //diavazw thesi mnimis 6
         Soft_I2C_Stop();

         //apothikeuw ta dedomena (dekades , monades ) me to 7 krataw ta bit 6 5 4 poy xreiazomai gia ta lepta
          seconds[0]=((temp& 0X70)>>4)+0x30;      //olisthisi gia na einai stoixismena kai ta kanw +0x30 kai to metatrepw se ascii
          seconds[1]=(temp & 0x0F) + 0x30;


          //kanw to idio gia ta deuterolepta gt exoyn to idio format me ta minutes
          minutes[0]=((temp1 & 0X70)>>4)+0x30;
          minutes[1]=(temp1 & 0x0F) + 0x30;

          //Kanw to idio me tis wres
          hours[0]=((temp2 & 0x70)>>4)+0x30;
          //hours[1]=((temp2 & 0x30)>>4)+0x30;
          hours[1]=(temp2 & 0x0F)+0x30;

          //to day den xrisimeuei kapoy apla to evala gia na min berdeytw
          //giati to temp3 diavazei mia thesi mnimis poy einai katw apo to temp4
          day[0]=((temp3 & 0x70)>>4) +0x30;
          day[1]=(temp3 & 0x0F) +0x30;

          date[0]=((temp4 & 0x30)>>4)+0x30;
          date[1]=((temp4 & 0x0F))+0x30;

          month[0]=((temp5 & 0x10)>>4)+0x30;
          month[1]=(temp5 & 0x0F)+0x30;

          year[0]=((temp6 & 0xF0)>>4)+0x30;
          year[1]=(temp6 & 0x0F)+0x30;

          Lcd8_Config(&PORTE, &PORTD, 2,1,0,7,6, 5, 4, 3, 2, 1, 0); // Lcd_Init_EP5, see Autocomplete
          LCD8_Cmd(LCD_CURSOR_OFF);                  // send command to LCD (cursor off)
          LCD8_Cmd(LCD_CLEAR);                       // send command  to LCD (clear LCD)
         //tupwnw gia wra
          LCD8_Chr(1,1,hours[0]);                    //wra
          LCD8_Chr(1,2,hours[1]);

          LCD8_Out(1,3,":");
          LCD8_Chr(1,4,minutes[0]);                  //lepta
          LCD8_Chr(1,5,minutes[1]);

          LCD8_Out(1,6,":");
          LCD8_Chr(1,7,seconds[0]);                  //deuterolepta
          LCD8_Chr(1,8,seconds[1]);

          //tupwnw gia hmeromhnia
          LCD8_Chr(2,1,date[0]);
          LCD8_Chr(2,2,date[1]);

          LCD8_Out(2,3,"/");
          LCD8_Chr(2,4,month[0]);                   //arithmos mhna
          LCD8_Chr(2,5,month[1]);

          LCD8_Out(2,6,"/");
          LCD8_Chr(2,7,year[0]);                    //xronia
          LCD8_Chr(2,8,year[1]);

}
 //2o erwtima syanrtisi gia ton vimatiko kinitira
void stepMotor(int taxuthta_peristrofis){
        //kwdikas gia vimatiko kinhthra
         TRISB = 0b00001111;                                //epeidh xrhsimopoiw mono 4 podarakia arxikopoiw ta 4 ws eisodoi ta alla 4 ws exodoi
         PORTB =0x00;

         while(1){                                         //to syndew sta rb4 rb5 rb6 rb7
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

               Vdelay_ms(taxuthta_peristrofis);             //1 strofi ana 3sec
         }
}
//3o erwtima synartisi gia ton servokinitira
void adc_and_servo(){
          unsigned int speed_tester;                        //h metavliti pou tis paraxwrw tin timi toy potensiometrou
          unsigned char ch;
          unsigned int adc_rd;
          char text[6] ="0000";
          long tlong;
          //energopoiw to systhma A/D
          ADCON0     = 1;
          ADCON1     = 0x01;                                  // configure VDD as Vref, PORTA pins as analog, PORTB pins as digital

          Lcd8_Config(&PORTE, &PORTD, 2,1,0, 7,6,5,4,3,2,1,0);
          Lcd8_Cmd(LCD_CURSOR_OFF);                           // Turn off cursor
          Lcd8_Cmd(LCD_CLEAR);                                // Clear screen
        	Lcd8_Out(1, 1, "ADC Value:");                       // Print text on LCD

          while (1) {

              adc_rd  = ADC_read(0)/4;                      // get ADC value from first channel
                                                            //to kanw dia 4 gia na eimai mesa sto plaisio timwn (0-255)
              wordToStr(adc_rd, text);
              Lcd8_Out(2,4, text);
              delay_ms(20);

              speed_tester=adc_rd;                         //dinw tin timi apo to potensiometro gia na tin xrhsimopoihsw ston servokinitira
              //SERVO MOTOR CONTROL USING PWM MODULE ON RC2
              PORTC.F2 = 0xFF;                             // Set PORTC.2 to 1
              TRISC.F2 = 0x00;                             // PORTC.2 exodos

              Pwm_Init(500);                               // Initialize PWM module 500Hz ->2ms period

              Pwm_Start();                                 // Start PWM
              Pwm_Change_Duty(speed_tester);               // set speed apo 0 ews 255

              delay_ms(300);
              WordtoStr(speed_tester, text);
              LCD8_Out(1,8,text);
              LCD8_Out(1,13,"/255");
         }
}
void main(){

   char keypressed;
   int taxuthta_peristrofis;
   taxuthta_peristrofis=7;                                 //gia tin taxitita tou stepper

   keypressed = my_read_keypad();

   TRISD = 0x00;                                           //Define PORTD to operate as outpout
   TRISA = 0xFB;                                           // Define PORTA pin 2 as output.

   if(keypressed=='1'){                                    //otan patisw to koubi 1 kalw tin sunartisi date_time pou tha mas deixei sto lcd tin wra kai tin hmeromhni
       date_time();
    }
    else if(keypressed=='2'){                              //patwntas to 2 energopoieitai o vimatikos kinitiras
       stepMotor(taxuthta_peristrofis);                    //synartisi gia ton vimatiko kinitira
    }
    else if(keypressed=='3'){                              //otan patisw to 3  xekinaei o servokinitiras
       adc_and_servo();                                    //kalw tin sunartisi
    }
  }
