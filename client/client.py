import sys
from socket import socket, AF_INET, SOCK_STREAM


def main():
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <ip> <port>")
        return 0
    # get ip and port from CMD arguments
    ip = sys.argv[1]
    port = sys.argv[2]
    try: # parse the port to integer
        port = int(port)
    except ValueError:
        print("Port must be an integer")
        return 0

    # establish connection with the server
    sock = socket(AF_INET, SOCK_STREAM)
    sock.connect((ip, port))

    # receive requests from user, send to server and wait for response
    while True:
        req = input("Enter request: ")
        req += '\n'
        sock.send(req.encode())
        res = sock.recv(1024)
        print(res.decode())


if __name__ == '__main__':
    main()
