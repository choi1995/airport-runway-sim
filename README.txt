CPSC 221 Project 1 (2017)

Group Members:
William Choi
	- CPSC ID: x4a9
	- Student Number: 36643138
Ruishen Lu
	- CPSC ID: a1x8
	- Student Number: 49334139

**************************************************************************************

Comments:
Average Waiting Time was calculated by dividing the wait time of each plane that have either landed/taken off by the total number of planes that have either landed/taken off.

Note that the average wait time could be small in the case that very few planes ever got the chance to hit the runway. This is quite often the case for planes waiting to take off when the landing queue is full.

**************************************************************************************

INSTRUCTIONS:
1) LQueue_drivier.C contains the methods we’ve used to test both part 1 and part 2 of the project.  

LQueue_driver.C : The main C++ file. Used primarily to test the LQueue and the AirportSim classes.
LQueue.C : Linked list queue implementation. Includes move_to_front and merge_two_queues methods.
LQueue.h : header file for the linked list queue ADT.
AirportSim.C : The class that implements the airport runway simulation. Randomly adds planes to the landing and the takeoff queue.  Randomly creates emergency requests, which utilizes the move_to_front function.
The “run” method is used to run the simulation.
AirportSim.h : The header file for the AirportSim class.
