CPP = g++
OBJECT = obj
OPTIONS = -std=c++11 -lm -lcrypt -pipe -O2 -Wall

%: %.cpp
	@clear
	@$(CPP) -g -Wall $(OPTIONS) -o $(OBJECT) $<
	@./$(OBJECT) < entrada.txt > saida.txt
