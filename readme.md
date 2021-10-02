-------------------
About
-------------------
Project Description: 
    
    Project 1 for CSE 321 at the University at Buffalo. The project main purpouse is to help 
    students understand how to document and write code in a proffesional manner.As well as 
    practice good coding and project planning practices. Contains code provided by 
    Dr. Jennifer Winikus and edited by Anthony R. Feliciano.
    

Contribitor List:
    - Dr. Jennifer Winikus (jwinikus@buffalo.edu)
    - Anthony R. Feliciano (arfelici)
--------------------
Features
--------------------
    1.Running either CSE321_project1_arfelici_corrected_code.cpp or p1_code_provided.cpp through Mbed Studio, will initiate a program that
    allows the user to toggle the flashing of an output LED on pin PB_7 by using an input button on pin PB_15 
    while connected to a NUCLEO-L4R5ZI.

    2. CSE321_project1_arfelici_template.cpp has a header comment that will be used to document future code.


--------------------
Required Materials
--------------------
    -Nucleo L4R5ZI
    -Bread Board
    -Resistors(1kOhm)
    -USB A to Micro USB B cable
    -Male to Male jumper wires

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
    3. Using male to male jumper  connect one pin in the breadboard and one pin into CN11 pin 23  and CN11 pin 21 (as shown in 5.16 of the RM0432 Manual)
    4. Open Mbed Studio
    5. Open Project1/CSE321_project1_arfelici
    6. Set the target to your connect NUCLEO-L4R5ZI
    7. Open CSE321_project1_arfelici_corrected_code
    8. Press the Run button on the left hand side of the screen

--------------------
Files
--------------------
- p1_code_provided.cpp:
    Date Created: 2021 September 30

    File Summary:
        This file contains the code give by Dr. Jennifer Winikus. The file's main purpouse is to allow a user to flash a LED light on pin 
        PB_7 and use a button to toggle this flashing LED that is on pin PB_15. The code also has many formatting errors put in place intentionally by
        Dr. Jennifer Winikus in order for her students to fix in the corresponding file CSE321_project1_arfelici_corrected_code.cpp. 

     Principle investigator:
        Name: Anthony R. Feliciano
        Institution: University at Buffalo, Engineering and Applied Sciences Department
        Address: Buffalo, NY 14260
        Email: arfelici@buffalo.edu
    

- CSE321_project1_arfelici_template.cpp:
    Date Created: 2021 September 30

    File Summary:
        This file acts as a sample code template to use for future documentation. 
        This is used in part 3 of Project 1 for the clas CSE 321 at the University at Buffalo

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
----------
Declarations
----------
CSE321_project1_arfelici_corrected_code.cpp:
    -controller:
        Type:Thread              
        Purpouse: Instantiates a thread to drive an LED to have an on time of 2000ms and off time 500ms

    -blueLED(LED2):
        Type:DigitalOut        
        Purpouse:Establish blue led on pin PB_7 as an output

    -button1(BUTTON1):
        Type:InterruptIn
        Purpouse: Establish button 1 as an input on pin PB_15 

    -button1Pressed:
        Type: int
        Purpouse: value that symbolizes when Button 1 is being pressed (0 for not pressed and 1 for pressed)

    -ledFlashing:
        Type: int
        Purpouse: value that symbolizes when the LED is flashing and when it isn't (0 for flashing and 1 for not flashing)

p1_code_provided.cpp:
    -controller:
        Type:Thread              
        Purpouse: Instantiates a thread to drive an LED to have an on time of 2000ms and off time 500ms

    -fire(LED2):
        Type:DigitalOut        
        Purpouse:Establish blue led on pin PB_7 as an output

    -cherish(BUTTON1):
        Type:InterruptIn
        Purpouse: Establish button 1 as an input on pin PB_15 

    -unicorn:
        Type: int
        Purpouse: value that symbolizes when Button 1 is being pressed (0 for not pressed and 1 for pressed)

    -zombie:
        Type: int
        Purpouse: value that symbolizes when the LED is flashing and when it isn't (0 for flashing and 1 for not flashing)

CSE321_project1_arfelici_template.cpp:
    None

----------
Custom Functions
----------

CSE321_project1_arfelici_corrected_code.cpp:
    -InitHandler:
        Input:None
        Output:Void              
        Purpouse: 
            Defines the logic of the controller thread which is to toggle the blinking LED

    -onRise:
        Input:None
        Output:Void              
        Purpouse: 
            This function toggles the buttonPressed state of Thread allowing the onFall function to activate
            

    -onFall:
        Type:InterruptIn
        Purpouse: 
            This function defines the controller Threads behavior on Fall. 
            Toggles LED flashing state to allow the controller Thread to flash the light.

CSE321_project1_arfelici_corrected_code.cpp:
    -saveTheWorld:
        Input:None
        Output:Void              
        Purpouse: 
            Defines the logic of the controller thread which is to toggle the blinking LED

    -live_or_die:
        Input:None
        Output:Void              
        Purpouse: 
            This function toggles the buttonPressed state of Thread allowing the onFall function to activate
            

    -wrong_or_not:
        Type:InterruptIn
        Purpouse: 
            This function defines the controller Threads behavior on Fall. 
            Toggles LED flashing state to allow the controller Thread to flash the light.



