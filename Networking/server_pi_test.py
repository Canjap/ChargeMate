import socket
from time import sleep

msg = "hi! I'm the server"

HOST = "server.local"
PORT = 65329

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(2)
conn, addr = s.accept()
print(addr)

while True:
    data = conn.recv(1024)
    if not data:
        print("no data")
        s.close()
        break
    print(data.decode("utf-8"))
    conn.send(msg.encode("utf-8"))
    sleep(1)
