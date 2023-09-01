import proto

class Key():
	def __init__(this,x,y,w,h,cr,cb,cg,button=None,beat=None):
		this.x = x
		this.y = y
		this.h = h
		this.w = w
		this.cr = cr
		this.cg = cg
		this.cb = cb
		this.button = button
		this.beat = beat

def _init():
	global score,combo,bps,keys,notes,windowW,windowH,state,maxCombo
	score = 0
	combo = 0
	maxCombo = 0
	state = "menu"
	windowW = proto.draw.getWindowWidth()
	windowH = proto.draw.getWindowHeight()
	keys = [
		Key(50,400,50,20,  255,0,0,      proto.K_A),
		Key(125,400,50,20, 0,255,0,     proto.K_S),
		Key(200,400,50,20, 0,0,255,     proto.K_D),
		Key(275,400,50,20, 255,0,255,    proto.K_F),
		Key(50,430,1,1,0,0,0,     proto.K_Up),
		Key(125,430,1,1,0,0,0,     proto.K_Down),
		Key(200,430,1,1,0,0,0,      proto.K_Left),
		Key(275,430,1,1,0,0,0,     proto.K_Right)
	]
	notes = []

def updateGame():
	global combo,score,state,endBeat,maxCombo
	currentSec = proto.music.getOffset(music)
	currentBeat = bps*currentSec
	if int(currentBeat) == endBeat:
		proto.music.stop(music)
		state = "menu"
	for note in notes:
		note.y = 400-(note.beat-currentBeat) * 100 #last number in equation is speed of note
		for key in keys[:4]:
			if proto.keyPressed(key.button) and proto.collide_rects(key.x, key.y, key.w, key.h, note.x, note.y, note.w, note.h):
				combo += 1
				score += 5*combo
				notes.remove(note)
			if proto.collide_rects(keys[4].x,keys[4].y,keys[4].w,keys[4].h, note.x, note.y, note.w, note.h) or proto.collide_rects(keys[5].x,keys[5].y,keys[5].w,keys[5].h, note.x, note.y, note.w, note.h) or proto.collide_rects(keys[6].x,keys[6].y,keys[6].w,keys[6].h, note.x, note.y, note.w, note.h) or proto.collide_rects(keys[7].x,keys[7].y,keys[7].w,keys[7].h, note.x, note.y, note.w, note.h):
				if combo > maxCombo:
					maxCombo = combo
				combo = 0

def updateMenu():
	global state,music,data,bps,endBeat,score,combo,maxCombo
	if state == "menu" and proto.keyPressed(proto.K_Up):
		music = proto.music.load('audio/Intergalactic.wav')
		bps = 106/60 #beats per second
		startBuffer = 9 
		numRows = 0 
		data = open("audio/Intergalactic.txt", 'r').readlines()
		for y in range(len(data)):
			numRows += 1
			for x in range(len(data[y])):
				if data[y][x] == '0':
					lane = keys[x].x
					match lane:
						case 50:
							note = Key(keys[x].x,0,50,20,255,0,0,proto.K_A,startBuffer+1*y)
						case 125:
							note = Key(keys[x].x,0,50,20,0,255,0,proto.K_S,startBuffer+1*y)
						case 200:
							note = Key(keys[x].x,0,50,20,0,0,255,proto.K_D,startBuffer+1*y)
						case 275:
							note = Key(keys[x].x,0,50,20,255,0,255,proto.K_F,startBuffer+1*y)
					notes.append(note)
		endBeat = numRows+startBuffer+3
		score = 0
		combo = 0
		maxCombo = 0
		proto.music.play(music)
		state = "game"
	if state == "menu" and proto.keyPressed(proto.K_Down):
		music = proto.music.load('audio/MyNameIsJonas.wav')
		bps = 186/60 #beats per second
		startBuffer = 26 
		numRows = 0 
		data = open("audio/MyNameIsJonas.txt", 'r').readlines()
		for y in range(len(data)):
			numRows += 1
			for x in range(len(data[y])):
				if data[y][x] == '0':
					lane = keys[x].x
					match lane:
						case 50:
							note = Key(keys[x].x,0,50,20,255,0,0,proto.K_A,startBuffer+1*y)
						case 125:
							note = Key(keys[x].x,0,50,20,0,255,0,proto.K_S,startBuffer+1*y)
						case 200:
							note = Key(keys[x].x,0,50,20,0,0,255,proto.K_D,startBuffer+1*y)
						case 275:
							note = Key(keys[x].x,0,50,20,255,0,255,proto.K_F,startBuffer+1*y)
					notes.append(note)
		endBeat = numRows+startBuffer+3
		score = 0
		combo = 0
		maxCombo = 0
		proto.music.play(music)
		state = "game"

def _update():
	global state
	if state == "game":
		updateGame()
	if state == "menu":
		updateMenu()

def _draw():
	global keys, ticker
	if state == "menu":
		if score != 0 and maxCombo != 0:
			proto.draw.text("Score: " + str(score), 80, 250, 20, 1, 1, 1)
			proto.draw.text("Max Combo: x" + str(maxCombo), 80, 200, 20, 1, 1, 1)
		proto.draw.text("Welcome to My Game! Press ASDF keys to the beat!", 80, 350, 20, 1, 0, 0)
		proto.draw.text("Press the up arrow to play Intergalatic!", 80, 375, 20, 1, 1, 1)
		proto.draw.text("Press the down arrow to play My Name is Jonas!", 80, 400, 20, 1, 1, 1)

	if state == "game":
		proto.draw.text("Score: " + str(score), 450, 350, 20, 1, 1, 1)
		proto.draw.text("Combo: x" + str(combo), 450, 375, 20, 1, 1, 1)
		proto.draw.text("A", 67,430, 20, 1, 1, 1)
		proto.draw.text("S", 142,430, 20, 1, 1, 1)
		proto.draw.text("D", 217,430, 20, 1, 1, 1)
		proto.draw.text("F", 292,430, 20, 1, 1, 1)
		for key in keys:
			if proto.keyPressed(key.button):
				proto.draw.rect(key.x, key.y, key.w, key.h, 0,0,0)
			else:
				proto.draw.rect(key.x, key.y, key.w, key.h, key.cr, key.cg, key.cb)

		for note in notes:
			proto.draw.rect(note.x, note.y, note.w, note.h, note.cr, note.cg, note.cb)