
SOURCES=$(shell find . -name "*.cpp")
OBJECTS=$(SOURCES:%.cpp=%.o)
TARGET=main

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK.cpp) $^ -std=c++11 $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS)

