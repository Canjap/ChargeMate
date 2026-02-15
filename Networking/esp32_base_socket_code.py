import socket
from time import sleep

msg = "hi! I'm the server"

HOST = "server.local"
PORT = 10000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(2)

while True:
        client, addr = s.accept()
        while True:
                content = client.recv(1024)
                if len(content) == 0:
                        break
                else:
                        print(content.decode("utf-8"))
                        if content.decode("utf-8")=="pressed":
                            print("going to button")
                            msg = "pressed"
                            client.send(msg.encode("utf-8"))
                        client.send(msg.encode("utf-8"))
        print("Closing connection")
        client.close()
        sleep(2)
