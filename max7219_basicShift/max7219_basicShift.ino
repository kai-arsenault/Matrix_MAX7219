#include <Max7219Matrix.h>
#include <avr/pgmspace.h>

int data = 8;    // DIN pin of MAX7219 module
int load = 9;    // CS pin of MAX7219 module
int clock = 10;  // CLK pin of MAX7219 module

int maxInUse = 4;    //number of LED matricies

Max7219Matrix m(data, load, clock, maxInUse); // define 

byte buffer[10];


char string1[] = " A B C D E F G H I J K L M N O P Q R S T U V X W Y Z ";
char string2[] = " a b c d e f g h i j k l m n o p q r s t u v x w y z ";
char string3[] = " 1 2 3 4 5 6 7 8 9 0 - = ";
char string4[] = " ! @ # $ % ¨ & * ( ) _ + ";
char string5[] = " ' , . ; ~ ] ´ [ | < > : ^ } ` { / ?  ";
char hello[] = " Hello, welcome back. ";




void setup(){
  m.init(); // module initialize
  m.setIntensity(0); // dot matix intensity 0-15
  Serial.begin(9600); // serial communication initialize
}

void loop(){
  /*
  // this is the code if you want to entering a message via serial console
  while (Serial.available() > 0){
    byte c = Serial.read();
    Serial.println(c, DEC);
    printCharWithShift(c, 100);
  }
  delay(100);
  m.shiftLeft(false, true);
  */
  
  printStringWithShift(hello, 50);

}

void printCharWithShift(char c, int shift_speed){
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7*c, 7);
  m.writeSprite(32, 0, buffer);
  m.setColumn(32 + buffer[0], 0);
  
  for (int i=0; i<buffer[0]+1; i++) 
  {
    delay(shift_speed);
    m.shiftLeft(false , false);
  }
}

void printStringWithShift(char* s, int shift_speed){
  while (*s != 0){
    printCharWithShift(*s, shift_speed);
    s++;
  }
}

void printString(char* s)
{
  int col = 0;
  while (*s != 0)
  {
    if (*s < 32) continue;
    char c = *s - 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(col, 0, buffer);
    m.setColumn(col + buffer[0], 0);
    col += buffer[0] + 1;
    s++;
  }
}
