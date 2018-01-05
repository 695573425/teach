# -*- coding: utf-8 -*-
"""
Created on Tue Nov 25 16:22:34 2014

@author: dell
"""
import sys
def create_Graph():
    global cities,dis,links # saaaaaa 
    
    try:
        infile = open('F:\\13_Distances.txt','r')
        
        for lin in infile.readlines():
            l = lin.split()
            
            dis.append(tuple(l))
            
            cities.add(l[0])
            
            if l[0] not in links.keys():
                links[l[0]]=[]
            else:
                links[l[0]].append(l[1])
    except IOError,e:
        print e
        return 0
    else:
        infile.close()
        return 1
        
#============= main body ============
cities =set()
dis = []
links= {}
if 1==create_Graph():
    print "1. Succeed to create cities'maps."
else:
    print "Cannot create the cities'maps and exit"
    sys.exit()
    
#for i in cities:
#    print i
#for i in dis:
#    print i
#for i in links.items():
#    print i
print "2. to calculate the least cost road"

s_city = raw_input("Source Node:")
if s_city not in cities:
    print "No city name and not share"
d_city = raw_input("Desitation Node:")
if d_city not in cities:
    print "No city name and not share"
if s_city == d_city:
    print "The minimum dis from",s_city,"to",d_city,"is",0
else:
    # step one
    T=set([s_city])
    LC={}                # for minimiun rats
    Path={}                # for least route recordsz
    
    for i in cities:
        LC[i]=10e6
        Path[i]=[s_city]
    
    for i in links[s_city]:
        for j in dis:
            if list(j[0:2])==[s_city,i]:
                LC[i]=float(j[2])
                Path[i].append(i)
    
    neighbor = set(links[s_city])
    count = 0
    while True:
        # step two
        min_L = 10e6
        n_city = ""
 
        for i in neighbor:
            if i in cities-T and float(LC[i])<min_L:
                min_L=float(LC[i])
                n_city = i
      
        # step three
        T = T|set([n_city])
 
        neighbor =  (neighbor|set(links[n_city]))-T
        print T
        for x_city in neighbor:
            d = 0
            for j in dis:
                if [n_city, x_city] == list(j[:2]):
                    d = float(j[2])
                    if LC[x_city] > LC[n_city] + d:
#                        print x_city,LC[x_city],LC[n_city]+ d
                        LC[x_city] = LC[n_city]+ d
                        Path[x_city] = Path[n_city]+[x_city]
#                        print Path[x_city]
        # step four
        if T==cities:
            break 
        count += 1
    print "3.The minimum dis from",s_city,"to",d_city,"is", LC[d_city]
    print "4.The least route from",s_city,"to",d_city,"is", Path[d_city]

    
    