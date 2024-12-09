#ifndef PROJECT_NETFLIX_CLIENTCONTEXT_H
#define PROJECT_NETFLIX_CLIENTCONTEXT_H

#include <map>
#include <string>
#include <variant>

using namespace std;

class ClientContext {
public:

    /**
     * constructor.
     * @param cs
     */
     ClientContext(int cs);

    /**
     * get the client socket
     * @return client context
     */
    int getClientSocket();

private:
    int clientSocket;

};

#endif //PROJECT_NETFLIX_CLIENTCONTEXT_H
