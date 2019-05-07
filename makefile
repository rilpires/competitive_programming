CPP = g++
OBJECT = obj
OPTIONS = -std=c++11 -lm -lcrypt -pipe -O2 -Wall
INPUT_FILE = entrada.txt
OUTPUT_FILE = saida.txt

%: %.cpp
	@clear
	@$(CPP) -g -Wall $(OPTIONS) -o $(OBJECT) $<
	@./$(OBJECT) < $(INPUT_FILE) > $(OUTPUT_FILE)
