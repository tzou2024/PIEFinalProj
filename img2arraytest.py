# import the required modules

import cv2
from matplotlib import pyplot as plt
import numpy as np
import serial
import time
  
# Read the image
img = cv2.imread(r'C:\Users\tzou\Documents\GitHub\PIEFinalProj\330px-Flag_of_the_United_States.svg.png', 0)
#plt.imshow(img, interpolation='nearest')p

#plt.show()

"""
img = cv2.imread("mic.jpg")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
hist = cv2.calcHist([gray],[0],None,[256],[0,256])
colors = np.where(hist>5000)
img_number = 0
for color in colors[0]:
    print(color)
    split_image = img.copy()
    split_image[np.where(gray != color)] = 0
    cv2.imwrite(str(img_number)+".jpg",split_image)
    img_number+=1
plt.hist(gray.ravel(),256,[0,256])
plt.savefig('plt')
plt.show()
"""
# Apply median blur
img = cv2.medianBlur(img, 5)

  
# Apply MEAN thresholding to get refined edges
image = cv2.adaptiveThreshold(
    img, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)

# Convert the image into a compatible size
# We will use 60 pixels wide image so that text
# fits in the console
  
# Preserve the ratio
ratio = len(image)/len(image[0])
# Assign new width and calculate new height
new_width = 9

new_height = int(ratio*new_width)
# Resize the image
image = cv2.resize(image, (new_height, new_width))
  
# Iterate over the array and print the dark pixels
# or we can use any other symbol too.
serialfile = ""
for i in range(len(image)):
    for j in range(len(image[0])):
        print("o" if image[i, j] < 100 else ".", end="")
        serialfile += str(("1" if image[i, j] < 100 else "0"))
    print()

print(serialfile)
print(len(serialfile))
from numpy import asarray
# asarray() class is used to convert
# PIL images into NumPy arrays
numpydata = asarray(image)
  
# <class 'numpy.ndarray'>
print(numpydata)
  
#  shape

print(new_width)

print(new_height)
finalstring = ""
for i in range(new_width):
    for j in np.flip(numpydata[:,i]):
        if j > 250:
            finalstring = finalstring + "0"
        else:
            finalstring = finalstring + "1"
print(finalstring)

'''
arduino = serial.Serial(port='COM10', baudrate=9600, timeout=.1)
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data

while True:
    num = input("Send Data") # TakiYng input from user
    if num:
        value = write_read(serialfile)
        print(num)
        '''