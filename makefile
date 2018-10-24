.PHONY: clean

all_files = cryptography.cpp draw.cpp fileIO.cpp general.cpp input.cpp math.cpp model.cpp varConv.h varTypes.h windInfo.h cryptography.h draw.h fileIO.h general.h input.h math.h model.h varConv.cpp varTypes.cpp windInfo.cpp zlib.h

all: $(all_files)
	g++ -c $(all_files) -std=c++11
	
clean:
	rm *.o *.gch -r -f