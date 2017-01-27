//
//  main.cpp
//  pass1
//
//  Created by Ruishen on 2017-01-26.
//  Copyright © 2017 Ruishen. All rights reserved.
//

#include "LQueue.h"
#include <iostream>

using namespace std;

int main (void){
    srand(time(NULL));
    int tland;
    int ttake;
    int landingRate;
    int simDuration;
    int takeoffRate;
    Queue landingQueue;
    Queue takeoffQueue;
    
    cout<< "Time for a plane to land (in minutes): ";
    cin>> tland;
   
    cout<< "Time for a plane to takeoff (in minutes): ";
    cin>> ttake;
  
    cout<< "Landing rate (planes per hour): ";
    cin>> landingRate;
    
    cout<< "Takeoff rate (planes per hour): ";
    cin>> takeoffRate;

  
    cout<< "How long to run the simulation: ";
    cin>>simDuration;
    
    int flightNum = 1000;
    int landingQueueSize = 0;
    int takeoffQueueSize = 0;
    
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
    
    for(int i = 0; i < simDuration; i++) {
        int landingNum = rand() % 60;
        int takeoffNum = rand() % 60;
        
        cout << "********************************" << endl;
        cout << "Time = " << i << endl;
        
        if(runwayTime != 0 ) {
            runwayTime--;
            if(runwayTime == 0) {
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
        }
        
        if(landingNum < landingRate) {
            landingQueue.enqueue(flightNum, i);
            landingQueueSize++;
            if(landingQueueSize>maxPlanesInLandingQueue){
                maxPlanesInLandingQueue=landingQueueSize;
            }
            cout << "Plane " << flightNum << " wants to land; added to landing queue; " << landingQueueSize << " in queue" << endl;
            flightNum++;
        }
        if(takeoffNum < takeoffRate) {
            takeoffQueue.enqueue(flightNum, i);
            
            takeoffQueueSize++;
            if(takeoffQueueSize>maxPlanesInTakeoffQueue){
               maxPlanesInTakeoffQueue=takeoffQueueSize;
            }

            cout << "Plane " << flightNum << " wants to take off; added to takeoff queue; " << takeoffQueueSize << " in queue" << endl;
            flightNum++;
        }
        if(runwayTime == 0){
            if(landingQueue.empty()){
                if(!takeoffQueue.empty()){
                    currentFlightNum = takeoffQueue.front();
                    totalTakeoffWaitingTime = totalTakeoffWaitingTime + i - takeoffQueue.getArrivalTimeFromBack();
                    totalPlanesLanded++;
                    takeoffQueue.dequeue();
                    takeoffQueueSize--;
                    runwayTime = ttake;
                    isLanding = false;
                }
            } else {
                currentFlightNum = landingQueue.front();
                totalLandingWaitingTime = totalLandingWaitingTime + i - takeoffQueue.getArrivalTimeFromBack();
                totalPlanesTakenOff++;
                landingQueue.dequeue();
                landingQueueSize--;
                runwayTime = tland;
                isLanding = true;
            }
        }
        
        if(runwayTime != 0) {
            string planeMotion;
            if(isLanding){
                planeMotion = "Landing";
            } else {
                planeMotion = "Taking off";
            }
            cout << planeMotion << ": Plane " << currentFlightNum << endl;
        }
    }
    cout << "End of Programme" << endl;
    
    // Statistics
    cout << "Maximum number of planes in Landing queue was: " << maxPlanesInLandingQueue << endl;
    cout << " Average Minutes spent waiting to land: " << ((double) totalLandingWaitingTime)/totalPlanesLanded << endl;
    cout << "Maximum number of planes in Takeoff queue was: " << maxPlanesInTakeoffQueue << endl;
    cout << " Average Minutes spent waiting to takeoff: " << ((double) totalTakeoffWaitingTime)/totalPlanesTakenOff << endl;
}

