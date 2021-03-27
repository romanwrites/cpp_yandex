#pragma once

#include "date.h"
#include <string>
#include <iosfwd>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <functional>

class Database {
 public:
  void Add(Date const &date, std::string const &event);
  void Print(std::ostream &o) const;

  template<class Predicate>
  int RemoveIf(Predicate const &predicate) {
    int count = 0;

    auto it = storage_vector.begin();
    while (it != storage_vector.end()) {
      auto const border = std::stable_partition(
          it->second.begin(),
          it->second.end(),
          [&](std::string &event) {
            return predicate(it->first, event);
      });

      for (auto vector_it = it->second.begin(); vector_it != border; ++vector_it) {
        storage.at(it->first).erase(*vector_it);
        ++count;
      }

      it->second.erase(it->second.begin(), border);

      if (it->second.empty()) {
        storage.erase(it->first);
        it = storage_vector.erase(it);
      } else {
        ++it;
      }
    }

    return count;
  }

  std::vector<std::string> FindIf(std::function<bool(Date, std::string)> const &predicate) const;

  std::string Last(Date const &date) const;

 private:
  std::map<Date, std::set<std::string> > storage;
  std::map<Date, std::vector<std::string> > storage_vector;

};
