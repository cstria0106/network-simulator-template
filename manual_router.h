#ifndef MANUAL_ROUTER_H
#define MANUAL_ROUTER_H

#include "address.h"
#include "router.h"

class ManualRouter : public Router {

public:
  // 목적지 주소에 따른 다음 링크를 설정한다.
  void addRoutingEntry(const Address &destination, Link *nextLink);
};

#endif