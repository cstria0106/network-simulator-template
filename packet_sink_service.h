#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service {
private:
  PacketSinkService(Host *host, short port);
};

#endif