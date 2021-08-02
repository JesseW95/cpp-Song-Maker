main_a =  main.o SoundIO.o SoundSamples.o wave.o
main_b =  main2.o SoundIO.o SoundSamples.o wave.o
all = main.o main2.o SoundIO.o SoundSamples.o wave.o
CFLAG = -Wall -g
CC = g++
INCLUDES =
LIBS = -lm

all:main_a main_b
	-rm -f *.o

main_a:${main_a}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ $^
	
main_b:${main_b}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ $^

clean:
	-rm -f *.o core *.core main_a.exe main_b.exe *.txt

.cpp.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $<