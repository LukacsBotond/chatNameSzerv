CFLAGS = -Wall -lpthread -std=c++17 -g

kliens: ./kliens/*.cpp ./common/*.cpp ./common/*.h
	g++ -o ./exec/kli ./kliens/*.cpp ./common/*.cpp $(CFLAGS)

szerver: ./serv/*.cpp ./serv/*.cpp ./common/*.cpp ./common/*.h
	g++ -o ./exec/szerver ./serv/*.cpp ./common/*.cpp $(CFLAGS)

nameServ: ./nameServ/*.cpp ./common/*.cpp ./common/*.h
	g++ -o ./exec/nameServ ./nameServ/*.cpp ./common/*.cpp $(CFLAGS)

all: kliens nameServ szerver

clean: 
	rm -f kliens
	rm -f nameServ
	rm -f szerver