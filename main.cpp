/*main.cpp*/

//
// Yash Mude
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #06: hashing DIVVY data
// 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <utility>
#include <set>

#include "hash.h"
#include "util.h"
#include "hashmap.h"

using namespace std;


class prioritize
{
  public:
    bool operator()(const pair<int,double>& p1, const pair<int,double>& p2) const
    {
        if(p1.second > p2.second)
        {
            return true;
        }
        
        else if(p1.second == p2.second)
        {
            if(p1.first > p2.first)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};

//
// StationData
// 
// A struct which stores station id, station abbrev, station fullname,
// station latitude, station longitude, station capacity and station online date
// 
struct StationData
{
    int id;
    string abbrev;
    string fullname;
    double latitude;
    double longitude;
    int capacity;
    string online_date;
    
    // setting default values
    StationData()
    {
        id = -1;
        abbrev = "";
        fullname = "";
        latitude = -999;
        longitude = -999;
        capacity = -1;
        online_date = "";
    }
};


//
// TripData
//
// A struct which stores trip id, trip starttime, trip stoptime,
// trip bikeid, trip duration, trip from station, trip to station,
// trip identifies(gender), trip birthyear(of user)
// 
struct TripData
{
    string tripid;
    string starttime;
    string stoptime;
    string bikeid;
    string duration;
    int from;
    int to;
    string identifies;
    string birthyear;
    
    // setting default values
    TripData()
    {
        tripid = "";
        starttime = "";
        stoptime = "";
        bikeid = "";
        duration = "";
        from = -999;
        to = -999;
        identifies = "";
        birthyear = "";
    }
};

//
// string2int
// 
// Converts a string to an integer, unless string is empty, in
// which case 0 is returned.
// 
int string2int(string s)
{
	if (s == "")
		return 0;
	else
		return stoi(s);
}


//
// help
// 
// A function to print out all the commands that can be
// permormed by the user's input
// 
void help()
{
  cout << "Available commands:" << endl;
  cout << " Enter a station id (e.g. 341)" << endl;
  cout << " Enter a station abbrevation (e.g. Adler)" << endl;
  cout << " Enter a trip id (e.g. Tr10426561)" << endl;
  cout << " Enter a bike id (e.g. B5218)" << endl;
  cout << " Nearby stations (e.g. nearby 41.86 -87.60 0.5)" << endl;
  cout << " Similar trips (e.g. similar Tr10424639 0.3)" << endl;
    
}


//
// lookupById
// 
// A function to output station details using station ID if exists,
// else station not found
// 
void lookupById(string input, hashmap<int, StationData>& stationsById)
{
    StationData ab;
    if(stationsById.search(stoi(input), ab, HashByStationID))  // search whether the station id exist or not
    {
        cout << "Station:" << endl;
        cout << " ID: " << ab.id << endl;
        cout << " Abbrev: " << ab.abbrev << endl;
        cout << " Fullname: " << ab.fullname << endl;
        cout << " Location: " << "(" << ab.latitude << ", " << ab.longitude << ")" << endl;
        cout << " Capacity: " << ab.capacity << endl;
        cout << " Online date: " << ab.online_date << endl;
    }
    else
    {
        cout << "Station not found" << endl;
    }
}


//
// lookupByAbbrev
// 
// A function to output station details using station abbrev if exists,
// else station not found
// 
void lookupByAbbrev(string input, hashmap<string, StationData> stationsByAbbrev)
{
    StationData gh;
    if(stationsByAbbrev.search(input, gh, HashByStationAbbrev))  // search whether the station abbrev exist or not
    {
        cout << "Station:" << endl;
        cout << " ID: " << gh.id << endl;
        cout << " Abbrev: " << gh.abbrev << endl;
        cout << " Fullname: " << gh.fullname << endl;
        cout << " Location: " << "(" << gh.latitude << ", " << gh.longitude << ")" << endl;
        cout << " Capacity: " << gh.capacity << endl;
        cout << " Online date: " << gh.online_date << endl;
    }
    else
    {
        cout << "Station not found" << endl;
    }
}


//
// lookupByTripId
// 
// A function to output trip details using trip ID if exists,
// else trip not found
// 
void lookupByTripId(string input, hashmap<string, TripData>& tripsById, hashmap<int, StationData>& stationsById)
{
    TripData ef;
    StationData cd;
    if(tripsById.search(input, ef, HashByTripId))  // search whether the trip ID exist or not
    {
        cout << "Trip:" << endl;
        cout << " ID: " << ef.tripid << endl;
        cout << " Starttime: " << ef.starttime << endl;
        cout << " Bikeid: " << ef.bikeid << endl;
        cout << " Duration: ";
        
        int duration = stoi(ef.duration);
        if(duration > 3600){
            cout << duration/3600 << " hours, ";
            duration = duration%3600;
        }
        cout << duration/60 << " minutes, " << duration%60 << " seconds" << endl;  // calculating duration of the trip
        
        stationsById.search(ef.from, cd, HashByStationID);  // searching for station name using station ID
        cout << " From station: " << cd.abbrev << " (" << ef.from << ")" << endl;
        
        stationsById.search(ef.to, cd, HashByStationID);  // searching for station name using station ID
        cout << " To station: " << cd.abbrev << " (" << ef.to << ")" << endl;
        cout << " Rider identifies as: " << ef.identifies << endl;
        cout << " Birthyear: " << ef.birthyear << endl;
    }
    else
    {
        cout << "Trip not found" << endl;
    }
}


//
// lookupByBikeId
// 
// A function to output bike ID and usage using bike ID if exists,
// else bike not found
// 
void lookupByBikeId(string input, hashmap<string, int>& bikesById)
{
    int usageCount = 0;
    if(bikesById.search(input, usageCount, HashForBikeId))  // searching for bike details using bike ID
    {
        cout << "Bike:" << endl;
        cout << " ID: " << input << endl;
        cout << " Usage: " << usageCount << endl;
    }
    else
    {
        cout << "Bike not found" << endl;
    }
}


//
// nearByStations
// 
// A function to output nearby station within a range limit in ascending order secified by the user if exists,
// else none found
//
void nearByStations(string latitude, string longitude, string range, hashmap<int, StationData>& stationsById)
{
    cout << "Stations within " << range << " miles of (" << latitude << ", " << longitude << ")" << endl;
        
    vector<int> myvector = stationsById.keydata();
    priority_queue<
        pair<int,double>,           // (key,value) pair
        vector<pair<int,double>>,   // store pairs in vector
        prioritize> pq;             // prioritize function


        for(auto a : myvector){
            StationData ab;
            stationsById.search(a, ab, HashByStationID);  // searching the station id
            double dist = distBetween2Points(stod(latitude), stod(longitude), ab.latitude, ab.longitude);  // calculating distance between 2 locations
            if(dist <= stod(range))  // checking the range
            {
                pq.push(make_pair(ab.id, dist));  // insert into prioritize
            }
        }
    
    if(pq.empty())  // checking empty condition
    {
        cout << " none found" << endl;
    }
    else
    {
        while(!pq.empty())  // displaying all the nearby stations in ascending order according to distance
        {
            cout << " station " << pq.top().first << ": " << pq.top().second << " miles" << endl;
            pq.pop();
        }
    }
}


//
// similarTrips
// 
// A function to output nearby station within a range limit in ascending order secified by the user if exists,
// else none found
//
void similarTrips(string input, string range, hashmap<int, StationData>& stationsById, hashmap<string, TripData>& tripsById)
{
    TripData ab;
    StationData cd;
    
    cout << "Trips that follow a similar path (+/-" << range << " miles) as " << input << endl;
    
    if(!tripsById.search(input, ab, HashByTripId)){     // checking whether the trip exist or not
        cout << " no such trip" << endl;
    }
    else
    {    
        set<int> s;
        set<int> d;
        int trips = 0;
        vector<int> myvector = stationsById.keydata();

        tripsById.search(input, ab, HashByTripId);
        int from = ab.from;
        int to = ab.to;

        stationsById.search(from, cd, HashByStationID);
        double latitudeFrom = cd.latitude;
        double longitudeFrom = cd.longitude;

        stationsById.search(to, cd, HashByStationID);
        double latitudeTo = cd.latitude;
        double longitudeTo = cd.longitude;

        for(auto a : myvector){
            StationData ef;
            stationsById.search(a, ef, HashByStationID);
            double distFrom = distBetween2Points(latitudeFrom, longitudeFrom, ef.latitude, ef.longitude);  // calculating distance between 2 locations
            double distTo = distBetween2Points(latitudeTo, longitudeTo, ef.latitude, ef.longitude);        // calculating distance between 2 locations

            if(distFrom <= stod(range))
            {
                s.insert(ef.id);  // inserting data in set s
            }
            if(distTo <= stod(range))
            {
                d.insert(ef.id);  // inserting data in set d
            }
        }

        vector<string> myvector1 = tripsById.keydata();
        for(auto i : myvector1){
            TripData gh;
            tripsById.search(i, gh, HashByTripId);
            if((s.count(gh.from) > 0) && (d.count(gh.to) > 0)){
                trips++;   // increase trips count
            }
        }
        
        cout << " nearby starting points: ";
        for(auto b : s){
            cout << b << " ";
        }
        cout << endl;
        cout << " nearby ending points: ";
        for(auto b : d){
            cout << b << " ";
        }
        cout << endl;
        cout << " trip count: " << trips << endl;
    }
}


//
// inputData
//
// Given a filename denoting station id, station abbrev, station fullname,
// station latitude, station longitude, station capacity and station online date.
// inputs that data into the given hash table.
// 
bool inputData(string filename, hashmap<int, StationData>& stationsById, hashmap<string, StationData>& stationsByAbbrev)
{
    ifstream  infile(filename);
    
    if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
    
    // file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
    
    int stationsCount = 0;
    
    while (getline(infile, line))
    {
        stringstream s(line);
        
        string theid, thecapacity, theabbrev, thefullname, theonline_date, thelatitude, thelongitude;
        
        getline(s, theid, ',');           // first value => station id
        getline(s, theabbrev, ',');       // second value => station abbrev 
        getline(s, thefullname, ',');     // third value => station fullname
        getline(s, thelatitude, ',');
        getline(s, thelongitude, ',');
        getline(s, thecapacity, ',');
        getline(s, theonline_date, ',');
        
        //
		// store into hash table
		// 
        
        StationData ld;
        
        ld.id = stoi(theid);
        ld.abbrev = theabbrev;
        ld.fullname = thefullname;
        ld.latitude = stod(thelatitude);
        ld.longitude = stod(thelongitude);
        ld.capacity = stoi(thecapacity);
        ld.online_date = theonline_date;
        
        stationsById.insert(stoi(theid), ld, HashByStationID);         // inserting into hashmap
        stationsByAbbrev.insert(theabbrev, ld, HashByStationAbbrev);   // inserting into hashmap
        
        stationsCount++;
        
    }
    cout << "# of stations: " << stationsCount << endl;
    
    return true;  // we have data to be processed:
}


//
// inputData1
//
// Given a filename denoting trip id, trip starttime, trip stoptime,
// trip bike id, trip duration, trip from station, trip to station,
// trip identifies(gender) and trip birthyear(of the user)
// inputs that data into the given hash table.
// 
bool inputData1(string filename, hashmap<string, TripData>& tripsById, hashmap<string, int>& bikesById)
{
    ifstream  infile(filename);
    
    if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
    
    // file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
    
    int tripCount = 0;
    int bikeCount = 0;
    
    while (getline(infile, line))
    {
        stringstream s(line);
        
        int usageCount = 1;
        string thetripid, thestarttime, thestoptime, thebikeid, theduration, thefrom, theto, theidentifies, thebirthyear;
        
        getline(s, thetripid, ',');       // first value => trip id
        getline(s, thestarttime, ',');    // second value => trip starttime
        getline(s, thestoptime, ',');     // third value => trip stoptime
        getline(s, thebikeid, ',');
        getline(s, theduration, ',');
        getline(s, thefrom, ',');
        getline(s, theto, ',');
        getline(s, theidentifies, ',');
        getline(s, thebirthyear, ',');
        
        //
		// store into hash table
		// 
        
        TripData ld;
        
        ld.tripid = thetripid;
        ld.starttime = thestarttime;
        ld.stoptime = thestoptime;
        ld.bikeid = thebikeid;
        ld.duration = theduration;
        ld.from = stoi(thefrom);
        ld.to = stoi(theto);
        ld.identifies = theidentifies;
        ld.birthyear = thebirthyear;
        
        bool found = bikesById.search(thebikeid, usageCount, HashForBikeId);
        if(found)
        {
            usageCount++;   // increase usageCount
            bikeCount--;    // decrease bikeCount
        }
        
        tripsById.insert(thetripid, ld, HashByTripId);            // inserting into hashmap
        bikesById.insert(thebikeid, usageCount, HashForBikeId);   // inserting into hashmap
        
        tripCount++;  // increase tripCount
        bikeCount++;  // increase bikeCount
    }
    cout << "# of trips: " << tripCount << endl;
    cout << "# of bikes: " << bikeCount << endl << endl;
    
    return true;  // we have data to be processed:
}


int main()
{
    cout << "** DIVVY analysis program **" << endl << endl;
    
    // Allocate our hash table:
    const int A = 10000;
    const int B = 2500000;
    const int C = 50000;
    
    hashmap<int, StationData> stationsById(A);
    hashmap<string, StationData> stationsByAbbrev(A);
    hashmap<string, TripData> tripsById(B);  
    hashmap<string, int> bikesById(C);
    
    // string for filenames
    string file1;
    string file2;
    
    cout << "Enter stations file> ";
    getline(cin, file1);              // getting user input for file
    cout << "Enter trips file> ";
    getline(cin, file2);              // getting user input for file
    cout << endl;
    
    cout << "Reading " << file1 << endl;
    cout << "Reading " << file2 << endl << endl;
    
    bool stationFile = inputData(file1, stationsById, stationsByAbbrev);
    bool tripFile = inputData1(file2, tripsById, bikesById);
    
    if(!stationFile || !tripFile){   // checking file open condition
        return 0;
    }
    
    string command;

    cout << "Please enter a command, help, or #> ";
    getline(cin, command);  // getting user input
    
    while(command != "#")
    {
        if(command == "help"){
            help();  // calling help function
        }
        
        else if(isNumeric(command))
        {
            lookupById(command, stationsById);  // calling lookupById function
        }
        
        else if(command.substr(0,2) == "Tr")
        {
            lookupByTripId(command, tripsById, stationsById);  // calling lookupByTripId function
        }
        
        else if(command.substr(0,1) == "B")
        {
            lookupByBikeId(command, bikesById);  // calling lookupByBikeId function
        }
        
        else if(command.substr(0,6) == "nearby")
        {
            stringstream s(command);
            string nearby, latitude, longitude, range;
            getline(s, nearby, ' ');
            getline(s, latitude, ' ');
            getline(s, longitude, ' ');
            getline(s, range, ' ');
            
            nearByStations(latitude, longitude, range, stationsById);  // calling nearByStations function
        }
        
        else if(command.substr(0,7) == "similar")
        {
            stringstream s(command);
            string similar, tripid, range;
            getline(s, similar, ' ');
            getline(s, tripid, ' ');
            getline(s, range, ' ');
            
            similarTrips(tripid, range, stationsById, tripsById);  // calling similarTrips function
        }
        
        else
        {
            lookupByAbbrev(command, stationsByAbbrev);  // calling lookupByAbbrev function
        }
        
        cout << endl;
        cout << "Please enter a command, help, or #> ";
        getline(cin, command);  // getting user input
        
    }
	return 0;
}
