#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov 24 09:04:43 2020

@author: iad
"""


import numpy as np
import cv2
import TP_rob313_function as fnct
import matplotlib.pyplot as plt
import time

# Let us read the image
PATH_IMG = '../../donnees/images/'

im_col = cv2.imread(PATH_IMG+"Pompei.jpg")
im = cv2.cvtColor(im_col, cv2.COLOR_BGR2GRAY)
#im_pil
(h,w) = im.shape
print("Dimension de l'image :",h,"lignes x",w,"colonnes")
# let us plot the image
cv2.imshow('image de depart',im)
# affichage suivant juste pour etre sure de savoir dans quelle sens sont définis
# les coordonnées x et y
cv2.imshow('image de depart coupe', im[0:100,:])
k = cv2.waitKey(200) & 0xff
# Let us apply a homography on the image
H_true = np.array([[ 1.37054309e+00 , 3.26472981e-01 ,-9.09781842e+01],
 [ 3.46896567e-03,  1.65383589e+00, -7.78613246e+01],
 [ 1.73448284e-04,  1.14069045e-03 , 1.00000000e+00]])
theta = 0 #np.pi/8
c = np.cos(theta)
s = np.sin(theta)
eps = 1
l = 0.5
tx = 125 #-9.09781842e+01
ty = 75 #-7.78613246e+01
v1 = 0.00004
v2 = 0.0005
H_test = np.array([[  eps*l*c, -l*s ,tx],
                   [ eps*l*s,  l*c, ty],
                   [ v1,  v2 , 1.00000000e+00]])

print('this the homography we want to estimate\n',H_true)

print('this the homography test\n',H_test)

im2 = cv2.warpPerspective(im, H_true, (w,h))
imtest = cv2.warpPerspective(im, H_test, (w,h))

#Image.fromarray(im2_pil)

cv2.imshow('image test',imtest)
cv2.imshow('image apres Htrue',im2)
k = cv2.waitKey(200) & 0xff

# build a set of points
X_1=np.array([[100,440,1]])
X_2=np.array([[200,30,1]])
X_3=np.array([[20,80,1]])
X_4=np.array([[40,200,1]])
X_5=np.array([[300,140,1]])

X=np.concatenate((X_1, X_2,X_3, X_4, X_5), axis=0)

#x=np.transpose(np.matmul(H_true, np.transpose(X)))+ np.random.normal(0, 0.5, size=(5, 3))

# MODIFICATION DU TP : je n'ajoute du bruit que sur les deux premières 
# coordonnées homogènes en ayant au préalable fixé la troisième coordonnées à 1.
# De cette manière le bruit est plus facilement interprétable. Il s'agit du
# bruit en pixel sur les coordonnées 2D des points dans l'image. Ce n'etait pas
# le cas lorsque le bruit était aussi ajouté sur la troisième coordonnée.
x=np.transpose(np.matmul(H_true, np.transpose(X)))
x[:,:] = x[:,:]/x[:,2:3]
x[:,0:2] = x[:,0:2] + np.random.normal(0, 0.5, size=(5, 2))

print('initial point \n',X) # let us print the initial points
print('transformed point \n',x) # let us print the transform points


# Let us apply the DLT code to estimate the Homography
L1, err_singVal1, err_euclide2D1 = fnct.DLTcalib2(X, x)
L2, err_singVal2, err_euclide2D2 = fnct.NormalizedDLTcalib2(X, x, h, w)

print('Truth homography \n',H_true)
print('Truth homography \n',np.rint(H_true))
print('\n')
print('estimated homography DLT \n',L1)
print('estimated homography DLT \n',L1/L1[2,2])
print('estimated homography DLT \n',np.rint(L1)) #np.floor(L)) np.ceil(L))
print('The DLT homography estimation errors are \n err_singVal1 = ', err_singVal1, 'and err_euclide2D1 = ', err_euclide2D1)
print('\n')
print('estimated homography normalized DLT \n',L2)
print('estimated homography normalized DLT \n',L2/L2[2,2])
print('estimated homography normalized DLT \n',np.rint(L2)) #np.floor(L)) np.ceil(L))
print('The normalized DLT homography estimation errors are \n err_singVal2 = ',err_singVal2, 'and err_euclide2D2 = ', err_euclide2D2)


# we use the function make_regression to generate a random regression problem. 
n_samples = 1000
n_outliers = 100
# we call X and x the name of the points such that x=HX

# creation of random points and their transformation by H_true
X = np.concatenate((np.random.rand(n_samples,1)*h,
                    np.random.rand(n_samples,1)*w,
                    np.ones((n_samples,1))),
                   axis = 1)
x = np.matmul(X,H_true.transpose())

# add some noise to the transformed points
x[:,0:2] = x[:,0:2] + np.random.normal(0, 0.5, size=(n_samples, 2))

# replace some points by outliers
X[0:n_outliers,:] = np.concatenate((np.random.rand(n_outliers,1)*h,
                                    np.random.rand(n_outliers,1)*w,
                                    np.ones((n_outliers,1))),
                                   axis = 1)

# melange les outliers avec les inliers
indices = np.arange(n_samples)
np.random.shuffle(indices)
x = x[indices,:]
X = X[indices,:]


best_model, best_ic = fnct.run_ransac(X,x , 5.0, 5, 800, 10)
print('estimated homography',best_model)
print('estimated homography',np.rint(best_model)) #np.floor(L)) np.ceil(L)) 
print('Truth homography',H_true)
print('Truth homography',np.rint(H_true))


L1, err_singVal1, err_euclide2D1 = fnct.DLTcalib2(X, x)
L2, err_singVal2, err_euclide2D2 = fnct.NormalizedDLTcalib2(X, x, h, w)

print('Truth homography \n',H_true)
print('Truth homography \n',np.rint(H_true))
print('\n')
print('estimated homography DLT \n',L1)
print('estimated homography DLT \n',L1/L1[2,2])
print('estimated homography DLT \n',np.rint(L1)) #np.floor(L)) np.ceil(L))
print('The DLT homography estimation errors are \n err_singVal1 = ', err_singVal1, 'and err_euclide2D1 = ', err_euclide2D1)
print('\n')
print('estimated homography normalized DLT \n',L2)
print('estimated homography normalized DLT \n',L2/L2[2,2])
print('estimated homography normalized DLT \n',np.rint(L2)) #np.floor(L)) np.ceil(L))
print('The normalized DLT homography estimation errors are \n err_singVal2 = ',err_singVal2, 'and err_euclide2D2 = ', err_euclide2D2)

time.sleep(15)
cv2.destroyAllWindows()
