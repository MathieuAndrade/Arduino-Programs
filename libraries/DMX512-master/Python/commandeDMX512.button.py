import serial
import time
import Tkinter
 
def quit():
    global tkTop
    tkTop.destroy()
 
def A():
    ser.write(bytes('A'))

def Z():
    ser.write(bytes('Z'))

def E():
    ser.write(bytes('E'))

def Q():
    ser.write(bytes('Q'))

def S():
    ser.write(bytes('S'))

def D():
    ser.write(bytes('D'))

def W():
    ser.write(bytes('W'))

def X():
    ser.write(bytes('X'))

def C():
    ser.write(bytes('C'))


locations=['/dev/ttyACM0', '/dev/ttyUSB0','/dev/ttyUSB1','/dev/ttyUSB2','/dev/ttyUSB3',
'/dev/ttyS0','/dev/ttyS1','/dev/ttyS2','/dev/ttyS3']

for device in locations:
    try:
        ser = serial.Serial(device, 9600)
        print "Connexion sur", device
    except:
        print "Echec de connexion sur", device

print("Reinitialiser Arduino")
time.sleep(3)
ser.write(bytes('E'))
 
tkTop = Tkinter.Tk()
tkTop.geometry('300x600')
 
varLabel = Tkinter.StringVar()
tkLabel = Tkinter.Label(textvariable=varLabel)
tkLabel.pack()
 

tkButtonQuit = Tkinter.Button(
    tkTop,
    text="Quitter",
    command=quit)
tkButtonQuit.pack()
 
# Red
tkButtonA = Tkinter.Button(
    tkTop,
    text="Rouge : Diminuer",
    command=A)
tkButtonA.pack()
 
tkButtonZ = Tkinter.Button(
    tkTop,
    text="Rouge : Augmenter",
    command=Z)
tkButtonZ.pack()
 
tkButtonE = Tkinter.Button(
    tkTop,
    text="Rouge : Eteindre",
    command=E)
tkButtonE.pack()
 

# Green
tkButtonQ = Tkinter.Button(
    tkTop,
    text="Vert : Diminuer",
    command=Q)
tkButtonQ.pack()
 
tkButtonS = Tkinter.Button(
    tkTop,
    text="Vert : Augmenter",
    command=S)
tkButtonS.pack()
 
tkButtonD = Tkinter.Button(
    tkTop,
    text="Vert : Eteindre",
    command=D)
tkButtonD.pack()
 
# Blue
tkButtonW = Tkinter.Button(
    tkTop,
    text="Bleu : Diminuer",
    command=W)
tkButtonW.pack()
 
tkButtonX = Tkinter.Button(
    tkTop,
    text="Bleu : Augmenter",
    command=X)
tkButtonX.pack()
 
tkButtonC = Tkinter.Button(
    tkTop,
    text="Bleu : Eteindre",
    command=C)
tkButtonC.pack()


Tkinter.mainloop()
