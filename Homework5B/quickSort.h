void quickSort(int *ptr, int begin, int end)  
{  
    int temp = *(ptr + begin);//设置初始比较基准数据  
    int i = begin + 1, j = end, curPosition = begin;//定义开头和结尾的I j  
    bool direction = false;  
    while(i <= j)  
    {  
        if(direction)  
        {  
            if(*(ptr + i) > temp)//如果当前数据小于基准数据 那么换位置 改当前位置  
            {  
                *(ptr + curPosition) = *(ptr + i);  
                curPosition = i;  
                direction = false;  
            }  
            i++;  
        }else//先从后到前比较数据  
        {  
            if(*(ptr + j) < temp)//如果最后一个大于基准 那么最后一个数据赋值给当前基准数据的那个位置 调整基准数据的位置  
            {  
                *(ptr + curPosition) = *(ptr + j);//  
                curPosition = j;  
                direction = true;  
            }  
            j--;  
        }  
    }       
  
    *(ptr + curPosition) = temp;     
    if(curPosition - begin > 1)//前面小的比较  
        quickSort(ptr, begin, curPosition - 1);  
    if(end - curPosition > 1)//后面大的比较  
        quickSort(ptr, curPosition + 1, end);   
}  