modir := ./modules/
libs := $(patsubst %.cpp,%.so,$(wildcard $(modir)*.cpp))


#目标
all:main server	 $(libs) 

main:main.o common.o module.o
	g++ -g  main.o module.o common.o -ldl -o main
server:server.o common.o module.o
	g++ server.o common.o module.o -g -ldl -o server
#重载默认模式

%.o:%.cpp
	g++ -fPIC -g -c  -ldl $< -o $@

main.o:main.cpp
module.o:module.cpp module.h
server.o: server.cpp server.h
common.o:common.cpp common.h

#编译动态库
$(modir)%.o:$(modir)%.cpp (modir)%.h

$(modir)%.so:$(modir)%.o common.o
	g++ -fPIC -shared -g $< common.o -o $@

.PHONY:all clean cleanall

clean:
	-rm ./*.o $(modir)*.o
cleanall:
	-rm ./*.o server main $(modir)*.o $(modir)*.so
