#ifndef OBJECT_H
#define OBJECT_H

#include "simulator.h"
#include <iomanip>
#include <ios>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class Object {
private:
  static std::set<Object *> allObjects_;

  std::string generateId() {
    std::string id = std::to_string(rand() % 10000);
    if (id.length() < 4) {
      while (id.length() < 4) {
        id = "0" + id;
      }
    }
    return id;
  }
  std::string id_ = generateId();
  virtual std::string name() = 0;

public:
  Object() { allObjects_.insert(this); }

  virtual ~Object() { allObjects_.erase(this); }

  std::string toString() {
    std::ostringstream oss;
    oss << id_ << "<" << name() << ">";
    return oss.str();
  }

  virtual void initialize() {}

  // 모든 오브젝트를 초기화한다
  static void initializeAll() {
    for (Object *object : allObjects_) {
      object->initialize();
    }
  }

  // 모든 오브젝트를 메모리에서 해제한다.
  static void cleanup() {
    while (!allObjects_.empty()) {
      delete *allObjects_.begin();
    }
  }

  // 더미 함수
  static void checkMemoryLeak() {
    std::cout << "No memory leak detected." << std::endl;
  }

protected:
  void log(std::string message) {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss.precision(2);
    oss << Simulator::now() << "s";
    std::cout << std::setw(10) << std::left << oss.str() << std::setw(30)
              << std::left << toString() << " " << message << std::endl;
  }
};

#endif