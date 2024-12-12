#ifndef PROJECT_NETFLIX_SOCKETREQUESTPROVIDER_H
#define PROJECT_NETFLIX_SOCKETREQUESTPROVIDER_H

#include "../RequestProvider.h"
#include "../../request/Request.h"
#include "../../app/StateManager.h"

using namespace app;

/**
 * Provides requests from the socket.
 */
class SocketRequestProvider : public RequestProvider {
public:
    ~SocketRequestProvider();

    /**
     * return from the socket the wanted request with the arguments
     * @return request
     */
    Request *nextRequest() override;

    /**
     * constructor
     * @param port the server port
     * @param ip the server ip
     * @param backlog the max client to listen
     */
    SocketRequestProvider(int port, string ip, int backlog);

private:
    int serverPort;
    string serverIP;
    int backlogAmount;
    int serverSock;

    /**
     * method that read the client input and enter it to string stream
     * @param socket the client socket
     * @return string stream with the client msg
     */
    stringstream readSocketToStream(int socket);

    /**
     * get string stream and return vector<string> with the arguments in the stream
     * @param ss string stream
     * @return vector with the arguments in the stream
     */
    vector<string> parseArguments(stringstream &ss);
};


#endif
