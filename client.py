import socket

HOST = '192.168.0.139'
PORT = 5502

with socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0) as s:
    s.connect((HOST, PORT))
    print('connected to server')
    action = input("""
    1. Read Coil Status
    2. Read Input Status
    3. Read Holding Register
    4. Read Internal Register
    5. Force Single Coil
    6. Write Single Register 
    15. Force Multiple Coils
    16 Masked Write Register
    """)
    send_res = bytes(action, 'utf-8')

    s.send(send_res)

    modbus_addr = input("Enter address\n")

    send_addr = bytes(modbus_addr, 'utf-8')

    s.send(send_addr)