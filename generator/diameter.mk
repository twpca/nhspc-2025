diameter: diameter.cpp
	$(CC) diameter.cpp $(CCARGS) -o diameter

run_diameter: 
	python3 diameter.py	1		0		1		0				--seed	55688	-o	1_01.in
	python3 diameter.py	200		400		1		0		-c		--seed	55688	-o	1_02.in
	python3 diameter.py	400		200		1		0				--seed	55688	-o	1_03.in
	python3 diameter.py	400		0		1		0				--seed	55688	-o	1_04.in
	python3 diameter.py	400		400		1		0		-c		--seed	55688	-o	1_05.in
	python3 diameter.py	400		400		1		0				--seed	55688	-o	1_06.in
	python3 diameter.py	400		399		1		0		-l		--seed	55688	-o	1_07.in
	python3 diameter.py	400		399		1		0		-c	-a	--seed	55688	-o	1_08.in
	python3 diameter.py	400		400		1		0		-C		--seed	55688	-o	1_09.in
	python3 diameter.py	400		400		1		0		-c		--seed	22258	-o	1_10.in
	python3 diameter.py	400		400		1		0		-c		--seed	22964	-o	1_11.in
	python3 diameter.py	250		340		1		0		-k	235	--seed	22964	-o	1_12.in
	python3 diameter.py	350		385		1		0		-k	340	--seed	22964	-o	1_13.in

	python3 diameter.py	1		0		1		0				--seed	55688	-o	2_01.in
	python3 diameter.py	1000	999		1000	999		-c	-a	--seed	55688	-o	2_02.in
	python3 diameter.py	1000	999		1000	999		-c	-a	--seed	55688	-o	2_03.in
	python3 diameter.py	1000	999		1000	999		-l		--seed	55688	-o	2_04.in
	python3 diameter.py	2000	1999	2000	1999	-c	-a	--seed	66688	-o	2_05.in
	python3 diameter.py	2000	1999	2000	1999	-c	-a	--seed	66688	-o	2_06.in
	python3 diameter.py	2000	1999	2000	1999	-l		--seed	66688	-o	2_07.in

	python3 diameter.py	1000	3000	1000	3000	-c		--seed	22964	-o	3_01.in
	python3 diameter.py	2000	4000	1		0		-c		--seed	22964	-o	3_02.in
	python3 diameter.py	2000	4000	1500	3000	-c		--seed	22964	-o	3_03.in
	python3 diameter.py	1850	3000	2000	4000	-c		--seed	22964	-o	3_04.in
	python3 diameter.py	2000	4000	2000	4000	-c		--seed	22964	-o	3_05.in
	python3 diameter.py	2000	4000	2000	4000			--seed	22964	-o	3_06.in
	python3 diameter.py	1500	1500	1700	1700	-C		--seed	22964	-o	3_07.in
	python3 diameter.py	2000	1999	2000	1999	-c	-a	--seed	22964	-o	3_08.in
	python3 diameter.py	2000	1999	2000	1500		-a	--seed	22964	-o	3_09.in
	python3 diameter.py	2000	1999	2000	1999	-l		--seed	22964	-o	3_10.in
	python3 diameter.py 500		3580	500		3580	-k 420	--seed	66999	-o	3_11.in	
	python3 diameter.py	2000	3710	2000	3710	-k 1940	--seed	66777	-o	3_12.in


	python3 diameter.py	1500	150000	1500	170000	-c		--seed	25854	-o	4_01.in
	python3 diameter.py	2000	300000	1850	10000	-c		--seed	25292	-o	4_02.in
	python3 diameter.py	1900	7000	2000	150000	-c		--seed	23343	-o	4_03.in
	python3 diameter.py	2000	300000	2000	5000	-c		--seed	22964	-o	4_04.in
	python3 diameter.py	2000	300000	1		0		-c		--seed	22222	-o	4_05.in
	python3 diameter.py	2000	300000	2000	300000	-c		--seed	22208	-o	4_06.in
	python3 diameter.py	2000	300000	2000	300000			--seed	25854	-o	4_07.in
	python3 diameter.py	1900	250000	1900	250000			--seed	25854	-o	4_08.in
	python3 diameter.py	2000	2000	2000	2000	-C		--seed	25854	-o	4_09.in
	python3 diameter.py	2000	1999	2000	1999	-c	-a	--seed	25854	-o	4_10.in
	python3 diameter.py	2000	1999	2000	1888		-a	--seed	25854	-o	4_11.in
	python3 diameter.py	2000	1999	2000	1999	-l		--seed	25854	-o	4_12.in
	python3 diameter.py 2000	4000000	2000	4000000	-c		--seed	66999	-o	4_13.in
	python3 diameter.py 2000	1710475	2000	1710475	-k 150	--seed	66999	-o	4_14.in	
	python3 diameter.py 2000	1530625	2000	1530625	-k 250	--seed	66999	-o	4_15.in	
	python3 diameter.py 2000	1043845	2000	1043845	-k 555	--seed	66999	-o	4_16.in	
	python3 diameter.py 2000	889777	2000	889777	-k 666	--seed	66999	-o	4_17.in	
	python3 diameter.py 2000	748030	2000	748030	-k 777	--seed	66999	-o	4_18.in	
	python3 diameter.py 2000	395827	2000	395827	-k 1111	--seed	66999	-o	4_19.in	
	./diameter -type=path -len=3 -ed1=1 -ed2=1 -n=2000 > 4_20.in
	./diameter -type=path -len=10 -ed1=1 -ed2=1 -n=2000 > 4_21.in
	./diameter -type=path -len=100 -ed1=1 -ed2=1 -n=2000 -large_sub=1 > 4_22.in
	./diameter -type=path -len=10 -ed1=2 -ed2=2 -n=1500 -large_sub=1 -fix_type=attach -s=1 > 4_23.in
	./diameter -type=path -len=20 -ed1=2 -ed2=2 -n=1400 -fix_type=attach -s=1 > 4_24.in
	./diameter -type=path -len=30 -ed1=3 -ed2=3 -n=1300 -large_sub=1 -fix_type=attach -s=1 > 4_25.in
	./diameter -type=path -len=40 -ed1=3 -ed2=3 -n=1400 -fix_type=attach -s=2  > 4_26.in
	./diameter -type=path -len=50 -ed1=4 -ed2=4 -n=1700 -large_sub=1 -fix_type=attach -s=2 > 4_27.in
	./diameter -type=path -len=100 -ed1=2 -ed2=2 -n=1500 -fix_type=attach -s=1 > 4_28.in
	./diameter -type=path -len=500 -ed1=1 -ed2=1 -n=1800 -fix_type=clique > 4_29.in
	./diameter -type=path -len=700 -ed1=50 -ed2=50 -n=2000 > 4_30.in
	./diameter -type=cycle -len=10 -ed=2 -n=2000 > 4_31.in
	./diameter -type=cycle -len=20 -ed=1 -n=2000 -large_sub=1 > 4_32.in
	./diameter -type=cycle -len=50 -ed=1 -n=2000 -large_sub=1 > 4_33.in
	./diameter -type=cycle -len=100 -ed=1 -n=2000 > 4_34.in
	./diameter -type=cycle -len=200 -ed=5 -n=2000 -large_sub=1 > 4_35.in
	./diameter -type=cycle -len=300 -ed=1 -n=2000 > 4_36.in
	./diameter -type=cycle -len=500 -ed=1 -n=2000 > 4_37.in
	./diameter -type=cycle -len=50 -ed=2 -n=1600 -fix_type=attach -s=1 > 4_38.in
	./diameter -type=cycle -len=50 -ed=2 -n=1500 -fix_type=attach -s=1 > 4_39.in
	./diameter -type=cycle -len=100 -ed=2 -n=1500 -fix_type=attach -s=1 > 4_40.in
	./diameter -type=cycle -len=100 -ed=2 -n=1300 -fix_type=attach -s=1 > 4_41.in
	./diameter -type=cycle -len=200 -ed=2 -n=1500 -fix_type=attach -s=1 > 4_42.in
	./diameter -type=cycle -len=200 -ed=2 -n=1300 -fix_type=attach -s=1 > 4_43.in
	./diameter -type=cycle -len=300 -ed=2 -n=1600 -fix_type=attach -s=1 > 4_44.in
	./diameter -type=cycle -len=300 -ed=2 -n=1500 -fix_type=attach -s=1 > 4_45.in
	./diameter -type=path -len=670 -ed1=3 -ed2=1329 -n=2000 > 4_46.in
	./diameter -type=handmade1 -n=2000 > 4_47.in
	./diameter -type=cycle -len=20 -ed=1 -n=2000 abc > 4_48.in
	./diameter -type=cycle -len=100 -ed=1 -n=2000 abc > 4_49.in
	./diameter -type=cycle -len=100 -ed=1 -n=2000 123 > 4_50.in
	./diameter -type=cycle -len=100 -ed=2 -n=1500 -fix_type=attach abc -s=1 > 4_51.in
	./diameter -type=cycle -stype=handmade1 -len=20 -ed=1 -n=2000 abc > 4_52.in
	./diameter -type=cycle -stype=handmade1 -len=20 -ed=1 -n=2000 123 > 4_53.in
	./diameter -type=cycle -stype=handmade1 -len=40 -ed=1 -n=2000 > 4_54.in
	./diameter -type=handmade2 -n=2000 abc > 4_55.in
	./diameter -type=handmade2 -n=2000 def > 4_56.in
	./diameter -type=handmade2 -n=2000 123 > 4_57.in
	./diameter -type=handmade2 -n=2000 456 > 4_58.in
	./diameter -type=handmade2 -n=2000 789 > 4_59.in
	./diameter -type=handmade3 -n=2000 -ed=1990 > 4_60.in
	./diameter -type=handmade2 -stype=handmade1 -n=2000 abc > 4_61.in
	./diameter -type=handmade2 -stype=handmade1 -n=2000 def > 4_62.in
	./diameter -type=handmade2 -stype=handmade1 -n=2000 123 > 4_63.in
	./diameter -type=handmade2 -stype=handmade1 -n=2000 456 > 4_64.in
	./diameter -type=handmade2 -stype=handmade1 -n=2000 789 > 4_65.in
