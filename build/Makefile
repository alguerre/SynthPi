# This Makefile is ready for unit test execution with gtest
GPP = g++

GPP_TEST_FLAGS = -fprofile-arcs -ftest-coverage
LD_TEST_FLAGS = -lgcov -L /usr/local/lib -lgtest

GPP_FLAGS = -lwiringPi -lpthread -lasound -lm -Wno-psabi $(GPP_TEST_FLAGS) -I /usr/local/include
LD_FLAGS = -Wno-psabi $(LD_TEST_FLAGS) 

BIN_NAME = synthpi_test
OBJECTS = audio_driver.o mcp3008.o measurements.o waveform_generator.o
OBJ_TESTS = test.o ut_mcp3008.o ut_measurements.o

SRC = ../src/
TEST = ../test/

build: $(OBJECTS) $(OBJ_TESTS)
	$(GPP) -Wall -o $(BIN_NAME) $(OBJ_TESTS) $(OBJECTS) $(GPP_FLAGS) $(LD_FLAGS) 

synthpi.o: $(SRC)synthpi.cpp $(SRC)constants.h $(SRC)types.h
	$(GPP) $(GPP_FLAGS) -c $(SRC)synthpi.cpp

mcp3008.o: $(SRC)mcp3008.cpp ../src/mcp3008.h
	$(GPP) $(GPP_FLAGS) -c $(SRC)mcp3008.cpp

measurements.o: $(SRC)measurements.cpp $(SRC)measurements.h
	$(GPP) $(GPP_FLAGS) -c $(SRC)measurements.cpp

waveform_generator.o: $(SRC)waveform_generator.cpp $(SRC)waveform_generator.h
	$(GPP) $(GPP_FLAGS) -c $(SRC)waveform_generator.cpp

audio_driver.o: $(SRC)audio_driver.cpp $(SRC)audio_driver.h
	$(GPP) $(GPP_FLAGS) -c $(SRC)audio_driver.cpp

test.o: $(TEST)test.cpp
	$(GPP) $(GPP_FLAGS) -c $(TEST)test.cpp

ut_mcp3008.o: $(TEST)ut_mcp3008.cpp
	$(GPP) $(GPP_FLAGS) -c $(TEST)ut_mcp3008.cpp

ut_measurements.o: $(TEST)ut_measurements.cpp
	$(GPP) $(GPP_FLAGS) -c $(TEST)ut_measurements.cpp


.PHONY: all
all: build
	mkdir -p objects
	mv -f *.o objects/.
	mkdir -p ../bin
	mv $(BIN_NAME) ../bin/.

.PHONY: clean
clean:
	rm -rf *.o objects 
	rm -f *gcda *gcno *gcov

.PHONY: report
report:
	rm -rf $(TEST)/report
	lcov -c --directory . --output-file main_coverage.info 
	genhtml main_coverage.info --output-directory report
	mv report $(TEST)/.
	rm -f main_coverage.info
