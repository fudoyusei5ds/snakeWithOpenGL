WORKSPACE	= /home/tet/test_sets/workspace

INC		= -I$(WORKSPACE)/thirdpartylib/include
LIBS	= -lglfw3 -lX11 -lpthread -ldl -lXxf86vm -lglad
LIBGL	= /usr/lib/x86_64-linux-gnu/mesa/libGL.so.1
LIBGLEW	= /usr/lib/x86_64-linux-gnu/libGLEW.so.1.13
LIBX	= /usr/lib/x86_64-linux-gnu/libXrandr.so.2 \
		/usr/lib/x86_64-linux-gnu/libXi.so.6 \
		/usr/lib/x86_64-linux-gnu/libXinerama.so.1 \
		/usr/lib/x86_64-linux-gnu/libXcursor.so.1
LIBDIR	= -L$(WORKSPACE)/thirdpartylib/lib -L/usr/lib/x86_64-linux-gnu/mesa/
DEFINES	=
CFLAGS	= $(LIBDIR) $(LIBS) $(LIBGL) $(LIBGLEW) $(LIBX)

#############

all: main

main: 	main.cpp\
		shader.h rect.fs rect.vs\
		rectangle.h
	g++ main.cpp $(INC) $(CFLAGS) -o snake -std=c++11

test: test.cpp\
		shader.h rect.fs rect.vs\
		rect1.fs rect1.vs rect2.fs\
		rectangle.h
	g++ test.cpp $(INC) $(CFLAGS) -o main -std=c++11