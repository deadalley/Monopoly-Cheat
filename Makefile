CC = g++
CFLAGS = -c -g -std=c++11
IFLAGS = -I. -I./include
TFLAGS =
MAIN = main.cpp
SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC)) $(patsubst %.cpp,$(OBJDIR)/%.o,$(MAIN))
EXEC = monopoly

all: obj $(EXEC)

obj:
	mkdir obj

$(EXEC): $(OBJ)
	$(CC) -g $(IFLAGS) $^ -o $@ $(TFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(IFLAGS) $< -o $@

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(IFLAGS) $< -o $@

log:
	python3 plot_results.py

clean:
	rm -rf $(OBJDIR)/*.o $(EXEC) *.d
	rm -rf $(OBJDIR)

clr-log:
	rm -rf results/*.log

clr-results:
	rm -rf results/*.png

val:
	valgrind --leak-check=full --track-origins=yes ./$(EXEC)

run: $(EXEC)
	@./$(EXEC)
