datacenter: datacenter.cpp
	$(CC) datacenter.cpp $(CCARGS) -o datacenter

run_datacenter: datacenter
	./datacenter -n=100 -m=30000 -d=1 -c=10000000 -treetype=none -edgetype=random -weighttype=random -timetype=random > 1_01.in
	./datacenter -n=10000 -m=300000 -d=1 -c=1000000000 -treetype=none -edgetype=random -weighttype=random -timetype=random > 1_02.in
	./datacenter -n=100000 -m=300000 -d=1 -c=1000000000 -treetype=none -edgetype=random -weighttype=random -timetype=random > 1_03.in
	./datacenter -n=100000 -m=300000 -d=1 -c=1000000000 -treetype=line -treeweightl=0 -treeweightr=1 -edgetype=random -weighttype=random -timetype=random > 1_04.in
	./datacenter -n=100000 -m=300000 -d=1 -c=1000000000 -treetype=star -treeweightl=0 -treeweightr=1 -edgetype=random -weighttype=random -timetype=random > 1_05.in


	./datacenter -n=10 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=random -weighttype=random -timetype=end -distinct=1 > 2_01.in
	./datacenter -n=10 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=random -weighttype=random -timetype=end > 2_02.in
	./datacenter -n=10 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=random -weighttype=decreasing -timetype=end -distinct=1 > 2_03.in
	./datacenter -n=100 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=random -weighttype=random -timetype=end -distinct=1 > 2_04.in
	./datacenter -n=100 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=random -weighttype=random -timetype=end > 2_05.in
	./datacenter -n=100 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=random -weighttype=decreasing -timetype=end -distinct=1 > 2_06.in


	./datacenter -n=10000 -m=300000 -d=300000 -c=1000000000 -treetype=random -treeweightl=80 -treeweightr=100 -edgetype=random -weighttype=random -timetype=end -distinct=1 > 3_01.in
	./datacenter -n=10000 -m=300000 -d=300000 -c=1000000000 -treetype=line -edgetype=random -weighttype=random -timetype=end > 3_02.in
	./datacenter -n=10000 -m=300000 -d=300000 -c=1000000000 -treetype=line -treeweightl=90 -treeweightr=100 -edgetype=random -weighttype=random -timetype=end -distinct=1 > 3_03.in
	./datacenter -n=50000 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=random -weighttype=random -timetype=end -distinct=1 > 3_04.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=random -edgetype=random -weighttype=random -timetype=end > 3_05.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=random -treeweightl=90 -treeweightr=100 -edgetype=random -weighttype=random -timetype=end -distinct=1 > 3_06.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=line -edgetype=random -weighttype=random -timetype=end > 3_07.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=line -treeweightl=80 -treeweightr=100 -edgetype=random -weighttype=random -timetype=end -distinct=1 > 3_08.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=prim1 -treev=100 -treeweightl=99 -treeweightr=100 -edgetype=random -weighttype=random -timetype=end -distinct=1 > 3_09.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=prim2 -treev=100 -treeweightl=99 -treeweightr=100 -edgetype=random -weighttype=random -timetype=end -distinct=1 > 3_10.in

	
	./datacenter -n=200 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=random -weighttype=random -timetype=random -mxlen=1000 > 4_01.in
	./datacenter -n=1000 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=random -weighttype=random -timetype=random -mxlen=7000 > 4_02.in
	./datacenter -n=1000 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=random -weighttype=random -timetype=random -mxlen=10000 > 4_03.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=random -weighttype=random -timetype=random -mxlen=10000 > 4_04.in
	./datacenter -n=10000 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect -block=10000 > 4_05.in
	./datacenter -n=10000 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect -block=30000 > 4_06.in
	./datacenter -n=50000 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect -block=50000 > 4_07.in
	./datacenter -n=50000 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect -block=100000 > 4_08.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect -block=100000 > 4_09.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect > 4_10.in


	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=random -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=random -mxlen=100000 > 5_01.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=random -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=random > 5_02.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=random -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=distinct > 5_03.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=random -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=random > 5_04.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=random -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=distinct > 5_05.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=random -weightl=0 -weightr=10 -edgetype=random -weighttype=random -timetype=random > 5_06.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=line -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=distinct > 5_07.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=line -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=random -mxlen=1000 > 5_08.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=star -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=distinct > 5_09.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=star -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=random -mxlen=10000 > 5_10.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=prim1 -treev=100 -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=distinct > 5_11.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=prim1 -treev=100 -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=random -mxlen=1000 > 5_12.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=prim1 -treev=87 -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=distinct > 5_13.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=prim2 -treev=100 -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=distinct > 5_14.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=prim2 -treev=100 -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=distinct > 5_15.in
	./datacenter -n=100000 -m=300000 -d=300000 -c=1000000000 -treetype=prim2 -treev=500 -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=random -mxlen=100 > 5_16.in
	./datacenter -n=5000 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect -block=10000 > 5_17.in
	./datacenter -n=5000 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect -block=30000 > 5_18.in
	./datacenter -n=30000 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect -block=50000 > 5_19.in
	./datacenter -n=50000 -m=300000 -d=300000 -c=1000000000 -treetype=none -edgetype=connected -weighttype=random -timetype=intersect -block=100000 > 5_20.in
	./datacenter -n=50000 -m=300000 -d=300000 -c=1000000000 -treetype=random -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=random > 5_21.in
	./datacenter -n=50000 -m=300000 -d=300000 -c=1000000000 -treetype=line -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=random -mxlen=10000 > 5_22.in
	./datacenter -n=50000 -m=300000 -d=300000 -c=1000000000 -treetype=random -weightl=90 -weightr=100 -edgetype=random -weighttype=random -timetype=distinct > 5_23.in
	./datacenter -n=30000 -m=300000 -d=300000 -c=1000000000 -treetype=line -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=random -mxlen=10000 > 5_24.in
	./datacenter -n=10000 -m=300000 -d=300000 -c=1000000000 -treetype=random -weightl=40 -weightr=60 -edgetype=random -weighttype=random -timetype=random -mxlen=5000 > 5_25.in
