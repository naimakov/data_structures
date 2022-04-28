BUILD_DIR = ../../build/week_3

####################################################################################

IOPT=
IOPT_DBG=
LOPT=
LOPT_DBG=

CC =gcc
CXX=g++

IOPT+=-pipe -Wall -O2
IOPT_DBG+=-Wall -ggdb
LOPT+=-lm
LOPT_DBG+=-lm

IOPTCXX=$(IOPT) -std=c++14
IOPTCXX_DBG=$(IOPT_DBG) -std=c++14

all: $(BUILD_DIR)/make_heap.exe \
$(BUILD_DIR)/parallel_processing.exe

OBJ:=$(patsubst %.cpp,%.o,   $(patsubst %.c,%.o,$(SRC))   )
OBJ:=$(patsubst %,${BUILD_DIR}/%,$(OBJ) )

${BUILD_DIR}/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(IOPTCXX) -c $< -o $@

${BUILD_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(IOPT)  -c $< -o $@

${BUILD_DIR}/%_dbg.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(IOPTCXX_DBG) -c $< -o $@

${BUILD_DIR}/%_dbg.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(IOPT_DBG)  -c $< -o $@

${BUILD_DIR}/make_heap.exe: ${BUILD_DIR}/make_heap.o
	rm -f $@
	g++ $< $(LOPT_DBG) -o $@

${BUILD_DIR}/parallel_processing.exe: ${BUILD_DIR}/parallel_processing.o
	rm -f $@
	g++ $< $(LOPT_DBG) -o $@	

clean:
	cd ${BUILD_DIR}; rm -f `find . -name "*.o"`