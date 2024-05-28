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
  Object() {
#ifdef CHECK_MEMORY_LEAK
    allObjects_.insert(this);
#endif
  }

  virtual ~Object() {
#ifdef CHECK_MEMORY_LEAK
    allObjects_.erase(this);
#endif
  }

  std::string toString() {
    std::ostringstream oss;
    oss << id_ << "<" << name() << ">";
    return oss.str();
  }

  // 메모리 누수를 검사한다
  static void checkMemoryLeak() {
#ifdef CHECK_MEMORY_LEAK
    // 기록된 오브젝트가 남아있는 경우에는 메모리 누수가 발견된 것이다.
    if (allObjects_.size() > 0) {
      std::cerr << "Memory leak detected!" << std::endl
                << "Following objects are not deleted:" << std::endl;
      for (Object *object : allObjects_) {
        std::cerr << "  " << object->toString() << std::endl;
      }
    } else {
      std::cout << "No memory leak detected." << std::endl;
    }
#else
    std::cout << "Memory leak check is disabled." << std::endl;
#endif
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