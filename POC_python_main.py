import numpy as np
import cv2
import TP_rob313_function as fnct
import matplotlib.pyplot as plt
import time

#Ouverture du flux video

filename = 'Extrait1-Cosmos_Laundromat1(340p).m4v'
#filename = 'Rotation_OY(Pan).m4v'
directory = '../../donnees/videos/videos_ROB317/'
cap = cv2.VideoCapture(directory+filename)
#cap = cv2.VideoCapture(0)

ret, frame1 = cap.read() # Passe à l'image suivante
(height,width) = frame1.shape
prvs = cv2.cvtColor(frame1,cv2.COLOR_BGR2GRAY) # Passage en niveaux de gris
hsv = np.zeros_like(frame1) # Image nulle de même taille que frame1 (affichage OF)
hsv[:,:,1] = 255 # Toutes les couleurs sont saturées au maximum

index = 1
ret, frame2 = cap.read()
next_frame = cv2.cvtColor(frame2,cv2.COLOR_BGR2GRAY)

iPixRange = np.arange(height)
jPixRange = np.arange(width)
pointIm1_i, pointIm1_j = np.meshgrid(iPixRange, jPixRange, indexing = 'ij')
pointHomoIm1 = np.concatenate((pointIm1_i.reshape((-1,1)),
                           pointIm1_j.reshape((-1,1)),
                           np.ones((height*width,1))),
                          axis = 1)

while(ret):
    index += 1
    flow = cv2.calcOpticalFlowFarneback(prvs,next_frame,None, 
                                        pyr_scale = 0.5,# Taux de réduction pyramidal
                                        levels = 3, # Nombre de niveaux de la pyramide
                                        winsize = 15, # Taille de fenêtre de lissage (moyenne) des coefficients polynomiaux
                                        iterations = 3, # Nb d'itérations par niveau
                                        poly_n = 7, # Taille voisinage pour approximation polynomiale
                                        poly_sigma = 1.5, # E-T Gaussienne pour calcul dérivées 
                                        flags = 0)	
    Vi = flow[:,:,0].reshape((-1,1))
    Vj = flow[:,:,1].reshape((-1,1))
    VHomoIm1 = np.concatenate((Vi,
                           Vj,
                           np.zeros((height*width,1))),
                          axis = 1)
    pointHomoIm2 = pointHomoIm1 + VHomoIm1
    #best_model, best_ic, outliers = fnct.run_ransac(pointHomoIm1,pointHomoIm2 , 5.0, 5, 800, 10) param à regler et outlier à retourner

    mag, ang = cv2.cartToPolar(flow[:,:,0], flow[:,:,1]) # Conversion cartésien vers polaire
    hsv[:,:,0] = (ang*180)/(2*np.pi) # Teinte (codée sur [0..179] dans OpenCV) <--> Argument
    hsv[:,:,2] = (mag*255)/np.amax(mag) # Valeur <--> Norme 
    bgr = cv2.cvtColor(hsv,cv2.COLOR_HSV2BGR)
    result = np.vstack((frame2,bgr))
    cv2.imshow('Image et Champ de vitesses (Farneback)',result)
    k = cv2.waitKey(15) & 0xff
    if k == 27:
        break
    elif k == ord('s'):
        cv2.imwrite('Frame_%04d.png'%index,frame2)
        cv2.imwrite('OF_hsv_%04d.png'%index,bgr)
    prvs = next_frame
    ret, frame2 = cap.read()
    if (ret):
        next_frame = cv2.cvtColor(frame2,cv2.COLOR_BGR2GRAY) 

cap.release()
cv2.destroyAllWindows()

'''
height = 3
width = 7
iPixRange = np.arange(height)
jPixRange = np.arange(width)
pointIm1_i, pointIm1_j = np.meshgrid(iPixRange, jPixRange, indexing = 'ij')
pointIm1 = np.concatenate((pointIm1_i.reshape((-1,1)),
                           pointIm1_j.reshape((-1,1)),
                           np.ones((height*width,1))),
                          axis = 1)


Vi = flow[:,:,0].reshape((-1,1))
Vj = flow[:,:,1].reshape((-1,1))
Vim1 = np.concatenate((Vi,
                       Vj,
                       np.zeros((height*width,1))),
                      axis = 1)

pointIm2 = pointIm1 + Vim1



best_model, best_ic, outliers = fnct.run_ransac(X,x , 5.0, 5, 800, 10)
'''


