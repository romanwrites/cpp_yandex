#pragma once
#include "date.h"
#include <memory>

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum class LogicalOperation {
  And,
  Or
};

class Node {
 public:
  virtual bool Evaluate(Date const &date_compare_to, std::string const &event_compare_to) const = 0;
};

class EmptyNode : public Node {
 public:
  bool Evaluate(const Date &date_compare_to, const std::string &event_compare_to) const override;
};

class LogicalOperationNode : public Node {

 public:
  bool Evaluate(const Date &date_compare_to, const std::string &event_compare_to) const override;
  LogicalOperationNode(const LogicalOperation operation, const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs);

 private:
  LogicalOperation const operation;
  std::shared_ptr<Node> const lhs;
  std::shared_ptr<Node> const rhs;
};


class EventComparisonNode : public Node {

 public:
  bool Evaluate(const Date &date_compare_to, const std::string &event_compare_to) const override;

  EventComparisonNode(Comparison const &comparison, std::string const &event);

 private:
  Comparison const comparison;
  std::string const event;
};


class DateComparisonNode : public Node {

 public:
  bool Evaluate(const Date &date_compare_to, const std::string &event_compare_to) const override;

  DateComparisonNode(Comparison const &comparison, Date const &date);

 private:
  Comparison const comparison;
  Date const date;
};

