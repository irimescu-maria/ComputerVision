from tkinter import *
import tkinter.filedialog
from tkinter.colorchooser import askcolor    
from PIL import ImageTk, Image
import cv2
import os



# Capture from camera
cap = cv2.VideoCapture(0)

# function for video streaming
def video_stream():
    _, frame = cap.read()
    cv2image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGBA)
    img = Image.fromarray(cv2image)
    imgtk = ImageTk.PhotoImage(image=img)
    lmain.imgtk = imgtk
    lmain.configure(image=imgtk)
    lmain.after(1, video_stream) 
    
def load_video():

    global labelA, labelB, gri, binara
    # citim poza de la o locatie selectata de utilizator
    cale = tkinter.filedialog.askopenfilename()
    print(len(cale))
    if len(cale) > 0: #daca avem o cale
        video = cv2.VideoCapture(os.path.split(cale)[1])
     #   video = cv2.VideoCapture('drop.avi')

        print('video', video)
        
        if(video.isOpened() == False):
            print("Error opening video stream or file")
            
        while(video.isOpened()):
            ret, frame = video.read()
            if ret == True:
                frame_image = ImageTk.PhotoImage(Image.fromarray(frame))
                lmain.configure(image = frame_image)
                lmain.image = frame_image
              #  cv2.imshow('Frame', frame)
                
                if cv2.waitKey(25) & 0xFF == ord('q'):
                    break
                
            else:
                break

    video.release()
    cv2.destroyAllWindows()

root = tkinter.Tk()
#root.geometry("800x850+0+0")
root.configure(background="lightblue")

frame = tkinter.Frame(root, width=100, height=50)
frame.place(x=600,y=0)
frame.grid()

# Create a label in the frame
lmain = tkinter.Label(frame )
#lmain.grid()

button_camera = tkinter.Button(frame, text="Open camera", command = video_stream)
button_camera.pack(side=tkinter.LEFT)

button_video = tkinter.Button(frame, text = "Load video", command = load_video)
button_video.pack(side= tkinter.RIGHT)

root.mainloop()