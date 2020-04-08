# Author Xiao Hu
# Created on 02/04/2020
obj = hashtagcounter.o FibonacciHeap.o

hashtagcounter: $(obj)
	g++ -o hashtagcounter $(obj)
	
hashtagcounter.o: hashtagcounter.cpp FibonacciHeap.h
	g++ -std=c++11 -static -c hashtagcounter.cpp
	
FibonacciHeap.o: FibonacciHeap.cpp FibonacciHeap.h
	g++ -std=c++11 -static -c FibonacciHeap.cpp
clean:
	rm -rf $(obj) output_file*.txt hashtagcounter
