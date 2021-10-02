/*
* File:  CSE321_project1_arfelici_corrected_code.cpp
*
* Author1:Dr. Jennifer Winikus (jwinikus@buffalo.edu)
* Author2: Anthony R. Feliciano (arfelici@buffalo)
* Date: 2021 September 30
* Course: CSE 321 Embedded Systems
* Assignment: Project 1
*
* Inputs: Pin PC_13
* Outputs: Pin PB_7
* 
* Modules: 
*   - mbed.h
*
* Summary of the File:
*
*   This file contains the reformatted and recommented code of p1_code_provided.cpp written by Dr.Jennifer Winikus.
*   Both this file and p1_code_provided have the same functionality. They both have an input button on PC_13 and an output LED on PB_7.
*   The output LED stops and starts blinking when the button is pressed. This file is simply reformatted and with more helpful comments.
*
* References:
*    - RM0432 Reference Manuel :https://www.st.com/resource/en/reference_manual/rm0432-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
*    - MbedOS documentation: https://os.mbed.com/docs/mbed-os/v6.15/introduction/index.html
*
* Constraints:
*   Intended to be used with a NUCLEO-L4R5ZI
*/

#include "mbed.h"


//Function initializations
void initHandler();
void onRise(); 
void onFall();

Thread controller;              // Create a thread to drive an LED to have an on time of 2000ms and off time 500ms

DigitalOut blueLED(LED2);       // establish blue led as an output
InterruptIn button1(BUTTON1);   //establish button 1 as an input 

//states for button 1
int button1Pressed = 0;         //0 for not pressed and 1 for pressed
int ledFlashing = 0;            //0 for flashing and 1 for not flashing

int 
main() {
    // start the allowed execution of the thread
    printf("----------------START----------------\n");
    printf("Starting state of thread: %d\n", controller.get_state());
    controller.start(initHandler);  //init controller thread
    printf("State of thread right after start: %d\n", controller.get_state());  
    button1.rise(onRise);           //attach onRise function to button 1 
    button1.fall(onFall);           //attach onFall function to button 1
    return 0;
}

/* 
* This function defines the behavior of the controller thread initiated in the main function.
* When the ledFlashing state is 0 it make the output blueLED flash
*  
*/
void 
initHandler() {
    while (true) {
        //if flashing is enabled
        if(ledFlashing == 0){
            blueLED = !blueLED;         //Toggle LED light
            printf("Toggle LED"); 
            thread_sleep_for(2000);     //Sleep for 2000 miliseconds
            blueLED = !blueLED;         //Toggle LED light
            printf("Toggle LED"); 
            thread_sleep_for(500);      //Sleep for 500 miliseconds
        }
    }
}

/*
* This function toggles the buttonPressed state of Thread allowing the onFall function to activate
*/
void 
onRise() {
    button1Pressed = 1;                 // set button state to pressed
}

/*
*
* This function defines the controller Threads behavior on Fall.
* Toggles LED flashing state to allow the controller Thread to flash the light.
* 
*/
void 
onFall() {
    //if button was pressed , toggle LED flashing state
    if (button1Pressed == 1){
        ledFlashing++;          //increment ledFlashing state 
        ledFlashing %= 2;       //take mod of 2 so that the state's max value is 1    					    
        button1Pressed = 0;     //switch pressed state back to zero	
    }
}