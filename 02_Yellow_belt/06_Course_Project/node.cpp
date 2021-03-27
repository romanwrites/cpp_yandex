#include "node.h"
#include <string>
#include "date.h"

using namespace std;

bool EmptyNode::Evaluate(Date const &date_compare_to, string const &event_compare_to) const {
  return true;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation const operation, shared_ptr<Node> const &lhs, shared_ptr<Node> const &rhs) :
    operation(operation), lhs(lhs), rhs(rhs) {}

bool LogicalOperationNode::Evaluate(Date const &date_compare_to, string const &event_compare_to) const {
  switch (this->operation) {
    case LogicalOperation::And:
      return lhs->Evaluate(date_compare_to, event_compare_to) && rhs->Evaluate(date_compare_to, event_compare_to);
    case LogicalOperation::Or:
      return lhs->Evaluate(date_compare_to, event_compare_to) || rhs->Evaluate(date_compare_to, event_compare_to);
  }
}

EventComparisonNode::EventComparisonNode(Comparison const &comparison,  string const &event) :
    comparison(comparison), event(event) {}

bool EventComparisonNode::Evaluate(Date const &date_compare_to, string const &event_compare_to) const {
  switch (this->comparison) {
    case Comparison::Less:
      return event_compare_to < this->event;
    case Comparison::LessOrEqual:
      return event_compare_to <= this->event;
    case Comparison::Greater:
      return event_compare_to > this->event;
    case Comparison::GreaterOrEqual:
      return event_compare_to >= this->event;
    case Comparison::Equal:
      return event_compare_to == this->event;
    case Comparison::NotEqual:
      return event_compare_to != this->event;
  }
}

DateComparisonNode::DateComparisonNode(Comparison const &comparison,  Date const &date) :
    comparison(comparison), date(date) {}

bool DateComparisonNode::Evaluate(Date const &date_compare_to, string const &event_compare_to) const {
  switch (this->comparison) {
    case Comparison::Less:
      return date_compare_to < this->date;
    case Comparison::LessOrEqual:
      return date_compare_to <= this->date;
    case Comparison::Greater:
      return date_compare_to > this->date;
    case Comparison::GreaterOrEqual:
      return date_compare_to >= this->date;
    case Comparison::Equal:
      return date_compare_to == this->date;
    case Comparison::NotEqual:
      return date_compare_to != this->date;
  }
}

