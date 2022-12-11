import serial
import time

Mega_Serial = serial.Serial(
    
    # Window
    port='COM10',
    
    # 보드 레이트 (통신 속도)
    baudrate=115200,
)

while True:
    if Mega_Serial.readable():
        
        # 들어온 값이 있으면 값을 한 줄 읽음 (BYTE 단위로 받은 상태)
        # BYTE 단위로 받은 response 모습 : b'\xec\x97\x86\xec\x9d\x8c\r\n'
        response = Mega_Serial.readline()
        response = response[:len(response)-1].decode()
        response = response.replace('\r', '')
        
        # 디코딩 후, 출력 (가장 끝의 \n을 없애주기위해 슬라이싱 사용)
        print(response)
        with open("C:/Users/Won/Desktop/Smart-Home/Mega.txt", "w") as f:
            f.write(response)