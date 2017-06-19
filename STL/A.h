#include <stdio.h>
#include <iostream>
class A
{
	int m_value;
	static new_handler current_hander;
public:
	A(int value):m_value(value * value){}
	void Func(){
		printf("m_value = %d\n",m_value);

	}
	static new_handler set_new_handler(new_handler p)
	{
		new_handler old_hander = current_hander;
		current_hander = p;
		return old_hander;
	}
void *operator new(size_t size)
{
	printf("operator new called\n");
	new_handler global_hander = std::set_new_handler(current_hander);//首先调用标准的set_new_handler，自定义专属类的处理函数
	void *memory = NULL;
	try{
		memory = ::operator new(size);//调用global operator new，执行实际的内存分配。如果内存分配失败，刚才被安装的new_handler将被调用

	}catch(std::bad_alloc)//无论成功失败都需要恢复 全局的
	{
		std::set_new_handler(global_hander);
		throw;
	}
	std::set_new_handler(global_hander);//无论new成功还是失败，都必须在类自定义的operator new结束前恢复全局new_handler
	return memory;
}
};
void handlerFunc()
{
	std::cout<<"bad memory"<<std::endl;
}
new_handler A::current_hander = NULL;