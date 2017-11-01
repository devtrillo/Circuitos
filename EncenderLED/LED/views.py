from django.shortcuts import render
import RPi.GPIO as GPIO

def index(request,led, on):
    GPIO.setmode(GPIO.BOARD)
	GPIO.setwarnings(False)
	GPIO.setup(led,GPIO.OUT)
    if(on=='1'):
        GPIO.output(led,GPIO.HIGH)
        return return render(request, 'LED/index.html',{'LED1':LED1})