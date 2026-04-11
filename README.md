
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

### glfw3 Plugin Sample
This is a starting experimental template Qt project which allows to visualize simulation states in 3D scene using openGL 3.3 profile, glfw3 and glm libs.
In order to communicate with the hard real-time context a couple params were created. Thus two-way logical connection is provided.
The project is intended for redlab-E avionics test-bench systems.

#### Usage instructions
In order to start an experiment in conjuction with the qt extended plugin you need first to copy "Shaders" folder to the following path:
"/home/student/.oper_vis/plugins/" on your test-bench system

After that you may need to modify the following string in the Qt .pro file:

DESTDIR = /home/student/.oper_vis/plugins/

change "student" to your system login name. It allows you copying just after project building, automagically

If all is done correctly, you will see a scene similar to that:

<img width="835" height="655" alt="2026-04-08_15-00" src="https://github.com/user-attachments/assets/e2e0040a-0421-434d-8451-e8abc25d1ac4" />

 
Enjoy :-)
