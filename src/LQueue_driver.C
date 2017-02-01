/*---------------------------------------------------------------------
 Driver program to test the Queue class.
 ----------------------------------------------------------------------*/

#include "AirportSim.h"

using namespace std;

void testPart1();

void testPart2();

void print(Queue q);

int main(void)
{
//    testPart1();
    testPart2();
    
    return 0;
}

void testPart1()
{
    Queue q1;
    cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;
    
    cout << "How many elements to add to the queue? ";
    int numItems;
    cin >> numItems;
    for (int i = 1; i <= numItems; i++)
        q1.enqueue(100*i);
    
    cout << "Contents of queue q1 (via  print):\n";
    print(q1);
    cout << endl;
    Queue q2;
    q2 = q1;
    cout << "Contents of queue q2 after q2 = q1 (via  print):\n";
    print(q2);
    cout << endl;
    
    cout << "Queue q2 empty? " << q2.empty() << endl;
    
    cout << "Front value in q2: " << q2.front() << endl;
    
    while (!q2.empty())
    {
        cout << "Remove front -- Queue contents: ";
        q2.dequeue();
        q2.display(cout);
    }
    cout << "Queue q2 empty? " << q2.empty() << endl;
    cout << "Front value in q2?" << endl << q2.front() << endl;
    cout << "Trying to remove front of q2: " << endl;
    q2.dequeue();
    //system("PAUSE");
    
    //add nodes to q2 testing part (b)
    cout<<endl<< "********** Testing for Merge **********"<<endl;
    cout<<"Original Queue(q1):"<<endl;
    print(q1);
    cout<<"Queue to be added (q2)"<<endl;
    q2.enqueue(10);
    q2.enqueue(50);
    q2.enqueue(300);
    q2.enqueue(400);
    q2.enqueue(500);
    print(q2);
    q1.merge_two_queues(q2);
    cout << "Merged Queue(q1): " << endl;
    print(q1);
    cout << "Old Queue (q2): " << endl;
    print(q2);
    cout << "Queue q2 empty? " << q2.empty() << endl;
    
    cout<<endl<< "********** Testing for Move_to_front **********"<<endl;
    cout<<"Queue to be searched(q1)"<<endl;
    print(q1);
    
    q1.move_to_front(200);
    q1.move_to_front(400);
    q1.move_to_front(30);
    q1.move_to_front(600);
    
    cout << "q1 now: " << endl;
    print(q1);
}

void testPart2()
{
    AirportSim airportSimulator;
    airportSimulator.run();
}

void print(Queue q)
{
    q.display(cout);
}
