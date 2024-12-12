#ifndef PROJECT_NETFLIX_THREADREQUESTEXECUTOR_H
#define PROJECT_NETFLIX_THREADREQUESTEXECUTOR_H
#include "../RequestExecutor.h"
#include "../../response_sender/ResponseSender.h"
#include "../../app/StateManager.h"
#include "../../request_provider/RequestProvider.h"
#include <thread>
#include <functional>

using namespace std;

class ThreadRequestExecutor final : public RequestExecutor {
    ResponseSender *rSender;
    RequestProvider *rProvider;

public:
    ~ThreadRequestExecutor() override = default;

    /**
     * Constructor
     * @param responseSender ResponseSender
     */
    explicit ThreadRequestExecutor(ResponseSender *responseSender, RequestProvider* rp);

    /**
     * Executes each request according to their own execute method
     * @param clientContext the client context
     */
    void execute(ClientContext* clientContext) override;

private:
    /**
     * Inner function that executes the request and sends it to the client
     * @param request Request
     */
    void moveToSender(ClientContext* cl);
};


#endif //PROJECT_NETFLIX_THREADREQUESTEXECUTOR_H
