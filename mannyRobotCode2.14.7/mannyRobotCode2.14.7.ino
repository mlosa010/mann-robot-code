#include "RelayBoard.h"  //including the header file that was made


int decidingAlgo (int reading);

int unswitchedArray[5];
int switchedArray[5];
int finalArray[5];
int intermidiatearray[5]; //array holding the buble sorted values
int x=0;
int n=0;
int z=0;
int k=0;
int j=0;
int intermidiateprint= 0;
int storingIntermidiateArray =0;
int gettingFinalArray=0;
int count;
int temp;

RelayBoard relays(3, 4, 5, 6, 7,8);  // what relay numbers will be used

struct values {          //a group of variables asigned to one block of memory
    uint8_t pins[5];     //asigns pins in an array [] to have a width of 8 bits and be positive only
    uint16_t values[5];  ////asigns pins in an array [] to have a width of 16 bits and be positive only
    uint8_t code[5];
} readings = { .pins = { A0, A1, A2, A3, A4 }};  //defines what pins are used for readings

void read_value(uint8_t pin, struct values *v, RelayBoard *r);  //setting what will be read?

void setup()  //the setup for the program
{
    Serial.begin(9600);  // denotes what data rate in bits per second
}

void loop()  //the infinite loop 
{
  while(x<1){
    for (int i = 0; i < RelayBoard::PINS; i++) {  //the begining of the for loop dets i to n integer
        relays.select(i); //select the relays that are enabled( does it cycle threw here?)
        delay(3000);  //pauses code for 3 seconds
        read_value(i, &readings, &relays); //(enter the value from the pins struct?)
        Serial.print("Reading from ");  //prints the comment in serial data printout
        Serial.print(i);   //prints what i it is currently on from the struct
        Serial.print(": ");  //prints the ":" for the reading
        Serial.println(readings.values[i] * (5.0/1023.0));  //Prints the valueof the reading from a pin then changes it to volts
        unswitchedArray[i]=readings.values[i];
        intermidiatearray[i] = decidingAlgo(unswitchedArray[i]);
        
        x=1;
    }
    
    }
    while(n<1){
    Serial.println("");  
    Serial.println(unswitchedArray[0]);
    Serial.println(unswitchedArray[1]);
    Serial.println(unswitchedArray[2]);
    Serial.println(unswitchedArray[3]);
    Serial.println(unswitchedArray[4]);
    n=1;
    }
}





void read_value(uint8_t pin, struct values *v, RelayBoard *r)  //reads the values again?
{
    r->select(pin); //selects pins 
    v->values[pin] = analogRead(v->pins[pin]); 
}

int decidingAlgo(int result){
  
  if(result<=1014){
    relays.switchpolarity();
    
    if (result<= 50){
      result = 3;
    }
    else if(result>=50){
      result=5;
    }
  }

  if((result<=720)&&(result<=710)){
    result=2;
  }

  if ((result<=180)&&(result>=175)){
    result=1;
  }
  if ((result<=285)&&(result>=279)){
    result=5;
  }
  
return result;
}


  //Diode = 1.38  code 5
  //Resistor = 3.5  code 2
  //Inductor = 1.27  code 4
  //Capasitor = 5    code 3
  //wire = .87    code 1
