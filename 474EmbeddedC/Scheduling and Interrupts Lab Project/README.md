# Schedulers and Interrupts

Lab 3 Project focuses on applying different types of schedulers to run various tasks and implementing internal timer counters and interrupts for advanced schedulers. 
The specific schedulers implemented include: 1) primitive Round-Robin scheduler, 2) Synchronous Round-Robin with Interrupts scheduler, and 3) Data-Driven scheduler with Task Control Blocks.
All of these scheduler implementations are of the non-preemptive type, meaning that we trust each task or function to return by itself without having to force it. In this project, the tasks 
controlling simple devices such as toggling an LED, playing a melody with an 8ohm speaker, and displaying countdowns and general values with a 7-segment display. Although the devices
are simple in nature, the focus of this lab is to demonstrate the advanced techniques of scheduling any type of task and interrupts, whether toggling a simple LED or reading sensor data
on a sophisticated system. 

The program was written for the AVR ATMega2560 microcontroller. Within the main file, a single variable "demo_number" controls the flow of the entire program. Near the header is a
description of what each demo entails. Each demo will have an associated number of tasks and a type of scheduler. 
