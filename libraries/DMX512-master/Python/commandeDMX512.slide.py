from Tkinter import *
import serial
import time
import Tkinter


class DelManager(Frame):
    red = 0
    green = 0
    blue = 0

    def delRed(self, val):
        if val < DelManager.red:
            ser.write(bytes('A'))
            print "Red increase : ", val
        else:
            ser.write(bytes('Z'))       
            print "Red decrease : ", val
        DelManager.red = val


    def delGreen(self, val):
        if val < DelManager.green:
            ser.write(bytes('Q'))
            print "Green decrease : ", val
        else:
            ser.write(bytes('S'))       
            print "Green increase : ", val
        DelManager.green = val

    def delBlue(self, val):
        if val < DelManager.blue:
            ser.write(bytes('W'))
            print "Blue increase : ", val
        else:
            ser.write(bytes('X'))       
            print "Blue decrease : ", val
        DelManager.blue = val

    def resetLED(self):
        self.sliderRed.set(0)
        self.sliderGreen.set(0)
        self.sliderBlue.set(0)
        ser.write(bytes('E'))
        ser.write(bytes('D'))
        ser.write(bytes('C'))

    def createWidgets(self):
        self.sliderRed = Scale(self, from_ = 0, to = 50, tickinterval = 10, resolution = 5,
                            orient = HORIZONTAL,
                            length = "2i",
                            label = "Rouge",
                            command = self.delRed)

        self.sliderGreen = Scale(self, from_ = 0, to = 50, tickinterval = 10, resolution = 5,
                            orient = HORIZONTAL,
                            length = "2i",
                            label = "Vert",
                            command = self.delGreen)

        self.sliderBlue = Scale(self, from_ = 0, to = 50, tickinterval = 10, resolution = 5,
                            orient = HORIZONTAL,
                            length = "2i",
                            label = "Bleu",
                            command = self.delBlue)

        self.resetLED = Button(self, text = 'Reinitialiser curseurs',
                            command=self.resetLED)

        self.QUIT = Button(self, text = 'Quitter', foreground = 'red',
                           command = self.quit)

        self.sliderRed.pack(side = LEFT)
        self.sliderGreen.pack(side = LEFT)
        self.sliderBlue.pack(side = LEFT)

        self.resetLED.pack(side = LEFT)
        self.QUIT.pack(side = LEFT, fill = BOTH)


    def __init__(self, master = None):
        Frame.__init__(self, master)
        self.master.title("Console de commande DMX512")
        Pack.config(self)
        self.createWidgets()

locations = ['/dev/ttyACM0', '/dev/ttyUSB0','/dev/ttyUSB1','/dev/ttyUSB2','/dev/ttyUSB3',
'/dev/ttyS0','/dev/ttyS1','/dev/ttyS2','/dev/ttyS3']

for device in locations:
    try:
        ser = serial.Serial(device, 9600)
        print "Connection on ", device
    except:
        print "Failed connection on ", device

print("Reinitialize Arduino")
time.sleep(3)
ser.write(bytes('E'))

newDelManager = DelManager()
newDelManager.mainloop()
