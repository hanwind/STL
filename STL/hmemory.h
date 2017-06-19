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
		}else//含义重叠的部分
		{

			tmpdest = tmpdest + count;
			tempsrc = tempsrc + count;
			while(count--)
			{
				*--tmpdest = *--tempsrc;//注意下标问题
			}
		}
		return dest;//返回头指针
	}
}