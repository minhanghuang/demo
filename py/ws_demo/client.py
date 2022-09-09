import time
from websocket import create_connection


ws = create_connection("ws://192.168.10.3:9900/api/ws/")

ws.send("Hello, World")

time.sleep(1)
