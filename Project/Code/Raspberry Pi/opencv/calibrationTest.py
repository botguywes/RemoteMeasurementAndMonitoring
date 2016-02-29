import os
import cv2
import math
import time

##Resize with resize command
def resizeImage(img):
    dst = cv2.resize(img,None, fx=0.25, fy=0.25, interpolation = cv2.INTER_LINEAR)
    return dst

##Take image with Raspberry Pi camera
img_name = str(int(time.time())) + 'image.jpg'
os.system('raspistill -o images/' + img_name)

##Load image
img = cv2.imread("/home/pi/opencv/images/" + img_name) 
grey = cv2.imread("/home/pi/opencv/images/" + img_name, 0) #0 for grayscale

height, width = img.shape[:2]

total_radius = 300

w_y1 = (height/2) - (total_radius/2)
w_y2 = (height/2) + (total_radius/2)
w_x1 = (width/2) - (total_radius/2)
w_x2 = (width/2) + (total_radius/2)

#want to reduce the amount of the image we are working with
cropped = img[w_y1:w_y2, w_x1:w_x2]
cv2.imwrite('laser.jpg', cropped)

##Run Threshold on image to make it black and white
ret, thresh = cv2.threshold(grey[w_y1:w_y2, w_x1:w_x2], 200, 255, cv2.THRESH_BINARY)

cv2.imwrite('thresh_laser.jpg', thresh)

#thresh = cv2.adaptiveThreshold(cropped,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY,11,2)

##Use houghcircles to determine center of circle
circles = cv2.HoughCircles(thresh, cv2.cv.CV_HOUGH_GRADIENT, 1, 75, param1=50, param2=13, minRadius=0, maxRadius=175)
for i in circles[0,:]:
    #draw the outer circle
    cv2.circle(cropped,(i[0], i[1]), i[2], (0, 255, 0), 2)
    #draw the center of the circle
    cv2.circle(cropped,(i[0], i[1]), 2, (0,0,255), 3)

##Determine coordinates for center of circle
x1 = circles[0][0][0]
y1 = circles[0][0][1]

##print information
print "===== Calibration Program Results ====="

print "Blob Information: "
print "x1 = ", x1
print "y1 = ", y1
print circles

if math.fabs((total_radius/2) - x1) > 0:
  print "X distance off by: ", math.fabs((total_radius/2) - x1), " pixels"

if math.fabs((total_radius/2) - y1) > 0:
  print "Y distance off by: ", math.fabs((total_radius/2) - y1), " pixels"

##Resize image
img = resizeImage(img)
thresh = resizeImage(thresh)
cropped = resizeImage(cropped)

##Show Images 
cv2.imwrite("thresh.jpg",thresh)
cv2.imwrite("img.jpg",img)
cv2.imwrite("grey.jpg",grey)
cv2.imwrite("cropped.jpg", cropped)
cv2.waitKey(0)
