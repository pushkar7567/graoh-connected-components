CC=g++
OBJS= graph_concepts graph_concepts.o digraph.o
CFLAGS=-c -Wall -O2
PROGRAM=prog

PROGRAM: $(OBJS)

graph_concepts: graph_concepts.o
	$(CC) graph_concepts.o -o graph_concepts

graph_concepts.o: graph_concepts.cpp
	$(CC) graph_concepts.cpp -o graph_concepts.o $(CFLAGS)

digraph.o: digraph.cpp
	$(CC) digraph.cpp -o digraph.o $(CFLAGS)	

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)

