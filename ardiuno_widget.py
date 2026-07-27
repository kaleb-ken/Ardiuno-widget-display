"""
ardiuno_widget.py
======================
Displays data to lcd
"""
# Adding dependencies
import time
import serial
import json
from spotify_api import get_now_playing

arduino = serial.Serial('COM3', 9600, timeout=1)  # adjust COM port, or /dev/ttyACM0 on Linux/Mac
time.sleep(2)  # wait for Arduino reset after serial connect

while True:
    data = get_now_playing()
    if data:
        print(data)
        payload = json.dumps(data) + "\n"  # newline as message delimiter
        arduino.write(payload.encode())
    #time.sleep(1)  # poll once a second — plenty for a display