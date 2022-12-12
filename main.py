#  -*- coding: utf-8 -*-
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from datetime import datetime



def check():
    global CO_2, Temperature, Humidity, Channel, Motor, Door, DoorLock, Front
    with open("Uno.txt", "r") as file1:
        for line in file1.readlines():
            Uno_list = line.split("/")
            CO_2 = Uno_list[0]
            Temperature = Uno_list[1]
            Humidity = Uno_list[2]
            Channel = int(Uno_list[3])
            Motor = int(Uno_list[4])
            Door = int(Uno_list[5])
            print("\n", line,"\n")
    with open("Mega.txt", "r") as file2:
        for line in file2.readlines():
            Mega_list = line.split("/")
            DoorLock = int(Mega_list[0])
            Front = int(Mega_list[1])
            print("\n", line,"\n")

app = FastAPI()
app.mount("/static", StaticFiles(directory="static"), name="static")
templates = Jinja2Templates(directory="templates")

@app.get("/", response_class=HTMLResponse)
async def POST_Sensor(request: Request):
    check()
    Current_Time = str(datetime.now())[0:21]  # 필요한 부분 가공
    return templates.TemplateResponse("index.html", {"request": request, "Current_Time": Current_Time, "CO2":CO_2,"Temperature": Temperature, "Humidity": Humidity, "Channel": Channel, "Motor": Motor, "Door": Door, "DoorLock": DoorLock, "Front": Front})

@app.get("/info")
async def POST_Sensor():    
    
    Current_Time = str(datetime.now())[0:21]  # 필요한 부분 가공
    return {"Current_Time": Current_Time, "CO2":CO_2, "Temperature": Temperature, "Humidity": Humidity, "Channel": Channel, "Motor": Motor, "Door": Door, "DoorLock": DoorLock, "Front": Front}