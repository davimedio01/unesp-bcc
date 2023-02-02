from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
import cv2
import numpy as np

def main():
    key = get_random_bytes(16)
    iv = get_random_bytes(8)
    des = DES3.new(key, DES3.MODE_CBC, iv)
    
    image = cv2.imread("/home/gustavostahl/Pictures/simple_draw.jpg", 0)
    image = cv2.resize(image, (0,0), fx=.5, fy=.5)
    image_shape = image.shape
    image_flatten = image.flatten()
    image_uchar = bytes(image_flatten)

    encoded_image_uchar = des.encrypt(image_uchar)
    decoded_image_uchar = des.decrypt(encoded_image_uchar)

    encoded_image = np.frombuffer(encoded_image_uchar, dtype=np.uint8).reshape(image_shape)
    decoded_image = np.frombuffer(decoded_image_uchar, dtype=np.uint8).reshape(image_shape)

    image_concat = np.hstack((encoded_image, decoded_image))
    cv2.namedWindow("Image result", 0)
    cv2.imshow("Image result", image_concat)
    cv2.imwrite("cbc.jpg", image_concat)
    while True:
        k = cv2.waitKey(10)
        if k in [ord('q'), 27]:
            break
    cv2.destroyAllWindows()    

if __name__ == '__main__':
    main()