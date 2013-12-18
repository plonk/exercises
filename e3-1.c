#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch_original(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low+high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else	/* found match */
      return mid;
  }
  return -1;	/* no match */
}

int binsearch_modified(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low+high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
  }

  if (v[mid] == x)
    /* found match */
    return mid;
  else
    return -1;	/* no match */
}

#define ARRAY_SIZE 25000000
int test_data[ARRAY_SIZE];

int cmp(const void *a, const void *b)
{
  const int *aa = a, *bb = b;
  return *aa - *bb;
}

void populate(int array[], size_t size)
{
  int i;

  for (i = 0; i < size; ++i)
    array[i] = rand();
}

int main()
{
  srand(time(NULL));
  populate(test_data, ARRAY_SIZE);

  printf("filled\n");

  qsort(test_data, ARRAY_SIZE, sizeof(int), cmp);

  printf("sorted\n");


  int r1, r2;
  int i;
  for (i=0; i < 100000000; ++i)
    r1 = binsearch_original(1234, test_data, ARRAY_SIZE);
  for (i=0; i < 100000000; ++i)
    r2 = binsearch_modified(1234, test_data, ARRAY_SIZE);

  printf("binsearch_original: found? %s, where? %d\n",
	 r1 != -1 ? "yes" : "no", r1);
  printf("binsearch_modified: found? %s, where? %d\n",
	 r2 != -1 ? "yes" : "no", r2);
}
