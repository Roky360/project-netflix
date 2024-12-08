#ifndef SOCKETRESPONSESENDER_H
#define SOCKETRESPONSESENDER_H

#include "../ResponseSender.h"

class SocketResponseSender final : public ResponseSender {
public:
    SocketResponseSender() = default;

    ~SocketResponseSender() override = default;

    void sendResponse(Response *response) override;
};


#endif //SOCKETRESPONSESENDER_H
