#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "sort.h"

void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void swap_array(int *array, int i, int j)
{
	int tmp;
	tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

void swap_u32(void *a, void *b, int size)
{
	u32 t = *(u32 *)a;
	*(u32 *)a = *(u32 *)b;
	*(u32 *)b = t;
}
void swap_generic(void *a, void *b, int size)
{
	char t;
	char *ax = a;
	char *bx = b;
	do {
		t = *ax;
		*ax++ = *bx;
		*bx++ = t;
	} while (--size > 0);
}

void sort(void *base, size_t num, size_t size, 
		  int (*cmp_func)(const void *, const void *),
		  void (*swap_func)(void *, void *, int size))
{
	
}

// TODO:1
void sort_bubble(int array[], int num)
{
	int i, j;
	for(i = num; i > 1; i--)
	{
		for(j = 0; j < i-1; j++)
		{
			if(array[j] > array[j+1])
				swap_array(array, j, j+1);
		}
	}
}

// TODO:2
int quick_partition(int array[], int left, int right)
{
	int iPivot = array[left];
	while(left < right)
	{
		while(left < right && array[right] >= array[left])
			right--;
		if(left < right)
			array[left++] = array[right];
		while(left < right && array[left] <= array[right])
			left++;
		if(left < right)
			array[right--] = array[left];
	}
	array[left] = iPivot;
	return left;
}
void quick_recursion(int array[], int left, int right)
{
	int pos;
	if(left < right)
	{
		pos = quick_partition(array, left, right);
		quick_recursion(array, left, pos-1);
		quick_recursion(array, pos+1, right);
	}
}
void sort_quick(int array[], int num)
{
	quick_recursion(array, 0, num-1);
}

// TODO:3
void sort_insert(int array[], int num)
{
	int i, j, tmp;
	for(i = 1; i < num; i++)
	{
		tmp = array[i];
		for(j=i-1; j >= 0 && array[j] > tmp; j--)
			array[j+1] = array[j];
		array[j+1] = tmp;
	}
}

// TODO:4
void sort_shell_0(int array[], int num)
{
	int i, j, k, gap, tmp;

	for(gap = num / 2; gap > 0; gap /= 2) /* 步长 */
	{
		for(i = 0; i < gap; i++) /* 按组排序?? */
		{
			for(j = i + gap; j < num; j += gap)
			{
				if(array[j] < array[j-gap])
				{
					tmp = array[j];
					k = j - gap;
					while(k >= 0 && array[k] > tmp)
					{
						array[k+gap] = array[k];
						k -= gap;
					}
					array[k+gap] = tmp;
				}
			}
		}
	}
}
void sort_shell_1(int array[], int num)
{
	int i, j, gap;
	gap = num / 2;
	while(gap > 0)
	{
		for(i = gap; i < num; i++) /* */
		{
			j = i - gap;
			while(j >= 0)
			{
				if(array[j] > array[j+gap])
				{
					swap_array(array, j, j+gap);
					j -= gap;
				}
				else
				{
					j--;
				}
			}
		}
		gap /= 2;
	}

}
/* K&R P51 3.5*/
void sort_shell_2(int array[], int num)
{
	int i, j, gap;
	for(gap = num / 2; gap > 0; gap /= 2)
	{
		for(i = gap; i < num; i++)
		{
			for(j = i-gap; j >= 0 && array[j] > array[j+gap]; j -= gap)
				swap_array(array, j, j+gap);
		}
	}
}

// TODO:5
void sort_select(int array[], int num)
{
	int i, j, min;

	for(i = 0; i < num-1; i++)
	{
		min = i;
		for(j = i+1; j < num; j++)
		{
			if(array[min] > array[j])
				min = j;
		}
		if(min != i)
			swap_array(array, i, min);
	}
}

// TODO:6
/* 下标从0开始 */
int get_rchild(int i)
{
	return (i*2+2);
}
int get_lchild(int i)
{
	return (i*2+1);
}
int get_parent(int i)
{
	return (i-1)/2;
}

void sort_heap(int array[], int num)
{
}

// TODO:7
void merge_array(int array[], int first, int mid, int last, int tmp[])
{
	int i, j, m, n;
	int k = 0;
	i = first;
	m = mid;
	j = mid + 1;
	n = last;
	while(i <= m && j <= n)
	{
		if(array[i] < array[j])
			tmp[k++] = array[i++];
		else
			tmp[k++] = array[j++];
	}
	while(i <= m)
		tmp[k++] = array[i++];
	while(j <= n)
		tmp[k++] = array[j++];

	for(i = 0; i < k; i++)
		array[first+i] = tmp[i];
}

void merge_recursion(int array[], int first, int last, int tmp[])
{
	int mid;
	if(first < last)
	{
		mid = (first + last) / 2;
		merge_recursion(array, first, mid, tmp);
		merge_recursion(array, mid+1, last, tmp);
		merge_array(array, first, mid, last, tmp);
	}
}

void sort_merge(int array[], int num)
{
	int *pTmp;
	if((pTmp = malloc(num)) == NULL)
		return ;
	merge_recursion(array, 0, num-1, pTmp);
	free(pTmp);
}

// TODO:8
void sort_gnome(int array[], int num)
{

}

// TODO:9
void sort_comb(int array[], int num)
{

}
