#ifndef BULK_SEND_SERVICE_INSTALLER_H
#define BULK_SEND_SERVICE_INSTALLER_H

#include "address.h"
#include "bulk_send_service.h"
#include "service_installer.h"

class BulkSendServiceInstaller : public ServiceInstaller {
public:
  BulkSendService *install(Host *host, Address destination, short destPort,
                           double delay = 1, double startTime = 0,
                           double stopTime = 10.);
};

#endif