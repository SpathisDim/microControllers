#line 1 "C:/Users/Nhytu/Desktop/Erwtima5/ergasia_part2.c"

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


void interrupt() {
 if(PORTC.F2 == 0){
 PORTC.F2 = 1;
 }else {
 PORTC.F2 = 0;
 }
 INTCON = 0b11010000;
}

void interrupt_low() {

 if(INTCON3.INT1IF){
 if(PORTC.F0 == 0){
 PORTC.F0 =1;
 }else{
 PORTC.F0 = 0;
 }
 }
 if(INTCON3.INT2IF){
 if(PORTC.F1 == 1){
 PORTC.F1 =0;
 }else {
 PORTC.F1=1;
 }
 }
 INTCON3 = 0b00011000;
}


void main(){
 char keypressed;
 int i=0x41;
 keypressed=my_read_keypad();
 TRISB=0x0F;


 if(keypressed='5'){
 TRISC =0x00;
 PORTC.F1 = 1;

 PORTC.F0 = 0;


 INTCON = 0b11010000;
 INTCON3 = 0b00011000;
 RCON =0x80;

 Lcd8_Config(&PORTE, &PORTD, 2,1,0, 7,6,5,4,3,2,1,0);
 Lcd8_Cmd(LCD_CURSOR_OFF);
 Lcd8_Cmd(LCD_CLEAR);

 Lcd8_Out(1, 1, "5o Erwtima");
 while (1){
 Lcd8_Chr(2,5, i);
 i++;
 if (i>0x5A) i=0x41;
 }

 }

 }
