GPP = g++

GPP_PRODUCTION_FLAGS = -lwiringPi -lcrypt -lpthread -lasound -lm -Wno-psabi 
LD_PRODUCTION_FLAGS =

GPP_TEST_FLAGS = -fprofile-arcs -ftest-coverage -I /usr/local/include
LD_TEST_FLAGS = -Wno-psabi -lgcov -L /usr/local/lib -lgtest

GPP_FLAGS =  # to be defined as production or test
LD_FLAGS =   # to be defined as production or test
  
BIN_NAME =   # to be defined as production or test
OBJECTS =    # to be defined as production or test

BIN_TEST = synthpi_test
BIN_PRODUCTION = synthpi

OBJ_MAIN = synthpi.o
OBJ_SRC = audio_driver.o mcp3008.o measurements.o waveform_generator.o
OBJ_TESTS = test.o ut_mcp3008.o ut_measurements.o

SRC = ../src/
TEST = ../test/

build:
	$(GPP) -Wall -o $(BIN_NAME) $(OBJECTS) $(GPP_FLAGS) $(LD_FLAGS) 

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


.PHONY: copybin
copybin:
	mkdir -p ../bin
	mv $(BIN_NAME) ../bin/.


.PHONY: all
all: BIN_NAME=$(BIN_PRODUCTION)
all: GPP_FLAGS=$(GPP_PRODUCTION_FLAGS)
all: LD_FLAGS=$(LD_PRODUCTION_FLAGS)
all: OBJECTS=$(OBJ_MAIN) $(OBJ_SRC)
all: $(OBJ_MAIN) $(OBJ_SRC)
all: build
all: copybin


.PHONY: test
test: BIN_NAME=$(BIN_TEST)
test: GPP_FLAGS=$(GPP_PRODUCTION_FLAGS) $(GPP_TEST_FLAGS)
test: LD_FLAGS=$(LD_PRODUCTION_FLAGS) $(LD_TEST_FLAGS)
test: OBJECTS=$(OBJ_SRC) $(OBJ_TESTS)
test: $(OBJ_SRC) $(OBJ_TESTS)
test: build
test: copybin


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
