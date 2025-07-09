CXX=loongarch64-linux-gnu-g++
TARGET = main
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC) /home/su/work/opencv-4.5.5/install/include/opencv4)

CXXFLAGS = -c 

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY:clean
clean:
	rm -f *.o $(TARGET)

