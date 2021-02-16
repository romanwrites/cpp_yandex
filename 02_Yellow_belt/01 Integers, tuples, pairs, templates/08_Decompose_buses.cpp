#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string type;
    is >> type;
    if (type == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
        }
    } else if (type == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (type == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (type == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop" << endl;
    } else {
        for (const string& bus : r.buses) {
            os << bus << " ";
        }
        os << endl;
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<pair<string, vector<string> > > stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops_to_buses.empty()) {
        os << "No bus" << endl;
    } else {
        for (auto const& stop : r.stops_to_buses) {
            os << "Stop " << stop.first << ": ";
            if (stop.second.size() == 1) {
                os << "no interchange";
            } else {
                for (auto const& other_bus : stop.second) {
                    if (r.bus != other_bus) {
                        os << other_bus << " ";
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
        cout << "No buses" << endl;
    } else {
        for (const auto& bus_item : r.buses_to_stops) {
            cout << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                cout << stop << " ";
            }
            cout << endl;
        }
    }
    return os;
}

class BusManager {
private:
    map<string, vector<string> > buses_to_stops;
    map<string, vector<string> > stops_to_buses;

public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (auto const &stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_to_buses.count(stop) == 0) {
            return BusesForStopResponse();
        } else {
            return BusesForStopResponse{stops_to_buses.at(stop)};
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        vector<pair<string, vector<string> > > stops_to_buses_tmp;

        if (buses_to_stops.count(bus) == 0) {
            return StopsForBusResponse{bus, stops_to_buses_tmp};
        }
        for (auto const &i : buses_to_stops.at(bus)) {
            stops_to_buses_tmp.push_back({i, stops_to_buses.at(i)});
        }
        return StopsForBusResponse{bus, stops_to_buses_tmp};
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse{buses_to_stops};
    }
};

/*
Test:
10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES
 */

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
