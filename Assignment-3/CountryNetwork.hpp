/****************************************************************/
/*                  CountryNetwork Definition                   */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/

#pragma once
#include <iostream>
using namespace std;

// Country: node struct that will be stored in the CountryNetwork
struct Country
{
    string name;         // name of the country
    string message;      // message this country has received
    int numberMessages;       // no. of messages passed through this country
    Country *next;            // pointer to the next country
};


// class for storing and manipulating linked list of countries
class CountryNetwork {
    private:
        Country* head;  // pointer to head of linked list of cities

    public:
        // Complete the definition of the following methods in CountryNetwork.cpp
        CountryNetwork();
        void insertCountry(Country* previous, string countryName);
        void loadDefaultSetup();
        Country* searchNetwork(string countryName);
        void transmitMsg(string receiver, string msg);
        void printPath();
};