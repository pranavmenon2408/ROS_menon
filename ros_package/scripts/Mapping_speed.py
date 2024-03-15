import math

def joystickToDiff(x, y, minJoystick, maxJoystick, minSpeed, maxSpeed):
	
    
    z = math.sqrt(x * x + y * y)
    rad = math.acos(math.fabs(x) / z)
    angle = rad * 180 / math.pi

    tcoeff = -1 + (angle / 90) * 2
    # turn = tcoeff * math.fabs(math.fabs(y) - math.fabs(x))
    # turn = round(turn * 100, 0) / 100

    mov = max(math.fabs(y), math.fabs(x))
    turn = tcoeff * mov

    if (x >= 0 and y >= 0) or (x < 0 and y < 0):
        rawRight = mov
        rawLeft = turn
    else:
        rawLeft = mov
        rawRight = turn

    # Reverse polarity
    if y < 0:
        rawLeft = 0 - rawLeft
        rawRight = 0 - rawRight
    pwmb1 = -map(rawLeft, minJoystick, maxJoystick, minSpeed, maxSpeed)
    pwmb2 = -map(rawRight, minJoystick, maxJoystick, minSpeed, maxSpeed)
    return pwmb2,pwmb1

	#flex_range=0.3
        
    

    '''y=round(y,1)
	x=round(x,1)
	if x == 0 and y == 0:
		return 0, 0
    

	
	z = math.sqrt(x * x + y * y)

	
	rad = math.acos(math.fabs(x) / z)

	
	angle = rad * 180 / math.pi

	
	tcoeff = -1 + (angle / 90) * 2
	turn = tcoeff * math.fabs(math.fabs(y) - math.fabs(x))
	turn = round(turn * 100, 0) / 100

	# And max of y or x is the movement
	mov = max(math.fabs(y), math.fabs(x))

	# First and third quadrant
	if (x>=0 and y <=0.3) or (x <0 and y >0.3):
		rawLeft = mov
		rawRight = turn
	else:
		rawRight = mov
		rawLeft = turn

	# Reverse polarity
	temp=0
	if y > 0.3:
		temp=rawLeft
		rawLeft=rawRight
		rawRight=temp

	# minJoystick, maxJoystick, minSpeed, maxSpeed
	# Map the values onto the defined rang
	rightOut = map(rawRight, minJoystick, maxJoystick, minSpeed, maxSpeed)
	leftOut = map(rawLeft, minJoystick, maxJoystick, minSpeed, maxSpeed)'''
	
    
def map(v, in_min, in_max, out_min, out_max):
	# Check that the value is at least in_min
	if v < in_min:
		v = in_min
	# Check that the value is at most in_max
	if v > in_max:
		v = in_max
	return (v - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

def mechanum(x,y,rx,minSpeed,maxSpeed):
    y=-y
    x=round(x,1)
    y=round(y,1)
    rx=round(rx,1)
      
    denom=max(math.fabs(x)+math.fabs(y)+math.fabs(rx),1)
    frontleft=int(map(((y+x+rx)/denom),-1,1,minSpeed,maxSpeed))
    backright=int(map(((y+x-rx)/denom),-1,1,minSpeed,maxSpeed))
    backleft=int(map(((y-x+rx)/denom),-1,1,minSpeed,maxSpeed))
    frontright=int(map(((y-x-rx)/denom),-1,1,minSpeed,maxSpeed))
      
    return frontleft,frontright,backleft,backright

def omni(x,y,minSpeed,maxSpeed):
    r=math.sqrt(math.pow(x,2)+math.pow(y,2))
    theta=math.atan2(y,x)*180.0/math.pi
    if theta>90:
         theta=450-theta
    else:
         theta=90-theta
    theta=(theta*math.pi)/180.0
    wheel_angles=[(90*math.pi)/180.0,(225*math.pi)/180.0,(315*math.pi)/180.0]
    wheel_velocity=[]
    for i in wheel_angles:
         wv=r*math.sin(theta)*math.sin(i)+r*math.cos(theta)*math.cos(i)
         wv=int(map(wv,-1,1,minSpeed,maxSpeed))
         wheel_velocity.append(wv)
    return wheel_velocity
     
def nazi(x,y,minSpeed,maxSpeed):
    r=math.sqrt(math.pow(x,2)+math.pow(y,2))
    theta=math.atan2(y,x)*180.0/math.pi
    if theta>90:
         theta=450-theta
    else:
         theta=90-theta
    theta=(theta*math.pi)/180.0
    wheel_angles=[0,(90*math.pi)/180.0,(180*math.pi)/180.0,(270*math.pi)/180.0]
    wheel_velocity=[]
    for i in wheel_angles:
         wv=r*math.sin(theta)*math.sin(i)+r*math.cos(theta)*math.cos(i)
         wv=int(map(wv,-1,1,minSpeed,maxSpeed))
         wheel_velocity.append(wv)
    return wheel_velocity
    
      
	  
      
	
      
