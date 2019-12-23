rebirth (IOS 11.0 to 11.3.1 jailbreak)
======================================
rebirth is a security research tool using multipath tfp0 exploit and QiLin framework for IOS11.
It requires Xcode and an apple developer account for exploitation. It makes use of a lightweight
userland which is installed with the application in a non-persistent manner. The root file system
is mounted writeable on 11.0 to 11.2.6, this is not currently supported in 11.3 & up due to apfs.
Disables amfi code signing and includes SSH within the jailbreak using rootless techniques to avoid
persistence problems. This toolkit also includes utilities for IOS application hacking such as
cycript, Frida & dumpdecrypted.dylib for removing fairplay and instrumenting IOS mobile apps.

This is not a consumer jailbreak utility and no package management software is included. The goal 
of this project was to provide a lightweight stable utility for use by mobile forensics and mobile 
security practitioners. It provides a tethered minimalist root environment with no permanent device
modifications to assist in data recovery and/or IOS application hacking. 

Supports the following IOS 11.0 to 11.3.1 devices (see targets.c for full details):

iPad Air, iPad Air 2, iPad Pro (12.9-inch), iPad Pro (9.7-inch), iPad (5th generation), iPad Pro 
(12.9-inch, 2nd generation), iPad Pro (10.5-inch) iPhone 5s, iPhone 6, iPhone 6s, iPhone 6 Plus, 
iPhone 6s Plus, iPhone 7, iPhone 7 Plus, iPhone 8, iPhone 8 Plus, iPhone SE, iPhone X, iPad mini 2, 
iPad mini 3, iPad mini4 and iPod touch (6th generation).

![screenshot](/screenshot.png)

# Acknowledgements
Hacker House credits Ian Beer for the multipath exploit, jakeajames for his rootless SSH concept
and Johnathan Levin for the QiLin framework & OS binpack. 
