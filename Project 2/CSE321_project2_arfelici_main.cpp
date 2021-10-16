/*
* File:  CSE321_project2_arfelici_main.cpp
*
* Author1:Dr. Jennifer Winikus (jwinikus@buffalo.edu)
* Author2: Anthony R. Feliciano (arfelici@buffalo)
* Date: 2021 October 12
* Course: CSE 321 Embedded Systems
* Assignment: Project 2
*
* Inputs: Pin PC_13,PC_8,PC_6
* Outputs: Pin PB_8
* 
* Modules: 
*   - mbed.h
*
* Summary of the File:
*
*   This file contains the code to start a timer. The timer can be activated by pressing A and stopped by pressing B on the keypad. If the User were to press D 
*   Then the user can input a custom time for the timer.
*
* References:
*    - RM0432 Reference Manuel :https://www.st.com/resource/en/reference_manual/rm0432-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
*    - MbedOS documentation: https://os.mbed.com/docs/mbed-os/v6.15/introduction/index.html
*
* Constraints:
*   Intended to be used with a NUCLEO-L4R5ZI
*/


#include "mbed.h"
#include <iostream>


//function declarations
void isr_a(void);
void isr_b(void);
void isr_d(void);
void isr_Tick(void);
void tick(void);




int max_seconds = 599;              //max amount of seconds allowed 
int current_seconds = max_seconds;      
bool timer_active = false;          //boolean to represent when the timer should be counting down
Ticker timer;
DigitalOut name(LED2);

int main()
{   RCC->AHB2ENR |= 0x4;        //activate Peripheral clock on port C
    
    //set pin 8 to output mode
    GPIOC->MODER |= 0x10000;    
    GPIOC->MODER &= ~(0x20000);
   
    while (true) {
        GPIOC->ODR |= 0x100;
     
    }
    return 0;
}

//Function to attach to timer, going to be called as an interrupt every one second
void tick(void){
    if(timer_active){
        if(current_seconds > 0){
            current_seconds -= 1;       //decrease timer value
        }
        else{
            current_seconds = max_seconds;
            timer_active = false;        //deactivate timer
        }
    }
}


void isr_a(void){
    //TODO:implement on pressed a
    if(timer_active){
        timer.detach();             //detatch the ticker function
        timer_active = false;       //flip boolean to deative unintentional ticking
    }
}
void isr_b(void){
    //TODO:implement on pressed b
      if(timer_active){
        timer.detach();             //detatch the ticker function
        timer_active = false;       //flip boolean to deative unintentional ticking
    }
}


//This function asks the user for an input  
void isr_d(void){
    int  minutes;                                           //stores minute
    cout << "Type in the amount of minutes: ";              // Type a number and press enter
    cin >> minutes;                                         // Get user input from the keyboard
    cout << "Type in the amount of seconds: " << minutes;

    int seconds;                                            //stores seconds
    cout << "Type in the amount of seconds: ";              // Type a number and press enter
    cin >> seconds;                                         // Get user input from the keyboard
    cout << "Type in the amount of seconds: " << seconds;

    int seconds_to_add = ((minutes * 60) + seconds);
    
    //599 is 9 minutes and 59 seconds which is the maximum amount of times 
    if(seconds_to_add > 599){
        cout<<"The maximum amount is 9 minutes and 59 seconds";
    }
    else{
        max_seconds = seconds_to_add;               //set time given by users
        current_seconds = max_seconds;              //set current seconds to new 
        timer.attach(&tick,1);
        timer_active = true;
    }
    
}






