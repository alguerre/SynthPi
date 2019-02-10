# Makefile to compile the synthpi project in a raspbian environment.
# all: compile the project in production mode. 
# test: compile unit tests.
#    note: it is possible to compile the unit tests in ubuntu if ut_measurements.o and ut_mcp3008.o (rule OBJ_TEST) are not created.

# Variables definition
GPP = g++

BIN_TEST = synthpi_test
BIN_PRODUCTION = synthpi
BIN_NAME =   # to be defined as production or test by corresponding rule

GPP_PRODUCTION_FLAGS = -lwiringPi -lcrypt -lpthread -lasound -lm -Wno-psabi 
GPP_TEST_FLAGS = -fprofile-arcs -ftest-coverage -I /usr/local/include
GPP_FLAGS =  # to be defined as production or test by corresponding rule

LD_PRODUCTION_FLAGS =
LD_TEST_FLAGS = -Wno-psabi -lgcov -L /usr/local/lib -lgtest
LD_FLAGS =   # to be defined as production or test by corresponding rule
  
OBJ_MAIN = synthpi.o
OBJ_SRC = audio_driver.o waveform_generator.o measurements.o  mcp3008.o
OBJ_TEST = test.o ut_audio_driver.o ut_waveform_generator.o # ut_measurements.o ut_mcp3008.o
OBJECTS =    # to be defined as production or test by corresponding rule

SRC = ../src/
TEST = ../test/


# Compilation rules
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

ut_waveform_generator.o: $(TEST)ut_waveform_generator.cpp
	$(GPP) $(GPP_FLAGS) -c $(TEST)ut_waveform_generator.cpp

ut_audio_driver.o: $(TEST)ut_audio_driver.cpp
	$(GPP) $(GPP_FLAGS) -c $(TEST)ut_audio_driver.cpp


# Compilation modes
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
test: OBJECTS=$(OBJ_SRC) $(OBJ_TEST)
test: $(OBJ_SRC) $(OBJ_TEST)
test: build
test: copybin


# Functions
.PHONY: clean
clean:
	rm -rf *.o objects 
	rm -f *gcda *gcno *gcov

.PHONY: copybin
copybin:
	mkdir -p ../bin
	mv $(BIN_NAME) ../bin/.

.PHONY: report
report:
	rm -rf $(TEST)/report
	lcov -c --directory . --output-file main_coverage.info 
	genhtml main_coverage.info --output-directory report
	mv report $(TEST)/.
	rm -f main_coverage.info
