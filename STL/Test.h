#include <iostream>
#include "Foo.h"
#include "hmemory.h"
#include <vector>
#include <deque>
#include <algorithm>
#include <stack>
#include <list>
#include <queue>

#include "RBTree.h"
using namespace std;
namespace test
{
	#define N 10
	void fun1()
	{
		std::cout<<"------------测试目的是 placement new的用法---------------"<<std::endl;
		std::cout<<"------------时间：2017/4/15------------------------------"<<std::endl;
		char * buff = new char[sizeof(Foo)*N];//1）分配内存
		memset(buff,0,sizeof(Foo)*N);

		Foo *pfoo = new(buff)Foo;//构建对象
		pfoo->print();
		pfoo->set_f(1.0f);
		pfoo->get_f();
		pfoo->~Foo();//析构对象，显式的调用类的析构函数
		delete [] buff;//销毁内存
	}
	void fun2()
	{
		std::cout<<"------------测试目的是 memove 及 memcpy 的用法---------------"<<std::endl;
		std::cout<<"------------时间：2017/4/19------------------------------"<<std::endl;
		char s[] = "1234567890";
		char * p1 = s;
		char * p2 = s+2;
		memcpy(p2,p1,5);
		for(int i = 0;i < 5;++i)
			printf("%c ",p2[i]);//1 2 3 4 5
		printf("\n");
		memmove(p2,p1,5);//没有办法知道传递给他的内存区域的情况，所以应该使用memmove()函数
		for(int i = 0;i < 5;++i)
			printf("%c ",p2[i]);//1 2 1 2 3
	}
	void fun3()
	{
		std::cout<<"------------测试目的 自己实现memove ---------------"<<std::endl;
		std::cout<<"------------时间：2017/4/19------------------------------"<<std::endl;
		char s[] = "1234567890";
		char * p1 = s;
		char * p2 = s+2;
		han::_memmove(p2,p1,5);
		for (int i = 0;i < 5;++i)
		{
			printf("%c ",p2[i]);
		}
	}
	void fun4()
	{
		std::cout<<"------------测试目的 vector的元素析构 ---------------"<<std::endl;
		std::cout<<"------------时间：2017/4/19------------------------------"<<std::endl;
		std::vector<Foo *> foos(5);
		foos.push_back(new Foo());
		foos.pop_back();
		//std::vector<Foo *>::iterator it = foos.begin();
		//for(;it != foos.end();++it)
		//{
		//	std::cout<<&(it)<<std::endl;
	//	}
		//foos.clear();
	}
	void fun5()
	{
		std::cout<<"------------测试目的 deque的元素析构 ---------------"<<std::endl;
		std::cout<<"------------时间：2017/4/19------------------------------"<<std::endl;
		std::deque<int> ideq(20,9);
		std::deque<int>::iterator it = ideq.begin();
		//for(;it != ideq.end();++it)
			//std::cout<<*it<<std::endl;
		it = find(ideq.begin(),ideq.end(),9);
		std::cout<<*it<<std::endl;
	}
	void fun6()
	{
		std::cout<<"------------测试目的 stack ---------------"<<std::endl;
		std::cout<<"------------时间：2017/4/20------------------------------"<<std::endl;
		std::stack<int,std::list<int> > istack;
		istack.push(3);
		istack.push(4);
		std::cout<<istack.size()<<std::endl;
		std::cout<<istack.top()<<std::endl;

	}
	void fun7() 
	{
		std::cout<<"------------测试目的优先队列 ---------------"<<std::endl;
		std::cout<<"------------时间：2017/4/21------------------------------"<<std::endl;
		int ia[9]={0,1,2,3,4,8,9,3,5};
		priority_queue<int> ipq(ia,ia+9);
		for(int i = 0;i < ipq.size();++i)
			cout<<ipq.top()<<endl;
		while(!ipq.empty())
		{
			cout<<ipq.top()<<" ";
			ipq.pop();
		}
		cout<<endl;
	}
	void TestRBTree()
	{
		std::cout<<"------------测试目的红黑树 ---------------"<<std::endl;
		std::cout<<"------------时间：2017/6/20------------------------------"<<std::endl;
		HanSTL::RBTree<int,int> RBT;
		int arr[10] = {1,2,3,5,12,16,18,26,99,666};
		bool tag =false;
		for (int i = 0;i < 10;++i)
		{
			tag = RBT.insert(arr[i],i);
			tag =false;
		}
		RBT.InOrder();
		std::cout<<std::endl;
		std::cout<<"isRBTree"<<RBT.isRBTree()<<std::endl;
		std::cout<<std::endl;
	}
}
