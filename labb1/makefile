CC = g++
FLAGS = -g -Wall
SOURCE= konkordans.cpp
EXE= konkordans.out
RES= indextest.bin

index:
	/info/adk15/labb1/tokenizer < /info/adk15/labb1/korpus | sort > /var/tmp/konkordanzBitches ^C

all:
	$(CC) $(FLAGS) $(SOURCE) -o $(EXE)

clean:
	rm -f $(EXE) $(RES)
