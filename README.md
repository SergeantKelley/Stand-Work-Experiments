# Stand-Work-Experiments

This repository contains some of my successful experiments for Redlab-I testbench harware using Qt creator and Python.
This software is strongly intended for avionics test-bench hardware and cannot be run as a standalone app (excepting "Plugin Creator").

# System prerequisities

To compile all projects you will need to install the following libs right on your system:
- glfw3
- glew
- Tkinter GUI extension for Python language
- Qt Creator version 4.x or higher

## Details on projects

All project published here are system-specific and highly specialized

### Plugin maker

Pyhton app to swiftly create minimal Qt cpp plugin project

### Joystick Experimental plugin

Qt cpp experimental plugin project for additional controlling test-bench software with gamepad or joystick operating via USB. It based on glfw3 library

### Stand Plugin Sample

Minimal qt cpp project that implements architecture design pattern similar to MVC or MVP patterns. This is a sample project.
The general idea is to separate visual GUI representation and application logic. It gives a pretty good code modularity and readability and also allows easily connect and disconnect user-defined GUI


Enjoy :-)
