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
	new_handler global_hander = std::set_new_handler(current_hander);//���ȵ��ñ�׼��set_new_handler���Զ���ר����Ĵ�����
	void *memory = NULL;
	try{
		memory = ::operator new(size);//����global operator new��ִ��ʵ�ʵ��ڴ���䡣����ڴ����ʧ�ܣ��ղű���װ��new_handler��������

	}catch(std::bad_alloc)//���۳ɹ�ʧ�ܶ���Ҫ�ָ� ȫ�ֵ�
	{
		std::set_new_handler(global_hander);
		throw;
	}
	std::set_new_handler(global_hander);//����new�ɹ�����ʧ�ܣ������������Զ����operator new����ǰ�ָ�ȫ��new_handler
	return memory;
}
};
void handlerFunc()
{
	std::cout<<"bad memory"<<std::endl;
}
new_handler A::current_hander = NULL;