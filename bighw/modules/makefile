objects = $(patsubst %.cpp,%.so,$(wildcard *.cpp))

all:$(objects) 

%.so:%.o ../common.o
	g++ -fPIC -shared -g $< ../common.o -o $@
%.o:%.cpp %.h
	g++ -fPIC -g -c $< -o $@

.PHONY:clean all

clean:
	-rm ./*.o