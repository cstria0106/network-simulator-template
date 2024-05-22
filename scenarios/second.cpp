#include "../echo_service.h"
#include "../echo_service_installer.h"
#include "../host.h"
#include "../link_installer.h"
#include "../manual_router.h"
#include "../message_service_installer.h"
#include <string>
#include <vector>

#define COUNT 3

#define SERVER_ADDRESS_START 123
#define ECHO_PORT 3000

#define CLIENT_ADDRESS_START 456

int main() {
  std::vector<Host *> servers;
  std::vector<Host *> clients;

  for (int i = 0; i < COUNT; i++) {
    servers.push_back(new Host(SERVER_ADDRESS_START + i));
    clients.push_back(new Host(CLIENT_ADDRESS_START + i));
  }

  EchoServiceInstaller echoServiceInstaller(ECHO_PORT);
  for (int i = 0; i < COUNT; i++) {
    echoServiceInstaller.install(servers[i]);
  }

  std::vector<MessageServiceInstaller> messageServiceInstallers = {
      MessageServiceInstaller(servers[0]->address(), ECHO_PORT),
      MessageServiceInstaller(servers[1]->address(), ECHO_PORT),
      MessageServiceInstaller(servers[2]->address(), ECHO_PORT),
      // Invalid address
      MessageServiceInstaller(0, ECHO_PORT),
      // Invalid port
      MessageServiceInstaller(servers[0]->address(), 0),
  };

  std::vector<MessageService *> messageServices;

  for (size_t i = 0; i < messageServiceInstallers.size(); i++) {
    for (int j = 0; j < COUNT; j++) {
      messageServices.push_back(
          messageServiceInstallers[i].install(clients[j]));
    }
  }

  ManualRouter *router = new ManualRouter();

  LinkInstaller linkInstaller;
  std::vector<Link *> clientLinks;
  std::vector<Link *> serverLinks;

  for (int i = 0; i < COUNT; i++) {
    clientLinks.push_back(linkInstaller.install(router, clients[i]));
    serverLinks.push_back(linkInstaller.install(router, servers[i]));
  }

  for (int i = 0; i < COUNT; i++) {
    router->addRoutingEntry(servers[i]->address(), serverLinks[i]);
    router->addRoutingEntry(clients[i]->address(), clientLinks[i]);
  }

  for (int i = 0; i < COUNT; i++) {
    clients[i]->initialize();
    servers[i]->initialize();
  }

  for (int x = 0; x < 3; x++) {
    for (size_t i = 0; i < messageServices.size(); i++) {
      messageServices[i]->send("Hello " + std::to_string(x));
    }
  }

  for (int i = 0; i < COUNT; i++) {
    delete servers[i];
    delete clients[i];
  }

  delete router;

  for (int i = 0; i < COUNT; i++) {
    delete serverLinks[i];
    delete clientLinks[i];
  }
}