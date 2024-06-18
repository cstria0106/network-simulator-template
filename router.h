#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;
};

class Router : public Node {
protected:
  std::vector<RoutingEntry> routingTable_;

  void onReceive(Packet* packet) override {
    for(int i =0 ; i< routingTable_.size(); i++) {
      RoutingEntry entry = routingTable_[i];
      if(entry.destination == packet->destAddress()) {
        entry.nextLink->onReceive(this, packet);
        break;
      }
    }
  }
};

#endif