connections: connections.cpp
	$(CC) connections.cpp $(CCARGS) -o connections

run_connections: connections
	./connections random -n=100000 -k=1                > 1_01.in
	./connections random -n=92342  -k=1                > 1_02.in
	./connections random -n=100000 -k=1 -max_c=1000    > 1_03.in
	./connections random -n=100000 -k=1 -max_c=100000  > 1_04.in
	./connections slope  -n=100000 -k=1 -gap=100 -mid=49999 > 1_05.in
	./connections slope  -n=100000 -k=1 -gap=100 -mid=50000 > 1_06.in
	./connections slope  -n=99999  -k=1 -gap=100 -mid=49999 > 1_07.in
	./connections slope  -n=99999  -k=1 -gap=100 -mid=49998 > 1_08.in
	./connections slope  -n=99999  -k=1 -gap=100 -mid=50000 > 1_09.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-10 --rndsinr=10 --C=1500 seed=1 > 1_10.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-50 --rndsinr=50 --C=1500 seed=1 > 1_11.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-100 --rndsinr=100 --C=1500 seed=1 > 1_12.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-10 --rndsinr=10 --C=1000 --ratio=1.0 seed=1 > 1_13.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-50 --rndsinr=50 --C=1000 --ratio=1.0 seed=1 > 1_14.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-100 --rndsinr=100 --C=1000 --ratio=1.0 seed=1 > 1_15.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-10 --rndsinr=10 --C=3000 seed=1 > 1_16.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-50 --rndsinr=50 --C=3000 seed=1 > 1_17.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-100 --rndsinr=100 --C=3000 seed=1 > 1_18.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-10 --rndsinr=10 --C=5000 seed=1 > 1_19.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-50 --rndsinr=50 --C=5000 seed=1 > 1_20.in
	./connections cover_hack --n=100000 --k=1 --rndcosl=-10 --rndcosr=10 --rndsinl=-100 --rndsinr=100 --C=5000 seed=1 > 1_21.in
	./connections construct_hack --n=100000 --k=1 seed=1 > 1_22.in
	./connections construct_hack --n=100000 --k=1 --option=2 seed=1 > 1_23.in
	./connections random -n=20 -k=2                    > 2_01.in
	./connections random -n=4 -k=2                     > 2_02.in
	./connections random -n=20 -k=3                    > 2_03.in
	./connections random -n=20 -k=4                    > 2_04.in
	./connections random -n=20 -k=5                    > 2_05.in
	./connections random -n=20 -k=6                    > 2_06.in
	./connections random -n=20 -k=7                    > 2_07.in
	./connections random -n=20 -k=8                    > 2_08.in
	./connections random -n=20 -k=9                    > 2_09.in
	./connections random -n=20 -k=10                   > 2_10.in
	./connections random -n=20 -k=10 -max_c=100        > 2_11.in
	./connections long_path -k=10 -base_length=1       > 2_12.in
	./connections long_path -k=10 -base_length=100     > 2_13.in
	./connections slope  -n=20 -k=1 -gap=100 -mid=9    > 2_14.in
	./connections slope  -n=20 -k=1 -gap=100 -mid=10   > 2_15.in
	./connections slope  -n=19 -k=1 -gap=100 -mid=9    > 2_16.in
	./connections slope  -n=19 -k=1 -gap=100 -mid=10   > 2_17.in
	./connections slope  -n=4  -k=1 -gap=100 -mid=1    > 2_18.in
	./connections slope  -n=4  -k=1 -gap=100 -mid=2    > 2_19.in
	./connections grid -pattern_name=many_long_path -n=20 -d=150 -radius=10 -k=10 -num=3 -total_k=10 -distance=30 > 2_20.in
	./connections grid -pattern_name=many_long_path -n=20 -d=150 -radius=10 -k=10 -num=2 -total_k=10 -distance=30 > 2_21.in
	./connections grid -pattern_name=many_long_path -n=20 -d=150 -radius=10 -k=10 -num=1 -total_k=10 -distance=30 > 2_22.in
	./connections grid -pattern_name=flip_path -n=20 -d=100 -radius=10 -k=10 > 2_23.in
	./connections grid -pattern_name=flip_path -n=20 -d=100 -radius=10 -k=8  > 2_24.in
	./connections grid -pattern_name=many_flip_path -n=20 -d=100 -radius=10 -k=8 -num=2 -fix_k=4 -distance=30 > 2_25.in
	./connections random -n=3000 -k=2                  > 3_01.in
	./connections random -n=3000 -k=2 -max_c=100       > 3_02.in
	./connections random -n=3000 -k=2 -max_c=100000    > 3_03.in
	./connections grid -pattern_name=long_path -n=3000 -d=100 -radius=10 -k=2 -base_length=100 > 3_04.in
	./connections slope  -n=3000 -k=1 -gap=100 -mid=1499 > 3_05.in
	./connections slope  -n=3000 -k=1 -gap=100 -mid=1500 > 3_06.in
	./connections slope  -n=2999 -k=1 -gap=100 -mid=1499 > 3_07.in
	./connections slope  -n=2999 -k=1 -gap=100 -mid=1500 > 3_08.in
	./connections grid -pattern_name=many_long_path -n=3000 -d=1000 -radius=10 -k=2 -num=3 -total_k=20 -distance=30 > 3_09.in
	./connections construct_hack --n=3000 --k=2 seed=1 > 3_10.in
	./connections random -n=100000 -k=2                > 4_01.in
	./connections random -n=100000 -k=2 -max_c=1000    > 4_02.in
	./connections random -n=100000 -k=2 -max_c=100000  > 4_03.in
	./connections grid -pattern_name=long_path -n=100000 -d=100 -radius=10 -k=2 -base_length=100 > 4_04.in
	./connections grid -pattern_name=long_path -n=100000 -d=100 -radius=10 -k=2 -base_length=100 seed=1 > 4_05.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-10 --rndsinr=10 --C=1500 --ratio=0.95 seed=1 > 4_06.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-50 --rndsinr=50 --C=1500 --ratio=0.95 seed=1 > 4_07.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-100 --rndsinr=100 --C=1500 --ratio=0.95 seed=1 > 4_08.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-10 --rndsinr=10 --C=1000 --ratio=1.0 seed=1 > 4_09.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-50 --rndsinr=50 --C=1000 --ratio=1.0 seed=1 > 4_10.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-100 --rndsinr=100 --C=1000 --ratio=1.0 seed=1 > 4_11.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-10 --rndsinr=10 --C=3000 seed=1 > 4_12.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-50 --rndsinr=50 --C=3000 seed=1 > 4_13.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-100 --rndsinr=100 --C=3000 seed=1 > 4_14.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-10 --rndsinr=10 --C=5000 seed=1 > 4_15.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-50 --rndsinr=50 --C=5000 seed=1 > 4_16.in
	./connections cover_hack --n=100000 --k=2 --rndcosl=-10 --rndcosr=10 --rndsinl=-100 --rndsinr=100 --C=5000 seed=1 > 4_17.in
	./connections construct_hack --n=100000 --k=2 seed=1 > 4_18.in
	./connections construct_hack --n=100000 --k=2 --option=2 seed=1 > 4_19.in
	./connections random -n=3000 -k=15                 > 5_01.in
	./connections random -n=3000 -k=15 -max_c=100      > 5_02.in
	./connections random -n=3000 -k=15 -max_c=100000   > 5_03.in
	./connections grid -pattern_name=long_path -n=3000 -d=100 -radius=10 -k=15 -base_length=100 > 5_04.in
	./connections grid -pattern_name=many_long_path -n=3000 -d=1000 -radius=10 -k=15 -num=1 -total_k=20 -distance=30 > 5_05.in
	./connections grid -pattern_name=many_long_path -n=3000 -d=1000 -radius=10 -k=15 -num=2 -total_k=20 -distance=30 > 5_06.in
	./connections grid -pattern_name=many_long_path -n=3000 -d=1000 -radius=10 -k=15 -num=3 -total_k=20 -distance=30 > 5_07.in
	./connections grid -pattern_name=flip_path -n=3000 -d=100 -radius=10 -k=12 > 5_08.in
	./connections grid -pattern_name=flip_path -n=3000 -d=100 -radius=10 -k=14 > 5_09.in
	./connections grid -pattern_name=flip_path -n=3000 -d=100 -radius=10 -k=15 > 5_10.in
	./connections grid -pattern_name=many_flip_path -n=3000 -d=100 -radius=10 -k=8 -num=2 -fix_k=4 -distance=30 > 5_11.in
	./connections grid -pattern_name=many_flip_path -n=3000 -d=100 -radius=10 -k=12 -num=2 -fix_k=6 -distance=30 > 5_12.in
	./connections random -n=100000 -k=15               > 6_01.in
	./connections random -n=100000 -k=15 -max_c=1000   > 6_02.in
	./connections random -n=100000 -k=15 -max_c=100000 > 6_03.in
	./connections grid -pattern_name=long_path -n=100000 -d=10000 -radius=10 -k=12 -base_length=100 > 6_04.in
	./connections grid -pattern_name=long_path -n=100000 -d=10000 -radius=10 -k=13 -base_length=100 > 6_05.in
	./connections grid -pattern_name=long_path -n=100000 -d=100000 -radius=10 -k=14 -base_length=100 > 6_06.in
	./connections grid -pattern_name=long_path -n=100000 -d=100000 -radius=10 -k=15 -base_length=100 > 6_07.in
	./connections grid -pattern_name=many_long_path -n=100000 -d=10000 -radius=10 -k=15 -num=1 -total_k=20 -distance=30 > 6_08.in
	./connections grid -pattern_name=many_long_path -n=100000 -d=100000 -radius=10 -k=15 -num=2 -total_k=20 -distance=30 > 6_09.in
	./connections grid -pattern_name=many_long_path -n=100000 -d=10000 -radius=10 -k=15 -num=3 -total_k=20 -distance=30 > 6_10.in
	./connections grid -pattern_name=many_long_path -n=100000 -d=100000 -radius=10 -k=15 -num=3 -total_k=20 -distance=30 > 6_11.in
	./connections grid -pattern_name=flip_path -n=100000 -d=10000 -radius=10 -k=12 > 6_12.in
	./connections grid -pattern_name=flip_path -n=100000 -d=100000 -radius=10 -k=14 > 6_13.in
	./connections grid -pattern_name=flip_path -n=100000 -d=100000 -radius=10 -k=15 > 6_14.in
	./connections grid -pattern_name=many_flip_path -n=100000 -d=100000 -radius=10 -k=12 -num=2 -fix_k=6 -distance=30 > 6_15.in
	./connections grid -pattern_name=many_flip_path -n=100000 -d=10000 -radius=10 -k=8 -num=2 -fix_k=4 -distance=30 > 6_16.in
	./connections random -n=100000 -k=18               > 7_01.in
	./connections random -n=100000 -k=18 -max_c=1000   > 7_02.in
	./connections random -n=100000 -k=18 -max_c=100000 > 7_03.in
	./connections grid -pattern_name=long_path -n=100000 -d=100000 -radius=10 -k=16 -base_length=100 > 7_04.in
	./connections grid -pattern_name=long_path -n=100000 -d=10000 -radius=10 -k=17 -base_length=100 > 7_05.in
	./connections grid -pattern_name=long_path -n=100000 -d=100000 -radius=10 -k=18 -base_length=100 > 7_06.in
	./connections grid -pattern_name=many_long_path -n=100000 -d=100000 -radius=10 -k=16 -num=2 -total_k=20 -distance=40 > 7_07.in
	./connections grid -pattern_name=many_long_path -n=100000 -d=10000 -radius=10 -k=17 -num=2 -total_k=20 -distance=40 > 7_08.in
	./connections grid -pattern_name=many_long_path -n=98787 -d=100000 -radius=10 -k=18 -num=1 -total_k=20 -distance=40 > 7_09.in
	./connections grid -pattern_name=many_long_path -n=100000 -d=10000 -radius=10 -k=18 -num=2 -total_k=20 -distance=40 > 7_10.in
	./connections grid -pattern_name=many_long_path -n=89324 -d=10000 -radius=10 -k=18 -num=3 -total_k=20 -distance=40 > 7_11.in
	./connections grid -pattern_name=many_long_path -n=92233 -d=100000 -radius=10 -k=18 -num=4 -total_k=50 -distance=50 > 7_12.in
	./connections grid -pattern_name=flip_path -n=100000 -d=10000 -radius=10 -k=16 > 7_13.in
	./connections grid -pattern_name=flip_path -n=100000 -d=100000 -radius=10 -k=17 > 7_14.in
	./connections grid -pattern_name=flip_path -n=100000 -d=100000 -radius=10 -k=18 > 7_15.in
	./connections grid -pattern_name=many_flip_path -n=100000 -d=100000 -radius=10 -k=16 -num=2 -fix_k=8 -distance=40 > 7_16.in
