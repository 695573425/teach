# -*- coding: utf-8 -*-
"""
Created on Tue Aug 12 02:38:16 2014

@author: dell
"""

from Tkinter import * # Import tkinter

def changeRelief():
    reliefList = ['flat','raised','sunken','groove','ridge']
    global reliefIndex
    label.config(relief=reliefList[reliefIndex%len(reliefList)])
    reliefIndex += 1

def changeColor(event):
    colorList = ['red', 'blue','yellow']
    global colorIndex
    label.config(fg=colorList[colorIndex%len(colorList)])
    colorIndex += 1


reliefIndex = 0
colorIndex  = 0

root = Tk()           # Create a root toplevel window

label = Label(root,text="Welcome to python")
button1 = Button(root, text = "relief",command=changeRelief)
button2 = Button(root,text = "color")
button2.bind("<Button-1>",changeColor)

label.pack()
button1.pack(side=LEFT,anchor=CENTER, expand=YES)
button2.pack(side=LEFT,anchor=CENTER, expand=YES)


root.mainloop()       # Create an event loop

