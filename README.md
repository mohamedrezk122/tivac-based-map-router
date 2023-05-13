# GPS-Tracking-System

Our project consists of three main components:
1.	TM4C123GH6PM microcontroller
2.	Ublox NEO-6m GPS Module
3.	Trajectory Plotter web python based app


## Team Members

Names | id
----- | ----
Mahmoud Mohamed Mahmoud Ahmed | 2001261
Kareem Amr Mohamed Soliman |2001033
Mahmoud Mohamed Ali Soliman  | 2001866
Mohamed Ahmed Samir Amin | 2001876
Mohamed Yaser Elsaid | 2001226
Yousef Mohamed Ibrahim Mohamed | 2001496
Mohamed Mahmoud Rezk | 2002114
Abdalrahman Esaam Mohamed Elemam Elemam | 1900771

## Usage 

**LINUX platforms**

- First, download the tivaware (either the full SDK version or TM4c123gxl) from [here](https://www.ti.com/tool/SW-TM4C), this step requires TI account.

- Clone the project to your local machine
 ``` bash
git clone https://github.com/mohamedrezk122/tivac-based-map-router
 ```

- Follow this [tutorial](https://www.hackster.io/tcss/upload-code-to-ti-tm4c123-using-linux-cmake-and-lm4tools-c33cec) on how to setup lm4tools( for flashing binaries to the board), and tivaware.

- Open terminal in project directory and execute the following commands
``` bash
mkdir build
cmake ..
make 
sudo make flash   
```
