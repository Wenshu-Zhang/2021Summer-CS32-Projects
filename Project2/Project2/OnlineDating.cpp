//
//  OnlineDating.cpp
//  Project2
//
//  Created by Claire Z on 7/7/21.
//

#include "OnlineDating.h"
#include <iostream>
#include <string>

//constructor
OnlineDating::OnlineDating(){       //initialize private members
    head = nullptr;
    tail = nullptr;
}

//destructor
OnlineDating::~OnlineDating(){      //delete all dynamic elements
    Match* p =head;                 //start deleting with head
    while(p != nullptr){            //and then one by one in the linkedlist
        Match* dp = p->next;
        delete p;
        p = dp;
    }
}

//copy constructor
OnlineDating::OnlineDating(const OnlineDating &rhs){
    if(rhs.head == nullptr){
        this->head = nullptr;
        return;
    }
    Match* p = new Match;           //copy the head
    head = p;
    p->prev = nullptr;
    Match* dp = rhs.head;
    p->firstName = dp->firstName;
    p->lastName = dp->lastName;
    p->value = dp->value;
    dp = dp->next;                  //proceed to the next element that needs to be copied
    while(dp != nullptr){           //examine if the next element is nullptr
        p->next = new Match;        //if not, create a new node for copying
        p->next->prev = p;          // take care of the prev pointer
        p = p->next;                //start copying
        p->firstName = dp->firstName;
        p->lastName = dp->lastName;
        p->value = dp->value;
        p->next = nullptr;          //don't know if there's a next element, set p->next
                                    //to nullptr for safety
        dp = dp->next;              //proceed to the next element
        tail = p;                   //let the tail pointer point to the current last element
    }
}

//Assignment operator
const OnlineDating& OnlineDating::operator=(const OnlineDating &rhs){
    if(&rhs == this)                //if the same as rhs, return *this
        return *this;
    OnlineDating copy(rhs);         //make a copy of rhs
    Match* temp = head;             //create temporary pointers and let them point to head
    Match* tempT = tail;            //and tail of this
    head = copy.head;               //make head and tail point to the copy's head
    tail = copy.tail;               //and tail
    copy.head = temp;               //let the copy pointers point to the orginal linkedlist
    copy.tail = tempT;              //they will be deleted when the function is finished
    return *this;
}

bool OnlineDating::noMatches() const{
    if(howManyMatches() == 0)       //if nothing in the linkedlist, return true
        return true;
    else                            //otherwise, false
        return false;
}

int OnlineDating::howManyMatches() const{
    int count = 0;
    Match* p = head;                //start with head
    while (p != nullptr){           //if it's not nullptr
        count++;                    //add 1 to count
        p = p->next;                //proceed to examine the next one
    }
    return count;                   //return the size of the linked list
}

bool OnlineDating::makeMatch(const std::string& firstName, const std::string& lastName, const OnlineType& value){
    if(someoneAmongMatches(firstName,lastName))
        return false;               //if already in the list, return false
    Match* p = head;
    if(howManyMatches() == 0){      //if the first one in the list
        Match* first = new Match;   //make a new node and copy in the values
        first->firstName = firstName;
        first->lastName = lastName;
        first->value = value;
        first->prev = nullptr;      //previous pointer of the head should be nullptr
        first->next = nullptr;
        head = first;               //make the head pointer point to the first node
        tail = first;               //also make the tail pointer point to the first node
        return true;
    }
//    int count = 0;                  //find where to insert the new match
    while (p->next != nullptr && lastName > p->lastName){
        p = p->next;
//        count++;
    }
    if(lastName <= p->lastName){      //if the previous loop stopped
                                                            //because of the last name
        Match* insert = new Match;  //make a new match and copy in the values
        insert->firstName = firstName;
        insert->lastName = lastName;
        insert->value = value;
        if(lastName == p->lastName){
            //if the last name equals to the one p points to
            //examine the order of tmheir firstnames
            while(p->next != nullptr && lastName == p->lastName && firstName > p->firstName){
                p = p->next;
//                count++;
            }
            //if firstname is smaller, insert it to the front of where p points to
            if(firstName < p->firstName){
                insert->next = p;
                insert->prev = p->prev;
                if(p != head){
                    p->prev->next = insert;
                    p->prev = insert;
                }
                else{               //if p is head, insert it to the very front
                    p->prev = insert;
                    head = insert;  //make the head pointer point to this match
                }
                return true;
            }
            else{                   //if firstname is greater, insert it to the next of
                                    //where p points to
                insert->prev = p;
                insert->next = p->next;
                //if p is not the tail
                if(p!= tail){
                    p->next->prev = insert;
                    p->next = insert;
                }
                //if p is the tail
                else{
                    p->next = insert;
                    tail = insert;  //make the tail pointer point to insert
                }
                return true;
            }
        }
        insert->next = p;           //if lastName is smaller, add insert to one position before p
        insert->prev = p->prev;
        if(p != head){              //if p is not head
            p->prev->next = insert;
            p->prev = insert;
        }
        else{                       //if p is head, make the head pointer point to insert
            p->prev = insert;
            head = insert;
        }
        return true;
    }
    else{                           //if p is the tail and lastName is greater than all lastNames in the list
        Match* atEnd = new Match;   //add it to the end of the linked list
        atEnd->firstName = firstName;
        atEnd->lastName = lastName;
        atEnd->value = value;
        atEnd->prev = p;
        p->next = atEnd;
        atEnd->next = nullptr;
        tail = atEnd;
        return true;
    }
}

bool OnlineDating::transformMatch(const std::string& firstName, const std::string& lastName, const OnlineType & value){
    if(!someoneAmongMatches(firstName, lastName))
        return false;               //change nothing if the person is not a match
    Match* p = head;
    while(p->firstName != firstName || p->lastName != lastName)
        p = p->next;                //loop through to find the match
    p->value = value;
    return true;
}

bool OnlineDating::makeOrTransform(const std::string& firstName, const std::string& lastName, const OnlineType& value){
    if(!someoneAmongMatches(firstName, lastName)){
        makeMatch(firstName, lastName, value);
        return true;                //if not a match, make a match and return true
    }
    else{                           //if is a match, transform it
        transformMatch(firstName, lastName, value);
        return true;                //and return true
    }
}

bool OnlineDating::blockPreviousMatch(const std::string& firstName, const std::string& lastName){
    if (!someoneAmongMatches(firstName, lastName))
        return false;               //if not a match, return false
    Match* p = head;                //else, find the match
    while(p->firstName != firstName || p->lastName != lastName)
        p = p->next;
    if(p == head){                  //if the match is the head,
        if(p->next != nullptr){
            p->next->prev = nullptr;//make the next match the new head
            head = p->next;
            delete p;               //delete the match from the list
            return true;            //and return true
        }
        else{
            delete p;
            head = nullptr;
            tail = nullptr;
            return true;
        }
    }
    else if (p == tail){            //if the match is the tail
        p->prev->next = nullptr;    //make the previous match the new tail
        tail = p->prev;
        delete p;                   //delete the match from the list
        return true;                //and return true
    }
    else{                           //if in the middle
        p->prev->next = p->next;    //make the previous match's next map to the next of p
        p->next->prev = p->prev;    //make the next match's next map to the previous of p
        delete p;                   //delete p
        return true;                //and return true
    }
}

bool OnlineDating::someoneAmongMatches(const std::string& firstName, const std::string& lastName) const{
    Match* p = head;                //start with the head
    while(p != nullptr){            //loop through every element
        if(p->lastName == lastName && p->firstName == firstName){
            return true;            //if there is a matching case, return true
        }
        p = p->next;
    }
    return false;                   //if not such match is found, return false
}

bool OnlineDating::lookAtMatches(const std::string& firstName, const std::string& lastName, OnlineType& value) const{
    if(!someoneAmongMatches(firstName, lastName))
        return false;               //if no such match, return false
    else{
        Match* p = head;            //start with the head
        while(p->lastName != lastName || p->firstName != firstName){
            p = p->next;            //loop through the elements until one's values match
        }
        value = p->value;           //change the value parameter to the value of the match
        return true;
    }
}

bool OnlineDating::confirmMatch(int i, std::string& firstName, std::string& lastName, OnlineType & value) const{
    if(i < 0 || i >= howManyMatches())
        return false;               //if invalid i value, return false
    Match* p =head;                 //start with the head
    for (int k = 0; k < i; k++)     //find the match at position i with loop
        p = p->next;
    firstName = p->firstName;       //pass in the values of the match to the parameters
    lastName = p->lastName;
    value = p->value;
    return true;                    //return true while everything behaved correctly
}

void OnlineDating::tradeMatches(OnlineDating& other){
    //swap the content of two linked lists
    Match* temp = head;             //create a temp pointer which points to what head points to
    head = other.head;              //make the head pointer point to other's head
    other.head = temp;              //make other's head pointer point to the head of this,
                                    //which temp points to
}

bool mergeMatches(const OnlineDating & odOne, const OnlineDating & odTwo, OnlineDating & odJoined){
    bool merge = true;
    std::string firstName = "";
    std::string lastName = "";
    OnlineType value;
    //copy all matches into odJoined from odOne
    for (int i = 0; i < odOne.howManyMatches(); i++){
        odOne.confirmMatch(i, firstName, lastName, value);
        odJoined.makeMatch(firstName, lastName, value);
    }
    //selectively copy matches into odJoined from odTwo
    for (int k = 0; k < odTwo.howManyMatches(); k++){
        //get the values of this match
        odTwo.confirmMatch(k, firstName, lastName, value);
        //if it already exists
        if(odJoined.someoneAmongMatches(firstName, lastName)){
            OnlineType r_value;     //get its value
            odJoined.lookAtMatches(firstName, lastName, r_value);
            if (r_value != value){  //if the values don't match
                merge = false;      //the function will return false
                //make sure this match does not appear in odJoined by deleting it
                odJoined.blockPreviousMatch(firstName, lastName);
            }
            //if they do match, do nothing
        }
        else{                       //if no such match yet, make a match in odJoined
            odJoined.makeMatch(firstName, lastName, value);
        }
    }
    return merge;                   //return if the merge was successful
}

void authenticateMatches(const std::string& fsearch, const std::string& lsearch, const OnlineDating& odOne, OnlineDating& odResult){
    std::string firstName = "";
    std::string lastName = "";
    OnlineType value;
    //delete everything in odResult if it has any
    while (odResult.howManyMatches() != 0){
        odResult.confirmMatch(0, firstName, lastName, value);
        odResult.blockPreviousMatch(firstName, lastName);
    }
    if (fsearch == "*"){            //if fsearch is *
        if(lsearch != "*"){         //and lsearch is not *
                                    //find all matches that have a lastname that matches lsearch
            for(int i = 0; i < odOne.howManyMatches(); i++){
                odOne.confirmMatch(i, firstName, lastName, value);
                if(lastName == lsearch){
                    odResult.makeMatch(firstName, lastName, value);
                }
            }
        }
        else{                       //or if lsearch is also*
                                    //copy in all matches from odOne to odResult
            for(int i = 0; i < odOne.howManyMatches(); i++){
                odOne.confirmMatch(i, firstName, lastName, value);
                odResult.makeMatch(firstName, lastName, value);
            }
        }
    }
    else if (fsearch !="*"){        //if fsearch is not *
        if(lsearch != "*"){         //and lsearch is not *
                                    //find all matches that have the matching full name
            for(int i = 0; i < odOne.howManyMatches(); i++){
                odOne.confirmMatch(i, firstName, lastName, value);
                if(firstName == fsearch && lastName == lsearch){
                    odResult.makeMatch(firstName, lastName, value);
                }
            }
        }
        else{                       //if fsearch is not *
                                    //and lsearch is *
                                    //find all that has a firstname that matches fsearch
            for(int i = 0; i < odOne.howManyMatches(); i++){
                odOne.confirmMatch(i, firstName, lastName, value);
                if(firstName == fsearch){
                    odResult.makeMatch(firstName, lastName, value);
                }
            }
        }
    }
}
