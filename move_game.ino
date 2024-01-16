#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Player.h"



char screen[4][20] = {
  {'@',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ','C',' ',' ',' ',' ',' ',' ',' ','U',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};


const byte ROWS = 4; 
const byte COLS = 4; 

const char hexaKeys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','x'},
  {'*','0','#','/'}
};

const byte rowPins[ROWS] = {11, 10, 9, 8};  
const byte colPins[COLS] = {4, 3, 2, 0};  
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char U = '2';
char D = '8';
char R = '6';
char L = '4';

char last = ' ';

LiquidCrystal_I2C lcd(0x27,20,4);  

void setup()
{
  lcd.init();             
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("world");
  Player player;
}

  
void loop(){
  char k = customKeypad.getKey();
  
  player.setPos();
  
  
  if (k == U || k == D || k == R || k == L){
    last = k;
  }
  
  if (k == U && player.py>0) {setPos(player.px, player.py-1);} // up
  if (k == D && player.py<3) {setPos(player.px, player.py+1);} // down
  
  if (k == R && player.px<19){setPos(player.px+1, player.py);} // right 
  if (k == L && player.px>0) {setPos(player.px-1, player.py);} // left
  
  if (k =='+'){cleave(player.px,player.py);}
  
  print();


} // loop


void cleave(int x, int y){
  if (last == U){
    if (y > 0){
      if (x<19){screen[player.py-1][player.px+1] = '#';}
      print();
      screen[player.py-1][player.px+1] = ' ';
      screen[player.py-1][player.px] = '#';
      print();
      screen[player.py-1][player.px] = ' ';
      if (x>0){screen[player.py-1][player.px-1] = '#';}
      print();
      screen[player.py-1][player.px-1] = ' ';
    }
  }
  if (last == D){
    if (y < 3){
      if (x>0){screen[player.py+1][player.px-1] = '#';}
      print();
      screen[player.py+1][player.px-1] = ' ';
      screen[player.py+1][player.px] = '#';
      print();
      screen[player.py+1][player.px] = ' ';
      if (x<19){screen[player.py+1][player.px+1] = '#';}
      print();
      screen[player.py+1][player.px+1] = ' ';
    }
  }
  if (last == R){
    if (x < 19){
      if (y>0){screen[player.py-1][player.px+1] = '#';}
      print();
      screen[player.py-1][player.px+1] = ' ';
      screen[player.py][player.px+1] = '#';
      print();
      screen[player.py][player.px+1] = ' ';
      if(y<3){screen[player.py+1][player.px+1] = '#';}
      print();
      screen[player.py+1][player.px+1] = ' ';
    }
  }
  if (last == L){
    if (x > 0){
      if (y>0){screen[player.py-1][player.px-1] = '#';}
      print();
      screen[player.py-1][player.px-1] = ' ';
      screen[player.py][player.px-1] = '#';
      print();
      screen[player.py][player.px-1] = ' ';
      if (y<3){screen[player.py+1][player.px-1] = '#';}
      print();
      screen[player.py+1][player.px-1] = ' ';
    }
  }
}
void print(){
  for (int y = 0; y < 4; y++){
    for (int x = 0; x < 20; x++){
      lcd.setCursor(x,y);
      lcd.print(screen[y][x]);
    } // x
  } // y 
}