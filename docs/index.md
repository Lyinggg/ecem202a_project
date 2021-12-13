# Abstract

An automatic pet feeder is a good choice when people are away from home but need to take care of their pets. However, most auto-feeders on the market have a similar disadvantage, that they mechanically pour food on time with a fixed amount, without checking how much food remains in the bowl. This will cause a build-up of food if there is much food left since the last feeding. We want to design a new auto-feeder that can avoid such problems. 

In our approach, we use a highly accurate load module and a computer vision algorithm with picture capture to measure a more accurate remaining amount of food and water, so that we can dynamically adjust our next feeding based on the data. Our auto-feeder also connects to the internet and provides users with a mobile App to monitor the previous and current status of the feeder, and allows users to manually feed their pets if needed. To achieve our goals, we design and 3D-print the prototype of our auto-feeder, and use two Arduino Nano 33 BLE Sense to collect signals from the load module and drive motors to deliver food. Signals are then sent to the Raspberry Pi through Bluetooth for further processing. Because of time limits, for remaining water detection we only complete the basic algorithm to read images and detect water level using OpenCV on the Raspberry Pi. We implement a cloud server and a mobile App. The Raspberry Pi will send information about the feeder to the cloud server. A user can use the mobile App to view previous feeding activity by requesting data stored in the cloud server. A user can also set a new feeding frequency and feeding amount, or even feed cats manually by sending an HTTP POST request to the server. 

Our results showed that we essentially achieve all of the designing goals. The machine is able to deliver food automatically, dynamically adjust the feeding amount based on remaining food, and monitor the amount of remaining water if given an image of the water tank. Users are also able to monitor the log and manually feed their pets on the mobile App.

# Team

* Weitao Sun
* Liying Han

# Required Submissions

* [Proposal](https://github.com/7hgTnec/ecem202a_project/blob/main/docs/proposal.md)
* [Midterm Checkpoint Presentation Slides](https://www.youtube.com/watch?v=6sHJ5y1Uhzs)
* [Final Presentation Slides](https://www.youtube.com/watch?v=KdiD5BC-hSk)
* [Demo Video](https://drive.google.com/file/d/1RbNqImx3Dk9ITvyLzwktnJUrLoQa-qmm/view?usp=sharing)
* [Final Report](https://github.com/7hgTnec/ecem202a_project/blob/main/docs/report.md)
