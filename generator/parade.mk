parade: parade.cpp
	$(CC) parade.cpp $(CCARGS) -o parade

run_parade: parade
	./parade random		-n=48763	-k=1	-min_c=1	-max_c=1000000000					> 1_01.in
	./parade random		-n=100000	-k=1	-min_c=1	-max_c=1000000000					> 1_02.in
	./parade bounded	-n=100000	-k=1	-min_c=1	-max_c=1000000000	-len=100		> 1_03.in
	./parade bounded	-n=100000	-k=1	-min_c=1	-max_c=1000000000	-len=1000		> 1_04.in
	./parade bounded	-n=100000	-k=1	-min_c=1	-max_c=1000000000	-len=10000		> 1_05.in
	./parade max		-n=100000	-k=1	-min_c=1	-max_c=1000000000					> 1_06.in
	./parade max		-n=100000	-k=1	-min_c=998	-max_c=244353						> 1_07.in
	./parade min		-n=100000	-k=1	-min_c=1	-max_c=1000000000					> 1_08.in
	./parade min		-n=100000	-k=1	-min_c=123456	-max_c=98765432					> 1_09.in
	./parade random		-n=1		-k=1	-min_c=1	-max_c=1000000000					> 1_10.in
	./parade random		-n=5		-k=5	-min_c=1	-max_c=10							> 2_01.in
	./parade random		-n=20		-k=20	-min_c=1	-max_c=20							> 2_02.in
	./parade random		-n=500		-k=20	-min_c=1	-max_c=1000000000					> 2_03.in
	./parade bounded	-n=500		-k=20	-min_c=1	-max_c=1000000000	-len=1000		> 2_04.in
	./parade bounded	-n=500		-k=20	-min_c=1	-max_c=1000000000	-len=10000		> 2_05.in
	./parade bounded	-n=500		-k=20	-min_c=1	-max_c=1000000000	-len=100000		> 2_06.in
	./parade max		-n=500		-k=20	-min_c=1	-max_c=1000000000					> 2_07.in
	./parade max		-n=500		-k=20	-min_c=998	-max_c=244353						> 2_08.in
	./parade min		-n=500		-k=20	-min_c=1	-max_c=1000000000					> 2_09.in
	./parade min		-n=500		-k=20	-min_c=1234567	-max_c=67384721					> 2_10.in
	./parade random		-n=1		-k=1	-min_c=1	-max_c=1000000000					> 2_11.in
	./parade bounded	-n=100000	-k=20	-min_c=1	-max_c=100000		-len=1			> 3_01.in
	./parade bounded	-n=100000	-k=20	-min_c=1	-max_c=1000			-len=1			> 3_02.in
	./parade bounded	-n=100000	-k=20	-min_c=1	-max_c=2000			-len=1			> 3_03.in
	./parade bounded	-n=100000	-k=20	-min_c=1	-max_c=5000			-len=1			> 3_04.in
	./parade bounded	-n=100000	-k=20	-min_c=1	-max_c=10000		-len=1			> 3_05.in
	./parade min		-n=100000	-k=20	-min_c=48763	-max_c=48763					> 3_06.in
	./parade random_s3	-n=1		-k=1	-min_c=1	-max_c=100000						> 3_07.in
	./parade random_s3	-n=5		-k=5	-min_c=1	-max_c=100000						> 3_08.in
	./parade random_s3	-n=500		-k=20	-min_c=1	-max_c=100000						> 3_09.in
	./parade random_s3	-n=100000	-k=20	-min_c=1	-max_c=100000						> 3_10.in
	./parade random_s3	-n=100000	-k=20	-min_c=1	-max_c=10000						> 3_11.in
	./parade random_s3	-n=100000	-k=20	-min_c=1	-max_c=1000							> 3_12.in
	./parade random_s3	-n=100000	-k=20	-min_c=1	-max_c=100							> 3_13.in
	./parade random		-n=100000	-k=20	-min_c=1	-max_c=1000000000					> 4_01.in
	./parade bounded	-n=100000	-k=20	-min_c=1	-max_c=1000000000	-len=1000		> 4_02.in
	./parade bounded	-n=100000	-k=20	-min_c=1	-max_c=1000000000	-len=10000		> 4_03.in
	./parade bounded	-n=100000	-k=20	-min_c=1	-max_c=1000000000	-len=100000		> 4_04.in
	./parade max		-n=100000	-k=20	-min_c=1	-max_c=1000000000					> 4_05.in
	./parade max		-n=100000	-k=20	-min_c=998	-max_c=244353						> 4_06.in
	./parade min		-n=100000	-k=20	-min_c=1	-max_c=1000000000					> 4_07.in
	./parade min		-n=100000	-k=20	-min_c=998	-max_c=244353						> 4_08.in


