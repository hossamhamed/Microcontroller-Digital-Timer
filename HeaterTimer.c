#include <HeaterTimer.h>

 int selection;
 int initial;
 int loops;
 int toggle;
 int longPressActivated;
 
  void delay_1sec() {    
    int i;
    for(i=0;i<100;i++) {
      if (input(select) == 0) 
        break;    
      delay_ms(10);
    }    
  }
   
  void delay_1min() {
    int i;
    for(i=0;i<60;i++) {
      if (input(select) == 0) 
        break;    
      delay_1sec();
    }        
  }
   
  void delay_minutes(unsigned int v_min) {  
    int i;
    for(i=0;i<v_min;i++) {
      if (input(select) == 0) 
        break;    
      delay_1min();
    }          
  }

void beeb() {
  output_high(Buzzer);
  delay_ms(50);
  output_low(Buzzer);
}

void longBeeb() {
  output_high(Buzzer);
  delay_ms(3000);
  output_low(Buzzer);
}

void all_off() {
    output_low(LED0);
    output_low(LED1);
    output_low(LED2);
    output_low(LED3);
    output_low(LED4);              
}

void all_on() {
    output_high(LED0);
    output_high(LED1);
    output_high(LED2);
    output_high(LED3);
    output_high(LED4);              
}

void execSelection( int sel) {

        switch (sel){
          case 0:              // OFF position
            output_low(LED0);
            output_low(LED1);
            output_low(LED2);
            output_low(LED3);
            output_low(LED4);            
            output_low(Relay);            
            break;
            
          case 1:            
            output_high(LED0);
            
            output_low(LED1);
            output_low(LED2);
            output_low(LED3);
            output_low(LED4);

            output_high(Relay);
            delay_minutes(30);
            if (input(select) != 0) {
              output_low(Relay);     
              all_off();
              longBeeb();
            }  
            break;
            
          case 2:
            output_high(LED1);
            
            output_low(LED0);
            output_low(LED2);
            output_low(LED3);
            output_low(LED4);
            
            output_high(Relay);            
            delay_minutes(60);
            if (input(select) != 0) {
              output_low(Relay);   
              all_off();
              longBeeb();
            }  
            break;
            
          case 3:
            output_high(LED2);
            output_low(LED0);
            output_low(LED1);
            output_low(LED3);
            output_low(LED4);

            output_high(Relay);
            delay_minutes(90);
            if (input(select) != 0) {
              output_low(Relay);
              all_off();
              longBeeb();
            }  
            break;
            
          case 4:
            output_high(LED3);
            
            output_low(LED0);
            output_low(LED1);
            output_low(LED2);
            output_low(LED4);
            
            output_high(Relay);
            delay_minutes(120);
            if (input(select) != 0) {
              output_low(Relay);
              all_off();
              longBeeb();
            }  
            break;          
            
          case 5:
            output_high(LED4);
            
            output_low(LED0);
            output_low(LED1);
            output_low(LED2);
            output_low(LED3);
            
            output_high(Relay);
            delay_minutes(180);
            if (input(select) != 0) {
              output_low(Relay);
              all_off();
              longBeeb();
            }  
            break;                      
        }                
}


void load_selection() {
  int storedSelection;
  storedSelection = read_eeprom(50);    
  //fprintf(Debug,"Stored selection:%u \r\n",storedSelection);  
  if (storedSelection == 100) {
      all_on();
      output_high(Relay);    
  }
  else 
    execSelection(storedSelection);  
}


void main()
{

   output_b(0);
   output_a(0);
 
   selection = 0;
   initial = 1;
   loops = 0;
   toggle = 0;
   longPressActivated = 0;
   
   beeb(); // ON beeb
   
   load_selection();
   
   
   while(true)
   {
      if(input(select) == 0) {  // select button pressed
        beeb();
        do {     
          delay_ms(100);
          loops++;
          if (loops > 30) {
             if (toggle == 0) {
                all_on();
                output_high(Relay);
                toggle = 1;
                longPressActivated = 1;
                write_eeprom(50,100); // store all on
             }
             else {
                all_off();
                output_low(Relay);
                toggle = 0;
                longPressActivated = 0;
                write_eeprom(50,0); // store all on
             }
             loops = 0;
             break;
          }
            
        } while(input(select) == 0); // wait until button released
        loops = 0;
        

       selection ++;
       
       if (selection > 5)
         selection = 0;
      
      if (longPressActivated == 0) {
         //fprintf(Debug,"Selection:%u \r\n",selection);
         write_eeprom(50,selection);
         execSelection(selection);       
         
      }  
      
      
        
      }// end if
      
      
   } // end while

}
