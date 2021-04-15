
'''
Realizati un program cu GUI care sa citeasca o poza si o culoare, apoi sa produca o imagine
binara care sa transforme toti pixelii din imaginea initiala care sunt apropiati sub un anumit
prag de culoarea selectata in alb, iar pe ceilalti in negru. Pragul se stabileste printr-un slider.
'''
from tkinter import *
from PIL import Image
from PIL import ImageTk
import tkinter.filedialog
from tkinter.colorchooser import askcolor                  
import cv2
import os


def callback():
    result = askcolor(color="#6A9662", 
                      title = "Bernd's Colour Chooser") 
    print (result)
  
# Stabilim dimensiunile etichetelor cu poze in functie de
# lungimea dorita pentru eticheta si de dimensiunile pozei
def stabilesteInaltimea(lungimePanou, lungimePoza, inaltimePoza):
    inaltimePanou = (lungimePanou * inaltimePoza) / lungimePoza
    return int(inaltimePanou)
# Metoda ce urmeaza sa fie apelata de catre butonul de incarcare a pozei
def selectareImagine():

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
                cv2.imshow('Frame', frame)
                
                if cv2.waitKey(25) & 0xFF == ord('q'):
                    break
                
            else:
                break

    video.release()
    cv2.destroyAllWindows()


root = Tk()

root.title('Ponderare binara')
labelA = None
labelB = None
gri = None #imaginea gri este globala ca sa o folosim in schimbaPrag
# Butonul care apeleaza metoda "selectareImagine"
btn = Button(root, text="Incarca o imagine", command = selectareImagine)
#adaugam butonul in partea de jos a ferestrei
btn.pack(side="bottom", fill="both", expand="no", padx="10", pady="10")
#adaugam un slider si pentru acesta o metoda

Button(root, 
       text='Choose Color', 
       fg="darkgreen", 
       command=callback).pack(side=LEFT, padx=10)

# Lansam interfata
root.mainloop()