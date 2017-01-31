/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/
 
#include <iostream>
using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
   myFront = myBack = 0;
   if (!original.empty())
   {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
      {
         myBack->next = new Queue::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

//--- Definition of Queue destructor
Queue::~Queue()
{ 
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
                     ptr;
  while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
   if (this != &rightHandSide)         // check that not q = q
   {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
         myFront = myBack = 0;
      else
      {                                // copy rightHandSide's list
         // Copy first node
         myFront = myBack = new Queue::Node(rightHandSide.front());

         // Set pointer to run through rightHandSide's linked list
         Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != 0)
         {
           myBack->next = new Queue::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{ 
   return (myFront == 0); 
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value, const int currentTime)
{
   Queue::NodePointer newptr = new Queue::Node(value, currentTime);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
   if (!empty())
      return (myFront->data);
   else
   {
	return 0;
   }
}

int Queue::getArrivalTimeFromFront() const
{
    if (!empty())
        return (myFront->arrivalTime);
    else
    {
        return -1;
    }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
   if (!empty())
   {
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
         myBack = 0;
   }   
   else
      cerr << "*** Queue is empty -- can't remove a value ***\n";
}

void Queue::move_to_front(const QueueElement & key)
{
    Queue::NodePointer prevPtr = 0;
    for (Queue::NodePointer ptr = myFront; ptr != 0; ptr = ptr->next)
    {
        if (ptr->data == key) {
            if(ptr == myBack)
                myBack = prevPtr;
            prevPtr->next = ptr->next;
            ptr->next = myFront;
            myFront = ptr;
            
            prevPtr = NULL;
            ptr = NULL;
            break;
        }
        prevPtr = ptr;
    }
}

void Queue::merge_two_queues( Queue & q2)
{
    Queue::NodePointer refPtr = myFront;
    Queue::NodePointer q1PrevPtr = 0;
    
    Queue::NodePointer q2Ptr = q2.myFront;
    
    while(q2Ptr != 0)
    {
        Queue::NodePointer nextPtr = q2Ptr->next;
        if(empty()){
        }else {
            for(Queue::NodePointer q1Ptr = refPtr; q1Ptr != 0; q1Ptr = q1Ptr->next)
            {
                if(q2Ptr->data < q1Ptr->data)
                {
                    q2.myFront = q2Ptr->next;
                    
                    q2Ptr->next = q1Ptr;
                    if(q1PrevPtr == 0){
                        myFront = q2Ptr;
                    } else {
                        q1PrevPtr->next = q2Ptr;
                    }
                    refPtr = q1Ptr;
                    q1PrevPtr = q2Ptr;
                    break;
                } else if(q1Ptr->next == 0) {
                    myBack->next = q2.myFront;
                    myBack = q2.myBack;
                    q2.myFront=NULL;
                    q2.myBack=NULL;
                }
                q1PrevPtr = q1Ptr;
            }
        }
        q2Ptr = nextPtr;
    }
    q1PrevPtr = NULL;
    refPtr = NULL;
}
