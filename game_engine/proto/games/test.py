import proto

import time
import math

x = 320
y = 240
d = 200.0
hit = 0

def _init():
    global start, audio, music, offset, circNum, rect
    start = time.time()
    audio = proto.audio.load('audio/244655__greenvwbeetle__pop-1.wav')
    music = proto.music.load('audio/Intergalactic.wav')
    proto.music.play(music)
    print(proto.audio.VOLUME_LOUD) # print out enum value
    circNum = proto.draw.createCircle(320,240,20,0.1,0.5,0.5)
    rect = proto.draw.createRect(100, 100, 50, 50, 1.0, 1.0, 1.0)
    t = (42, -2)
    print(t, proto.tupleswap(t))

def _update():
    global x,y,d,start,audio, hit
    delta_time = proto.deltatime()
    x += d * delta_time
    if x <= 20:
        d = abs(d)
        proto.audio.play(audio)
        hit = 20
    if x >= 620:
        d = -abs(d)
        proto.audio.play(audio)
        hit = 20
    y = math.sin(time.time() - start) * 200 + 240
    hit -= 100.0 * delta_time

    # proto_keyPressed = proto.keyPressed()
    # print(proto_keyPressed)

    # uncomment next line to simulate a slower machine
    # time.sleep(0.1)

def test_collide_rects(should_collide):
    x1 = 5
    y1 = 5
    w1 = 50
    h1 = 50

    y2 = 30
    w2 = 50
    h2 = 50
    if should_collide:
        x2 = 30
    else:
        x2 = 300

    if (proto.collide_rects(x1, y1, w1, h1, x2, y2, w2, h2)):
        proto.draw.rect(x1, y1, w1, h1, 1, 0, 0)
        proto.draw.rect(x2, y2, w2, h2, 1, 0, 0)
    else:
        proto.draw.rect(x1, y1, w1, h1, 0, 0, 1)
        proto.draw.rect(x2, y2, w2, h2, 0, 1, 0)
    return

def test_collide_circles(should_collide):
    x1 = 50
    y1 = 50
    r1 = 30

    y2 = 60
    r2 = 50
    if should_collide:
        x2 = 60
    else:
        x2 = 200

    if (proto.collide_circles(x1, y1, r1, x2, y2, r2)):
        proto.draw.circle(x1, y1, r1, 1, 0, 0)
        proto.draw.circle(x2, y2, r1, 1, 0, 0)
    else:
        proto.draw.circle(x1, y1, r1, 0, 0, 1)
        proto.draw.circle(x2, y2, r1, 0, 1, 0)
    return

def _draw():
    global x,y,hit,circNum, rect

    r,g,b = (0.5, 0.5, 0.5) if hit <= 0 else (0.9, 0.6, 0.1)
    proto.draw.moveCircle(circNum,x,y)
    #proto.draw.circle(x, y, 20, r, g, b)
    proto.draw.drawPermaCircle(circNum)
    #modify with create and permacircle
    r,g,b = (0.5, 0.5, 0.5) if hit <= 0 else (0.9, 0.6, 0.1)
    proto.draw.circle(x, y, 20, r, g, b)
    proto.draw.drawPermaRect(rect)
