# Table of Contents
* Abstract
* [Introduction](#1-introduction)
* [Related Work](#2-related-work)
* [Technical Approach](#3-technical-approach)
* [Evaluation and Results](#4-evaluation-and-results)
* [Discussion and Conclusions](#5-discussion-and-conclusions)
* [References](#6-references)

# Abstract

An automatic pet feeder is a good choice when people are away from home but need to take care of their pets. However, most auto-feeders on the market have a similar disadvantage, that they mechanically pour food on time with a fixed amount, without checking how much food remains in the bowl. This will cause a build-up of food if there is much food left since the last feeding. We want to design a new auto-feeder that can avoid such problems. 

In our approach, we use a highly accurate load module and a computer vision algorithm with picture capture to measure a more accurate remaining amount of food and water, so that we can dynamically adjust our next feeding based on the data. Our auto-feeder also connects to the internet and provides users with a mobile App to monitor the previous and current status of the feeder, and allows users to manually feed their pets if needed. To achieve our goals, we design and 3D-print the prototype of our auto-feeder, and use two Arduino Nano 33 BLE Sense to collect signals from the load module and drive motors to deliver food. Signals are then sent to the Raspberry Pi through Bluetooth for further processing. Because of time limits, for remaining water detection we only complete the basic algorithm to read images and detect water level using OpenCV on the Raspberry Pi. We implement a cloud server and a mobile App. The Raspberry Pi will send information about the feeder to the cloud server. A user can use the mobile App to view previous feeding activity by requesting data stored in the cloud server. A user can also set a new feeding frequency and feeding amount, or even feed cats manually by sending an HTTP POST request to the server. 

Our results showed that we essentially achieved all of the designing goals. The machine is able to deliver food automatically, dynamically adjust the feeding amount based on remaining food, and monitor the amount of remaining water if given an image of the water tank. Users are also able to monitor the log and manually feed their pets on the mobile App.


# 1. Introduction

## 1.1. Motivation & Objective
Nowadays, more and more families own pets. According to AVMA’s statistics, as of 2018 there were 38.4% of families owning dogs and 25.4% of families owning cats<sup>[1]</sup>. As a result, how to feed pets when no one is at home becomes a big problem. Our objective is to design an auto-feeder for dogs and cats to solve this problem.

## 1.2. State of the Art & Its Limitations

There are many products with auto-feeding functions on the market. After a literature survey, we found those products to have similar functions, that is users need to control the product manually, or set a time period to let the product feed pets automatically, using a mobile App<sup>[2]</sup>. They are all ignoring one issue: products are only mechanically pouring food on time, without checking how much food remains in the bowl. This will cause a build-up of food if the food continues to be poured into the bowl when there is much food left since the last feeding.

## 1.3. Novelty & Rationale

Some products mention that they have the function to detect the remaining food in the bowl. However, their method of detecting is simply by putting a sensor into the food delivery port to detect whether the food is piled up or not. However, it cannot know the exact amount remaining in the bowl. 
In our approach, we plan to use a highly accurate load module and a trained AI with picture capture to measure a more accurate remaining amount of food and water, so that we can dynamically adjust our next feeding based on this data.

## 1.4. Potential Impact

The main difference in our product compared with others is that we added a detective module so that the auto-feeder can detect how much food’s remaining before each feeding. And with this module we can also dynamically change the amount of each feeding. 
Hence, compared with other products, this method can avoid excessive feeding and keep food as fresh as possible.

## 1.5. Challenges

There are two main challenges we may encounter. 

First, how to detect the amount of remaining food and water in containers accurately? After research, we found one way is to use an IR distance sensor. However, the accuracy of this method may not be guaranteed when food containers are shallow, because the precision of IR distance sensors is usually greater than 2-10cm. We think of two feasible methods to solve the food and water detection issue, respectively. To detect the remaining amount of food, we can use a load module with accuracy as small as grams to read weight changes. To keep track of water volume, we take pictures of the water tank with a camera, and decide the water level using computer vision methods.

Second, how should we integrate each part well to make a complete product? We have arduino boards with sensors, cameras to collect information and control motors / steering gears, a Raspberry Pi to process signals, perform computer vision tasks and network communication. Besides those hardwares, we will also design a mobile app that can control the auto-feeder remotely, and notify users of its current status. Our challenge is to merge all those functional components into one complete product.

One risk we may face is that if we use a camera to take pictures in users' homes then we need to pay attention to data leakage and privacy issues. Also, we need to take care of unexpected cases, like food gets stuck at the food delivery port. We should design our containers well to avoid such issues.


## 1.6. Requirements for Success

To perform the project, we need programming skills related to Arduino, Raspberry Pi, and iOS development. We need to implement circuits that receive signals and control motors / steering gears. We also need to use CAD to design and 3D print the components we need for the auto-feeder. Basic knowledge of network IoT is also required.

Resources we need include: 
Cameras, Load Cell Module, 3D printer, Arduino Nano 33 BLE Sense Raspberry Pi Model 3 B, softwares (see 9.c) and corresponding online documents.

## 1.7. Metrics of Success

Our project achieves success if the following are satisfied:
1. The physical components of the auto-feeder well; i.e. the bowl can be filled with food successfully, as well as water can be pumped into the bottle successfully.
2. Our auto-feeder can detect the remaining amount of food and water with high accuracy. We need to perform experiments and ensure that the accuracy rate is at least 95%. The auto-feeder should also act accordingly, by controlling the food to be fed next time with respect to the amount of remaining food. Again, we will design experiments to test this function.
3. Our mobile App performs remote work perfectly. It should allow users to feed manually, and notify users of the current status of food and water containers correctly. The App package should not be too large, with no less than 100M.
  


# 2. Related Work

## a. Papers

The paper on Automatic Pet Feeder designed by Kank, Aasavari and Gaikwad gave us a brief overview of current auto-feeders on the market<sup>[2]</sup>. We found that most auto-feeders implemented a similar function, that is to allow users to control the feeder using a mobile App, and users can set a time period to feed their pets. Some products may add other functions like playing audio sound, or using a distance sensor to detect the location of a pet so that the auto-feeder can serve food when it comes close. However, the weakness in common is that those products cannot serve food and water smartly based on the remaining amount in a bowl and a bottle, thus inspiring us to design a auto-feeder that can overcome this issue.

## b. Software

EasyGUI<sup>[4]</sup> 
XCode^<sup>[5]</sup>
PyCharm<sup>[6]</sup>
Arduino<sup>[7]</sup>
SOLIDWORK<sup>[8]</sup>

# 3. Technical Approach

## 3.1. Overview
The flowchart below shows the three major technical parts. The first part is the hardware and signal processing part, which includes Raspberry Pi, Arduino Nano 33 BLE Sense and 3D printer. We will use a load module to detect the food amount in the bowl, and an ultrasonic module to detect food in the big tank. The signals are collected by Arduino, and then sent to Raspberry Pi through Bluetooth. The Raspberry Pi will process signals to detect the remaining amount in the food container.

The second and third technical parts are a cloud server and a mobile App. The Raspberry Pi will send information about the feeder, for example, the remaining amount of food and water, to the cloud server. A user can use the mobile app to see the previous record of feeding activity, by requesting data stored in the cloud server. A user can also feed cats manually, then the mobile app will send an HTTP post to read and write to the cloud server. When the cloud server receives instructions to feed cats, it will send information to the Raspberry Pi and ask it to add more food.
![image](https://raw.githubusercontent.com/7hgTnec/ecem202a_project/main/docs/media/pic/Overiview.jpg)

## 3.2. 3D Print

We designed and 3D-printed the prototype of our auto-feeder. The left picture is the overview of the machine, which consists of a food tank, a water tank and two bowls below. The right picture is the structure inside the food tank. We can control three step motors to rotate the three vertical gears, so that they can drive the main gear on the top to release cat food.

<p align="center">
<img src="https://raw.githubusercontent.com/7hgTnec/ecem202a_project/main/docs/media/pic/3Dmodel_0.jpg" width="280"/><img src="https://raw.githubusercontent.com/7hgTnec/ecem202a_project/main/docs/media/pic/3Dmodel_1.jpg" width="260"/>
</p>

## 3.3. Arduino Nano 33 BLE
We let the Nano build a connection with Raspberry Pi by Bluetooth LE by “ArduinoBLE.h” library. After the connection is built, Nano collects the local data, such as food weight, and sends the data to the Raspberry Pi by bluetooth. To avoid block delay, we record the time since the last activity to make sure the time difference between two activities is 2 seconds. Every few seconds Nano checks if there is any command data received from Raspberry Pi. If Nano gets a command value which is bigger than 0, then it will control the step motors to rotate corresponding quarters to release cat food. 

However, using only one Nano has some issues. Since the step motor is driven by a continuous signal during the food conveying period, the program will be blocked until the food conveying process is done. Another issue is that Nano is powered by a USB port, but the power of a USB port is not enough to drive 3 step motors together. To solve these problems, we added an additional Nano as a driver with an individual power supply. When the master Nano needs to convey food, it only sends a message to the driver Nano, and the driver Nano will continue to release food. We can avoid the block issue during the food conveying process in this way. Also, due to the exclusive power supply, motors will have enough power to do the conveying.

There is another thing we need to point out. There are actually two hardware implementations of Serial on Nano 33 BLE. One is Serial which is used to communicate with a PC via USB port. Another one is Serial1 which is used to communicate with another device via TX/RX.

## 3.4. Raspberry Pi
On Raspberry Pi, we use the bluepy library to build bluetooth with Nano. And use the requests library to handle HTTP requests such as GET/POST. We use the same technique as we did in Nano. Using intervals to do period tasks without blocking. It uses long polling to update the command from the server per second by GET method. Alse, it uses the POST method to send Nano’s data to the server so that the server can make decisions based on those data.

## 3.5. Server
On the server side, we use the Flask framework to build a HTTP server which listens at 5000 port. It provides serial GET and POST methods to allow Raspberry Pi or user’s application to get data from the server and set data to the server. The following are the features of each HTTP requests handler function.

- feed [‘POST’]:
  
  User’s application can use the API to manually send a feed command to the auto-feeder to add more food. In our design, while the user sends the feed command, it also needs to send a password in the json format to do the identification.
  
  Then the server will check the remaining food amount in the bowl. If the remaining amount is too close to the target amount, the server will inhibit this manually feed operation. And return an error message to the server to notify users how much food is in the bowl. Otherwise, this function will set the cmd value to the corresponding quarter that the motor needs to rotate to convey food. 

- getFre [‘GET’]:
  
  This API is provided to Raspberry Pi to get the user setted auto-feed frequency. The type of Fre is an integer corresponding to the hour interval between each feeding.

- setFre [‘POST’]:
  
  This API is provided to the user's application to enable the user to set the auto-feed frequency.

- getAmount [‘GET’]:
  
  This API is provided to the Raspberry Pi to enable it to get the user setted auto-feed amount. The type of amount is an integer corresponding to how much gram of food needs to be fed.

- setAmount [‘POST’]:
  
  This API is provided to the user’s application to enable the user to set the auto-feed amount in one feeding.

- log [‘GET’]:
  
  This API is provided to the user’s application to enable it to grab the last 10 recent activities.

- getcmd [‘GET’]:
  
  This API is provided to the Raspberry Pi to enable it to get the cmd from the server. The cmd is an integer, and it means how many quarter laps the machine needs to rotate. According to our design, the machine will deliver food 4 times in one lap, and the minimum countable unit is a quarter lap. In our test, the machine delivers around 5g of food in one quarter lap. Therefore, the value of cmd is calculated by the amount of food to deliver divided by 5g. For example, if we want to feed 20g of food, then the cmd value should be 4. 

- reset() [‘GET’]:
  
  This API is provided to Raspberry Pi to let it tell the server the last cmd has been received and processed. 

- data [‘POST’]:
  
  This API is provided to Raspberry Pi to enable it to send local data to the server in Json format by POST.

## 3.6. iOS App

The client end for our auto-feeder is a mobile App. We developed an iOS App using Swift and SwiftUI. The app has three major functions.
1. Users can change the auto-feeding settings in "Settings". They can change the feeding frequency of the auto-feeder, and the desired amount of food to add for each feed. 
2. Users can view the previous activities of the feeder in "Activity History". The information includes previous feeding activities, frequency/feeding amount changed by users, and the remaining amount in the food container.
3. Users can click on the "Feed" button on the App to feed manually if needed. If the container is not full, users can see a message that indicates a successful feeding. Otherwise, if the container is full or will overflow after one more feeding, then users will be notified of this and receive a message of failure on the last feeding. 

For function 1 (or 3), the app sends an HTTP post request to the server, and the server will change the auto-feeding frequency and the maximum amount of each feeding (or control the feeder to add food to containers). To realize the function 2, the App will send an HTTP get request to read the log stored on the server. Then the App can show users previous activities of the feeder.

## 3.6. OpenCV

Our auto-feeder should have the feature to detect the water remaining in the container. However, we didn’t manage our time well to complete the 3D printing of the water tank, and our camera also had some issues, so we just realized the basic function of water level detection using openCV. If we are given an image of some bottle, our algorithm can detect the percentage of water left in it. The logic of our algorithm is:
1. Perform image binarization and smoothing;
2. Detect all contours;
3. Find the largest contour and bound it by box;
4. Calculate the remaining amount of water by reading the height of the box.

This algorithm works for ideal images, i.e., it may require a clean background and good lighting conditions to function well.


# 4. Evaluation and Results
There are four main goals we need to achieve: 
1. Our machine should be able to deliver food automatically;
2. Users should be able to monitor the log and manually feed their pets; 
3. Our machine should be able to automatically adjust the feeding amount based on the remaining food; 
4. Our machine should be able to monitor the amount of remaining water.

We performed tests to evaluate our auto-feeder. We first tested the functioning of auto-feeding with fixed frequency. We set the feeding period to 5, 10 and 20 minutes and the feeding amount each time to 20. Our machine managed to add food to the bowl according to the frequency of every 5, 10 and 20 minutes, respectively. 

Second, we tested the ability of our machine to adjust feeding food amounts dynamically. In a series of three tests, we set the amount of food to be conveyed to be 22g, 19g, 19g, when the remaining amount of food in the bowl was 0g, 4g, 8g. We added one more test to feed manually, and the default amount of manual feeding was 20g. We set 15g to be the maximum amount of food remaining in the bowl, i.e., the bowl was full at 15g. In each of the tests, if our machine detected that the remaining food in the bowl was less than 15g, the server accepted the feeding operation. Otherwise, when the amount of food was greater than 15g, the server refused the feeding operation and returned an error message. 

Third, we test the CV algorithm to detect remaining water. When the water bottle was in a light environment with a clean background, our program can recognize the water surface and calculate the percentage of remaining water accurately. 

# 5. Discussion and Conclusions
Our machine achieves essentially all of the designing goals, but there are still some issues that need to be solved. First, our power supply will overheat if the motors work for a long time continuously. If overheat happens, the power supply cannot support enough power to drive the motors until it cools down. The second issue is that our components are too complex and the cost is expensive. In future we plan to use PCBs to substitute wire connections. We can also replace Nano and Raspberry Pi by an ESP8266-Arduino, since the main purpose of Raspberry Pi is to build connections between Nano and Server by the internet. Finally, our water detection part is not complete. We should finish the 3D-printing of the water tank and add a camera to take pictures of the tank. We can also improve the openCV program, as now it only works without ideal images without too much noise. We need a better model to do this recognition, and AI+CV may be a good solution.

In summary, even though some functionalities currently require special conditions to work, we have reasonable solutions to solve those problems in the future. By our serial tests, we have proved our machine can dynamically adjust the feeding amount to ensure that the total amount of food in the bowl is always close to or less than the target amount to avoid food piling up. The results indicate that our design logic can solve the over-feeding problem we mentioned at the beginning.


# 6. References
[1] "U.S. pet ownership statistics", American Veterinary Medical Association, 2021. [Online]. Available: https://www.avma.org/resources-tools/reports-statistics/us-pet-ownership-statistics. [Accessed: 05- Nov- 2021].

[2] "Kank, Aasavari and Gaikwad (Mohite), Vaishali, Automatic Pet Feeder (October 20, 2018). Available at SSRN: https://ssrn.com/abstract=3274472 or http://dx.doi.org/10.2139/ssrn.3274472. [Accessed: 05- Nov- 2021].

[3] "The CIFAR-10 dataset. “Learning Multiple Layers of Features from Tiny Images, Alex Krizhevsky, 2009.” https://www.cs.toronto.edu/~kriz/cifar.html. [Accessed: 05- Nov- 2021].

[4] "EasyGUI — easygui 0.97 (2014-12-20) documentation", Easygui.sourceforge.net, 2021. [Online]. Available: http://easygui.sourceforge.net/. [Accessed: 05- Nov- 2021].

[5] "Xcode - Apple Developer", Apple Developer, 2021. [Online]. Available: https://developer.apple.com/xcode/. [Accessed: 05- Nov- 2021].

[6] "PyCharm: the Python IDE for Professional Developers by JetBrains", JetBrains, 2021. [Online]. Available: https://www.jetbrains.com/pycharm/. [Accessed: 05- Nov- 2021].

[7] "Arduino IDE 1.8.16", 2021. [Online]. Available: https://www.arduino.cc/en/software. [Accessed: 05- Nov- 2021].

[8] "SOLIDWORKS", 2021. [Online]. Available: https://www.solidworks.com/. [Accessed: 05- Nov- 2021].





