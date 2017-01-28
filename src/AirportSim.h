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
    /** Constructors **/
    AirportSim();
    AirportSim(int tland, int ttake, int landingRate, int simDuration, int takeoffRate);
    /** To run the simulator **/
    void run();
    
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
    void runwayActionComplete();
    void randomTrafficGenerator(const int currentTime);
    void handleTraffic(const int currentTime);
    void currentRunwayStatus();
    void generateStats();
};


#endif /* AirportSim_h */
