CXX = clang++
CXXFLAGS = -Iinclude -lraylib

dummy_only: src/*.cpp
	$(CXX) $(CXXFLAGS) -DDUMMY_ONLY src/dummy.cpp src/main.cpp -o dummy_only

debug:
	$(CXX) $(CXXFLAGS) -g src/*.cpp -o debug

clean:
	rm -rf dummy_only
	rm -rf debug
	rm -rf *.o

