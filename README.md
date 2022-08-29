# OpenGL Engine

This is a game engine. It's based on OpenGl.

Now available:
- Base 2D objects
- Keyboard input 
- Mouse input
- 2D physics
- Init objects from file. You need to use my own language to do this

# Language for objects

Firstly, you need to indicate type of object.
After that you can indicate position, size, color, vertices.
You can check example in the Object.object file.
### Examples for primitive objects.
#### For Point
	type=point
	position=0,0
	color=255,255,255,255
#### For Line
	type=line
	position=0,0
	position=40,0
	color=255,255,255,255
#### For Rectangle
	type=rectangle
	position=0,0
	scale=1,1
	color=255,255,255,255
#### For Circle
	type=circle
	position=0,0
	radius=50
	color=255,255,255
#### For Triangle
	type=triangle
	position=0,0
	scale=1,1
	vertex=-20,0
	vertex=0,20
	vertex=20,0
	color=255,255,255,255
#### For Polygon
	position=0,0
	scale=1,1
	vertex=-100,-100,
	vertex=-50,40
	vertex=0,100
	vertex=100,20
	color=255,255,255,255
