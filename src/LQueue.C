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

void Queue::move_to_front(const QueueElement & key){
        Queue::NodePointer sptr = myFront;
        Queue::NodePointer kptr = new Queue::Node(key);
        for (sptr = myFront; sptr != 0; sptr = sptr->next){
            if (sptr->data==key){
                kptr->next=myFront;
                myFront=kptr;
            }
        }
}

void Queue::merge_two_queues( Queue &q2){
    Queue::NodePointer curr1;
    Queue::NodePointer curr2;
    Queue::NodePointer curr3;
    Queue temp;
    if (empty()){                       // if q1 empty
        myFront=q2.myFront;
        myBack=q2.myBack;
        q2.myFront=NULL;
        q2.myBack=NULL;
    }
    else if (q2.empty()){               // if q2 empty
        return;
    }
    
    // ignore
   /* else{
        for(curr2=q2.myFront;(curr2->next)!=0;curr2=curr2->next){
            for(curr1=myFront; (curr1->next)!=0; curr1=curr1->next){
                if(((curr2->data)<=(curr1->next->data))&&((curr2->data) > (curr1->data))){
                    Queue::NodePointer temp = new Queue::Node(curr2->data);
                    temp->data=curr2->data;
                    temp->next=curr1->next;
                    curr1->next=temp;
                }
                   }
                   }
        }
   // while (!q2.empty()){
  //      q2.dequeue();
  //  }
    */
    else{                               // other cases
        curr2=q2.myFront;
        curr1=myFront;
        while(curr1!=0&&curr2!=0){
            if((curr2->data)<(curr1->data)){
                Queue::NodePointer tn = new Queue::Node(curr2->data);
                temp.enqueue(tn->data);
                curr2=curr2->next;
            }
            else{
                Queue::NodePointer tn = new Queue::Node(curr1->data);
                temp.enqueue(tn->data);
                curr1=curr1->next;
            }
        }                              //basically compare two value and add to temp
        
        // put what's left to temp. At lease one of curr1 and curr2 is zero so we can jsut use two while loop
        while(curr1!=0){
            temp.enqueue(curr1->data);
            curr1=curr1->next;
        }
        
        while(curr2!=0){
            temp.enqueue(curr2->data);
            curr2=curr2->next;
        }

    
        // clean q1 and q2
        
    }
    while (!q2.empty()){
             q2.dequeue();
         }
    while(!this->empty()){
        this->dequeue();
    }
    
        // put everything in temp to q1
    curr3=temp.myFront;
    while(curr3){
        this->enqueue(curr3->data);
        curr3=curr3->next;
    }
    
}

