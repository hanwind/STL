#include <iostream>
class B
{
public:
	B(){std::cout<<"B"<<std::endl;}
};
class Foo
{
	char cc;
	float f;
	B *b;
	
public:
	Foo(){
		b = new B();
		std::cout<<"construct Foo"<<std::endl;}
	Foo(const Foo& foo){std::cout<<"copy Foo"<<std::endl;}
	~Foo(){std::cout<<" destory Foo"<<std::endl;}
	void print(){
		std::cout<<"ADDR: "<<this<<std::endl;
	}
	void set_f( float _f ) { 
		std::cout << "set f val : " << _f << std::endl;
		f = _f;
	}
	void get_f() {
		std::cout << "get f val : " << f << std::endl;
	}

};