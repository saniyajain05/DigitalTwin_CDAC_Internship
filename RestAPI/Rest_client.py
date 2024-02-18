from flask import Flask
from flask_restful import Api, Resource
from websocket import create_connection
import requests
import socket

app = Flask(__name__)
api = Api(app)

Server = socket.gethostbyname(socket.gethostname())

#BASE = "http://10.252.4.251:5000/"

class LightStatus(Resource):
    def get(self, status):

        #print(f"Received light status: {status}")
        #"ws://10.252.5.3:8080"
        ws = create_connection('ws://' + Server + ":8080")
        
        ws.send(f"Action: Light {status}")

        ws.close()
        
        #response = requests.get(BASE + f"lightstatus/{status}")


        return {"Status": status}

api.add_resource(LightStatus, "/lightstatus/<string:status>")



if __name__ == "__main__":
    app.run(debug=True, host = "0.0.0.0")
    