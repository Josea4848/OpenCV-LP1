# Makefile

# Compilador
CXX := g++

# Flags do compilador
CXXFLAGS := -std=c++11 -Wall -Wextra

# Bibliotecas externas
OPENCV_CFLAGS := $(shell pkg-config --cflags opencv4)
OPENCV_LIBS := $(shell pkg-config --libs --static opencv4)

# Arquivos fonte
SOURCES := main.cpp Game.cpp Object.cpp Screen.cpp

# Nome do executável
EXECUTABLE := game

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(OPENCV_CFLAGS) $^ -o $@ $(OPENCV_LIBS)

clean:
	rm -f $(EXECUTABLE)
