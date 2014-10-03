CC=g++
CFLAGS=-Wall -Werror -O3 -std=c++11 -g -Wl,--no-as-needed -ldl -rdynamic -fstack-protector-all

INCLUDE=-Iinclude/ -Iinclude/libs/

# include statements necessary to link all the individual libraries
INCLUDE_LIBS=-Iexternal/entangle-server/include/ -Iexternal/entangle-server/external/giga/external/catch/include/ -Iexternal/entangle-server/external/exceptionpp/include/ -Iexternal/entangle-server/external/msgpp/include/ -Iexternal/entangle-server/external/giga/include/libs/stacktrace/ -Iexternal/entangle-server/external/giga/external/cachepp/include/ -Iexternal/entangle-server/external/giga/include/ -Iexternal/entangle-server/external/msgpp/include/

LIBS=-pthread

S_SOURCES+=src/*cc libs/*/*cc
S_OBJECTS=$(S_SOURCES:.cc=.o)

T_SOURCES+=src/*cc tests/*cc libs/*/*cc
T_OBJECTS=$(T_SOURCES:.cc=.o)

S_EXECUTABLE=entangle.app
T_EXECUTABLE=tests.app

.PHONY: all clean test prep

all: $(S_SOURCES) $(S_EXECUTABLE)

$(S_EXECUTABLE): $(S_OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDE_LIBS) $(INCLUDE) $(S_OBJECTS) -o $@ $(LIBS)

$(T_EXECUTABLE): $(T_OBJECTS)
	@$(CC) $(CFLAGS) -D _ENTANGLE_NO_MAIN $(INCLUDE_LIBS) $(INCLUDE) $(T_OBJECTS) -o $@ $(LIBS)

prep:
	@rm -rf tests/files/
	@mkdir -p tests/files/

DO_TEST?=true
test: clean $(S_EXECUTABLE) $(T_EXECUTABLE) prep
	@if [ "$(DO_TEST)" = "true" ]; then \
		ulimit -c unlimited && time ./$(T_EXECUTABLE) | tee results.log; \
	fi

clean:
	@rm -f $(S_EXECUTABLE) $(T_EXECUTABLE) *.o *.log core
