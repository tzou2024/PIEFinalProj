# import the required modules
import cv2
from matplotlib import pyplot as plt
import numpy as np
import serial
arduinoComPort = "COM8"
baudRate = 9600

serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)
  
# Read the image
img = cv2.imread(r'C:\Users\tzou\Desktop\Olin 2021\PIE\BigProj\mickey.jpg', 0)
#plt.imshow(img, interpolation='nearest')

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
new_width = 60
new_height = int(ratio*new_width)
# Resize the image
image = cv2.resize(image, (new_height, new_width))
  
# Iterate over the array and print the dark pixels
# or we can use any other symbol too.
serialfile = []
for i in range(len(image)):
    for j in range(len(image[0])):
        print("o" if image[i, j] < 100 else ".", end="")
        serialfile.append("1" if image[i, j] < 100 else "0")
    print()

print(serialfile)
print(len(serialfile))

def serial_write(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)


while True:
    serial_write(serialfile)