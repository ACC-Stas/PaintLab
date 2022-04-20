cmake_minimum_required(VERSION 3.22)
project(PaintProject)

set(CMAKE_CXX_STANDARD 17)
set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(PaintProject main.cpp Figures/Dot.h Figures/Dot.cpp Figures/Drawable.h Figures/Line.h Figures/Line.cpp Figures/Point.h Figures/Point.cpp Figures/Rectangle.h Figures/Rectangle.cpp Drawer.cpp Drawer.h Paint.cpp Paint.h Figures/RadialBrush.cpp Figures/RadialBrush.h)
target_link_libraries(PaintProject ${OpenGlLinkers}) # linking opengl libraries to the project
