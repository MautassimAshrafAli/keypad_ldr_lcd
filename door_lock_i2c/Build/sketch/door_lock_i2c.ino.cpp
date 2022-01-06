#include <Arduino.h>
#line 1 "C:\\Users\\ashra\\Desktop\\dore_lock\\door_lock_i2c\\door_lock_i2c.ino"
#include <Keypad.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);

const int ldr_1 = A0 , ldr_2 = A1;
const int led_red = 13 , led_g = 12;
const int sp = 11;
int a0_val = 0;
int a1_val = 0;
String a0_a1;
int res_a0_a1 = 0;
int i = 0;

const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};
byte rowPins[rows] = {6, 5, 4, 3};
byte colPins[cols] = {9, 8, 7};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

String pass = "1a23b";
String in_c = "";

#line 32 "C:\\Users\\ashra\\Desktop\\dore_lock\\door_lock_i2c\\door_lock_i2c.ino"
void setup();
#line 51 "C:\\Users\\ashra\\Desktop\\dore_lock\\door_lock_i2c\\door_lock_i2c.ino"
void loop();
#line 117 "C:\\Users\\ashra\\Desktop\\dore_lock\\door_lock_i2c\\door_lock_i2c.ino"
void main_pass();
#line 127 "C:\\Users\\ashra\\Desktop\\dore_lock\\door_lock_i2c\\door_lock_i2c.ino"
void t_pass();
#line 137 "C:\\Users\\ashra\\Desktop\\dore_lock\\door_lock_i2c\\door_lock_i2c.ino"
void f_pass();
#line 170 "C:\\Users\\ashra\\Desktop\\dore_lock\\door_lock_i2c\\door_lock_i2c.ino"
void pass_s();
#line 205 "C:\\Users\\ashra\\Desktop\\dore_lock\\door_lock_i2c\\door_lock_i2c.ino"
void digit(char d_1 ,char d_2 ,char d_3 ,char d_4 ,char d_5 ,char d_6 ,char d_7,char d_8,char d_9,char d_10,char d_11,char d_12);
#line 32 "C:\\Users\\ashra\\Desktop\\dore_lock\\door_lock_i2c\\door_lock_i2c.ino"
void setup()
{  

   Serial.begin(9600);
   
   pinMode(led_red,OUTPUT);
   pinMode(led_g,OUTPUT);
   pinMode(ldr_1,INPUT);
   pinMode(ldr_2,INPUT);
   pinMode(sp,OUTPUT);
   
   lcd.begin();
   lcd.backlight();
   main_pass();
 
}

int switch_to_num_alph_c = 0;

void loop()
{

char key = keypad.getKey();

if(key){

   switch(key) {
   
     case '#':
        if(pass == in_c){
        
           t_pass();
           
           delay(1000);
           
           while(pass == in_c){
           
              pass_s();
              
              delay(1000);
           }
           
        }else{
        
           f_pass();
           
        }
     break;
     
     case '*':
     
     
     switch_to_num_alph_c ++;
         
     switch(switch_to_num_alph_c) {
     case 1 :
     
          digit('a','b','c','d','e','f','g','h','i','*','j','#');
          
     break;
     
    case 2 :
     
          digit('1','2','3','4','5','6','7','8','9','*','0','#');
          
          switch_to_num_alph_c = 0;
          
     break;
     }
     
  
     break;
     
     default:
     
       lcd.write(key);
       in_c += key;
     
     break;
   }

}
 
}

void main_pass(){

   noTone(sp);
   lcd.clear();
   lcd.setCursor(1,0);
   lcd.print("Insert pass");
   lcd.setCursor(1,1);
   
}

void t_pass(){

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Welcome mutassim");
   
}

int wrong_pass_c = 0;

void f_pass(){

   lcd.clear();
   lcd.setCursor(2,0);
   lcd.print("WRONG PASS");
   delay(1000);
   main_pass();
   in_c = "";
   
   wrong_pass_c++;
   while(wrong_pass_c >=3)
   {

      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("EXPIRED PASS");
      
      
      for(int i=700;i<800;i++){
            tone(sp,i);
            delay(15);
      }
      for(int i=800;i>700;i--){
             tone(sp,i);
             delay(15);
      }
      
      break;
      
   }
   
}

void pass_s(){
   
   noTone(sp);
   lcd.clear();
   
   a0_val = analogRead(A0);
   a1_val = analogRead(A1);
   a0_a1 = "A0:" + String(a0_val) + " A1:" + String(a1_val); 
   lcd.setCursor(0,0);
   lcd.print(a0_a1);
   
   res_a0_a1 = a0_val - a1_val;
   
   lcd.setCursor(12,1);
   lcd.print(String(res_a0_a1)+"  ");
    
   if(res_a0_a1 >= 0){
   
      lcd.setCursor(0,1);
      lcd.print("positive");
      digitalWrite(led_red,LOW);
      digitalWrite(led_g,HIGH);
      
   }else{
   
      lcd.setCursor(0,1);
      lcd.print("negative");
      digitalWrite(led_g,LOW);
      digitalWrite(led_red,HIGH);
      
    
   }

}

void digit(char d_1 ,char d_2 ,char d_3 ,char d_4 ,char d_5 ,char d_6 ,char d_7,char d_8,char d_9,char d_10,char d_11,char d_12){

  keys[0][0] = d_1;keys[0][1] = d_2;keys[0][2] = d_3;
  keys[1][0] = d_4;keys[1][1] = d_5;keys[1][2] = d_6;
  keys[2][0] = d_7;keys[2][1] = d_8;keys[2][2] = d_9;
  keys[3][0] =d_10;keys[3][1] =d_11;keys[3][2] =d_12;
  
}

