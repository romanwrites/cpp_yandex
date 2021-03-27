#include "test_runner.h"

using namespace std;

TestRunner::~TestRunner() {
  if (fail_count > 0) {
    std::cerr << fail_count << " tests failed. Terminate" << std::endl;
    exit(1);
  }
}

void Assert(bool b, string const &hint) {
  AssertEqual(b, true, hint);
}
