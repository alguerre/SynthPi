GPP = g++
GPPFLAGS = -Wall -lwiringPi -lpthread -lasound -lm -Wno-psabi
BIN_NAME = synthPi
OBJECTS = synthpi.o audio_driver.o mcp3008.o measurements.o waveform_generator.o
SRC = ../src/

build: $(OBJECTS)
	$(GPP) $(GPPFLAGS) -o $(BIN_NAME) $(OBJECTS)

synthpi.o: $(SRC)synthpi.cpp $(SRC)constants.h $(SRC)types.h
	$(GPP) $(GPPFLAGS) -c $(SRC)synthpi.cpp

mcp3008.o: $(SRC)mcp3008.cpp ../src/mcp3008.h
	$(GPP) $(GPPFLAGS) -c $(SRC)mcp3008.cpp

measurements.o: $(SRC)measurements.cpp $(SRC)measurements.h
	$(GPP) $(GPPFLAGS) -c $(SRC)measurements.cpp

waveform_generator.o: $(SRC)waveform_generator.cpp $(SRC)waveform_generator.h
	$(GPP) $(GPPFLAGS) -c $(SRC)waveform_generator.cpp

audio_driver.o: $(SRC)audio_driver.cpp $(SRC)audio_driver.h
	$(GPP) $(GPPFLAGS) -c $(SRC)audio_driver.cpp

.PHONY: all
all: build
	mkdir -p objects
	mv -f *.o objects/.
	mkdir -p ../bin
	mv $(BIN_NAME) ../bin/.

.PHONY: clean
clean:
	rm -rf *.o objects ../bin/$(BIN_NAME)
