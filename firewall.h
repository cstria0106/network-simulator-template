#include "address.h"
#include "node.h"
#include "object.h"
#include <set>
#include <string>

class FirewallPolicy : public Object {};

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

public:
  void setReceiveLink(Link *link) { receiveLink_ = link; }

  void addAllowAnyPolicy(short destPort);
  void addAllowSpecificPolicy(Address srcAddress, short destPort);
};