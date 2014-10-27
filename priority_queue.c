/* Excerpte from : http://algs4.cs.princeton.edu/24pq/ */

#define less(x,y)
#define exch(x,y)
#define N

void bottom_up_reheapify(int k)
{
	while (k > 1 && less(k/2, k))
	{
		exch(k, k/2);
		k = k / 2;
	}
}

void top_down_heapify(int k)
{
	int j;
	while (2*k <= N) /* have one child at least */
	{
		j = 2 * k; /* j point to left child */
		if (j < N && less(j, j+1)) /* j < N : means having two children, j == N: have one child only */
			j++; /* j ponit to right child */
		/* j, point to the larger one of its two children */
		if (!less(k, j)) /* until we reach the one with both children smaller */
			break;
		exch(k, j);
		k = j;
	}
}
