#ifndef THRPOOLREQUESTEXECUTOR_H
#define THRPOOLREQUESTEXECUTOR_H

#include "../RequestExecutor.h"
#include "../../request_provider/RequestProvider.h"
#include "../../response_sender/ResponseSender.h"
#include "../thread_pool/ThreadPool.h"

class ThrPoolRequestExecutor : public RequestExecutor {
    RequestProvider *provider;
    ResponseSender *sender;
    ThreadPool *pool;

public:
    ThrPoolRequestExecutor(RequestProvider *provider, ResponseSender *sender, ThreadPool *pool);

    ~ThrPoolRequestExecutor() override;

    /**
     * Handles the execution of requests of one client connection.
     * @param clientContext Context object of the client.
     */
    void execute(ClientContext *clientContext) override;
private:
    /**
     * Internal method that handles the connection of the client by indefinitely receiving requests, executing them
     * and sending back the response.
     * @param context Context object of the client.
     */
    void handleClient(ClientContext *context) const;
};


#endif //THRPOOLREQUESTEXECUTOR_H
