# -*- coding: utf-8 -*-
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from fastapi.encoders import jsonable_encoder
from datetime import datetime
import random

# Door_Out_Servo_M, Door_Out_LCD, Door_Out_LED
# Door_In_LED
# Living_Servo_M, Living_DC_M, Living_TV_LCD, Living_LED
# Kitchen_Servo_M, Kitchen_LED, Kitchen_Induction
# Room1_LED
# Room2_Step_M, Room2_LED

app = FastAPI()

app.mount("/static", StaticFiles(directory="static"), name="static")

templates = Jinja2Templates(directory="templates")

@app.get("/", response_class=HTMLResponse)
async def Page(request: Request):#, ncnt_people: str, current_time: str, standard_time: str):
    Door_Out_Servo_M, Door_Out_LCD, Door_Out_LED = 0, 0, 0
    Door_In_LED = 0
    Living_Servo_M, Living_DC_M, Living_TV_LCD, Living_LED = 0, 0, 0, 0
    Kitchen_Servo_M, Kitchen_LED, Kitchen_Induction = 0, 0, 0
    Room1_LED = 0
    Room2_Step_M, Room2_LED = 0, 0
    Current_Time = str(datetime.now())[0:21]  # 필요한 부분 가공
    return templates.TemplateResponse("new.html", {"request": request ,"Current_Time": Current_Time,"Door_Out_Servo_M": Door_Out_Servo_M, "Door_Out_LCD": Door_Out_LCD, "Door_Out_LED": Door_Out_LED, "Door_In_LED": Door_In_LED, "Living_Servo_M": Living_Servo_M, "Living_DC_M": Living_DC_M, "Living_TV_LCD": Living_TV_LCD, "Living_LED": Living_LED, "Kitchen_Servo_M": Kitchen_Servo_M, "Kitchen_LED": Kitchen_LED, "Kitchen_Induction": Kitchen_Induction, "Room1_LED": Room1_LED, "Room2_Step_M": Room2_Step_M, "Room2_LED": Room2_LED})  # FastAPI로 new.html에 변수 값 전달


@app.get("/DATA")
async def POST_Sensor():    
    Door_Out_Servo_M, Door_Out_LCD, Door_Out_LED = 0, 0, 0
    Door_In_LED = 0
    Living_Servo_M, Living_DC_M, Living_TV_LCD, Living_LED = 0, 0, 0, 0
    Kitchen_Servo_M, Kitchen_LED, Kitchen_Induction = 0, 0, 0
    Room1_LED = 0
    Room2_Step_M, Room2_LED = 0, 0
    
    Current_Time = str(datetime.now() )[0:21]  # 필요한 부분 가공
    return {
            "Current_Time": Current_Time,
            "Door_Out_Servo_M": Door_Out_Servo_M, "Door_Out_LCD": Door_Out_LCD, "Door_Out_LED": Door_Out_LED,
            "Door_In_LED": Door_In_LED,
            "Living_Servo_M": Living_Servo_M, "Living_DC_M": Living_DC_M, "Living_TV_LCD": Living_TV_LCD, "Living_LED": Living_LED,
            "Kitchen_Servo_M": Kitchen_Servo_M, "Kitchen_LED": Kitchen_LED, "Kitchen_Induction": Kitchen_Induction,
            "Room1_LED": Room1_LED,
            "Room2_Step_M": Room2_Step_M, "Room2_LED": Room2_LED
            }