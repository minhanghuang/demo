import websocket
import unittest
import requests
import json
import time


class TestFastApi(unittest.TestCase):
    def test_http_get(self):
        resp = requests.get("http://127.0.0.1:8000/api/get")
        self.assertEqual(resp.status_code, 200)
        json_content = json.loads(resp.text)
        self.assertEqual(json_content["status"], "10000")
        self.assertEqual(json_content["msg"], "ok")

    def test_http_post(self):
        data = {
            "name": "John",
            "age": 30,
            "city": "New York",
        }
        resp = requests.post("http://127.0.0.1:8000/api/post", json=data)
        self.assertEqual(resp.status_code, 200)
        json_content = json.loads(resp.text)
        self.assertEqual(json_content["status"], "10000")
        self.assertEqual(json_content["msg"], "ok")

    def test_websocket(self):
        data = {
            "name": "Tom",
            "age": 27,
            "city": "New York",
        }
        client = websocket.create_connection("ws://127.0.0.1:8000/ws/ok")
        client.send(json.dumps(data))
        print(f"recv data: {client.recv()}")
        time.sleep(0.5)
        client.send(json.dumps(data))
        print(f"recv data: {client.recv()}")
        time.sleep(0.5)
        client.close(websocket.STATUS_NORMAL)


if __name__ == '__main__':
    unittest.main()
