#define CHECK_MEMORY_LEAK

#include "../auto_router.h"
#include "../bulk_send_service_installer.h"
#include "../echo_service.h"
#include "../echo_service_installer.h"
#include "../firewall.h"
#include "../host.h"
#include "../link_installer.h"
#include "../nat.h"
#include <vector>

#define CLIENT_ADDRESS_1 "10.0.0.1"
#define CLIENT_ADDRESS_2 "10.0.0.2"
#define SERVER_ADDRESS "10.0.0.3"

#define PORT_1 3000
#define PORT_2 4000
#define PORT_3 5000

int main() {
  Simulator::prepare();

  std::vector<Node *> nodes;

  auto client1 = new Host(Address(CLIENT_ADDRESS_1));
  auto client2 = new Host(Address(CLIENT_ADDRESS_2));
  auto server = new Host(Address(SERVER_ADDRESS));
  nodes.push_back(client1);
  nodes.push_back(client2);
  nodes.push_back(server);

  auto firewall = new Firewall();
  firewall->addAllowAnyPolicy(PORT_1);
  firewall->addAllowSpecificPolicy(client1->address(), PORT_2);
  nodes.push_back(firewall);

  auto router = new AutoRouter();
  nodes.push_back(router);

  std::vector<Link *> links;

  LinkInstaller linkInstaller;
  links.push_back(linkInstaller.install(client1, router, 0.1));
  links.push_back(linkInstaller.install(client2, router, 0.1));
  links.push_back(linkInstaller.install(firewall, server, 0.005));

  auto firewallReceiveLink = linkInstaller.install(router, firewall, 0.1);
  firewall->setReceiveLink(firewallReceiveLink);
  links.push_back(firewallReceiveLink);

  router->calculate(nodes, links);

  EchoServiceInstaller(PORT_1).install(server);
  EchoServiceInstaller(PORT_2).install(server);
  EchoServiceInstaller(PORT_3).install(server);

  BulkSendServiceInstaller bulkSendInstaller;
  bulkSendInstaller.install(client1, Address(SERVER_ADDRESS), PORT_1, 1, 1, 5);
  bulkSendInstaller.install(client1, Address(SERVER_ADDRESS), PORT_2, 1, 1, 5);
  bulkSendInstaller.install(client1, Address(SERVER_ADDRESS), PORT_3, 1, 1, 5);
  bulkSendInstaller.install(client2, Address(SERVER_ADDRESS), PORT_1, 1, 1, 5);
  bulkSendInstaller.install(client2, Address(SERVER_ADDRESS), PORT_2, 1, 1, 5);
  bulkSendInstaller.install(client2, Address(SERVER_ADDRESS), PORT_3, 1, 1, 5);

  Simulator::run();
}