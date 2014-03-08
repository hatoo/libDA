CC = g++ -std=c++1y -msse4.2 -O3 -Wall
CCtest = g++ -std=c++1y -msse4.2 -Wall
CCpg = g++ -std=c++1y -msse4.2 -O3 -Wall -pg

default : Hand.o Card.o ucb1_tuned.o montecarlo.o simulate.o
	$(CC) -shared -o libDA.dll Hand.o Card.o ucb1_tuned.o montecarlo.o simulate.o -Wl,--export-all-symbols

Hand.o : Hand.h Hand.cpp
	$(CC) -c -o Hand.o Hand.cpp

Card.o : Card.cpp Card.h
	$(CC) -c -o Card.o Card.cpp

test : test.cpp Card.o Hand.o simulate.o montecarlo.o ucb1_tuned.o
	$(CCtest) test.cpp Card.o Hand.o simulate.o montecarlo.o ucb1_tuned.o -lgtest -lgtest_main -lpthread -o test

ucb1_tuned.o : ucb1_tuned.h ucb1_tuned.cpp
	$(CC) -c -o ucb1_tuned.o ucb1_tuned.cpp

simulate.o : Card.h Hand.h simulate.cpp simulate.h
	$(CC) -c -o simulate.o simulate.cpp

montecarlo.o : montecarlo.cpp montecarlo.h
	$(CC) -c -o montecarlo.o montecarlo.cpp

prof: profile.cpp montecarlo.cpp montecarlo.h Card.cpp Card.h Hand.h Hand.cpp simulate.cpp simulate.h ucb1_tuned.cpp ucb1_tuned.h
	$(CCpg) -o prof profile.cpp montecarlo.cpp Card.cpp Hand.cpp simulate.cpp ucb1_tuned.cpp -g -fmudflap -lmudflap

clean :
	rm *.o
	rm *.exe