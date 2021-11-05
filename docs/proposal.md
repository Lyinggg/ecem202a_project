# Project Proposal

## 1. Motivation & Objective

Nowadays, more and more families own pets. According to AVMA’s statistics, as of 2018 there were 38.4% of families owning dogs and 25.4% of families owning cats<sup>[1]</sup>. As a result, how to feed pets when no one is at home becomes a big problem. Our objective is to design an auto-feeder for dogs and cats to solve this problem.

## 2. State of the Art & Its Limitations

There are many products with auto-feeding functions on the market. After a literature survey, we found those products to have similar functions, that is users need to control the product manually, or set a time period to let the product feed pets automatically, using a mobile App<sup>[2]</sup>. They are all ignoring one issue: products are only mechanically pouring food on time, without checking how much food remains in the bowl. This will cause a build-up of food if the food continues to be poured into the bowl when there is much food left since the last feeding.

## 3. Novelty & Rationale

Some products mention that they have the function to detect the remaining food in the bowl. However, their method to detect is simply putting a sensor into the food delivery port to detect whether the food is piled up or not. However, it cannot know the exact amount remaining in the bowl. 
In our approach, we plan to use a highly accurate load module and a trained AI with picture capture to measure a more accurate remaining amount of food and water, so that we can dynamically adjust our next feeding based on this data.

## 4. Potential Impact

The main difference in our product compared with others is that we added a detective module so that the auto-feeder can detect how much food’s remaining before each feeding. And with this module we can also dynamically change the amount of each feeding. 
Hence, compared with other products, this method can avoid excessive feeding and keep food as fresh as possible.

## 5. Challenges

There are two main challenges we may encounter. 

First, how to detect the amount of remaining food and water in containers accurately? After research, we found one solution is to use an IR distance sensor. However, the accuracy of this method may not be guaranteed when food containers are shallow, because the precision of IR distance sensors is usually greater than 2-10cm. We think of two feasible methods to solve the food and water detection issue, respectively. To detect the remaining amount of food, we can use a load module with accuracy as small as grams to read weight changes. To keep track of water volume, we capture pictures of the water marks with a camera, and decide whether the container is empty using machine learning methods.

Second, how should we integrate each part well to make a complete product? We have arduino boards with sensors, cameras to collect information and control motors / steering gears, a Raspberry Pi to process signals, perform machine learning tasks and network communication. Besides those hardwares, we will also design a mobile app that can control the auto-feeder remotely if necessary, and notify users of its current status. Our challenge is to merge all those functional components into one complete product.

One risk we may face is that if we add a live stream function in the mobile app to allow users to see their pets through the camera, we need to pay attention to the data leakage and privacy issue. Also, we need to take care of unexpected cases, like food gets stuck at the food delivery port. We should design our containers well to avoid such issues.


## 6. Requirements for Success

To perform the project, we need programming skills related to Arduino, Raspberry Pi, and iOS development. We need to implement circuits that receive signals and control motors / steering gears. We also need to use CAD to design and 3D print the components we need for the auto-feeder. Basic knowledge on network, IoT are also required.

Resources we need include: 
Cameras, Load Cell Module, 3D printer, Arduino Nano 33 BLE Sence, Raspberry Pi Model 3 B, softwares (see 9.c) and corresponding online documents.

## 7. Metrics of Success

Our project achieves success if the following are satisfied:
1. The physical components of the auto-feeder works well, i.e., the bowl can be filled with food successfully, as well as water can be pumped into the bottle successfully.
2. Our auto-feeder can detect the remaining amount of food and water with high accuracy. We need to perform experiments and ensure that the accuracy rate is at least 95%. The auto-feeder should also act accordingly, by controlling the food to be fed next time with respect to the amount of remaining food. Again, we will design experiments to test this function.
3. Our mobile App performs remote work perfectly, and notify users of the current status of food and water containers correctly. The App package should not be too large, with no less than 100M.
  

## 8. Execution Plan

### (1) 3D Modeling and Printing (Weitao Sun).
Based on our project goals, we need to design a 3D model for various components of the auto-feeder. Main parts are the feeding device and platform to install all sensors and boards.

### (2) AI image recognition (Liying Han)
We need to train a machine learning model to estimate the amount of water remaining in the bottle from a camera picture by using TensorFlow.

### (3) Sensor data collection, process and transmit (Liying Han, Weitao Sun)
We need to collect all data from different sensors using Arduino Nano 33 BLE, like camera images and a load module. Then we do some basic processing of those data, and send them to Raspberry Pi.

### (4) Server (Weitao Sun)
On the Raspberry Pi side, we need to process the data we get from Arduino, and try to detect the amount of food left in the bowl and the amount of water remaining in the bottle. Then we store those data, and build a http server to send those data to mobile.

### (5) Client (Liying Han)
Make an easy iOS app so that the user can use it to monitor the feeder’s status based on the data sent from the server.

## 9. Related Work

### 9.a. Papers

The paper on Automatic Pet Feeder designed by Kank, Aasavari and Gaikwad gave us a brief overview of current anto-feeders on the market<sup>[2]</sup>. We found that most auto-feeders implemented a similar function, that is to allow users to control the feeder using a mobile App, and users can set a time period to feed their pets. Some products may add other functions like playing audio sound, or using a distance sensor to detect the location of a pet so that the auto-feeder can serve food when it comes close. However, the weakness in common is that those products cannot serve food and water smartly based on the remaining amount in a bowl and a bottle, thus inspiring us to design a auto-feeder that can overcome this issue.

### 9.b. Datasets

The CIFAR-10 dataset<sup>[3]</sup>.

### 9.c. Software

EasyGUI<sup>[4]</sup>, 
XCode^<sup>[5]</sup>, 
PyCharm<sup>[6]</sup>, 
Arduino<sup>[7]</sup>, 
SOLIDWORK<sup>[8]</sup>.

## 10. References
[1]"U.S. pet ownership statistics", American Veterinary Medical Association, 2021. [Online]. Available: https://www.avma.org/resources-tools/reports-statistics/us-pet-ownership-statistics. [Accessed: 05- Nov- 2021].

[2]"Kank, Aasavari and Gaikwad (Mohite), Vaishali, Automatic Pet Feeder (October 20, 2018). Available at SSRN: https://ssrn.com/abstract=3274472 or http://dx.doi.org/10.2139/ssrn.3274472. [Accessed: 05- Nov- 2021].

[3]"The CIFAR-10 dataset. “Learning Multiple Layers of Features from Tiny Images, Alex Krizhevsky, 2009.” https://www.cs.toronto.edu/~kriz/cifar.html. [Accessed: 05- Nov- 2021].

[4]"EasyGUI — easygui 0.97 (2014-12-20) documentation", Easygui.sourceforge.net, 2021. [Online]. Available: http://easygui.sourceforge.net/. [Accessed: 05- Nov- 2021].

[5]"Xcode - Apple Developer", Apple Developer, 2021. [Online]. Available: https://developer.apple.com/xcode/. [Accessed: 05- Nov- 2021].

[6]"PyCharm: the Python IDE for Professional Developers by JetBrains", JetBrains, 2021. [Online]. Available: https://www.jetbrains.com/pycharm/. [Accessed: 05- Nov- 2021].

[7]"Arduino IDE 1.8.16", 2021. [Online]. Available: https://www.arduino.cc/en/software. [Accessed: 05- Nov- 2021].

[8]"SOLIDWORKS", 2021. [Online]. Available: https://www.solidworks.com/. [Accessed: 05- Nov- 2021].


