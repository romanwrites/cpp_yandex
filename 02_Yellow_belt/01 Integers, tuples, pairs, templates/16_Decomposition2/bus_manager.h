#pragma once
#include <iostream>
#include <map>
#include "responses.h"
using namespace std;

class BusManager {
private:
    map<string, vector<string> > buses_to_stops;
    map<string, vector<string> > stops_to_buses;

public:
    void AddBus(const string& bus, const vector<string>& stops);

    BusesForStopResponse GetBusesForStop(const string& stop) const;

    StopsForBusResponse GetStopsForBus(const string& bus) const;

    AllBusesResponse GetAllBuses() const;
};
