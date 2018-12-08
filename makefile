.PHONY: clean

all_files = cryptography.cpp cryptography.h draw.cpp draw.h fileIO.cpp fileIO.h general.cpp general.h input.cpp input.h math.cpp math.h model.cpp model.h network.cpp network.h varConv.cpp varConv.h varTypes.cpp varTypes.h windInfo.cpp windInfo.h zlib.h

debug_flags = -g
debug_indicator_file = debug_made.txt

all: $(all_files)
	rm -rf $(debug_indicator_file)
	g++ -c $(all_files) -std=c++11

debug: $(all_files)
	rm -rf $(debug_indicator_file)
	g++ -c $(all_files) -std=c++11 $(debug_flags)
	echo "Zlib compiled in debug mode" > $(debug_indicator_file)

clean:
	rm $(debug_indicator_file) -rf
	rm *.o *.gch -r -f
