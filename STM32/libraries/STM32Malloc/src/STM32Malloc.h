
#ifndef __STM32MALLOC_H__
#define __STM32MALLOC_H__

class MALLOCClass
{
  private:
	uint8_t*  memBase;				//内存池 管理SRAMBANK个区域的内存
    const uint32_t memSize;         //内存总大小
    const uint32_t memBlockSize;;   //内存分块大小
	uint8_t   memReady = 0; 		//内存管理是否就绪
    uint32_t  memMapSize;           //内存管理状态表大小

  public:
    uint16_t* pMemMap = NULL; 		//内存管理状态表

    MALLOCClass(uint8_t* memBase, const uint32_t memSize, const uint32_t memBlockSize = 32)
	           : memBase(memBase),memSize(memSize),memBlockSize(memBlockSize)
		 {
		 }

	uint8_t Init(void){
		if(memReady) return HAL_OK;
		memMapSize = memSize / memBlockSize;		   
		pMemMap = (uint16_t*) malloc(memMapSize * 2);
		if (pMemMap != NULL) {
            myMemSet(pMemMap, 0, memMapSize * 2); //内存状态表数据清零
            myMemSet(memBase, 0, memSize);   //内存池所有数据清零
			memReady =1;
			return HAL_OK;
		}
		return 1;
	}
	
    //size:内存大小(字节)
    //返回值:分配到的内存首地址.
    void* alloc(uint32_t size)
    {
      uint32_t offset;
      offset = myMemMalloc(size);
      if (offset == (uint32_t)0xFFFF'FFFF) 
		  return NULL;
      else 
		  return (void *)((uint32_t)memBase + offset);
    }

    //释放内存
    //ptr:内存首地址
    void free(void *ptr)
    {
      if (ptr){
        uint32_t offset = (uint32_t)ptr - (uint32_t) memBase;
        myMemFree(offset); //释放内存
	  }
    }

    //*ptr:旧内存首地址
    //size:要分配的内存大小(字节)
    //返回值:新分配到的内存首地址.
    void *realloc(void *ptr, uint32_t size)
    {
      uint32_t offset = this->myMemMalloc(size);
      if (offset == (uint32_t)0xFFFF'FFFF){
		  return NULL;
	  }
	  else
      {
        this->myMemCpy((void*)((uint32_t)memBase + offset), ptr, size); //拷贝旧内存内容到新内存
        this->free(ptr);                            //释放旧内存
        return (void *)((uint32_t)memBase + offset);        //返回新内存首地址
      }
    }

    //获取内存使用率
    //返回值:使用率(0~100)
    uint8_t perused(void)
    {
      uint32_t used = 0;
      uint32_t i;
      for (i = 0; i < memMapSize; i++)
      {
        if (pMemMap[i])  used++;
      }
      return (used * 100) / memMapSize;
    }


  private:
    //复制内存
    //*des:目的地址
    //*src:源地址
    //n:需要复制的内存长度(字节为单位)
    void myMemCpy(void *des,void *src, uint32_t n)  
    {  
        volatile uint8_t *xdes = (uint8_t*)des;
    	volatile uint8_t *xsrc = (uint8_t*)src; 
        while(n--) *xdes++ = *xsrc++;  
    }  

    //设置内存
    //*s:内存首地址
    //c :要设置的值
    //count:需要设置的内存大小(字节为单位)
    void myMemSet(void *s,uint8_t c,uint32_t count)  
    {  
        volatile uint8_t *xs = (uint8_t *)s;  
        while(count--)*xs++=c;  
    }	   
	
    //内存分配(内部调用)
    //size:要分配的内存大小(字节)
    //返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址
    uint32_t myMemMalloc(uint32_t size)
    {
      int offset = 0;
      uint32_t nmemb; //需要的内存块数
      uint32_t cmemb = 0; //连续空内存块数
      uint32_t i;
      if (!memReady) Init(); //未初始化,先执行初始化
      if (size == 0) return 0XFFFFFFFF; //不需要分配
      nmemb = size / memBlockSize; //获取需要分配的连续内存块数
      if (size % memBlockSize) nmemb++;

      for (offset = memMapSize - 1; offset >= 0; offset--) //搜索整个内存控制区
      {

	   if (pMemMap[offset]==0) cmemb++; //连续空内存块数增加
       else cmemb = 0;             //连续内存块清零

        if (cmemb == nmemb)           //找到了连续nmemb个空内存块
        {
          for (i = 0; i < nmemb; i++)     //标注内存块非空
          {
            pMemMap[offset + i] = nmemb;
          }
          return (memBlockSize * offset ); //返回偏移地址
        }
      }
      return 0xFFFF'FFFF;//未找到符合分配条件的内存块
    }

    //释放内存(内部调用)
    //offset:内存地址偏移
    //返回值:0,释放成功;1,释放失败, 2 偏移超区了
    uint8_t myMemFree(uint32_t offset)
    {
      int i;
      if (!memReady) //未初始化,先执行初始化
      {
        Init();
        return 1;//未初始化
      }
      if (offset < memSize) //偏移在内存池内.
      {
        int index = offset / memBlockSize;  //偏移所在内存块号码
        int nmemb = pMemMap[index]; //内存块数量
        for (i = 0; i < nmemb; i++)       //内存块清零
        {
          pMemMap[index + i] = 0;
        }
        return 0;
      }
	  return 2;//偏移超区了.
    }

};

#endif /* __STM32MALLOC_H__ */

/***********************END OF FILE ****************************/

