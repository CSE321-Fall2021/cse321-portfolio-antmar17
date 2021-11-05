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
    1.Event Queue
        Allows atomic operations of events and is used to counteract bounce
    
    2.Ticker 
        Allows for consistent interrupt operations to be executed in a given interval

    3.InterruptIn
        This creates a reference to an interrupt with a variable name to allow additional interaction. This interrupt is triggered by the button, with actions on both rise and fall of the signal. 
        There are methods to configure the interrupt, specifically: rise and fall

    4. Ticker 
        This creates an ISR that is called on a set interva given in the second paramater.


----------
Declarations
----------
CSE321_project1_arfelici_main.cpp:
    -queue:
     Type: EventQueue
     Purpouse: allows atomic operations of function calls        

    -column1:
        Type: InterruptIn
        Purpouse: allows for Interrupts to be called on given port            
    
    -mainTicker;         
        Type: Ticker 
        Purpouse: Tiicker object for the main loop that controls row power

    -TimerTicker:
        Type: Ticker 
        Purpouse: Ticker object to keep track of time
    
    - TimeLeft
        Type: int 
        Purpouse: represents time left in seconds
    
    - TimerActive
        Type: bool
        Purpouse: state variable for timer
    
    -rowNum
        Type:int
        Purpouse:represent row number that is being powered
    
    -lcdObj
        Type:CSE321_LCD
        Purpouse: LCD object to control LCD functions 


----------
Custom Functions
----------

CSE321_project2_arfelici_main.cpp:
    -void main_loop():
        -Type:void 
        -Purpouse: main loop to be put in main ticker.Powers rows
    
    -void initialize_registers():
        -Type: void
        -Purpouse: Activates registers clocks and put outputs and inputs into appropraite configuration
    
    -void handle_button_pressed(int row):
        -Type:void 
        -Purpouse: sub routine to handle all button presses
    
    -void handle_timer():
        -Type:void
        -Purpouse:
    
    -void get_user_input():
        -Type: void 
        -Purpouse: gets the user input of minutes and seconds via the scanf function 
    
    -void start_timer():
        -Type: void 
        -Purpouse: Starts the timer

    -void stop_timer():
        -Type: void
        -Purpouse: starts the timer

    -char *concat(const char *s1, const char *s2):
        -Type: char*
        -Purpouse: concatenates two strings

    -void row1(bool on):
        -Type: void
        -Purpouse: turns on row1

    -void row2(bool on):
        -Type:void
        -Purpouse: turns on row2

    -void row3(bool on):
        -Type:void
        -Purpouse:turns on row3

    -void blink1(bool on):
        -Type: void
        -Purpouse: turns on first blinker light

    -void blink2(bool on):
        -Type: boid
        -Purpouse: turns on second blinker light
