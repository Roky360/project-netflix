#ifndef THRPOOLREQUESTEXECUTOR_H
#define THRPOOLREQUESTEXECUTOR_H

#include "../RequestExecutor.h"
#include "../../request_provider/RequestProvider.h"
#include "../../response_sender/ResponseSender.h"

class ThrPoolRequestExecutor : public RequestExecutor {
    RequestProvider *provider;
    ResponseSender *sender;
    ThreadPool *pool;

public:
    ThrPoolRequestExecutor(RequestProvider *provider, ResponseSender *sender, ThreadPool *pool);

    ~ThrPoolRequestExecutor() override;

    void execute(ClientContext *clientContext) override;

private:
    void handleClient(ClientContext *context) const;
};


#endif //THRPOOLREQUESTEXECUTOR_H
