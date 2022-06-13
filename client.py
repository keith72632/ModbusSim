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
    action_bytes = bytes(action, 'utf-8')

    s.send(action_bytes)

    modbus_addr = input("Enter address\n")

    modbus_addr_bytes = bytes(modbus_addr, 'utf-8')

    s.send(modbus_addr_bytes)

    if action == "5" or "6" or "15" or "16":
        val = input("Input value to be written\n")
        val_byte = bytes(val, 'utf-8')

    recv_buf = s.recv(16)
    recv_decoded = int.from_bytes(recv_buf, "little")
    print(f'Data recived {recv_buf}')
    print(recv_decoded)
