#include "testlib.h"
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <set>
#include <cassert>

class Testcase {
public:
	int n, k;
    std::vector<std::pair<int, int>> a;
    Testcase(int _n = 0, int _k = 0): n(_n), k(_k), a(n) {}
    void print() {
        std::ios::sync_with_stdio(0), std::cin.tie(0); 
        std::cout << n << " " << k << "\n";
        for (auto [l, r] : a)
            std::cout << l << " " << r << "\n";
    }
};

Testcase generator_random()
{
    int n=opt<int>("n");
    int k=opt<int>("k");
    int min_c=opt<int>("min_c");
    int max_c=opt<int>("max_c");
    auto testcase=Testcase(n, k);
	auto &a=testcase.a;

	for(int i=0;i<n;i++)
	{
		int l=rnd.next(min_c,max_c);
		int r=rnd.next(min_c,max_c);
		if(l>r) std::swap(l,r);
		a[i]=std::make_pair(l,r);
	}

	return testcase;
}
Testcase generator_random_s3()
{
    int n=opt<int>("n");
    int k=opt<int>("k");
    int min_c=opt<int>("min_c");
    int max_c=opt<int>("max_c");
    auto testcase=Testcase(n, k);
	auto &a=testcase.a;

	for(int i=0;i<n;i++)
	{
		int x=rnd.next(min_c,max_c);
		a[i]=std::make_pair(x,x);
	}

	return testcase;
}

Testcase generator_bounded()
{
    int n=opt<int>("n");
    int k=opt<int>("k");
    int min_c=opt<int>("min_c");
    int max_c=opt<int>("max_c");
	int len=opt<int>("len");
    auto testcase=Testcase(n, k);
	auto &a=testcase.a;

	for(int i=0;i<n;i++)
	{
		int d=rnd.next(1,len);
		int l=rnd.next(min_c,max_c-d+1);
		int r=l+d-1;
		a[i]=std::make_pair(l,r);
	}

	return testcase;
}
Testcase generator_max() // TODO: support len = 1
{
	int n=opt<int>("n");
	int k=opt<int>("k");
	int min_c=opt<int>("min_c");
	int max_c=opt<int>("max_c");

	auto testcase=Testcase(n,k);
	auto &a=testcase.a;

	int cnt=(n+k-1)/k;
	assert(max_c-min_c+1>=cnt*2); // easier to generate
	for(int b=0;b<n;b+=cnt)
	{
		int need=std::min(n,b+cnt)-b;
		std::set<int> s;
		for(int i=0;i<need-1;i++)
		{
			while((int)s.size()==i)
			{
				int x=rnd.next(min_c+1,max_c);
				s.insert(x);
			}
		}
		int cur=min_c;
		std::vector<std::pair<int,int> > tmp;
		for(auto x:s)
		{
			tmp.push_back(std::make_pair(cur,x-1));
			cur=x;
		}
		tmp.push_back(std::make_pair(cur,max_c));
		for(int i=1;i<(int)tmp.size();i++)
		{
			int j=rnd.next(0,i);
			if(j<i) std::swap(tmp[i],tmp[j]);
		}
		for(int i=0;i<(int)tmp.size();i++)
		{
			a[b+i]=tmp[i];
		}
	}

	return testcase;
}
Testcase generator_min()
{
	int n=opt<int>("n");
	int k=opt<int>("k");
	int min_c=opt<int>("min_c");
	int max_c=opt<int>("max_c");

	auto testcase=Testcase(n,k);
	auto &a=testcase.a;

	for(int i=0;i<n;i++)
	{
		a[i]=std::make_pair(min_c,max_c);
	}

	return testcase;
}


int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    std::string generator_str = argv[1];
    std::map<std::string, std::function<Testcase()>> generator_func;
    generator_func["random"] = generator_random;
	generator_func["random_s3"] = generator_random_s3;
	generator_func["bounded"] = generator_bounded;
	generator_func["max"] = generator_max;
	generator_func["min"] = generator_min;

    auto testcase = generator_func[generator_str]();
    testcase.print();
}

