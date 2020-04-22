##### MACROS #####
FLAGS= -ggdb -c -Wall
LIN_GL_LIBS = -L/usr/lib -lglut -lGLU -lGL
LIN_X_LIBS = -L/usr/X11/lib -L/usr/X11R6/lib -lX11 -lXext -lXmu -lXt -lXi -lSM -lICE
LIN_LIBS = $(LIN_GL_LIBS) $(LIN_X_LIBS) -lm
LIN_INCLUDES = -I/usr/X11R6/include
LIBS = $(LIN_LIBS)
INCLUDES = $(LIN_INCLUDES)
CC = gcc

##### RULES #####
robot: robot.o
	$(CC) -o robot robot.o $(LIBS)

robot.o: robot.c
	$(CC) robot.c $(FLAGS) $(INCLUDES)
