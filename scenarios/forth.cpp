#define CHECK_MEMORY_LEAK

#include "../auto_router.h"
#include "../bulk_send_service_installer.h"
#include "../echo_service.h"
#include "../echo_service_installer.h"
#include "../host.h"
#include "../link_installer.h"
#include "../packet_sink_service_installer.h"
#include <vector>

#define COUNT 3

#define SERVER_ADDRESS_START 123
#define ECHO_PORT 3000
#define SINK_PORT 3001

#define CLIENT_ADDRESS_START 456

int main() {
  Simulator::prepare();
  std::vector<Node *> nodes;
  std::vector<Host *> servers;
  std::vector<Host *> clients;

  for (int i = 0; i < COUNT; i++) {
    auto server = new Host(SERVER_ADDRESS_START + i);
    servers.push_back(server);
    nodes.push_back(server);

    auto client = new Host(CLIENT_ADDRESS_START + i);
    clients.push_back(client);
    nodes.push_back(client);
  }

  EchoServiceInstaller echoServiceInstaller(ECHO_PORT);
  for (int i = 0; i < COUNT; i++) {
    echoServiceInstaller.install(servers[i]);
  }

  PacketSinkServiceInstaller packetSinkServiceInstaller;
  for (int i = 0; i < COUNT; i++) {
    packetSinkServiceInstaller.install(servers[i], SINK_PORT);
  }

  BulkSendServiceInstaller bulkSendServiceInstaller;
  for (int i = 0; i < COUNT; i++) {
    for (int j = 0; j < COUNT; j++) {
      bulkSendServiceInstaller.install(clients[i], servers[j]->address(),
                                       ECHO_PORT);
      bulkSendServiceInstaller.install(clients[i], servers[j]->address(),
                                       SINK_PORT);
      bulkSendServiceInstaller.install(clients[i], servers[j]->address(), 0);
    }
    bulkSendServiceInstaller.install(clients[i], Address("0.0.0.0"), ECHO_PORT);
    bulkSendServiceInstaller.install(clients[i], Address("0.0.0.0"), SINK_PORT);
  }

  LinkInstaller linkInstaller;
  std::vector<Link *> links;

  AutoRouter *router = new AutoRouter();
  nodes.push_back(router);
  for (int i = 0; i < COUNT; i++) {
    links.push_back(linkInstaller.install(router, clients[i]));
    links.push_back(linkInstaller.install(router, servers[i]));
  }

  router->calculate(nodes, links);

  for (int i = 0; i < COUNT; i++) {
    clients[i]->initialize();
    servers[i]->initialize();
  }

  Simulator::run();

  for (auto node : nodes) {
    delete node;
  }

  for (auto link : links) {
    delete link;
  }

  Object::checkMemoryLeak();
}