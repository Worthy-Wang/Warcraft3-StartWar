#版本三
CC=g++
target=app
src=$(wildcard *.cpp)
obj=$(patsubst %.cpp, %.o, $(src))
CPPFLAGS=-g -Wall

$(target):$(obj)
	$(CC) $(CPPFLAGS) $^ -o $@
%.o:%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@
clean:
	rm -rf $(target) $(obj)
