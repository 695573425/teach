# -*- coding: utf-8 -*-
"""
Created on Sun Oct 12 10:06:35 2014

@author: Yongfeng.Yuan

GUI: Tkinter
DataBase: sqlite3

A simple program for calling the roll and saving historical records in the database
"""
from Tkinter import *
import tkFont
import random 
import time
import sqlite3

#db = 'test.db'
db = 'call_Roll.db'
def readfile():
    path = 'F:/课件/Python/name list.txt'
    uipath = unicode(path , "utf8")
    file = open(uipath,'r')

    name_list = []

    try:
        all_Lists = file.readlines()
#        print all_Lists
        for i_list in all_Lists:
            name_list.append(tuple(i_list.split()))
    finally:
        file.close()
    return name_list

def start_call(self):
    global flag
    global selected_Student
    
    flag = True
    
    read_List = readfile()
    
    while (flag==True):
        random_num = random.randrange(len(read_List))
        label.config(label,text=read_List[random_num][2]+' '+unicode(read_List[random_num][1]))
        selected_Student = read_List[random_num][2]+' '+unicode(read_List[random_num][1])
        label.update()
        time.sleep(0.1)
    else:
        while True:
            path = 'F:/课件/Python/'+db
            uipath = unicode(path , "utf8")
            cx = sqlite3.connect(uipath)
            cu = cx.cursor()
            item =  selected_Student.split()
            cu.execute("select * from catalog where st_num = \'" + item[0] + '\'')       # item[0] is student number
            show_item = cu.fetchone()
            if show_item[4] <= 5:
                break
            else:
                pass
            random_num = random.randrange(len(read_List))
            label.config(label,text=read_List[random_num][2]+' '+unicode(read_List[random_num][1]))
            selected_Student = read_List[random_num][2]+' '+unicode(read_List[random_num][1])
            label.update()
        pass

def stop_call(self):
    global flag
    flag = False
    R1.config(state = 'active')
    R2.config(state = 'active')
    R3.config(state = 'active')

def export_all(self):
    path = 'F:/课件/Python/'+db
    uipath = unicode(path , "utf8")
    cx = sqlite3.connect(uipath)
    cu = cx.cursor()
    
    cu.execute("select * from catalog ")       # item[0] is student number
    show_item = cu.fetchall()
    write_List = []
    for item in show_item:
        str1 = str(item[0])+"\t"+item[1]+"\t"+item[2]+"\t"+str(item[3])+\
        "\t"+str(item[4])+"\n"
        write_List.append(str1)
    fpath = 'F:/课件/Python/final scores.txt'
    uifpath = unicode(fpath , "utf8")
    file = open(uifpath,'w')
    try:
        file.writelines(write_List)
    finally:
        file.close()

    pass
    
def sel():
    global selected_Student
    
    path = 'F:/课件/Python/' + db
    uipath = unicode(path , "utf8")

    cx = sqlite3.connect(uipath)
    cu = cx.cursor()
    
    item =  selected_Student.split()
    
    cu.execute("select * from catalog where st_num = \'" + item[0] + '\'')       # item[0] is student number
    show_item = cu.fetchone()
    selection = selected_Student+ " got " + str(var.get()) + " score(s)!\n" +\
    "The total score is " + str(show_item[4]+var.get())                    # show_item[4] is scores in table catalog

    cu.execute("update catalog set scores = "+  str(show_item[4]+var.get()) + \
     " where st_num = \'" + item[0] + '\'')
    cx.commit()
    R1.config(state = 'disable')
    R2.config(state = 'disable')
    R3.config(state = 'disable')
    label.config(text = selection)
   
def create_DB():
    path = 'F:/课件/Python/' + db
    uipath = unicode(path , "utf8")
    read_List = readfile()
    
    cx = sqlite3.connect(uipath)
    cu=cx.cursor()
    cu.execute("create table catalog (id integer primary key,st_num varchar(20) UNIQUE,\
    name varchar(20), count integer, scores integer)")
    
    for item in read_List:
        insert_Item = (item[0],item[2],unicode(item[1]),0,0)
        cx.execute("insert into catalog values (?,?,?,?,?)",insert_Item)
    cx.commit()

           
window = Tk()
flag = True
window.geometry("800x500+200+100")
window.minsize(800,500)

ft = tkFont.Font(family = 'Fixdsys',size = 15,weight = tkFont.BOLD)
top_label = Label(window, fg='blue',text=" I want to u !!!",borderwidth=1,
                  font = ft, width = 15, height=2,anchor='center')
top_label.place(relx=0.5,rely=0.3,x=-75,y=-100)

ft1 = tkFont.Font(family = 'Courier New',size = 24,weight = tkFont.BOLD)
label = Label(window, fg='Red',bg='white',text=" Ready !",borderwidth=1,
              font = ft1, width = 35, height=5,relief ='raised',anchor='center')
label.place(relx=0.5,rely=0.3,x=-330,y=-50)

ft2 = tkFont.Font(family = 'Verdana',size = 12,weight = tkFont.BOLD)
bt_Start = Button(window,text="Start",relief="raised",width = 15,
                  height=2,anchor='center',font=ft2)
bt_Start.bind('<Button-1>',start_call)
bt_Start.place(relx=0.5,rely=0.65,x=-330,y=0)

bt_Stop = Button(window,text="Stop",relief="raised",width = 15, 
                 height=2,anchor='center',font=ft2)
bt_Stop.bind('<Button-1>',stop_call)
bt_Stop.place(relx=0.5,rely=0.65,x=-80,y=0)

bt_Export = Button(window,text="Export",relief="raised",width = 15, 
                 height=2,anchor='center',font=ft2)
bt_Export.bind('<Button-1>',export_all)
bt_Export.place(relx=0.5,rely=0.65,x=160,y=0)

var = IntVar()
R1 = Radiobutton(window, text="Score 0", variable=var, value=0,
                  command=sel, font=ft2)
R1.place(relx=0.5,rely=0.85,x=-230,y=0)

R2 = Radiobutton(window, text="Score 1", variable=var, value=1,
                  command=sel, font=ft2)
R2.place(relx=0.5,rely=0.85,x=-30,y=0)

R3 = Radiobutton(window, text="Score 2", variable=var, value=2,
                  command=sel, font=ft2)
R3.place(relx=0.5,rely=0.85,x=170,y=0)

R1.config(state = 'disable')
R2.config(state = 'disable')
R3.config(state = 'disable')

#create_DB()                # Only run the code in this program at first time 

window.mainloop()

