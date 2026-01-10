# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -O2 \
    -I external/glad/ \
    -I external/glfw/include \
    -I include/

LDFLAGS := -L external/glfw/lib-mingw-w64 -lglfw3 -lgdi32 -lopengl32

# ONLY compile files in src/
ifeq ($(OS),Windows_NT)
    SRCS := $(shell powershell -Command "Get-ChildItem src -Recurse -Filter *.cpp | ForEach-Object { $$_.FullName }") \
            external/glad/src/glad.c
    RM := powershell -Command "Get-ChildItem -Recurse -Include *.o | Remove-Item -ErrorAction SilentlyContinue"
else
    SRCS := $(shell find src -name "*.cpp") external/glad/src/glad.c
    RM := rm -f *.o
endif

OBJS := $(SRCS:.cpp=.o)
TARGET := main.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo Linking $(TARGET)...
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)
	@echo Cleaning up object files...
	@$(RM)
	@echo Build successful!

%.o: %.cpp
	@echo Compiling $<...
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	@echo Compiling $<...
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist $(TARGET).exe del $(TARGET).exe
	@powershell -Command "Get-ChildItem -Recurse -Include *.o | Remove-Item -ErrorAction SilentlyContinue"
	@echo Clean complete.

run: $(TARGET)
	@echo Running...
	./$(TARGET)