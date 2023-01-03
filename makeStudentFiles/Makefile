main.x: main.o DepGraph.o MakeTree.o systemInterface.o Token.o Tokenizer.o
	g++ -std=c++17 main.o DepGraph.o MakeTree.o systemInterface.o Token.o Tokenizer.o -o main.x

main.o: main.cpp DepGraph.hpp MakeTree.hpp TreeNode.hpp GraphNode.hpp systemInterface.hpp Token.hpp
	g++ -std=c++17 -c main.cpp -o main.o 

DepGraph.o: DepGraph.cpp DepGraph.hpp MakeTree.hpp TreeNode.hpp GraphNode.hpp systemInterface.hpp Tokenizer.hpp Token.hpp
	g++ -std=c++17 -c DepGraph.cpp -o DepGraph.o

MakeTree.o: MakeTree.cpp MakeTree.hpp TreeNode.hpp GraphNode.hpp systemInterface.hpp
	g++ -std=c++17 -c MakeTree.cpp -o MakeTree.o

systemInterface.o: systemInterface.cpp systemInterface.hpp
	g++ -std=c++17 -c systemInterface.cpp -o systemInterface.o

Token.o: Token.cpp Token.hpp
	g++ -std=c++17 -c Token.cpp -o Token.o

Tokenizer.o: Tokenizer.cpp Tokenizer.hpp Token.hpp
	g++ -std=c++17 -c Tokenizer.cpp -o Tokenizer.o

clean:
	rm -fr main.x *.o
