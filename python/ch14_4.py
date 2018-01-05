from Tkinter import * # Import tkinter

def increaseCircle(event):
#    print event.keysym
    canvas.delete("oval")
    global radius
    if radius < 100:
        radius += 2
    canvas.create_oval(100 - radius, 100 - radius, 
                       100 + radius, 100 + radius, tags = "oval")
    
def decreaseCircle(event):
#    print event.keysym
    canvas.delete("oval")
    global radius
    if radius > 2:
        radius -= 2
    canvas.create_oval(100 - radius, 100 - radius, 
                       100 + radius, 100 + radius, tags = "oval")

window = Tk() # Create a window
window.title("Control Circle Demo") # Set a title

canvas = Canvas(window, bg = "white", width = 200, height = 200)
radius = 50
canvas.create_oval(100 - radius, 100 - radius, 
                   100 + radius, 100 + radius, tags = "oval")

# Bind canvas with key events
canvas.bind("<Alt-Shift-A>", increaseCircle)
canvas.bind("<Down>", decreaseCircle)
canvas.focus_set()

#canvas.pack()
#canvas.grid(row = 0,column=1)
canvas.place(x=100,y=100)
window.mainloop() # Create an event loop
