#ifndef __SORT_H__
#define __SORT_H__

void swap(int *a, int *b);
void swap_array(int *array, int i, int j);
void swap_u32(void *a, void *b, int size);
void swap_generic(void *a, void *b, int size);

void sort(void *base, size_t num, size_t size, 
		  int (*cmp_func)(const void *, const void *),
		  void (*swap_func)(void *, void *, int size));

void sort_bubble(int array[], int num);
void sort_quick(int array[], int num);

void sort_insert(int array[], int num);
void sort_shell(int array[], int num);

void sort_select(int array[], int num);
void sort_heap(int array[], int num);

void sort_merge(int array[], int num);

void sort_gnome(int array[], int num);

void sort_comb(int array[], int num);


#endif
