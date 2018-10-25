.PHONY: clean

all_files = cryptography.cpp cryptography.h draw.cpp draw.h fileIO.cpp fileIO.h general.cpp general.h input.cpp input.h math.cpp math.h model.cpp model.h network.cpp network.h varConv.cpp varConv.h varTypes.cpp varTypes.h windInfo.cpp windInfo.h zlib.h

all: $(all_files)
	g++ -c $(all_files) -std=c++11
	
clean:
	rm *.o *.gch -r -f
