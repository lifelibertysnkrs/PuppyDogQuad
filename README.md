PuppyDogQuad
============

An opensource system for image tracking quadcopters!

PuppyDogQuad uses blob tracking to track colors and follow them. 

Usage
-----------------------

Here's what you'll need to get started:
```
1 Quadcopter Frame (I used a Flamewheel 450)
4x Motor's/ESC's (I used stock DJI Motors and opto 30 ESC's)
1x Rasberry Pi (I used Model B+)
1x Arduino Uno 
1x Webcam (the higher res, the better)
```
First install the "motion" packages that allow the Raspberry pi to work with the Webcam.

Next, instal the imgproc library on the Raspberry pi from: http://rahul.cc/docs/imgproc.zip

```
wget http://rahul.cc/docs/imgproc.zip
unzip imgproc.zip
cd library 
sudo make install
cd ..

```

Next, we need to set up the image tracking program itself. Download tracking.py and then do the following in terminal

```
crontab -e

```

add the following line to the file:

```
@reboot sudo python /[PATH]/tracking.py

```

where [PATH] is the path to tracking.py.

Next we'll need to set up the Arduino. Wire in your reciever and flight controller following the pin layout in Interjekt.ino.

Then compile and upload to the Arduino.

Finally, connect the Raspberry Pi and via USB to allow for Serial communicatino between the two.

You're ready to go!
