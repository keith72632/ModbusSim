import socket

HOST = ''
PORT = 5502

with socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0) as s:
    s.connect((HOST, PORT))
    print('connected to server')
    data = s.recv(1024);
print('recived', repr(data))