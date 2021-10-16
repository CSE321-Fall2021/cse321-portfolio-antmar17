-------------------
About
-------------------
Project Description: 
    
    Project 2 for CSE 321 at the University at Buffalo. The project main purpouse is to help 
    students understand how to interact with off board peripherals and external modules. Contains code provided by 
    Dr. Jennifer Winikus and edited by Anthony R. Feliciano.
    

Contribitor List:
    - Dr. Jennifer Winikus (jwinikus@buffalo.edu)
    - Anthony R. Feliciano (arfelici)
--------------------
Features
--------------------
    1.Running  CSE321_project1_arfelici_main.cpp will run a program in which a timer is set to a specific time chosen by the user.
    2.User can stop timer
    3.User can start timer 
    4.User can input a custom time. 

    


--------------------
Required Materials
--------------------
    -Nucleo L4R5ZI
    -Bread Board
    -Resistors(1kOhm)
    -USB A to Micro USB B cable
    -Male to Male jumper wires
    - 4 x 4 Matrix Keypad
    - 16 x 2 LCD

--------------------
Resources and References
--------------------
    - RM0432 Reference Manuel :https://www.st.com/resource/en/reference_manual/rm0432-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
    - MbedOS documentation: https://os.mbed.com/docs/mbed-os/v6.15/introduction/index.html

--------------------
Getting Started
--------------------
    This section will describe the general setup


    1. Attach your laptop to the NUCLEO-L4R5ZI via the USB A to Micro USB B cable
    2. Attach a resistor to the bread board with one part on the negative portion and one on the positive
    3. Using male to male jumper  connect one pin in the breadboard and one pin into all the outputs and input pins(as shown in 5.16 of the RM0432 Manual)
    4. Open Mbed Studio
    5. Open Project2/CSE321_project2_arfelici_main.cpp
    6. Set the target to your connect NUCLEO-L4R5ZI
    8. Press the Run button on the left hand side of the screen

--------------------
Files
--------------------
-   CSE321_project2_arfelici_main.cpp:
    Date Created: 2021 September 30

    File Summary:
        This file contains the code to start a timer. The timer can be activated by pressing A and stopped by pressing B on the keypad. If the User were to press D 
        Then the user can input a custom time for the timer.

     Principle investigator:
        Name: Anthony R. Feliciano
        Institution: University at Buffalo, Engineering and Applied Sciences Department
        Address: Buffalo, NY 14260
        Email: arfelici@buffalo.edu
    



----------
API and Built In Elements Used
----------
API's: 
    - mbed: allows for streamlined interaction between C plus plus and the NUCLEO-L4R5ZI hardware.

Built In Elements Used:
    1.Thread
        Allows the instantiating of a thread to allow for scheduleing and priority managment. The thread is also given a function as a parameter
        to define it's behavior.
        
    2.DigitalOut
       Allows you to set up a GPIO pin as an output.

    3.InterruptIn
        This creates a reference to an interrupt with a variable name to allow additional interaction. This interrupt is triggered by the button, with actions on both rise and fall of the signal. 
        There are methods to configure the interrupt, specifically: rise and fall

    4. Ticker 
        This creates an ISR that is called on a set interva given in the second paramater.


----------
Declarations
----------
CSE321_project1_arfelici_main.cpp:
    -max_seconds:
     Type: int
     Purpouse: max amount of seconds allowed            

    -current_seconds:
        Type: int
        Purpouse: current amount of seconds allowed            
    
    -timer_active:          
        Type: bool 
        Purpouse: boolean to represent when the timer should be counting down

    -timer:
        Type: Ticker 
        Purpouse: Ticker object to keep track of time




----------
Custom Functions
----------

CSE321_project2_arfelici_main.cpp:

    -void isr_a(void):
        Type: void 
        Purpouse: onRise for A button will start the timer.
        
    -void isr_b(void):
        Type: void 
        Purpouse: onRise for B button will stop the timer.
        
    -void isr_d(void):
        Type: void 
        Purpouse: onRise for D button will take time from user.
        
    -void isr_Tick(void):
        Type: void 
        Purpouse: interval interrupt for counting down the timer value
  




