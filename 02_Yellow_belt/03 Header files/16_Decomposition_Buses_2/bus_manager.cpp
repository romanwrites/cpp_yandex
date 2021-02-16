#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (auto const &stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
        return BusesForStopResponse();
    } else {
        return BusesForStopResponse{stops_to_buses.at(stop)};
    }
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    vector<pair<string, vector<string> > > stops_to_buses_tmp;

    if (buses_to_stops.count(bus) == 0) {
        return StopsForBusResponse{bus, stops_to_buses_tmp};
    }
    for (auto const &i : buses_to_stops.at(bus)) {
        stops_to_buses_tmp.push_back({i, stops_to_buses.at(i)});
    }
    return StopsForBusResponse{bus, stops_to_buses_tmp};
}

AllBusesResponse BusManager::GetAllBuses() const {
    return AllBusesResponse{buses_to_stops};
}
