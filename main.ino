import network
import urequests
import ssd1306
from time import sleep
import ujson
from machine import Pin, PWM, I2C

# Adafruit IO Credentials
AIO_USERNAME = ""
AIO_KEY = ""

# Wi-Fi Credentials
WIFI_SSID = "Wokwi-GUEST"
WIFI_PASS = ""

# Define components
pir = Pin(2, Pin.IN)       # PIR sensor on GP2
led = Pin(3, Pin.OUT)      # LED on GP3
buzzer = PWM(Pin(4))       # Buzzer on GP4

# OLED Display Setup (128x64)
i2c = I2C(0, scl=Pin(1), sda=Pin(0))  # Use GP0 for SDA, GP1 for SCL
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

study_time = 0  # Track study time in seconds
inactive_time = 0  # Track inactivity
alert_status = 0  # 1 if inactivity alert is triggered, else 0

# Connect to Wi-Fi
def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(WIFI_SSID, WIFI_PASS)

    timeout = 10  # 10-second timeout
    while not wlan.isconnected() and timeout > 0:
        print("Connecting to WiFi...")
        sleep(1)
        timeout -= 1

    if wlan.isconnected():
        print("Connected to Wi-Fi:", wlan.ifconfig())
    else:
        print("WiFi connection failed!")

# Send data to Adafruit IO
def send_to_adafruit(feed, value):
    url = "https://io.adafruit.com/api/v2/{}/feeds/{}/data".format(AIO_USERNAME, feed)
    headers = {
        "Content-Type": "application/json",
        "X-AIO-Key": AIO_KEY
    }
    data = ujson.dumps({"value": value})

    try:
        response = urequests.post(url, headers=headers, data=data)
        response.close()
        print(f"Data sent to {feed}: {value}")
    except Exception as e:
        print("Failed to send data:", str(e))

# Send SMS using Adafruit IO Trigger
def send_sms(message):
    send_to_adafruit("sms-alert", message)  # Publish to `sms-alert` feed
    print("SMS Alert Sent to Adafruit IO!")

# Update OLED Display
def update_oled():
    oled.fill(0)  # Clear screen
    oled.text("Study Assistant", 10, 10)
    oled.text(f"Time: {study_time}s", 10, 30)
    oled.text(f"Alert: {alert_status}", 10, 50)
    oled.show()

# Main loop
def main():
    counter = 0
    global study_time, inactive_time, alert_status
    connect_wifi()

    while True:
        if pir.value() == 1:  # Motion detected
            led.on()
            study_time += 1
            inactive_time = 0  # Reset inactivity counter
            print(f"Studying... Time: {study_time} seconds")
        else:
            led.off()
            inactive_time += 1
            if inactive_time > 20:  # 10 minutes of inactivity (set to 20 seconds for testing)
                buzzer.freq(1000)
                buzzer.duty_u16(30000)
                sleep(1)
                buzzer.duty_u16(0)
                if alert_status == 0:
                    alert_status = 1  # Alert triggered
                    send_sms("Inactivity Alert! Get back to studying!")  # Send SMS alert via Adafruit IO
                print("⚠️ Inactivity Alert! Get Back to Study!")

        # Update OLED display
        update_oled()

        counter += 1  # Increase counter every second
        if counter >= 10:  # Send data every 10 seconds (change to 60 for real use)
            send_to_adafruit("study-time", study_time)  # Send study time
            send_to_adafruit("alert-status", alert_status)  # Send alert status
            counter = 0  # Reset counter
            alert_status = 0  # Reset alert status

        sleep(1)

# Run the program
try:
    main()
except KeyboardInterrupt:
    print("Program stopped!")
