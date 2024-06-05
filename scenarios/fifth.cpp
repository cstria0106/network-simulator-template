#define CHECK_MEMORY_LEAK

#include "../auto_router.h"
#include "../bulk_send_service_installer.h"
#include "../echo_service.h"
#include "../echo_service_installer.h"
#include "../host.h"
#include "../link_installer.h"
#include "../nat.h"
#include <vector>

#define KNU_ADDRESS_1 "114.70.121.27"
#define KNU_ADDRESS_2 "114.70.121.28"
#define KNU_ADDRESS_3 "114.70.121.29"

#define SERVER_ADDRESS "223.130.192.248"
#define SERVER_PORT 80

// Create network and return it's NAT
Nat *createNatNetwork(Address natAddress, int clientCount) {

  Nat *nat = new Nat(Address(natAddress));

  BulkSendServiceInstaller bulkSendInstaller;
  LinkInstaller linkInstaller;
  for (int i = 0; i < clientCount; i++) {
    auto client = new Host(Address("192.168.0." + std::to_string(i + 2)));
    linkInstaller.install(client, nat, 0.005);
    bulkSendInstaller.install(client, Address(SERVER_ADDRESS), SERVER_PORT, 1,
                              1, 3);
  }

  return nat;
}

int main() {
  Simulator::prepare();

  std::vector<Node *> internetNodes;

  // 한빛관 네트워크
  auto nat1 = createNatNetwork(Address(KNU_ADDRESS_1), 2);
  // 공6호관 네트워크
  auto nat2 = createNatNetwork(Address(KNU_ADDRESS_2), 3);
  // 공4호관 네트워크
  auto nat3 = createNatNetwork(Address(KNU_ADDRESS_3), 3);
  internetNodes.push_back(nat1);
  internetNodes.push_back(nat2);
  internetNodes.push_back(nat3);

  Host *server = new Host(Address(SERVER_ADDRESS));
  internetNodes.push_back(server);
  EchoServiceInstaller echoServiceInstaller(SERVER_PORT);
  echoServiceInstaller.install(server);

  AutoRouter *router1 = new AutoRouter();
  AutoRouter *router2 = new AutoRouter();
  AutoRouter *router3 = new AutoRouter();
  internetNodes.push_back(router1);
  internetNodes.push_back(router2);
  internetNodes.push_back(router3);

  std::vector<Link *> links;
  LinkInstaller installer;
  auto wanLink1 = installer.install(nat1, router1, 0.2);
  auto wanLink2 = installer.install(nat2, router1, 0.2);
  auto wanLink3 = installer.install(nat3, router2, 0.1);
  nat1->setWanLink(wanLink1);
  nat2->setWanLink(wanLink2);
  nat3->setWanLink(wanLink3);
  links.push_back(wanLink1);
  links.push_back(wanLink2);
  links.push_back(wanLink3);

  links.push_back(installer.install(router1, router3, 0.1));
  links.push_back(installer.install(router2, router3, 0.1));

  links.push_back(installer.install(router3, server, 0.1));

  router1->calculate(internetNodes, links);
  router2->calculate(internetNodes, links);
  router3->calculate(internetNodes, links);

  Simulator::run();
}