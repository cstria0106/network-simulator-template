#include "address.h"
#include "node.h"
#include "object.h"
#include <set>
#include <string>

class FirewallPolicy : public Object {
  public:
  virtual bool isAllowed(Packet* packet);
};

class Firewall : public Node {
private:
  class AllowAnyPolicy : public FirewallPolicy {
  private:
    short destPort_;

  public:
    AllowAnyPolicy(short destPort) : destPort_(destPort) {}
  };

  class AllowSpecificPolicy : public FirewallPolicy {
  private:
    Address srcAddress_;
    short destPort_;

  public:
    AllowSpecificPolicy(Address srcAddress, short destPort)
        : srcAddress_(srcAddress), destPort_(destPort) {}
  };

  Link *receiveLink_ = nullptr;
  std::vector<FirewallPolicy*> policies_;

public:
  void setReceiveLink(Link *link) { receiveLink_ = link; }

  void addAllowAnyPolicy(short destPort);
  void addAllowSpecificPolicy(Address srcAddress, short destPort);

  void onReceive(Packet* packet) {
    for(int i = 0; i < policies_.size(); i++) {
      FirewallPolicy* policy =  policies_[i];
      if(policy->isAllowed(packet)) {
        allowPacket(packet);
        return;
      }
    }

    dropPacket(packet);
  }
};