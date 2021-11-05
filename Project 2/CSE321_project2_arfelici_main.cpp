/*
 * File:  CSE321_project2_arfelici_main.cpp
 *
 * Author1:Dr. Jennifer Winikus (jwinikus@buffalo.edu)
 * Author2: Anthony R. Feliciano (arfelici@buffalo)
 * Date: 2021 October 12
 * Course: CSE 321 Embedded Systems
 * Assignment: Project 2
 *
 * Inputs: PC_8,PB_8,PB_9
 * Outputs: Pin PC_11,PC_10,PC_9,PC_5,PC_4,
 *
 * Modules:
 *   - mbed.h
 *
 * Summary of the File:
 *
 *   This file contains the code to start a timer. The timer can be activated by
 * pressing A and stopped by pressing B on the keypad. If the User were to press
 * D Then the user can input a custom time for the timer.
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
#include "1802.h"
#include "mbed.h"
#include "mbed_events.h"
#include "rtos.h"
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

// function initializers
void main_loop();
void initialize_registers();
void handle_button_pressed(int row);
void handle_timer();
void get_user_input();
void start_timer();
void stop_timer();
char *concat(const char *s1, const char *s2);
void row1(bool on);
void row2(bool on);
void row3(bool on);
void blink1(bool on);
void blink2(bool on);

// event queue data structure to synchronize actions and mediate bounce
EventQueue queue(32 * EVENTS_QUEUE_SIZE);

// Interrupt in to represent the column of buttons
InterruptIn column1(PC_8, PullDown);

// Ticker object to handle main loop
Ticker mainTicker;

// Timer ticker to handle the behavior of the timer
Ticker TimerTicker;

// amount of time in seconds left
int TimeLeft = 0;
// state variable to tell when the timer is active or not
bool TimerActive = false;
// integer variable to tell what row is currently beinig powered
int rowNum = 0;
// LCD object to set up and control the LCD screen
CSE321_LCD lcdObj(16, 2, LCD_5x10DOTS, PB_9, PB_8);

int main() {
  // initialize lcd
  lcdObj.begin();
  initialize_registers();
  // add ticker events to EventQueue for main loop and Timer
  mainTicker.attach(queue.event(main_loop), 0.07);
  TimerTicker.attach(queue.event(handle_timer), 1);
  column1.rise(queue.event(handle_button_pressed, rowNum));

  // continuously call events attached to tickers
  queue.dispatch_forever();
  return 0;
}


/*
*Handles power of rows and passing row number to column
*/
void main_loop() {
  // pass row number to column 1's rise handler
  column1.rise(queue.event(handle_button_pressed, rowNum));
  if (rowNum == 0) {
    row1(true);
    row2(false);
    row3(false);
  } else if (rowNum == 1) {
    row1(false);
    row2(true);
    row3(false);
  } else if (rowNum == 3) {
    row1(false);
    row2(false);
    row3(true);
  }
  //Increment row Num
  rowNum += 1;
  rowNum %= 4;
}

/*
* Initializes registers
*/
void initialize_registers() {
  // initialize clock for ports C and B
  RCC->AHB2ENR |= 0x6;
  // Put pins PC_11,PC_10,PC_9,PC_5 and PC_4in ouput mode
  // 0101 0100 0000 0101 0000  0000
  GPIOC->MODER |= 0x540500;
  // 1010 1000 0000 1010 0000  0000
  GPIOC->MODER &= ~(0xA80A00);
}

/**   controls pin power
 *   @param on boolen to decide wheather pin is on or off
 */
void row1(bool on) {
  if (on) {
    GPIOC->ODR |= 0x800;
  } else {
    GPIOC->ODR &= ~(0x800);
  }
}

/**   controls pin power
 *   @param on boolen to decide wheather pin is on or off
 */
void row2(bool on) {
  if (on) {
    // 0000 0000 0000 0100 0000  0000
    GPIOC->ODR |= 0x400;
  } else {
    GPIOC->ODR &= ~(0x400);
  }
}


/**   controls pin power
 *   @param on boolen to decide wheather pin is on or off
 */
void row3(bool on) {
  if (on) {
    // 0000 0000 0000 0010 0000  0000
    GPIOC->ODR |= 0x200;
  } else {
    GPIOC->ODR &= ~(0x200);
  }
}

/**   controls pin power
 *   @param on boolen to decide wheather pin is on or off
 */
void blink1(bool on) {
  // 0000 0000 0000 0010 0001  0000

  if (on) {
    GPIOC->ODR |= 0x10;
  } else {
    GPIOC->ODR &= ~(0x10);
  }
}


/**   controls pin power
 *   @param on boolen to decide wheather pin is on or off
 */
void blink2(bool on) {
  // 0000 0000 0000 0000 0010  0000
  if (on) {
    GPIOC->ODR |= 0x20;
  } else {
    GPIOC->ODR &= ~(0x20);
  }
}
/**   Concatenates two strings
 *   @param s1 String 1
 *   @param s2 string 2
 *   @return concatenated string consisting of s1 and s2
 */
char *concat(const char *s1, const char *s2) {
  // allocate memory for both strings
  char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1);

  // perform copy operation on alllocated memory
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

/**
 *  Sub routine to handle the behavior of the timer.
*/
void handle_timer() {
  if (TimerActive && TimeLeft > 0) {
    // decrement time variable
    TimeLeft -= 1;
    int m, s;
    // convert time left to appropriate minutes and seconds
    m = (TimeLeft / 60);
    s = (TimeLeft - (m * 60));
    const char *output = "Time Left: ";

    // convert integers to c++ strings
    std::string tmpm = std::to_string(m);
    std::string tmps = std::to_string(s);

    // convert c++ strings to c strings
    char const *m_char = tmpm.c_str();
    char const *s_char = tmps.c_str();

    // concat minutes and seconds to final output string
    output = concat(output, m_char);
    output = concat(output, ":");
    output = concat(output, s_char);

    // print on serial amount of time remaining
    printf("Time Remaining:%d minutes %d seconds\n", m, s);

    // clear lcd and output current time
    lcdObj.clear();
    lcdObj.print(output);
    free((void*)output);

  } else if (TimerActive && TimeLeft == 0) {
    // alert user that times up on terminal
    printf("Times Up!\n");
    lcdObj.clear();
    lcdObj.print("Times Up!");
    // deactivate timer
    TimerActive = false;

    // turn on lights to indicate that time has been reached
    blink1(true);
    blink2(true);
  }
}

/*
    Function that uses scanf to get input from the user
*/
void get_user_input() {
  // variable to store user input
  int minutes, seconds;
  while (true) {
    // prompt user to enter information
    printf("Enter Amount of minutes\n");
    scanf("%d", &minutes);
    printf("Enter the amount of seconds\n");
    scanf("%d", &seconds);

    // time conversion in case user inputs more than 60 seconds
    int totalTime = (minutes * 60) + seconds;

    // check for invalid times
    if (totalTime <= 599 && totalTime >= 0) {
      printf("Time Entered!\n\n");
      TimeLeft = totalTime;
      break;
    }
    printf(
        "Max time is 9 minutes and 59 seconds please enter a valid time!\n\n");
  }
}

/*
    Function that starts the timer
*/
void start_timer() {

  if (!TimerActive && TimeLeft > 0) {

    // alert user that timer has started
    printf("Timer started!\n");
    //turn off finished lights
    blink1(false);
    blink2(false);

    // turn on timer
    TimerActive = true;
  } else {
    // alert user that there is no time entered
    printf("Please input a time!\n");
  }
}

/*
    Function that stops the timer
*/
void stop_timer() {
  if (TimerActive) {
    // Turn off timer
    TimerActive = false;
  }
}

/**
 *  function that handles what happens when the user presses a button
 *  @param row inter that represent the row that was being powered when the
 * function was called
 */
void handle_button_pressed(int row) {
  // if A pressed
  if (row == 0) {
    start_timer();
    // if B pressed
  } else if (row == 1) {
    printf("B pressed\n");
    stop_timer();
    // if D pressed
  } else if (row == 3) {
    get_user_input();
  }
}