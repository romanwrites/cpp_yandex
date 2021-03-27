#include "database.h"
using namespace std;

std::vector<std::string> Database::FindIf(std::function<bool(Date, std::string)> const &predicate) const {
  std::vector<std::string> entries;

  auto it = storage_vector.begin();
  while (it != storage_vector.end()) {
    for (auto vec_it = it->second.begin(); vec_it != it->second.end(); ++ vec_it) {
      if (predicate(it->first, *vec_it)) {
        entries.push_back(it->first.ToString() + " " + *vec_it);
      }
    }
    ++it;
  }

  return entries;
}

void Database::Add(const Date &date, const string &event) {
  auto const res = storage[date].insert(event);

  if (res.second) {
    storage_vector[date].push_back(event);
  }
}

void Database::Print(ostream &o) const {
  for (auto const &entry : storage_vector) {
    for (auto const &event : entry.second) {
      o << entry.first.ToString() << " " << event << endl;
    }
  }
}

std::string Database::Last(Date const &date) const {
  auto it = storage_vector.upper_bound(date);

  if (it == storage_vector.begin()) {
    return "No entries";
  }

  it = prev(it);

  return it->first.ToString() + " " + it->second.back();
}
