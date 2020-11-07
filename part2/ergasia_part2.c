//ftiaxnw tin sunartisi gia na dinw tis times ap to eikoniko pliktrologio
char  my_read_keypad()
{
   char var, key;
   int i,j;

   PORTD = 0xFF;                    //arxikopoiw ola ta podarakia tou D sto 1
   TRISD = 0xFF;                    //kanw to portD ws eisodo

   TRISB = 0x00;                    //kanw to portB ws eisodo
   PORTB = 0xFF;                    //arxikopoiw ola ta podarakia tou B sto 1

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
   }while (key == 0);
    return key;
}

//SYNARTISI INTERRUPT GIA TO ERWTHMA 5  (sto c0 to rele1 sto c2 o anemistiras sto c3 to buzzer)
void interrupt() {
    if(PORTC.F2 == 0){                                        //an einai kleisto to anoigw
         PORTC.F2 = 1;                                        //anoigei o anemistiras
    }else {
        PORTC.F2 = 0;                                         //alliws to kleinw
    }
    INTCON =  0b11010000;                                     //katharismos interrupt flag
}

void interrupt_low() {

    if(INTCON3.INT1IF){                                       //otan pataw to int1 anoigei to rele1
            if(PORTC.F0 == 0){                                //otan einai svisto
               PORTC.F0 =1;                                   //to anoigw
            }else{
               PORTC.F0 = 0;                                  //alliws to kleinw
            }
    }
    if(INTCON3.INT2IF){                                       //otan pataw to int2
         if(PORTC.F1 == 1){                                   //an einai kleisto to buzzer
           PORTC.F1 =0;                                       //anoixe to
         }else {
           PORTC.F1=1;                                        //to ekana auto gia na kleinw to buzzer otan xanapataw int2
         }
    }
    INTCON3 = 0b00011000;                                     //katharismos interrupt flag
}


void main(){
     char keypressed;
     int i=0x41;                                                    //se HEX to A
     keypressed=my_read_keypad();
     TRISB=0x0F;                                                    //gia to keypad
     
//gia na xekinisei pataw to 5 apo to pliktrologio
    if(keypressed='5'){
          TRISC =0x00;                                              //energopoiw to portc ws exodo
          PORTC.F1 = 1;                                             //thelw na einai kleisto stin arxi to buzzer gia na to anoigw patwntas to int2

          PORTC.F0 = 0; //otan dinw tin timi 5 apo to keypad gia na xekinisei to erwtima anoigei to rele1 enw thelw na to anoigw egw me to int1 ara to mhdenizw edw kai tha anoigei me to int1

          //arxikopoihsh gia tin leitourgia twn interrupts
          INTCON =  0b11010000;                                    //gia to interrupt 0
          INTCON3 = 0b00011000;                                    //vazw 1 sto 4o bit gia na kanw enable ektos apo to int1 kai to int2
          RCON =0x80;
          
          Lcd8_Config(&PORTE, &PORTD, 2,1,0, 7,6,5,4,3,2,1,0);     //define PORT and PIN Connections
          Lcd8_Cmd(LCD_CURSOR_OFF);                                // Turn off blinking cursor
          Lcd8_Cmd(LCD_CLEAR);                                     // Clear screen

          Lcd8_Out(1, 1, "5o Erwtima");
          while (1){                                               //while gia na emfanizw sunexws sto LCD ta kefalaia grammata A..Z
              Lcd8_Chr(2,5, i);
              i++;                                                  //A......Z
              if (i>0x5A) i=0x41;                                   //otan ftasei sto Z paei pali sto A
           }

     }
    
 }