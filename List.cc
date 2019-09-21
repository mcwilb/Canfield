/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     List.cc
  Last updated:  September 3, 2019
  Description:   Implementation of a container class for a list.

**********************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

#include "general.h"
#include "List.h"

// Default constructor.
List::List()
    : head(NULL), tail(NULL), size(0) // empty list
{
} // List::List()

// Copy constructor. The target object should be assigned a hard copy
// of the list contained in the data object.
List::List(List &data)
    : head(NULL), tail(NULL), size(0) // start with an empty list
{
    *this = data; // then use the operator= form this class
} // List::List()

// Destructor. Deletes the entire list.
List::~List()
{
    // call the function makeEmpty instead so that we only have to
    // change things in one place
    makeEmpty();
} // List::~List()

// Assignment operator. It must also make a hard copy of the
// list. Make sure that the tail of the target object is also set
// correctly.
List &List::operator=(List &data)
{
    if (this != &data) // check that we're not assigning the object to itself
    {
        makeEmpty();
        size = data.size;
        head = data.head->copy(); // make a copy of the list instead of 
                                  // of assigning just the pointer 
        tail = head->lastNode();  // now we have to find the last node
                                  // because we've copied the list
    }

    return *this; 
} // List::operator=()

// Returns the size of the list.
int List::getSize()
{
    return size;
} // List::getSize()

// Inserts a new node with the number parameter stored as datum at the
// front of the list. It must make sure to update both the head and
// the tail of the list if need be.
void List::insertFront(int number)
{
    // create a node with the data and pointing towards the head
    ListNodePtr newNode = new ListNode(number, head);
    testAllocation(newNode);

    size++;             // we're adding a node

    head = newNode;     // this one becomes the head of the list

    if (size == 1)      // if it was the first one
        tail = newNode; // then it's also the tail
} // List::insertFront()

// Removes the node in the list that follows the one referenced by the
// iterator. If the iterator contains a NULL pointer, the front node
// is removed. It returns false if the list was empty and no node was
// removed and true otherwise.
bool List::removeNodeAfter(ListIterator iter)
{
    if (!iter) // current in iter is NULL
        return removeFront();
    else 
    {
        if (!iter.current->next) // iter is the last node
            return false;        // nothing to remove in this case
        else
        {
            ListNodePtr temp = iter.current->next; // the node to delete
            iter.current->next = iter.current->next->next; // adjust links
            delete temp;
            size--;
            if (!iter.current->next) // if the node deleted was the last one
                tail = iter.current; // then we have a new tail.
            return true;
        }
    }
} // List::removeNodeAfter()

// Checks if the list is empty.
bool List::isEmpty()
{
    return (size == 0); // we can check the size or the pointers
} // List::isEmpty()

// Converts the list to Boolean. It returns true if the list is not
// empty, and false if it is.
List::operator bool()
{
    return !isEmpty(); // return true if the list is not empty
} // List::operator bool()

// Deletes the entire list and resets all the data.
void List::makeEmpty()
{
    if (size) // if the list is not empty
    {
        deleteList(head); // call the function from ListNode.cc
        head = NULL; // then reset the data
        tail = NULL;
        size = 0;
    }
} // List::makeEmpty()

// Difference operator - it must compare the content of the two lists
// and not just the pointers to them.
bool List::operator!=(List &data)
{
    return !(*this == data); // call the operator== on the object,
                             // not on the pointer
} // List::operator!=()

// Concatenates the data list to the one in the target object and
// empties the data list.
void List::concatenate(List &data)
{
    if (head != data.head) // if the two lists are not the same
    {
        if (head) // if the first list is not empty
        {
            // call the ListNode function to add the second list 
            // to the tail of the first
            tail->concatenate(data.head); 
            size += data.size; // we also have to update the size
            if (data.tail)     // and the tail
                tail = data.tail;
        }
        else // if the first list is empty
        {
            // move the list from the second one into it
            head = data.head;
            size = data.size;
            tail = data.tail;
        }
        if (data) // if the second list was not empty, unlink/empty it
        {
            data.size = 0;
            data.head=NULL;
            data.tail=NULL;
        }
    }
    else // error
        cout << "Attepmt to concatenate a list to itself. "
             << "Operation ignored." << endl;
} // List::concatenate()
  
// Prints the last node in the list: the tail.
void List::printLast()
{
    if (tail) // check that we have a last node
        cout << "The last node in the list contains " 
             << tail->datum << endl;
    else
        cout << "The list is empty, it has no last node" << endl;
} // List::printLast()

/*******************************************************************/
// Functions using list iterators.

// Begining of the list returned as a list iterator.
ListIterator List::begin()
{
    return ListIterator(head); 
} // 

// End of the list returned as a list iterator.
ListIterator List::end()
{
    return ListIterator(tail);
} // List::end()

// Prints the list to the console. It also outputs the number of nodes
// and whether the list is empty.  The function is writen using list
// iterators.
void List::print()
{
    // print the count first
    cout << "The list has " << size << " nodes." << endl;

    if (size)   // if the list is not empty
    {
        // print all the nodes using an iterator
        cout << "Here are the nodes of the list:" << endl;
        ListIterator iter(head); //start from the head
        while (iter) // while we haven't reached the end
        {
            cout << *iter << ' '; // print the datum
            ++iter; // move to the next node
        }
        cout << endl;
    }
} // List::print()

// Searches for the parameter number in the list and returns a list
// iterator referencing the node containing this number. If the number
// is not in the list, it returns an iterator where the pointer
// current is NULL.
ListIterator List::locate(int number)
{
    ListIterator locator = begin(); // start form the head
    while (locator && *locator != number) // while we haven't reached the end
                                          // nor found the target
        ++locator; // move to the next node
    return locator; // return the iterator containing the target
                    // or containing NULL if it wasn't there
} // List::locate()

// Returns the element i of the list in the form of a list iterator,
// where index=0 returns the first node of the list. If the list has
// less than index+1 nodes, then it should return a null iterator.
ListIterator List::nodeAtIndex(int index)
{
    // This should work once you implement moveForward.
    ListIterator start = begin();
    start.moveForward(index);
    return start;
} // List::nodeAtPosition()

// The bubble sort implemented on the list using list iterators.
void List::bubbleSort()
{
    if (head) // if the list is not empty
    {
        bool ordered = false;
        ListIterator iter1, iter2; // need two iterators
        while (!ordered) // while the list is not sorted
        {
            ordered = true; // we'll assume it is sorted
            iter1 = head;   // start form the head with one
            iter2 = head->next; // and the next with the other
            while (iter2) 
            {
                if (*iter1 > *iter2) // if two nodes are out of order
                {
                    iter1.swap(iter2); // swap their datums
                    ordered = false;   // and set the flag
                }
                ++iter1; // move both iterators at the same time
                ++iter2; // so they will allways be adjacent nodes
            }
        }
    }
} // List::bubbleSort()

/*******************************************************************/
// Functions to be written by the student. 


// Comparison operator - it must compare the content of the two
// lists and not just the pointers to them.
bool List::operator==(List &data)
{
    ListIterator iter1(head), iter2(data.head);

    //Comparing size of the two lists.  If the lists  are not the same size,
    //return false. 
    if(size!=data.size)
      return false;

    //Accesses data within iter 1 and compares to data
    //of iter2 while they aren't NULL.  If they do not match returns false.

    while (iter1 && iter2)
    {
      if(*iter1!=*iter2) 
      return false;

      //Accesses and compares data of iter1 and iter 2.  If they match then
      //both iter1 and iter2 are incremented to move to the next nodes.  
      if(*iter1==*iter2)
      {
      ++iter1;
      ++iter2;
      }

    } 
      return true;
    

} // List::operator==()


// Inserts a new node with the specified content at the back of the
// list. Could be calling another class method if appropriate. The
// code must be supplied by the student.
void List::insertBack(int number)
{
   
    // create a node with the data number passed in
  ListNodePtr newNode = new ListNode(number, NULL);
    testAllocation(newNode);

    size++;
    // adding the new node to the back of the list and assigning tail to the
    // newNode.
    if (tail)
       tail->next = newNode;
       tail = newNode;

       
    if (size == 1)      // if it was the first one
        head = newNode; // then point head to newNode.
} // List::insertBack()

// Inserts a node after the node pointed to by current in the
// iterator. We assume that the existing node is part of the list. If
// current in the iterator is NULL, then the function should insert
// the new node at the front of the list. The function should update
// head, tail, and size properly.
void List::insertAfter(ListIterator iter, int number)
{
    
    ListNodePtr newNode = new ListNode(number);
    testAllocation(newNode);

    if (!iter) // current if iter is NULL
        return insertFront();
   
    else
    {
      newNode=newNode->next;
      newNode=iter.current->next;
      //iter.current->next =newNode; //point iter to newNode
      newNode->next= iter.current->next->next;//newNode next link
                                              //is pointed 2 forward of iter's.
       size++; 
    }
    if(size==1)
      tail = newNode; //update tail if node inserted is only node.

    if(newNode->next == NULL)
      tail = newNode;  //if newNode is at end of list update tail
                       //to point at new node.
     
} // List::insertAfter()

// Removes the front node from the list and deletes the memory of the
// node to be removed. The function should return true if a node was
// removed, and false if the list was already empty. The head, tail
// (!), and size of the list should be updated correctly.
// THIS DOES NOT NEED TO USE ITERATORS.
bool List::removeFront()
{
    //Check to see if the list is empty.  If empty return false.
    if(head==NULL)
       return false;

    //Created a ListNodePtr, p, pointed it at head.
    //Head is then pointed to head->next.
    //After which we can delete the node p was pointing to.
    //Return true once the node has been deleted.

    ListNodePtr p=head;
    head=head->next;
    delete p;
    size--;

    if(size==0)
      tail = NULL;

    
    return true;

} // List::removeFront()

// Checks if the list is in ascending order.
bool List::isOrdered()
{
    ListIterator leadingIter=begin(), priorIter=begin(); //set both iterators
                                                      //pointing to head.

    if (!leadingIter) //if leadingIter is Null
      cout << "The list is empty."<<endl;
    
    //loop while leadingIter is not NULL.
    while(leadingIter)
    {
      ++leadingIter; //Increment to move leadingIter to next node.
      if(*priorIter <= *leadingIter)//compare data if priorIter is less than
      {                             //leadingIter, increment priorIter.
	  ++priorIter;             
      }
      
      else if(*priorIter>*leadingIter) //if priorIter is larger than the
	                               //following number, then return false
	                               //as the list is not ordered.
      return false;
    }
  
  return true;
  
} // List::isOrdered()

// Counts the number of negative values in the list. If the list is
// empty, just return 0.
int List::countNegative()
{
    int count=0;
    ListIterator iter(head);//using an iterator to traverse list

    while (iter) //while not NULL
    {
      if(*iter<0) //check data and compare to see if negative (<0).
	count++; //increment counter to track number of negatives.
      ++iter; //increment iter to move to next node.
    }
  
    return count; //returns total number of negatives.
} // List::countNegative()

// This function computes the sum of all the numbers stored in the
// list. It should be implemented using list iterators.
int List::sum()
{
    int sum=0;
    ListIterator iter(head); //uses list iterator to traverse the list.
   
    while(iter)//as long as the pointer is not null
               //the loop will add the numbers.
    {
        sum=sum+*iter; //*iter accesses the data and the data is added to sum
        ++iter;//advancing the iterator to the next node.
    }
	   
    return sum;
    
} // List::sum()

void List::returnElementPosition(int elementNum)
{
  //The element number entered by user is passed into function.
  //ListerIterator iter is created and calls nodeAtIndex.
  ListIterator iter=nodeAtIndex(elementNum);

  //Prints out the data pointed to by iterator.
  cout<< "The element given for the number entered is: "
      << *iter <<endl;
  
}//returnElementPosition

void List::locateANumber(int searchNum)
{
    ListIterator iter=locate(searchNum);

    if(*iter==searchNum)
        cout << "The number you entered is located in the list." << endl;
    else
        cout << "The number you entered is not located in the list." << endl;

}//locateANumber()

// This function should implement the selection sort on a list using
// list iterators. It should have an iterator scanning the list but
// stopping before the last node. For every position in the list, it
// would have to find the location of the minimal number in the list
// using a call to the appropriate function from the ListIterator
// class. Then if the location of the minimum is not the same as the
// current node, swap the value of the current node with the minimum.
void List::selectionSort()
{

    ListIterator iter1(head), iter2(head);
  
    if(head) //checking to make sure list isn't empty
    {
        while(iter1) //while iter1 not null
        {
	    iter2=iter1.min(); //find smallest number in list,  set iter2.
      
           if (*iter1 > *iter2) // if iter1 datum is larger than iter2 datum
           {
             iter1.swap(iter2); // swap their datums
             ++iter1;
	   }
	}	   
    }
    
} // List::selectionSort()
// Very simple display of the List with no other messages.
void List::display()
{
      if (size) 
      {
        ListIterator iter(head);
        while (iter) 
         {
            cout << setw(2) << *iter << ' ';
            ++iter;
         }
    }
} // List::display()
 
