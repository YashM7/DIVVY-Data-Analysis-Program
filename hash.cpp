/*hash.cpp*/

//
// Yash Mude
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #06: hashing DIVVY data
// 
// 

#include <iostream>
#include <string>
#include <cctype>  /*isdigit*/
#include <regex>   /*regular expressions*/

#include "hash.h"

using namespace std;

//
// isNumeric
//
// Returns true if the given string is numeric (all digits), false
// if not.  If the string is empty, false is returned since there 
// are no digits present.
//
bool isNumeric(string s)
{
	//
	// A string is numeric if it contains 1 or more digits, so let's
	// use a regular expression to check that.
	//
	// we are using POSIX basic notation for regular expressions, see
	//   https://en.cppreference.com/w/cpp/regex/ecmascript
	// where [:d:] means digit, [[:d:]] means match a single digit.
	// The + means match the preceding sub-expression 1 or more times.
	//
	regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}


//
// HashForId
//
int HashByStationID(int theid, int N)
{
    return theid % N;
}


//
// HashForId
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int HashByStationID(int theid)
{
    return HashByStationID(theid, 10000);
}


//
// HashForAbbrev
//
int HashByStationAbbrev(string abbrev, int N)
{
    unsigned long long hash = 5381;
    for(auto a : abbrev){
        hash = (hash * 33) + a;
    }
    return hash % N;
}


//
// HashForAbbrev
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int HashByStationAbbrev(string abbrev)
{
    return HashByStationAbbrev(abbrev, 10000);
}


//
// HashForTripId
//
int HashByTripId(string tripId, int N) //Tr10426561
{
    tripId.erase(0,2);
    return stoi(tripId) % N;
}


//
// HashForTripId
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int HashByTripId(string tripId)
{
    return HashByTripId(tripId, 2500000);
}


//
// HashForBikeId
//
int HashForBikeId(string bikeId, int N)  //B5229
{
    bikeId.erase(0,1);
    return stoi(bikeId) % N;
}


//
// HashForBikeId
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int HashForBikeId(string bikeId)
{
    return HashForBikeId(bikeId, 50000);
}