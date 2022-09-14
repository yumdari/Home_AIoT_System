import numpy as np
import cv2

lowerBound = np.array([20, 100, 100])
upperBound = np.array([40, 255, 255])

def showcam():
    try:
        cap = cv2.VideoCapture(1)
    except:
        print('Not working')
        return
    while True:
        ret, frame = cap.read()
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        color_mask = cv2.inRange(hsv, lowerBound, upperBound)
        ret1, thr = cv2.threshold(color_mask , 127, 255, 0)

        kernel = np.ones((11,11),np.uint8)
        result = cv2.morphologyEx(thr, cv2.MORPH_CLOSE, kernel)
        kernel2 = np.ones((5, 5), np.uint8)
        result2 = cv2.morphologyEx(result, cv2.MORPH_OPEN, kernel2)
        
        contours, _ = cv2.findContours(result2, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if len(contours) > 0:
            for i in range(len(contours)):
                area = cv2.contourArea(contours[i]) 
                if area > 10000:  
                    rect = cv2.minAreaRect(contours[i])
                    box = cv2.boxPoints(rect) 
                    box = np.int0(box) 
                    cv2.drawContours(frame, [box], 0, (0, 255, 0), 4)
        if not ret:
            print('error')
            break
        cv2.imshow('color_bitwise',color_mask)
        cv2.imshow('cam_load',frame)
        print('contours : %d'% len(contours))  
        k = cv2.waitKey(1) & 0xFF
        if k == 27:
            break
        if len(contours) > 3:
            count = 1
        else:
            count = 0
        print('택배 유무 : %d'% count)
    cap.release()
    cv2.destroyAllWindows()
showcam()
