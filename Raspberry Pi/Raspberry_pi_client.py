
# imports
from flask import Flask
from websocket import create_connection
from flask_restful import Api, Resource
from gpiozero import LED , Button
import threading
import time

app = Flask(__name__)
api = Api(app)

led = LED(18)
button = Button(16)

#Please edit base to the IP of your websocket server
BASE = "10.252.5.3"





# Function to deal with teh switch being pressed and toggling the light accordignly while sending a message to the websocket server.
def press_button():
    while (True):
    
        if button.is_pressed:
            led.toggle()
            
            if(led.is_lit):
                ws.send("This is the Raspi : Action: Light ON")
                
            else:
                ws.send("This is the Raspi : Action: Light OFF")
                
            #print("pressed")
            time.sleep(0.2)




            
# Function to deal with messages from the websocket server to switch the light on or off
def receive():

    while(True):
        data = ws.recv()
        
        #print("data",data)

        if "ON" in data:
            led.on()
        elif "OFF" in data:
            led.off()
            


    

#print(f"Received light status: {status}")

ws_Connection = "ws://" + BASE+ ":8080"
ws = create_connection(ws_Connection)

t1 = threading.Thread(target= receive)
t2 = threading.Thread(target= press_button)

t1.start()
t2.start()

t1.join()
t2.join()

