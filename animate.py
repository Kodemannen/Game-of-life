import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation
import time
import sys
import os

with open("pop.txt", "r") as popfile:
    data = np.loadtxt(popfile)

with open("rulevec.txt", "r") as f:
    rulevec = np.loadtxt(f, dtype=np.int32)

    # to string as well:
    rulevecstring = ""
    for elem in rulevec: 
        rulevecstring += str(elem)



# windows size:
N_GENERATIONS = data.shape[0]
POPSIZE = data.shape[1]
SCREEN_SIZE_Y = POPSIZE     # how big screen in y-direction

fps = 60


startmark = np.array([0])
endmark = np.array([2])

#current_screen = np.ones((SCREEN_SIZE_Y, POPSIZE))     # start with white screen
#current_screen[-1, :] = data[0, :]         # start at the top 
fig, ax = plt.subplots(nrows=1, ncols=1, sharex=False,  sharey=False)

indices = np.arange(0, N_GENERATIONS-SCREEN_SIZE_Y)


def update_frame(i):

    print(i/len(indices) * 100, "\%")
    ax.clear()

    if i < SCREEN_SIZE_Y:

        current_screen = np.ones((SCREEN_SIZE_Y, POPSIZE))

        # add take the ith first data on top of the screen:
        current_screen[:i+1, :] = data[:i+1, :]

    else:

        current_screen = data[i-SCREEN_SIZE_Y:i, :]

    ax.imshow(current_screen)
    ax.axis('off')
    
            



#-------------------------------------------------
# Generating .mp4
Writer = animation.writers['ffmpeg']
writer = Writer(fps=fps, metadata=dict(artist="Me"), bitrate=850)

ani = animation.FuncAnimation(fig, update_frame, indices)   #, fargs=(count,indices))
ani.save("1d_cellular_automata_" + rulevecstring + ".mp4", writer=writer, dpi=100)



