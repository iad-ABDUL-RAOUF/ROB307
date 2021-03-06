import numpy as np
import cv2
import POC_python_function as fnct
import matplotlib.pyplot as plt
import time

#Ouverture du flux video

filename = 'lions_chassent_buffles.m4v'
#filename = 'Rotation_OY(Pan).m4v'
#directory = '../../donnees/videos/videos_ROB317/'
directory = '../../../donnees/videos/video_vie_sauvage_youtube/'
figDirectory = '../../../figure/newFig/'
cap = cv2.VideoCapture(directory+filename)
#cap = cv2.VideoCapture(0)
startIndex = 3400

# passe le début de la video
index = 0
ret = True
while(ret & (index<=startIndex)):
    ret, frame1 = cap.read() # Passe à l'image suivante
    index = index+1
    print(index)

(height,width,channels) = frame1.shape
prvs = cv2.cvtColor(frame1,cv2.COLOR_BGR2GRAY) # Passage en niveaux de gris
hsv = np.zeros_like(frame1) # Image nulle de même taille que frame1 (affichage OF)
hsv[:,:,1] = 255 # Toutes les couleurs sont saturées au maximum

ret, frame2 = cap.read()
next_frame = cv2.cvtColor(frame2,cv2.COLOR_BGR2GRAY)

'''
iPixRange = np.arange(height)
jPixRange = np.arange(width)
pointIm1_i, pointIm1_j = np.meshgrid(iPixRange, jPixRange, indexing = 'ij')
pointHomoIm1 = np.concatenate((pointIm1_i.reshape((-1,1)),
                           pointIm1_j.reshape((-1,1)),
                           np.ones((height*width,1))),
                          axis = 1)
'''
# initialise certaine grandeurs
pas = 20
iPixRange = np.arange(pas//2,height,pas)
jPixRange = np.arange(pas//2,width,pas)
DS_height = iPixRange.size
DS_width = jPixRange.size
pointIm1_i, pointIm1_j = np.meshgrid(iPixRange, jPixRange, indexing = 'ij')
DS_pointHomoIm1 = np.concatenate((pointIm1_i.reshape((-1,1)),
                                         pointIm1_j.reshape((-1,1)),
                                         np.ones((DS_height*DS_width,1))),
                                        axis = 1)
matOutBool = np.ones((height, width), dtype=bool)






# RANSAC parameters
threshold = 1 # marge d'erreur accepté en pixel pour dire qu'un point fit
sample_size = 5
goal_inliers = int(DS_height*DS_width*0.6)
max_iterations = 100
stop_at_goal = True
random_seed = None



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
    '''
    Vi = flow[:,:,0].reshape((-1,1))
    Vj = flow[:,:,1].reshape((-1,1))
    VHomoIm1 = np.concatenate((Vi,
                               Vj,
                               np.zeros((height*width,1))),
                              axis = 1)
    '''
    DS_Vi = flow[pas//2::pas,pas//2::pas,0].reshape((-1,1))
    DS_Vj = flow[pas//2::pas,pas//2::pas,1].reshape((-1,1))
    DS_VHomoIm1 = np.concatenate((DS_Vi,
                                  DS_Vj,
                                  np.zeros((DS_height*DS_width,1))),
                                 axis = 1)
    '''
    pointHomoIm2 = pointHomoIm1 + VHomoIm1
    '''
    # DS_pointHomoIm1.shape = (2304, 3) = DS_VHomoIm1.shape, 2304 = DS_height*DS_width
    DS_pointHomoIm2 = DS_pointHomoIm1 + DS_VHomoIm1
    # best_model matrice 3*3 mais OSEF, best_ic int, DS_outliersBool vecteur booleen  
    best_model, best_ic, DS_outliersBool = fnct.run_ransac(DS_pointHomoIm1, DS_pointHomoIm2, threshold, sample_size, goal_inliers, max_iterations, stop_at_goal, random_seed)
    
    if best_ic == None:
        print(None)
        DS_frameOutliers = np.zeros_like(frame1[pas//2::pas,pas//2::pas,:])
        DS_frameInliers = np.zeros_like(frame1[pas//2::pas,pas//2::pas,:])
        frameOutliers = np.zeros_like(frame1)
        frameInliers = np.zeros_like(frame1)
    else :
        print(np.count_nonzero(DS_outliersBool))
        # determine les objets mobile (outliers) sur l'image echantilloné
        DS_matOutBool = DS_outliersBool.reshape((DS_height,DS_width))
        DS_frameOutliers = frame1[pas//2::pas,pas//2::pas,:].copy()
        DS_frameOutliers[~DS_matOutBool] = 0
        DS_frameInliers = frame1[pas//2::pas,pas//2::pas,:].copy()
        DS_frameInliers[DS_matOutBool] = 0
        # determine les objets mobile sur l'image complete à partir des outlier sur l'image echantilloné 
        for i in range(pas):
            for j in range (pas):
                matOutBool[i::pas,j::pas] = DS_matOutBool
        frameOutliers = frame1.copy()
        frameOutliers[~matOutBool] = 0
        frameInliers = frame1.copy()
        frameInliers[matOutBool] = 0
    DS_inOutFrame = np.vstack((frame1[pas//2::pas,pas//2::pas,:],DS_frameOutliers,DS_frameInliers))
    
    
    
    
    

    '''
    # outliers = pointHomoIm1[outliersIdx,:]
    matOutBool = outliersBool.reshape((height,width))
    frameOutliers = frame1.copy()
    frameOutliers[~matOutBool,:] = 0
    frameInliers = frame1.copy()
    frameInliers[matOutBool,:] = 0
    inliersOutliersFrame = np.vstack((frameInliers,frameOutliers,frame1))
    cv2.imshow('inliersOutliersFrames',inliersOutliersFrames)
    '''
    

    # DS_inOutFrameDuplique = np.zeros((DS_inOutFrame[0]*3, DS_inOutFrame[1]*3))
    # DS_inOutFrameDuplique[0::3, 0::3] = DS_inOutFrame
    # DS_inOutFrameDuplique[0::3, 1::3] = DS_inOutFrame
    # DS_inOutFrameDuplique[0::3, 2::3] = DS_inOutFrame
    # DS_inOutFrameDuplique[1::3, 0::3] = DS_inOutFrame
    # DS_inOutFrameDuplique[1::3, 1::3] = DS_inOutFrame
    # DS_inOutFrameDuplique[1::3, 2::3] = DS_inOutFrame
    # DS_inOutFrameDuplique[2::3, 0::3] = DS_inOutFrame
    # DS_inOutFrameDuplique[2::3, 1::3] = DS_inOutFrame
    # DS_inOutFrameDuplique[2::3, 2::3] = DS_inOutFrame
    # cv2.imshow('inliersOutliersFrames',DS_inOutFrameDuplique)
    cv2.imshow('inliersOutliersFrames',DS_inOutFrame)
    cv2.imshow('frameOutliers',frameOutliers)
    cv2.imshow('frameInliers',frameInliers)
    
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
        cv2.imwrite(figDirectory+'Frame_%04d.png'%index,frame2)
        cv2.imwrite(figDirectory+'OF_hsv_%04d.png'%index,bgr)
        cv2.imwrite(figDirectory+'DS_inOutFrame%04d.png'%index,DS_inOutFrame)
        cv2.imwrite(figDirectory+'DS_Outliers%04d.png'%index,DS_frameOutliers)
        cv2.imwrite(figDirectory+'DS_Inliers%04d.png'%index,DS_frameInliers)
        cv2.imwrite(figDirectory+'Outliers%04d.png'%index,frameOutliers)
        cv2.imwrite(figDirectory+'Inliers%04d.png'%index,frameInliers)
    prvs = next_frame
    ret, frame2 = cap.read()
    if (ret):
        frame1 = frame2.copy()
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

'''


'''



