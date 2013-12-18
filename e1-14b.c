#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>

#define MAX_ENTRIES 1024

struct ENTRY {
  wchar_t ch;
  int times;
};

struct ENTRY frequency_tbl[MAX_ENTRIES];
int next_free_index = 0;

int freq_get(wchar_t, int*);
void freq_set(wchar_t, int);

/* ch でルックアップして times をセットし、0 を返す。
   エントリーがなければ -1 を返す。 */
int freq_get(wchar_t ch, int * times)
{
  int i;

  for (i =0; i< next_free_index; ++i)
    if (frequency_tbl[i].ch == ch) {
      *times = frequency_tbl[i].times;
      return 0;
    }
  return -1;
}

void freq_set(wchar_t ch, int times)
{
  int i;

  for (i =0; i< next_free_index; ++i)
    if (frequency_tbl[i].ch == ch) {
      frequency_tbl[i].times = times;
      return;
    }

  /* エントリーがなかったので追加する */
  if (next_free_index == MAX_ENTRIES) {
    fprintf(stderr, "Error: entry table full\n");
    exit(1);
  } else {
    struct ENTRY this;

    this.ch = ch, this.times = times;
    frequency_tbl[next_free_index++] = this;

    return;
  }
}



int entry_comparer(struct ENTRY *a, struct ENTRY *b)
{
  if (a->ch > b->ch)
    return 1;
  else if (a->ch < b->ch)
    return -1;
  else
    return 0;
}

/*
 * 文字の頻度をヒストグラムにする
 */

void print_histogram()
{
  int i, j;

  qsort(frequency_tbl, next_free_index, sizeof(struct ENTRY),
	(int (*)(void*,void*)) entry_comparer);
  for (i = 0; i < next_free_index; ++i) {
    struct ENTRY this = frequency_tbl[i];

    if (iswgraph(this.ch))
      putwchar(this.ch);

    wprintf(L"\t%04Xh: ",this.ch);
      
    for (j = 0; j < this.times; ++j)
      putwchar(L'*');
    putwchar(L'\n');
  }
}

main()
{
  wint_t c;
  int cfreq[sizeof(wchar_t)*8] = { 0 };

  setlocale(LC_ALL, "");

  while ((c = getwchar()) != WEOF) {
    int times = 0;

    freq_get(c, &times);
    freq_set(c, times + 1);
  }

  /* ヒストグラムを出力しましょう */
  print_histogram();
}
