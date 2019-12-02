/*
   STM32GENERIC default config file
   2018 huaweiwx@sina.com
*/

#ifndef _HAL_DEFAULT_CONFIG_H_
#define _HAL_DEFAULT_CONFIG_H_

/***************  for freeRtos ****************/
#ifndef   portUSE_HEAP
#  define portUSE_HEAP 0  /*  port heap used heap_useNewlib */
#endif

#ifndef  configTOTAL_HEAP_SIZE
# define configTOTAL_HEAP_SIZE         (RAM_LENGTH/4)
#endif

#ifndef portTickUSE_TIMx
    #define portTickUSE_TIMx 0   /* 0 use systick*/
#else
# if (portTickUSE_TIMx !=0)
#   error "portTickUSE_TIMx be 0 omly"
# endif	
#endif


#endif /* _HAL_DEFAULT_CONFIG_H_ */
