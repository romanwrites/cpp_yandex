#include "query.h"

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
