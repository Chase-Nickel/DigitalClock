SOURCES = main.c
RLS_OBJECTS = $(SOURCES:%.c=obj/rls_%.o)
DBG_OBJECTS = $(SOURCES:%.c=obj/dbg_%.o)

CC = gcc
DBG_FLAGS = -std=c2x -g3 -Wall -Wextra -Werror -fsanitize=address,undefined
RLS_FLAGS = -std=c2x -Wall -Wextra -Werror -O2

EXE=bin/clock

obj/rls_%.o: src/%.c
	$(CC) $(RLS_FLAGS) -c $< -o $@

obj/dbg_%.o: src/%.c
	$(CC) $(DBG_FLAGS) -c $< -o $@

release: $(RLS_OBJECTS)
	$(CC) $(RLS_FLAGS) $(RLS_OBJECTS) -o $(EXE)

debug: $(DBG_OBJECTS)
	$(CC) $(DBG_FLAGS) $(DBG_OBJECTS) -o $(EXE)

run: $(EXE)
	./$(EXE)

clean:
	rm -f $(DBG_OBJECTS) $(RLS_OBJECTS) $(EXE)
