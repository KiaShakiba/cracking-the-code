NAME := blockchain

INC := -Iinclude

CPP_FLAGS := $(INC)

CPP_SRCS := $(wildcard *.cpp) $(wildcard */*.cpp)
CPP_HDRS := $(wildcard *.hpp) $(wildcard */*.hpp)
CPP_DEPS := $(CPP_SRCS:.cpp=.d)
CPP_OBJS := $(CPP_SRCS:.cpp=.o)

OBJS := $(CPP_OBJS)

.PHONY: clean

all: $(NAME)
	$(MAKE) distclean

$(NAME): $(OBJS)
	$(CXX) $(LFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CPP_FLAGS) -MMD -c $< -o $@

clean:
	rm -f $(CPP_DEPS)
	rm -f $(OBJS)
	rm -f $(NAME)

distclean:
	rm -f *~ */*~
	rm -f *.o */*.o
	rm -f *.d */*d

-include $(CPP_DEPS)
