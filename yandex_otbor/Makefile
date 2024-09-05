../build/bap2: bap2.cpp
	g++ bap2.cpp -O3 --std=c++20 -fsanitize=address,undefined -D_GLIBCXX_DEBUG{,_PEDANTIC} -DSEREGA -o ../build/bap2

run: ../build/bap2
	../build/bap2
