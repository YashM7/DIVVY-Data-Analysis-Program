/*hash.h*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <string>

using namespace std;

bool isNumeric(string s);
int HashByStationID(int theid, int N);
int HashByStationAbbrev(string abbrev, int N);
int HashByTripId(string tripId, int N);
int HashForBikeId(string bikeId, int N);