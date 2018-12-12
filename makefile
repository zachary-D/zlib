.DEFAULT_GOAL := all
.PHONY: all
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

#Cleans out temp files if the debug indicator is present
cleanIfDebug:
ifeq ($(debug_indicator_file), $(wildcard $(debug_indicator_file)))
	$(MAKE) clean
endif
	
#Cleans out temp files if the debug indicaotr is missing
cleanIfNoDebug:
	(test -s $(debug_indicator_file)) || $(MAKE) clean

#NOTE: An explanation of all the wonky multiline rules here - the | before prerequisites marks them as rules that need to be run, but that don't trigger the actual rule to run.  The final rule-declaration without any prerequisites are there because of the order make checks them - it first checks the last declaration (presumably it starts with the prerequisies associated with the actual definition of the rule), and then it jumps up to the first declaration and continues down in order.

#Defines 'debug' as a ""shortcut"" to $(debug_indicator_file)
debug:| $(debug_indicator_file) #Actually calls the $(debug_indicator_file) rule
debug: zlib.h.gch #This is here so that debug will trigger rules using this one as a prerequisite to recompile if (and only if) $(debug_indicator_file) actually recompiled zlib
debug:

#Build in debug mode
$(debug_indicator_file): g_flags += -g
$(debug_indicator_file): | cleanIfNoDebug
$(debug_indicator_file): zlib.h.gch
$(debug_indicator_file):
	echo "zlib compiled with debugging symbols" > $(debug_indicator_file)

#Compile and run the tests
runTests: tests.prog
	./tests.prog

gdbTests: tests.prog
	gdb -ex run --args tests.prog

tests.prog: tests.cpp $(debug_indicator_file)
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
