# Bike Fall Detection System

## Overview
This project implements a **Bike Fall and Hit Detection System** using an **ESP32 with an IMU sensor** for data collection and a **Seeed Studio XIAO nRF52840** board for real-time detection.  
The system uses a **machine learning model** trained in Python and deployed as a C++ header file (`model.h`).  

 **Future Goal**: To automatically **turn off the bike’s engine** when a fall or hit is detected, preventing accidents from worsening due to unintended acceleration.

---

## Features
- Collects real-time accelerometer and gyroscope data using an **IMU sensor**.
- Trains a **Random Forest Classifier** in Python for activity classification.
- Deploys the trained model on **Seeed XIAO nRF52840** for inference.
- Detects 3 states:
  -  Normal (Bike is stable)
  -  Accident (Bike has fallen)
  -  Hit (Collision detected)
 
- For this instance, uses **LED indicators**:
  - Green - Normal  
  - Red - Accident  
  - Blue - Hit  
