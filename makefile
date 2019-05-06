CPP = g++
OBJECT = a.out
OPTIONS = -std=c++11 -lm -lcrypt -pipe -O2 -Wall
INPUT_FILE = entrada.txt
OUTPUT_FILE = saida.txt

%: %.cpp
	@clear
	@g++ $(OPTIONS) -o $(OBJECT) -g -Wall $<
	@./$(OBJECT) < $(INPUT_FILE) > $(OUTPUT_FILE)
