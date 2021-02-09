#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 4, 3, 2, A4, A5);


const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
int LCDRow = 0;
int codSetat=0;
int codCorect=0;
int incercari=3;
int buttonEnter=0;
int buttonReset=0;
int buttonPinE=12;
int buttonPinR=13;
int temp;
String cod="";
String currentCode="";

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup(){
   Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.setCursor(0, 0);
   lcd.print("Setati codul:");
   pinMode(buttonPinE, INPUT);
   pinMode(buttonPinR, INPUT);
   analogReference(DEFAULT);
  	pinMode(A2, INPUT); // setarea pinului analogic A1 ca si pin de input
	digitalWrite(A2, HIGH);
}
  
void loop(){
  temp = analogRead(A2);
  Serial.println(temp);
  if (temp > 0){
    char key = keypad.getKey();
  	if (codCorect==0){
      	if (codSetat==0){
    		lcd.setCursor(0, 0);
    		lcd.print("Setati codul:");
        }
      	else{
          	lcd.setCursor(0, 0);
    		lcd.print("Introdu codul:");
      	}
  	}
  	else{
   		lcd.setCursor(0, 0);
    	lcd.print("In seif");
    	//led aprins
      
  	}
  	if (key){
    	Serial.println(key);
    	lcd.setCursor (LCDRow++, 1);
    	lcd.print(key);
    	cod = cod + char(key);
  	}
  	buttonEnter=digitalRead(buttonPinE);
  	buttonReset=digitalRead(buttonPinR);
  		if (buttonEnter==HIGH){
    		if (codSetat == 0){
      			currentCode=cod;
      			cod="";
      			codSetat=1;
      			incercari=3;
      			lcd.clear();
      			lcd.setCursor(0, 1);
      			lcd.print("Ati setat codul");
      			delay(500);
      			lcd.clear();
      			LCDRow=0;
    		}
    		else{
      			if (cod==currentCode){
        			lcd.clear();
        			lcd.setCursor(0, 1);
        			lcd.print("Cod corect");
        			delay(500);
        			lcd.clear();
        			codCorect=1;
        			incercari=3;
        			LCDRow=0;
      			}
      			else{
        			if (codCorect==0){
          				incercari--;
          				lcd.clear();
          				lcd.setCursor(0, 1);
          				lcd.print("Cod incorect");
          				delay(500);
          				lcd.clear();
          				LCDRow=0;
          				if (incercari==0){
            				lcd.clear();
            				lcd.setCursor(0, 0);
            				lcd.print("Ati blocat");
            				lcd.setCursor(0, 1);
	            			lcd.print("seiful");
                          	//buzz
                          	tone(A3, 5000, 10000);
    	        			delay(10000);
        	    			lcd.clear();
            				incercari=3;
            				LCDRow=0;
                          
                          	
          				}
        			}
        			else{
     			    	lcd.clear();
          				lcd.setCursor(0, 1);
          				lcd.print("Seif Inchis");
          				delay(500);
          				lcd.clear();
         				codCorect=0;
          				incercari=3;
          				LCDRow=0;
        			}
     			}
    		}
    	cod="";
        }
  		if (buttonReset==HIGH){
    		if (codCorect==0){
      			lcd.clear();
      			lcd.setCursor(0, 0);
      			lcd.print("Baga parola");
      			lcd.setCursor(0, 1);
      			lcd.print("prima data");
     			delay(500);
      			lcd.clear();
    		}
    		else{
      			codSetat=0;
      			codCorect=0;
      			incercari=3;
      			currentCode="";
      			lcd.clear();
      			lcd.setCursor(0, 0);
      			lcd.print("Ai resetat");
      			lcd.setCursor(0, 1);
      			lcd.print("codul");
      			delay(500);
      			lcd.clear();
    		}
  		}
  	}
  else{
    	lcd.setCursor(0, 0);
      	lcd.print("Seiful e");
      	lcd.setCursor(0, 1);
      	lcd.print("Inghetat");
      	delay(500);
      	lcd.clear();
  }
}