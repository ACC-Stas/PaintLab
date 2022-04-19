cmake_minimum_required(VERSION 3.22)
project(PaintProject)

set(CMAKE_CXX_STANDARD 17)
set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

add_executable(PaintProject main.cpp Figures/Dot.h Figures/Dot.cpp Figures/Figure.h Figures/Drawable.h)
target_link_libraries(PaintProject ${OpenGlLinkers}) # linking opengl libraries to the project
