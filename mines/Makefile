all:
	g++ -o solve solve.cpp -std=c++11 -O2
opencv:
	g++ -o opencvtest opencvtest.cpp -std=c++11 -O2 `pkg-config --cflags opencv` `pkg-config --libs opencv`
crop:
	g++ -o crop crop.cpp -std=c++11 -O2 `pkg-config --cflags opencv` `pkg-config --libs opencv`
get_size:
	g++ -o get_size get_size.cpp -std=c++11 -O2 `pkg-config --cflags opencv` `pkg-config --libs opencv`
