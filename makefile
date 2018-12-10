.PHONY: clean
.PHONY: removeDebugFlag
.PHONY: cleanIfNoDebug
.PHONY: cleanIfDebug
.PHONY: debug
.PHONY: runTests
.PHONY: gdbTests

g_flags = $(*.o) --std=c++11 -c
debug_indicator_file = debug_made.txt

#Compile the library
all: cleanIfDebug zlib.h.gch
	
#Clean out the repo (of compile files)
clean:
	rm $(debug_indicator_file) -rf
	rm *.o *.gch *.prog -r -f

#Removes the debug indicator
removeDebugFlag:
	rm -rf $(debug_indicator_file)

#Cleans out temp files if the debug indicator is present
cleanIfDebug:
ifeq ($(debug_indicator_file), $(wildcard $(debug_indicator_file)))
	$(MAKE) clean
endif
	
#Cleans out temp files if the debug indicaotr is missing
cleanIfNoDebug:
	(test -s $(debug_indicator_file)) || $(MAKE) clean

$(debug_indicator): debug
	echo "zlib compiled with debugging symbols" > $(debug_indicator_file)

#Build in debug mode
debug: g_flags += -g
debug: cleanIfNoDebug removeDebugFlag zlib.h.gch

#Compile the tests without running them
tests: tests.prog

#Compile and run the tests
runTests: tests.prog
	./tests.prog

gdbTests: tests.prog
	gdb -ex run --args tests.prog

tests.prog: debug tests.cpp
	g++ -o tests.prog tests.cpp *.o -std=c++11 -g

zlib.h.gch: zlib.h cryptography.o draw.o fileIO.o general.o input.o math.o model.o network.o var.o windInfo.o
	g++ zlib.h $(g_flags)

cryptography.o: cryptography.cpp cryptography.h
	g++ cryptography.cpp cryptography.h $(g_flags)

draw.o: draw.cpp draw.h
	g++ draw.cpp draw.h $(g_flags)

fileIO.o: fileIO.cpp fileIO.h
	g++ fileIO.cpp fileIO.h $(g_flags)

general.o: general.cpp general.h
	g++ general.cpp general.h $(g_flags)

input.o: input.cpp input.h
	g++ input.cpp input.h $(g_flags)

math.o: math.cpp math.h
	g++ math.cpp math.h $(g_flags)

model.o: model.cpp model.h
	g++ model.cpp model.h $(g_flags)

network.o: network.cpp network.h
	g++ network.cpp network.h $(g_flags)

var.o: var.cpp var.h
	g++ var.cpp var.h $(g_flags)

windInfo.o: windInfo.cpp windInfo.h
	g++ windInfo.cpp windInfo.h $(g_flags)
