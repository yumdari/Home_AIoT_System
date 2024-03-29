import numpy as np
import cv2
import time
import threading
from flask import Response, Flask
from socket import *

lowerBound = np.array([20, 100, 100])
upperBound = np.array([40, 255, 255])

#ip = "10.10.141.27"
ip = "10.10.141.217"
port = 5000
clientSocket = socket(AF_INET, SOCK_STREAM)		# 소켓 생성
clientSocket.connect((ip,port))					# 서버와 연결
#global preFlagFace
#global preFlagBox
preFlagFace = 0
preFlagBox = 0

# Box check
isBoxHere = 0
sentMsgBox = 0

boxOkCnt = 0
boxNoCnt = 0

# Face Check
faceFlag = 0
sentMsgface = 0

faceOkCnt = 0
faceNoCnt = 0


#detector = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
detector = cv2.CascadeClassifier('haarcascade_frontalface_alt.xml')

# Image frame sent to the Flask object
global video_frame
video_frame = None

# Use locks for thread-safe viewing of frames in multiple browsers
global thread_lock 
thread_lock = threading.Lock()

# Create the Flask object for the application
app = Flask(__name__)

def socketSendFace():
    clientSocket.send("CAM:0\n".encode("utf-8"))
    
def socketSendBox():
    clientSocket.send("CAM:1\n".encode("utf-8"))

def captureFrames():
    global video_frame, thread_lock
    socketFlagFace = 0
    socketFlagBox = 0
    global preFlagFace
    global preFlagBox


    # TEst
    global isBoxHere
    global sentMsgBox

    global boxOkCnt
    global boxNoCnt
  

    global faceFlag
    global sentMsgface

    global faceOkCnt
    global faceNoCnt

    
    # Video capturing from OpenCV
    video_capture = cv2.VideoCapture(0)
    count = 0
    while True and video_capture.isOpened():
    
        return_key, frame = video_capture.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = detector.detectMultiScale(gray, 1.3, 5)
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        color_mask = cv2.inRange(hsv, lowerBound, upperBound)
        ret1, thr = cv2.threshold(color_mask , 127, 255, 0)

        kernel = np.ones((11,11),np.uint8)
        result = cv2.morphologyEx(thr, cv2.MORPH_CLOSE, kernel)
        kernel2 = np.ones((5, 5), np.uint8)
        result2 = cv2.morphologyEx(result, cv2.MORPH_OPEN, kernel2)
        
        contours, _ = cv2.findContours(result2, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if len(contours) > 0:
            socketFlagBox = 1
            for i in range(len(contours)):
                area = cv2.contourArea(contours[i]) 
                if area > 10000:  
                    #socketFlagBox = 1
                    rect = cv2.minAreaRect(contours[i])
                    box = cv2.boxPoints(rect) 
                    box = np.int0(box) 
                    cv2.drawContours(frame, [box], 0, (0, 255, 0), 4)
                    if not (sentMsgBox):
                            socketSendBox()
                            sentMsgBox = 1
                            #isBoxHere = 1
                            boxOkCnt+= 1
                    else:
                        boxOkCnt+= 1

                    if(boxOkCnt % 1000 == 0):
                        isBoxHere = 1

                            
                    #if(preFlagBox!=socketFlagBox):
                    #    socketSendBox()
                else:
                    boxNoCnt+= 1
                    if(boxNoCnt % 1000 == 0):
                        isBoxHere = 0
                        sentMsgBox = 0
                    #socketFlagBox = 0

        #k = cv2.waitKey(1) & 0xFF
            
        for (x, y, w, h) in faces:
            socketFlagFace = 1
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
            if not (sentMsgface):
                socketSendFace()
                sentMsgface = 1
                faceOkCnt+=1
            else:
                faceOkCnt+=1

            if(faceOkCnt % 100 == 0):
                faceFlag = 1

        else:
            faceNoCnt+=1
            if(faceNoCnt % 100 == 0):
                faceFlag = 0
                sentMsgface = 0

        if not return_key:
            break
            
        with thread_lock:
            video_frame = frame.copy()
        
        key = cv2.waitKey(30) & 0xff
        if key == 27:
            break
        preFlagFace = socketFlagFace
        preFlagBox = socketFlagBox    
    video_capture.release()
 
    
    print('%d'% preFlagBox)
        
def encodeFrame():
    global thread_lock
    while True:
        # Acquire thread_lock to access the global video_frame object
        with thread_lock:
            global video_frame
            if video_frame is None:
                continue
            return_key, encoded_image = cv2.imencode(".jpg", video_frame)
            if not return_key:
                continue

        # Output image as a byte array
        yield(b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + 
            bytearray(encoded_image) + b'\r\n')

@app.route("/")
def streamFrames():
    return Response(encodeFrame(), mimetype = "multipart/x-mixed-replace; boundary=frame")


        

# check to see if this is the main thread of execution
if __name__ == '__main__':

    # Create a thread and attach the method that captures the image frames, to it
    process_thread = threading.Thread(target=captureFrames)
    process_thread.daemon = True

    # Start the thread
    process_thread.start()

    # start the Flask Web Application
    # While it can be run on any feasible IP, IP = 0.0.0.0 renders the web app on
    # the host machine's localhost and is discoverable by other machines on the same network 
    app.run("0.0.0.0", port="8001")
