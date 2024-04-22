import cv2
import numpy as np
import time

# Function to apply various effects on the video frame
def apply_effect(frame, effect):
    if effect == 'v':
        frame = cv2.flip(frame, 0)
    elif effect == 'h':
        frame = cv2.flip(frame, 1)
    elif effect == 'r':
        frame = cv2.rotate(frame, cv2.ROTATE_90_CLOCKWISE)
    elif effect == 'g':
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    elif effect == 'b':
        frame = cv2.blur(frame, (15, 15))
    elif effect == 'm':
        frame = cv2.medianBlur(frame, 15)
    return frame

# Main function
def main():
    cap = cv2.VideoCapture(0)
    active_effect = None
    font = cv2.FONT_HERSHEY_SIMPLEX

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        if active_effect:
            frame = apply_effect(frame, active_effect)

        current_time = time.strftime('%H:%M:%S', time.localtime())

        #display the current effect and time on the video
        cv2.putText(frame, f'Effect: {active_effect}', (10, 30), font, 1, (255, 255, 255), 2, cv2.LINE_AA)
        cv2.putText(frame, f'Time: {current_time}', (10, 70), font, 1, (255, 255, 255), 2, cv2.LINE_AA)

        cv2.imshow('Video', frame)

        key = cv2.waitKey(1)
        if key == ord('q'):
            break
        elif key in [ord('v'), ord('h'), ord('r'), ord('g'), ord('b'), ord('m')]:
            active_effect = chr(key)

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
