#include "address.h"
#include "host.h"
#include "link.h"
#include <set>
#include <vector>

struct NatEntry {
  Address internalAddress;
  short internalPort;
  short externalPort;
};

class Nat : public Node {
private:
  Address address_;

  Link *wanLink_;
  std::vector<NatEntry> natTable_;

  int lastPort_ = 1000;

  Packet *convertInternetToLanPacket(Packet* packet) {
    NatEntry* entry = 나트엔트리조회(packet);
    Packet* newPacket = new Packet(packet->srcAddress(), entry->internalAddress,  packet->srcPort(), entry->internalPort);
    return newPacket;
  }
  
  int getNewPort() {
    return lastPort_++;
  }

  void addNatEntry(Packet* packet) {
    int natPort = getNewPort();
    NatEntry* entry = new NatEntry();
    entry->internalAddress = packet->srcAddress();
    entry->internalPort = packet->srcPort();
    entry->externalPort = natPort;
    entries_.push_back(entry);
  }

  
  Packet *convertLanPacketToInternetPacket(Packet* packet) {
    NatEntry* entry;
    if(연결이처음생긴경우(packet)) {
      entry = addNatEntry(packet);
    }
    else  { // 연결이 이미 있으면
      entry = 나트엔트리조회(packet);
    }

    Packet* newPacket = new Packet(
      address_,
      packet->destAddress(),
      entry->externalPort,
      packet->destPort(),
    );

    return newPacket;
  }
  

public:
  Nat(Address address) : address_(address) {}
  void setWanLink(Link *link) { wanLink_ = link; }

  void onReceive(Link* link, Packet* packet) override {

  }
};
