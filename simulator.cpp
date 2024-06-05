#include "simulator.h"
#include "object.h"

double Simulator::time_ = 0.0;

void Simulator::run() {
  Object::initializeAll();

  // 모든 스케줄을 실행한다.
  // TODO: 구현

  Object::cleanup();
}