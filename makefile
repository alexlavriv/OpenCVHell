all: start

# Tool invocations
# Executable "start" depends on the files ProjectTest.o and Tests.o.
start: 
	g++ -g `pkg-config --cflags opencv` display_image.cpp `pkg-config --libs opencv` -lrestclient-cpp -L/usr/local/lib -lrestclient-cpp -lcurl -o display_image
