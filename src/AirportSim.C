//
//  AirportSim.cpp
//  Airport-Simulator
//
//  Created by WilliamChoi on 2017-01-28.
//  Copyright © 2017 William Choi. All rights reserved.
//

#include "AirportSim.h"

AirportSim::AirportSim()
{
    tland = ttake = landingRate = simDuration = takeoffRate = -1;
}

AirportSim::AirportSim(int tland, int ttake, int landingRate, int simDuration, int takeoffRate)
{
    this->tland = tland;
    this->ttake = ttake;
    this->landingRate = landingRate;
    this->simDuration = simDuration;
    this->takeoffRate = takeoffRate;
}

void AirportSim::run()
{
    srand(time(NULL));
    if(simDuration == -1 ){
        askForParameters();
    }
    
    for(int i = 0; i < simDuration; i++) {
        
        cout << "******************************************" << endl;
        cout << "Time = " << i << endl;
        
        if(runwayTime != 0 ) {
            runwayTime--;
            if(runwayTime == 0) {
                printRunwayActionComplete();
            }
        }
        
        randomTrafficGenerator(i);
        
        if(runwayTime == 0){
            handleTraffic(i);
        }
        
        if(runwayTime != 0) {
            printCurrentRunwayStatus();
        }
    }
    
    generateStats();
    cout << "End of Program" << endl;
}

void AirportSim::askForParameters()
{
    cout << "Time for a plane to land (in minutes): ";
    cin >> tland;
    
    cout << "Time for a plane to takeoff (in minutes): ";
    cin >> ttake;
    
    cout << "Landing rate (planes per hour): ";
    cin >> landingRate;
    
    cout << "Takeoff rate (planes per hour): ";
    cin >> takeoffRate;
    
    cout << "How long to run the simulation: ";
    cin >>simDuration;
}

void AirportSim::printRunwayActionComplete()
{
    string planeMotion;
    int queueNum;
    if(isLanding) {
        planeMotion = "Landing";
        queueNum = landingQueueSize;
    } else {
        planeMotion = "Takeoff";
        queueNum = takeoffQueueSize;
    }
    cout << planeMotion << " complete; " << queueNum << " in queue" << endl;
}

void AirportSim::randomTrafficGenerator(const int currentTime)
{
    int landingNum = rand() % 60;
    int takeoffNum = rand() % 60;
    
    if(landingNum < landingRate) {
        landingQueue.enqueue(flightNum, currentTime);
        landingQueueSize++;
        if(landingQueueSize>maxPlanesInLandingQueue){
            maxPlanesInLandingQueue=landingQueueSize;
        }
        cout << "Plane " << flightNum << " wants to land; added to landing queue; " << landingQueueSize << " in queue" << endl;
        flightNum++;
    }
    if(takeoffNum < takeoffRate) {
        takeoffQueue.enqueue(flightNum, currentTime);
        
        takeoffQueueSize++;
        if(takeoffQueueSize>maxPlanesInTakeoffQueue){
            maxPlanesInTakeoffQueue=takeoffQueueSize;
        }
        
        cout << "Plane " << flightNum << " wants to take off; added to takeoff queue; " << takeoffQueueSize << " in queue" << endl;
        flightNum++;
    }
}

void AirportSim::handleTraffic(const int currentTime)
{
    if(landingQueue.empty()){
        if(!takeoffQueue.empty()){
            currentFlightNum = takeoffQueue.front();
            totalTakeoffWaitingTime = totalTakeoffWaitingTime + currentTime - takeoffQueue.getArrivalTimeFromFront();
            totalPlanesTakenOff++;
            takeoffQueue.dequeue();
            takeoffQueueSize--;
            runwayTime = ttake;
            isLanding = false;
        }
    } else {
        currentFlightNum = landingQueue.front();
        totalLandingWaitingTime = totalLandingWaitingTime + currentTime - landingQueue.getArrivalTimeFromFront();
        totalPlanesLanded++;
        landingQueue.dequeue();
        landingQueueSize--;
        runwayTime = tland;
        isLanding = true;
    }
}

void AirportSim::printCurrentRunwayStatus()
{
    string planeMotion;
    if(isLanding){
        planeMotion = "Landing";
    } else {
        planeMotion = "Taking off";
    }
    cout << planeMotion << ": Plane " << currentFlightNum << endl;
}

void AirportSim::generateStats()
{
    cout << endl;
    cout << "STATISTICS" << endl;
    cout << "Maximum number of planes in Landing queue was: " << maxPlanesInLandingQueue << endl;
    
    cout << "Average Minutes spent waiting to land: ";
    if(totalPlanesLanded == 0) {
        cout << "No Planes Landed" << endl;
    } else {
        cout << ((double) totalLandingWaitingTime)/totalPlanesLanded << endl;
    }
    
    cout << "Maximum number of planes in Takeoff queue was: " << maxPlanesInTakeoffQueue << endl;
    
    // Note that the average time waiting to takeoff could be unusually small in the case that only a few planes got
    // to take off due to a constantly full landing queue.
    cout << "Average Minutes spent waiting to takeoff: ";
    if(totalPlanesTakenOff == 0) {
        cout << "No Planes Took off" << endl;
    } else {
        cout << ((double) totalTakeoffWaitingTime)/totalPlanesTakenOff << endl;
    }
}
