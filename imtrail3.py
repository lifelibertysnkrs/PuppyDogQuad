from imgproc import *
import serial
try:
        ser = serial.Serial('/dev/tty.usbserial', 9600)
        print("Serial Connection Active")
except:
        print("No Serial Devices Found")

# Create a camera 
cam = Camera(160, 120) 

# use the camera's width and height to set the viewer size 
view = Viewer(cam.width, cam.height, "Blob finding")

oldmean_x = 160
oldmean_y = 120
horizstatus = 0
verticalstatus = 0
while True:
        
	# x and y position accumulators 
	acc_x = 0 
	acc_y = 0 

	# number of pixels accumulated 
	acc_count = 0 
 
	# grab an image from the camera 
	image = cam.grabImage()


	# iterate over every pixel 
	for x in range(0, image.width, 15): 
		for y in range(0, image.height, 15): 
			# get the value of the current pixel 
			red, green, blue = image[x, y] 

			# check if the red intensity is greater than green and blue 
			if green > red+15 and green > blue+15: 
				# accumulate x and y of found pixel
				acc_x += x 
				acc_y += y 
				# increment the accumulated pixels' count 
				acc_count += 1 
				# colour pixels which pass the test black 
				image[x, y] = 0, 0, 0 

	# check the accumulator is greater than 0, to avoid a divide by 0
	if acc_count > 0: 
		# calculate the mean x and y positions
		if abs(oldmean_x-acc_x / acc_count) < 40 and abs(oldmean_y-acc_y / acc_count) < 40:
			mean_x = acc_x / acc_count 
			mean_y = acc_y / acc_count
			oldmean_x = mean_x
			oldmean_y = mean_y
			

		else:
			mean_x = image.width/2 
			mean_y = image.height/2
		
		print ("Position is ", mean_x,", ", mean_y)

		statusx = (mean_x-image.width/2)/10
		statusy = (mean_y-image.height/2)/10
		statusxy = statusy*10+statusx

		

		 
		# draw a small cross in red at the mean position 
		image[mean_x + 0, mean_y - 1] = 255, 0, 0 
		image[mean_x - 1, mean_y + 0] = 255, 0, 0 
		image[mean_x + 0, mean_y + 0] = 255, 0, 0 
		image[mean_x + 1, mean_y + 0] = 255, 0, 0 
		image[mean_x + 0, mean_y + 1] = 255, 0, 0 

	# display the image on the viewer 
	view.displayImage(image)
	try:
		ser.write(str(statusxy))
	except:
		pass
