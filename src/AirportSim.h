//
//  AirportSim.hpp
//  Airport-Simulator
//
//  Created by WilliamChoi on 2017-01-28.
//  Copyright © 2017 William Choi. All rights reserved.
//

#ifndef AirportSim_h
#define AirportSim_h

#include <iostream>
#include "LQueue.h"
using namespace std;

class AirportSim
{
public:
    /********* Constructors *********/
    AirportSim();
    /*-----------------------------------------------------------------------
     Construct an AirportSim object.
     
     Precondition:  None.
     Postcondition: tland, ttake, landingRate, simDuration, and takeoffRate are initialized to
     the default value of -1.
     -----------------------------------------------------------------------*/
    
    AirportSim(int tland, int ttake, int landingRate, int simDuration, int takeoffRate);
    /*-----------------------------------------------------------------------
     Construct a AirportSim object.
     
     Precondition:  tland - time it takes to land, ttake - time it takes to takeoff, 
     landingRate - number of planes landing per hour, takeoffRate - number of planes taking off per hour, 
     the duration the user wants to run the simulation for (mins)
     Postcondition: AirportSim object with tland, ttake, landingRate, simDuration, and takeoffRate initialized 
     to specified values
     -----------------------------------------------------------------------*/
    
    void run();
    /*-----------------------------------------------------------------------
     Run the airport runway simulation.
     
     Precondition:  None.
     Postcondition: Prompts the user for input parameters if they haven't been specified in the constructor. 
     Runs the simulation subsequently.
     -----------------------------------------------------------------------*/
    
private:
    int tland;
    int ttake;
    int landingRate;
    int simDuration;
    int takeoffRate;
    Queue landingQueue;
    Queue takeoffQueue;
    
    int flightNum = 1000;
    int landingQueueSize = 0;
    int takeoffQueueSize = 0;
    
    // Runway Details
    int runwayTime = 0;
    bool isLanding = false;
    int currentFlightNum = 0;
    
    // Statistics
    int totalLandingWaitingTime = 0;
    int totalTakeoffWaitingTime = 0;
    int totalPlanesLanded = 0;
    int totalPlanesTakenOff = 0;
    int maxPlanesInLandingQueue = 0;
    int maxPlanesInTakeoffQueue = 0;
    
    
    void askForParameters();
    /*-----------------------------------------------------------------------
     Prompts the user for input parameters.
     -----------------------------------------------------------------------*/
    
    void printRunwayActionComplete();
    /*-----------------------------------------------------------------------
     Prints that the landing or the takeoff has completed and the remaining planes in the queue.
     -----------------------------------------------------------------------*/
    
    void randomTrafficGenerator(const int currentTime);
    /*-----------------------------------------------------------------------
     Randomly adds planes to the landing and the takeoff queue (probability: rate/60).
     -----------------------------------------------------------------------*/
    
    void handleTraffic(const int currentTime);
    /*-----------------------------------------------------------------------
     Dequeues a plane from the queue, allowing it to land or takeoff. Landing has higher
     priority than takeoff.
     -----------------------------------------------------------------------*/
    
    void printCurrentRunwayStatus();
    /*-----------------------------------------------------------------------
     Prints the current status of the runway. (i.e. whether a plane is landing or taking off)
     -----------------------------------------------------------------------*/
    
    void generateStats();
    /*-----------------------------------------------------------------------
     Calculate and print statistics associated with the simulation.
     -----------------------------------------------------------------------*/
    
    void printBanner();
    /*-----------------------------------------------------------------------
     Prints a nice looking banner for the application
     -----------------------------------------------------------------------*/
    
    void randomEmergencyLanding(const int flightNum);
    /*-----------------------------------------------------------------------
     Randomly creates an emergency landing request. If a request is received, a plane will be 
     moved to the front of the landing queue.
     -----------------------------------------------------------------------*/

    void randomEmergencyTakeoff(const int flightNum);
    /*-----------------------------------------------------------------------
     Randomly creates an emergency takeoff request. If a request is received, a plane will be
     moved to the front of the takeoff queue.
     -----------------------------------------------------------------------*/
};


#endif /* AirportSim_h */
