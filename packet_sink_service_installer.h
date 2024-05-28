#ifndef PACKET_SINK_SERVICE_INSTALLER_H
#define PACKET_SINK_SERVICE_INSTALLER_H

#include "address.h"
#include "packet_sink_service.h"
#include "service_installer.h"

class PacketSinkServiceInstaller : public ServiceInstaller {
public:
  PacketSinkService *install(Host *host, short port);
};

#endif