# Single Color Code Tracking Example
import sensor, image, time, pyb, struct

from pyb import UART

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green things. You may wish to tune them...
thresholds = [(45, 65, 40, 80, 0, 65)]

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
uart = UART(3,9600)
uart.init(9600, bits=8, parity=None, stop=1) # init with given parameters
clock = time.clock()

#比较两色块大小
def compareBlob(blob1,blob2):
    temp = blob1.pixels() - blob2.pixels()
    if temp == 0:
        return 0
    elif temp > 0:
        return 1
    else:
        return -1

def send_data_packet(x, y):
    temp = struct.pack("bbBB",                #格式为俩个字符俩个整型
                   0xAA,                       #帧头1
                   0xAE,                       #帧头2
                   x, # up sample by 4    #数据1
                   y) # up sample by 4    #数据2
    uart.write(temp)                           #串口发送


while(True):

    clock.tick()
    bigBlob =None

    img = sensor.snapshot()

    #blobs = img.find_blobs(thresholds, pixels_threshold=1, area_threshold=1, merge=True)
    blobs = img.find_blobs(thresholds,pixels_threshold=50)
    if len(blobs)==0:
            #send_data_packet(254,254)
            continue
    bigBlob = blobs[0]
    for sblob in blobs:
        if compareBlob(bigBlob,sblob)== -1:
            bigBlob = sblob


    img.draw_rectangle(bigBlob.rect())
    img.draw_cross(bigBlob.cx(), bigBlob.cy())
    img.draw_string(20, 10, "%2d"%bigBlob.cx(),[255,0,0],scale = 2)
    img.draw_string(75, 10, "%2d"%bigBlob.cy(),[255,0,0],scale = 2)
    send_data_packet(bigBlob.cx(),bigBlob.cy())


    #print(clock.fps())
