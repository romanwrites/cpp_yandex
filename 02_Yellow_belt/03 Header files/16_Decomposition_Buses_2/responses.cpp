#include "responses.h"

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
