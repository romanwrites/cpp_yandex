#include "test_runner.h"
#include "database.h"
#include "condition_parser.h"
#include <sstream>
#include "node.h"
#include "test_runner.h"

#include <sstream>

/*
Вставить в main
------------------------------------------------------
  tr.RunTest(TestEmptyNode, "Тест 2 из Coursera");
  tr.RunTest(TestDbAdd, "Тест 3(1) из Coursera");
  tr.RunTest(TestDbFind, "Тест 3(2) из Coursera");
  tr.RunTest(TestDbLast, "Тест 3(3) из Coursera");
  tr.RunTest(TestDbRemoveIf, "Тест 3(4) из Coursera");
  tr.RunTest(TestInsertionOrder, "Тест на порядок вывода");
  tr.RunTest(TestsMyCustom, "Мои тесты");
  tr.RunTest(TestDatabase, "Тест базы данных с GitHub");
 -------------------------------------------------------
 */

using namespace std;

class AlwaysFalseNode : public Node {
	bool Evaluate(const Date&, const std::string& event) const override {
		return false;
	}
};

string ParseEvent(istream& is);

int DoRemove (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    return db.RemoveIf(predicate);
}

string DoFind (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    ostringstream os;
    for (const auto& entry : entries) {
        os << entry << endl;
    }
    os << entries.size();
    return os.str();
}

void TestDbAdd() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "straight ordering");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "holiday");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-01 holiday\n", out.str(), "several in one day");
    }
    {
        Database db;
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "reverse ordering");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-01 xmas\n", out.str(), "uniq adding");
    }
}

void TestDbFind() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, "date == 2017-01-01"), "simple find by date");
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", DoFind(db, "date < 2017-01-31"), "multiple find by date");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, R"(event != "xmas")"), "multiple find by holiday");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "new year2");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", DoFind(db, R"(date == 2017-01-07 OR event == "new year")"),
                "complex find or");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, R"(date == 2017-01-01 AND event == "new year")"),
                    "complex find and");
        AssertEqual("0", DoFind(db, R"(date == 2017-01-09 AND event == "new year")"),
                    "complex find and, nothing");
    }

  {
    Database db;
    db.Add({2017, 1, 1}, "new year");
    db.Add({2017, 1, 1}, "Holiday");
    db.Add({2017, 1, 7}, "xmas");
    AssertEqual("2017-01-07 xmas\n1", DoFind(db, "date == 2017-01-07"), "single find by date");
    AssertEqual("2017-01-01 new year\n2017-01-01 Holiday\n2017-01-07 xmas\n3", DoFind(db, "date < 2017-01-31"), "multiple find by date");
    AssertEqual("2017-01-01 new year\n2017-01-01 Holiday\n2", DoFind(db, R"(event != "xmas")"), "multiple find by event != xmas ");
    AssertEqual("2017-01-01 Holiday\n2017-01-07 xmas\n2", DoFind(db, R"(event != "new year")"), "multiple find by event != new year");
  }

  {
    Database db;
    db.Add({2017, 1, 1}, "event3");
    db.Add({2017, 1, 1}, "event2");
    db.Add({2017, 1, 1}, "event1");
    AssertEqual("2017-01-01 event3\n2017-01-01 event2\n2017-01-01 event1\n3",
                DoFind(db, "date == 2017-1-1"), "output in order by FindIf");
  }
}

void TestDbLast(){
  Database db;
  db.Add({2017, 1, 1}, "new year");
  db.Add({2017, 1, 7}, "xmas");
  {
    try {
      db.Last({2016, 12, 31});
      Assert(false, "last, found no entries");
    } catch (...){
      Assert(true, "last, found no entries");

    }
  }
  {
    ostringstream os;
    os << db.Last({2017, 1, 2});
    AssertEqual("2017-01-01 new year", os.str(), "greater than date");
  }
  {
    ostringstream os;
    os << db.Last({2017, 1, 1});
    AssertEqual("2017-01-01 new year", os.str(), "eq to date");
  }
  {
    ostringstream os;
    os << db.Last({2017, 1, 10});
    AssertEqual("2017-01-07 xmas", os.str(), "greater than max date");
  }
}

void TestDbRemoveIf () {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual(0, DoRemove(db, R"(event == "something")"), "Remove nothing");
        AssertEqual(1, DoRemove(db, R"(date == "2017-01-01")"), "Remove by date");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-07 xmas\n", out.str(), "Remove by date, left");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual(1, DoRemove(db, R"(event == "xmas")"), "Remove by event");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n", out.str(), "Remove by event, left");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 7}, "new year");
        AssertEqual(2, DoRemove(db, R"(event == "new year")"), "Multiple remove by event");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-07 xmas\n", out.str(), "Multiple remove by event, left");
    }
}

void TestInsertionOrder()
{
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 7}, "party");
        db.Add({2017, 1, 7}, "pie");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2017-01-07 party\n2017-01-07 pie\n", out.str(), "Remove by date, left");
    }

}

void TestsMyCustom()
{
    {
        Database db;
        db.Add({2019, 12, 18}, "Kolya");
        db.Add({2020, 1, 15}, "Katya");
        db.Add({2020, 2, 22}, "Riding");
        db.Add({2019, 12, 9}, "Go home");
        db.Add({2019, 12, 9}, "Read");
        ostringstream out;
        db.Print(out);
        AssertEqual("2019-12-09 Go home\n2019-12-09 Read\n2019-12-18 Kolya\n2020-01-15 Katya\n2020-02-22 Riding\n", out.str(), "Order of insertion");
    }

    {
        Database db;
        db.Add({2019, 12, 1}, "a");
        db.Add({2019, 12, 1}, "b");
        db.Add({2019, 12, 2}, "c");
        db.Add({2019, 12, 2}, "d");
        db.Add({2019, 12, 3}, "e");
        ostringstream out;
        db.Print(out);
        AssertEqual("2019-12-01 a\n2019-12-01 b\n2019-12-02 c\n2019-12-02 d\n2019-12-03 e\n", out.str(), "Order of insertion");
    }

    {
        Database db;
        istringstream ss("    a");
        const auto event = ParseEvent(ss);
        db.Add({2019, 12, 1}, event);
        ostringstream out;
        db.Print(out);
        AssertEqual("2019-12-01 a\n", out.str(), "My test 20");
    }

    {
        Database db;
        db.Add({2019, 12, 1}, "a");
        db.Add({2019, 12, 1}, "b");
        db.Add({2019, 12, 2}, "c c");
        db.Add({2019, 12, 2}, "d");
        db.Add({2019, 12, 3}, "e");
        db.Add({2019, 12, 3}, "f");
        ostringstream out;
        db.Print(out);
        AssertEqual("2019-12-01 a\n2019-12-01 b\n2019-12-02 c c\n2019-12-02 d\n2019-12-03 e\n2019-12-03 f\n", out.str(), "My test 2");
        AssertEqual(1, DoRemove(db, R"(event == "c" OR event == "d")" ), "My test 3");
        AssertEqual(1, DoRemove(db, R"(event == "e" AND event != "a")" ), "My test 4");
        db.Add({2019, 11, 30}, "a");
        AssertEqual("2019-12-03 f\n1", DoFind(db, R"(date >= 2019-12-3)"), "My test 5");
        AssertEqual("2019-12-03 f", db.Last({2019, 12, 4}), " My test 6");

        try
        {
            db.Last({2019, 11, 3});    
        }
        catch(invalid_argument&)
        {
            cerr << "Тест на No entries OK" << endl;
        }

        AssertEqual("2019-12-02 c c", db.Last({2019, 12, 2}), " My test 7");

        AssertEqual("2019-12-03 f", db.Last({2019, 12, 4}), " My test 8");
        
        db.Add({2019, 12, 3}, "m");
        AssertEqual("2019-12-03 m", db.Last({2019, 12, 3}), " My test 9");

        AssertEqual(1, DoRemove(db, R"(event == "e" AND event != "a" OR event == "m" AND date == 2019-12-3)" ), "My test 10");

        ostringstream out2;
        db.Print(out2);
        AssertEqual("2019-11-30 a\n2019-12-01 a\n2019-12-01 b\n2019-12-02 c c\n2019-12-03 f\n", out2.str(), "My test 11");
    }

    {
        Database db;
        db.Add({2019, 12, 1}, "a");
        db.Add({2019, 12, 1}, "b");
        db.Add({2019, 12, 1}, "a");
        db.Add({2019, 12, 2}, "c");
        db.Add({2019, 12, 2}, "a");
        db.Add({2019, 12, 2}, "a");

        AssertEqual(2, DoRemove(db, R"(event == "a")" ), "My test 12");
    }

    {
        Database db;
        db.Add({2019, 12, 1}, "a");
        db.Add({2019, 12, 1}, "aa");
        db.Add({2019, 12, 1}, "aaa");

        AssertEqual(2, DoRemove(db, R"(event >= "aa")" ), "My test 13");

        ostringstream out;
        db.Print(out);
        AssertEqual("2019-12-01 a\n", out.str(), "My test 14");
    }

    {
        Database db;
        db.Add({2019, 12, 1}, "a");
        db.Add({2019, 12, 1}, "aa");
        db.Add({2019, 12, 1}, "aaa");
        db.Add({2019, 12, 2}, "b");
        db.Add({2019, 12, 2}, "a");

        AssertEqual(2, DoRemove(db, R"(event > "aa")" ), "My test 15");

        ostringstream out;
        db.Print(out);
        AssertEqual("2019-12-01 a\n2019-12-01 aa\n2019-12-02 a\n", out.str(), "My test 16");
    }

    {
        Database db;
        db.Add({2019, 12, 1}, "a");
        db.Add({2019, 12, 1}, "aa");
        db.Add({2019, 12, 1}, "aaa");
        db.Add({2019, 12, 2}, "b");
        db.Add({2019, 12, 2}, "a");

        AssertEqual(2, DoRemove(db, R"(event < "aa")" ), "My test 17");

        ostringstream out;
        db.Print(out);
        AssertEqual("2019-12-01 aa\n2019-12-01 aaa\n2019-12-02 b\n", out.str(), "My test 18");
    }

    {
        Database db;
        db.Add({2019, 12, 1}, "a");
        db.Add({2019, 12, 1}, "b");

        AssertEqual(1, DoRemove(db, R"(event != "b")" ), "My test 19");

        db.Add({2019, 12, 1}, "c");

        AssertEqual("2019-12-01 c", db.Last({2019, 12, 1}), " My test 20");

        db.Add({2019, 12, 1}, "b");
        AssertEqual("2019-12-01 c", db.Last({2019, 12, 1}), " My test 21");

        ostringstream out;
        db.Print(out);
        AssertEqual("2019-12-01 b\n2019-12-01 c\n", out.str(), "My test 22");
    }

    
}

void TestDatabase() {
  istringstream empty_is("");
  auto empty_condition = ParseCondition(empty_is);
  auto empty_predicate = [empty_condition](const Date& date, const string& event) {
    return empty_condition->Evaluate(date, event);
  };

  // Add 2 - Del 1 - Add deleted again
  {
    Database db;
    Date d(2019, 1, 1);
    db.Add(d, "e1");
    db.Add(d, "e2");
    istringstream is(R"(event == "e1")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.RemoveIf(predicate), 1, "Db Add2-Del-Add 1");
    db.Add(d, "e1");
    AssertEqual(db.FindIf(empty_predicate).size(), 2, "Db Add2-Del-Add 2");
  }

  // Add
  {
    Database db;
    Date d(2019, 1, 1);
    db.Add(d, "e1");
    db.Add(d, "e1");
    istringstream is("date == 2019-01-01");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.FindIf(predicate).size(), 1, "Db Add Duplicates 1");
  }

  // Last
  {
    Database db;
    Date d(2019, 1, 1);
    Date d1(2019, 1, 2);
    Date d2(2018, 12, 22);
    db.Add(d1, "e1");
    db.Add(d2, "e2");
    AssertEqual(db.Last(d), "2018-12-22 e2", "Db Last 1");
    Date d3(2018, 12, 24);
    db.Add(d3, "e3");
    AssertEqual(db.Last(d), "2018-12-24 e3", "Db Last 2");

//    // Get last event for date before first event
//    try {
//      Date d4(2017, 2, 2);
//      db.Last(d4);
//      Assert(false, "Db Last 3");
//    } catch (invalid_argument e) {
//      // Pass
//    }

    // Delete event and get last
    istringstream is("date == 2018-12-24");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    db.RemoveIf(predicate);
    AssertEqual(db.Last(d), "2018-12-22 e2", "Db Last 4");

    AssertEqual(db.Last(d1), "2019-01-02 e1", "Db Last 5");
    db.Add(d2, "e4");
    AssertEqual(db.Last(d2), "2018-12-22 e4", "Db Last 6");
  }

  // Del
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date == 2018-01-07");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.RemoveIf(predicate), 2, "Db Del 1");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.RemoveIf(predicate), 4, "Db Del 2");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    AssertEqual(db.RemoveIf(empty_predicate), 4, "Db Del 3");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.RemoveIf(predicate), 1, "Db Del 4");
  }

  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1" OR date == 2019-01-01)");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.RemoveIf(predicate), 2, "Db Del 5");
  }

  // Find
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date == 2018-01-07");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.FindIf(predicate).size(), 2, "Db Find 1");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.FindIf(predicate).size(), 4, "Db Find 2");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    AssertEqual(db.FindIf(empty_predicate).size(), 4, "Db Find 3");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.FindIf(predicate).size(), 1, "Db Find 4");
  }

  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1" OR date == 2019-01-01)");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };    
    AssertEqual(db.FindIf(predicate).size(), 2, "Db Find 5");
  }

  // Add - Del - Add - Del
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");

    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");
  }

  {
    Database db;
    db.Add({2017, 1, 1}, "first");
    db.Add({2017, 1, 1}, "second");
    db.Add({2017, 1, 1}, "third");
    db.Add({2017, 1, 1}, "fourth");
    db.Add({2017, 1, 1}, "five");
    AssertEqual(2, DoRemove(db, R"(event == "second" OR event == "fourth")"), "Remove several");
    ostringstream os;
    db.Print(os);
    AssertEqual("2017-01-01 first\n2017-01-01 third\n2017-01-01 five\n", os.str(), "Check print after remove several- 3");
    }
}

void TestDateComparisonNode() {
  {
	DateComparisonNode dcn(Comparison::Equal, {2017, 11, 18});
	Assert(dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 1");
	Assert(!dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 2");
  }
  {
	DateComparisonNode dcn(Comparison::NotEqual, {2017, 11, 18});
	Assert(dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 3");
	Assert(!dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 4");
  }
  {
	DateComparisonNode dcn(Comparison::Less, {2017, 11, 18});
	Assert(dcn.Evaluate(Date{2017, 11, 17}, ""), "DateComparison 5");
	Assert(!dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 6");
	Assert(!dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 7");
  }
  {
	DateComparisonNode dcn(Comparison::Greater, {2017, 11, 18});
	Assert(dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 8");
	Assert(!dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 9");
	Assert(!dcn.Evaluate(Date{2017, 11, 17}, ""), "DateComparison 10");
  }
  {
	DateComparisonNode dcn(Comparison::LessOrEqual, {2017, 11, 18});
	Assert(dcn.Evaluate(Date{2017, 11, 17}, ""), "DateComparison 11");
	Assert(dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 12");
	Assert(!dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 13");
  }
  {
	DateComparisonNode dcn(Comparison::GreaterOrEqual, {2017, 11, 18});
	Assert(dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 14");
	Assert(dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 15");
	Assert(!dcn.Evaluate(Date{2017, 11, 17}, ""), "DateComparison 16");
  }
}

void TestEventComparisonNode() {
  {
	EventComparisonNode ecn(Comparison::Equal, "abc");
	Assert(ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 1");
	Assert(!ecn.Evaluate(Date{0, 1, 1}, "cbe"), "EventComparison 2");
  }
  {
	EventComparisonNode ecn(Comparison::NotEqual, "abc");
	Assert(ecn.Evaluate(Date{0, 1, 1}, "cde"), "EventComparison 3");
	Assert(!ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 4");
  }
  {
	EventComparisonNode ecn(Comparison::Less, "abc");
	Assert(ecn.Evaluate(Date{0, 1, 1}, "abb"), "EventComparison 5");
	Assert(!ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 6");
	Assert(!ecn.Evaluate(Date{0, 1, 1}, "abd"), "EventComparison 7");
  }
  {
	EventComparisonNode ecn(Comparison::Greater, "abc");
	Assert(ecn.Evaluate(Date{0, 1, 1}, "abd"), "EventComparison 8");
	Assert(!ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 9");
	Assert(!ecn.Evaluate(Date{0, 1, 1}, "abb"), "EventComparison 10");
  }
  {
	EventComparisonNode ecn(Comparison::LessOrEqual, "abc");
	Assert(ecn.Evaluate(Date{0, 1, 1}, "abb"), "EventComparison 11");
	Assert(ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 12");
	Assert(!ecn.Evaluate(Date{0, 1, 1}, "abd"), "EventComparison 13");
  }
  {
	EventComparisonNode ecn(Comparison::GreaterOrEqual, "abc");
	Assert(ecn.Evaluate(Date{0, 1, 1}, "abd"), "EventComparison 14");
	Assert(ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 15");
	Assert(!ecn.Evaluate(Date{0, 1, 1}, "abb"), "EventComparison 16");
  }
}

void TestLogicalOperationNode() {
  {
	LogicalOperationNode lon(LogicalOperation::And, make_shared<EmptyNode>(), make_shared<EmptyNode>());
	Assert(lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 1");
  }
  {
	LogicalOperationNode lon(LogicalOperation::And, make_shared<AlwaysFalseNode>(), make_shared<EmptyNode>());
	Assert(!lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 2");
  }
  {
	LogicalOperationNode lon(LogicalOperation::And, make_shared<EmptyNode>(), make_shared<AlwaysFalseNode>());
	Assert(!lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 3");
  }
  {
	LogicalOperationNode lon(LogicalOperation::And, make_shared<AlwaysFalseNode>(), make_shared<AlwaysFalseNode>());
	Assert(!lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 4");
  }
  {
	LogicalOperationNode lon(LogicalOperation::Or, make_shared<EmptyNode>(), make_shared<EmptyNode>());
	Assert(lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 5");
  }
  {
	LogicalOperationNode lon(LogicalOperation::Or, make_shared<AlwaysFalseNode>(), make_shared<EmptyNode>());
	Assert(lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 6");
  }
  {
	LogicalOperationNode lon(LogicalOperation::Or, make_shared<EmptyNode>(), make_shared<AlwaysFalseNode>());
	Assert(lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 7");
  }
  {
	LogicalOperationNode lon(LogicalOperation::Or, make_shared<AlwaysFalseNode>(), make_shared<AlwaysFalseNode>());
	Assert(!lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 8");
  }
}

void TestEmptyNode() {
  {
	EmptyNode en;
	Assert(en.Evaluate(Date{0, 1, 1}, "abc"), "EmptyNode 1");
	Assert(en.Evaluate(Date{2017, 11, 18}, "def"), "EmptyNode 2");
	Assert(en.Evaluate(Date{9999, 12, 31}, "ghi"), "EmptyNode 3");
  }
}