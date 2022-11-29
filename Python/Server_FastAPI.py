#  -*- coding: utf-8 -*-
from fastapi import FastAPI
from fastapi.templating import Jinja2Templates
from datetime import datetime

# Door_Out_Servo_M, Door_Out_LCD, Door_Out_LED
# Door_In_LED
# Living_Servo_M, Living_DC_M, Living_TV_LCD, Living_LED
# Kitchen_Servo_M, Kitchen_LED, Kitchen_Induction
# Room1_LED
# Room2_Step_M, Room2_LED

app = FastAPI()

templates = Jinja2Templates(directory="templates")

@app.get("/")
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