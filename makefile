CPP = g++
OBJECT = a.out
OPTIONS = -std=c++11 -lm -lcrypt -pipe -O2 -Wall

%: %.cpp
	@clear
	@g++ $(OPTIONS) -o $(OBJECT) $<
	@./$(OBJECT)
