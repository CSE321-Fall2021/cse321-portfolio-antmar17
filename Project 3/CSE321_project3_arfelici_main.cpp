/*
 * File:  CSE321_project2_arfelici_main.cpp
 *
 * Author: Anthony R. Feliciano (arfelici@buffalo)
 * Date: 2021 December 8
 * Course: CSE 321 Embedded Systems
 * Assignment: Project 3
 *
 * Inputs: PD7,PD6,Button 1
 * Outputs: PB8,PC8
 *
 * Modules:
 *   - mbed.h
 *   - hcsr04.h
 *
 * Summary of the File:
 *
 *   This file contains the code to start a rangefinder that will set off a buzzer if an object is detected too close.
 *
 * References:
 *    - RM0432 Reference Manuel
 * :https://www.st.com/resource/en/reference_manual/rm0432-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
 *    - MbedOS documentation:
 * https://os.mbed.com/docs/mbed-os/v6.15/introduction/index.html
 *
 * Constraints:
 *   Intended to be used with a NUCLEO-L4R5ZI
 */
#include "mbed.h"
#include "hcsr04.h"
InterruptIn button1(BUTTON1);
DigitalOut led1(PC_8);



//buzzer output object
//1 means no sound
//0 means sound
DigitalOut buzzer(PB_8);


//Object for Buzzer
HCSR04 hcs(PD_7,PD_6);

//flag to toggle buzzer 
bool isOn = false;

//functions to define button1 functionality
void onButton1Rise();
void onButton1Fall();
int main()
{   
    button1.rise(onButton1Rise);
    button1.fall(onButton1Fall);
    buzzer = 1;

    //distance of nearest detected object
    long distance;

 
    

    while (true) {
        //update distance
        distance = hcs.distance();
        printf("Distance %ld cm\n",distance);
        if(isOn){
             //if object is too close set off buzzer
            if(distance < 100){
                buzzer = 0;
                led1 = 1;
            }
            else{
                buzzer = 1;
                led1 = 0;
            }
        }

    }
}


void onButton1Rise(){
    //turn led and buzzer on
    led1 = 1;
    if(isOn){
        isOn = false;
        buzzer = 1;
    }
    else{
        isOn = true;
    }
}
void onButton1Fall(){
    //turn led and buzzer
    led1 = 0;
}

