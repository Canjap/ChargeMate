import socket

msg = "Hello World!"
msg = msg.encode("utf-8")


HOST = 'button1.local'
PORT = 65329


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send(msg)
data = s.recv(1024)
print(data.decode("utf-8"))
