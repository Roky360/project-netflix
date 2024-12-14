import sys
from socket import socket, AF_INET, SOCK_STREAM
import unittest

sock: socket = None


# Sends a request and returns the response
def ping_msg(data: str) -> str:
    sock.send(data.encode())
    return sock.recv(1024).decode()


class ServerTester(unittest.TestCase):
    def test_help(self):
        self.assertEqual(ping_msg("help\n"), """200 OK

DELETE, arguments: [userid] [movieid1] [movieid2] ...
GET, arguments: [userid] [movieid]
PATCH, arguments: [userid] [movieid1] [movieid2] ...
POST, arguments: [userid] [movieid1] [movieid2] ...
help
""")
        self.assertEqual(ping_msg("help 2\n"), "400 Bad Request\n")

    def test_post(self):
        self.assertEqual(ping_msg("POST 1 101 102 103\n"), "201 Created\n")
        self.assertEqual(ping_msg("POST 1 105\n"), "400 Bad Request\n")

    def test_patch(self):
        self.assertEqual(ping_msg("PATCH 1 101 105\n"), "204 No Content\n")
        self.assertEqual(ping_msg("PATCH 2 101 105 106 107\n"), "204 No Content\n")
        self.assertEqual(ping_msg("PATCH 3 101\n"), "204 No Content\n")
        self.assertEqual(ping_msg("PATCH 5 101\n"), "404 Not Found\n")

    def test_get(self):
        self.assertEqual(ping_msg("GET 7 101\n"), "404 Not Found\n")
        self.assertEqual(ping_msg("GET \n"), "204 No Content\n")


def main():
    global sock
    # establish connection with the server
    sock = socket(AF_INET, SOCK_STREAM)
    sock.connect(("127.0.0.1", 20200))

    # run tests
    unittest.main(argv=[sys.argv[0]])


if __name__ == '__main__':
    main()
