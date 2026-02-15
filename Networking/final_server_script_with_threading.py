import socket
import threading
from time import sleep

msg = "hi! I'm the server"

HOST = "server.local"
PORT = 10000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(2)

clients = []

def handle_client(conn,addr):
        print(f"Client addr: {addr}")
        clients.append(conn)
        try:
                while True:
                        data = conn.recv(1024)
                        if not data:
                                print(f"No data from {addr}")
                                break
                        print(f"Recieved message from {addr}: {data.decode()}")
                        forward_message(data, conn)
        except Exception as e:
                print(f"Error with {addr}: {e}")
        finally:
                clients.remove(conn)
                conn.close()
                print(f"Closed {addr} connection")

def forward_message(message, sender_connection):
        for client in clients:
                if client != sender_connection:
                        try:
                                client.sendall(message)
                        except Exception as e:
                                print(f"Failed to send message to {client}: {e}")

while True:
        conn, addr = s.accept()
        client_thread = threading.Thread(target=handle_client, args=(conn,addr))
        client_thread.start()
