import paho.mqtt.client as mqtt

ip = "127.0.0.1"
port = 1883


def on_connect(client, userdata, flags, reason_code, properties):
    print(f"Connected with result code {reason_code}")  # rc的值很重要，为0代表连接成功。
    client.subscribe("/mqtt/test")


def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))


if __name__ == "__main__":
    # pip install paho-mqtt
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(ip, port, 60)

    client.loop_forever()
