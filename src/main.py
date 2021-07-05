import cv2


cap = cv2.VideoCapture("rtmp://172.16.0.100:1935/live")

if (cap.isOpened()== False):
    print("Error opening video stream or file")
 


if __name__== "__main__":
    
    while(cap.isOpened()):

        ret, img = cap.read()

        cv2.imshow("img",img)

        if cv2.waitKey(1) == ord('q'):
            break


cap.release()

cv2.destroyAllWindows()