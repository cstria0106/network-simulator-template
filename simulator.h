#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RANDOM_SEED 369369

#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>

class Simulator;

class Schedule {
private:
  double time_;
  std::function<void()> function_;

public:
  double time() { return time_; }
  void call() { function_(); }

  Schedule(double time, std::function<void()> function)
      : time_(time), function_(function) {}
};

class Simulator {
private:
  static double time_;
  static std::priority_queue<Schedule> schedules_;

public:
  static double now() { return time_; }

  static void prepare() { srand(RANDOM_SEED); }

  static void schedule(double time, std::function<void()> function) {
    schedules_.push(Schedule (time, function));
  }

  static void run() {
    while(!schedules_.empty()) {
      Schedule schedule = schedules_.top();
      schedules_.pop();

      time_ = schedule.time();
      schedule.call();
    }
  }
};

#endif