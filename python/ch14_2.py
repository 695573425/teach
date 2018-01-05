# -*- coding: utf-8 -*-
"""
Created on Tue Aug 12 03:17:58 2014

@author: dell
"""

from Tkinter import *   # Import tkinter

root = Tk()             # Create a root window
# Create a label
label = Label(root, text = "Welcome to Python") 
# Create a canvas
canvas = Canvas(root,bg="white") 
# Create a button
button = Button(root, text = "Click Me") 

label.pack(side="left") # Display the label in the window
canvas.pack(side="left")# Display the canvas in the window
button.pack(side="left")           # Display the button in the window

root.mainloop()         # Create an event loop
