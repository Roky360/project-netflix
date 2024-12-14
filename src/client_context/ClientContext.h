#ifndef PROJECT_NETFLIX_CLIENTCONTEXT_H
#define PROJECT_NETFLIX_CLIENTCONTEXT_H

#include <string>

using namespace std;

class ClientContext {
    int clientSocket;

public:
    /**
     * constructor.
     * @param cs
     */
    explicit ClientContext(int cs);

    /**
     * get the client socket
     * @return client context
     */
    int getClientSocket() const;
};

#endif //PROJECT_NETFLIX_CLIENTCONTEXT_H
