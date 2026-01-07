chomp: chomp.cpp
	$(CC) chomp.cpp $(CCARGS) -o chomp

run_chomp: chomp
	./chomp -cls=1 -cases=10 -seed=8C926444148860C0
	./chomp -cls=2 -cases=30 -seed=480C085FA49FFA38
	./chomp -cls=3 -cases=30 -seed=5A1BFE297AEF1302