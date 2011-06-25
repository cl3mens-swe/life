GCC=/usr/bin/gcc
FLAGS=
TARGET=life
OBJ=life.o

$(TARGET): $(OBJ)
	$(GCC) $(FLAGS) $(OBJ) -o $(TARGET)

$(OBJ): $(TARGET).c
	$(GCC) $(FLAGS) -c $(TARGET).c