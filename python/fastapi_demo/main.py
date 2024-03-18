import json
import uvicorn
import asyncio
import logging
from typing_extensions import Dict
from fastapi import FastAPI, WebSocket, Request, responses

app = FastAPI()


@app.websocket("/ws/ok")
async def ws_ok(websocket: WebSocket):
    await websocket.accept()
    try:
        while True:
            data: Dict = await websocket.receive_json()
            print(f"receive data: {data} type: {type(data)}")
            await websocket.send_bytes(json.dumps(data))
            await asyncio.sleep(0.3)
    except Exception as e:
        logging.error(e)
    finally:
        pass


@app.get("/api/get", response_class=responses.UJSONResponse)
async def api_get():
    return responses.UJSONResponse(
        status_code=200,
        content={
            "status": "10000",
            "msg": "ok",
        })


@app.post("/api/post", response_class=responses.UJSONResponse)
async def api_post(request: Request):
    data = await request.json()
    print(f"request data: {data}")
    return responses.UJSONResponse(
        status_code=200,
        content={
            "status": "10000",
            "msg": "ok",
        })


def main():
    uvicorn.run('main:app', host='0.0.0.0', port=8000)


if __name__ == "__main__":
    main()
