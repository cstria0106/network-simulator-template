#define CHECK_MEMORY_LEAK

#include "../auto_router.h"
#include "../bulk_send_service_installer.h"
#include "../host.h"
#include "../link_installer.h"
#include "../packet_sink_service_installer.h"

int main() {
  {
    std::vector<Host *> hosts;
    std::vector<Node *> nodes;
    Host *bulkSendHost = new Host(Address("10.0.0.1"));
    Host *packetSinkHost = new Host(Address("10.0.1.1"));

    hosts.push_back(bulkSendHost);
    hosts.push_back(packetSinkHost);
    nodes.push_back(bulkSendHost);
    nodes.push_back(packetSinkHost);

    BulkSendServiceInstaller *bulkSendServiceInstaller =
        new BulkSendServiceInstaller();
    PacketSinkServiceInstaller *packetSinkServiceInstaller =
        new PacketSinkServiceInstaller();

    bulkSendServiceInstaller->install(bulkSendHost, Address("10.0.1.1"), 5000);
    packetSinkServiceInstaller->install(packetSinkHost, 5000);

    std::vector<AutoRouter *> routers;
    for (int i = 0; i < 4; i++) {
      auto router = new AutoRouter();
      routers.push_back(router);
      nodes.push_back(router);
    }

    std::vector<Link *> links;
    LinkInstaller *linkInstaller = new LinkInstaller();
    links.push_back(linkInstaller->install(bulkSendHost, routers[0], 1.1));
    links.push_back(linkInstaller->install(bulkSendHost, routers[1], 1.2));
    links.push_back(linkInstaller->install(routers[0], routers[2], 1.3));
    links.push_back(linkInstaller->install(routers[1], routers[2], 1.4));
    links.push_back(linkInstaller->install(routers[2], routers[3], 1.5));
    links.push_back(linkInstaller->install(routers[3], packetSinkHost, 1.6));

    for (AutoRouter *router : routers) {
      router->calculate(nodes, links);
    }

    for (Host *host : hosts) {
      host->initialize();
    }

    Simulator::run();

    for (Node *node : nodes) {
      delete node;
    }

    for (Link *link : links) {
      delete link;
    }
  }

  Object::checkMemoryLeak();
}