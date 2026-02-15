import socket 
import I2C_LCD_driver
from gpiozero import Button
from time import *

HOST = 'server.local'
PORT = 10000

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))

#relay hat uses BCM pinout
button = Button(18)

mylcd = I2C_LCD_driver.lcd()


def countdown_20_minutes():
    """
    Counts down from 20 minutes and alerts the user when 2 minutes remain.
    """
    total_seconds = 20 * 60  # 20 minutes in seconds
    alert_threshold = 2 * 60  # 2 minutes in seconds
    alert_shown = False
    delay(5)
    while total_seconds > 0:
        minutes = total_seconds // 60
        seconds = total_seconds % 60
        
        # Display the time
        t_now = f"Time: {minutes:02d}:{seconds:02d}"
        mylcd.lcd_display_string(t_now)
        
        # Alert when 2 minutes are left
        if total_seconds <= alert_threshold and not alert_shown:
            mylcd.lcd_clear()
            mylcd.lcd_display_string("2 MINUTES LEFT! UNPLUG!")
            sleep(5)
            mylcd.lcd_clear()
            alert_shown = True
        
        sleep(1)
        total_seconds -= 1

    mylcd.lcd_display_string("TIME'S UP!")
    sleep(5)
    mylcd.lcd_clear()


mylcd.lcd_clear()
while True:
    #need to reverse the output bc of wiring i think
    mylcd.lcd_clear()
    if not button.is_pressed:
        pressed_notif = "pressed1"
        client.send(pressed_notif.encode("utf-8"))
        mylcd.lcd_display_string("Pressed!", 1)
        #countdown_20_minutes()
        sleep(1)
