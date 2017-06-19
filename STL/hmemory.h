namespace han
{
	void *_memmove(void *dest,const void *src,size_t count)
	{
		char * tmpdest = (char *)dest;
		char * tempsrc = (char *)src;
		if(tmpdest <= tempsrc || tmpdest >= tempsrc+count)
		{
			while(count--)
			{
				*tmpdest++ = *tempsrc++; 
			}
		}else//�����ص��Ĳ���
		{

			tmpdest = tmpdest + count;
			tempsrc = tempsrc + count;
			while(count--)
			{
				*--tmpdest = *--tempsrc;//ע���±�����
			}
		}
		return dest;//����ͷָ��
	}
}