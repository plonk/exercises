#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    if (month < 1 || month > 12) {
        printf("day_of_year: month out of range (%d)\n", month);
        return -1;
    }

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    char *tab_year = daytab + leap, *m;
    if (day < 1 || day > *(tab_year + month)) {
        printf("day_of_year: day out of range (%d)\n", day);
        return -1;
    }

    for (m = tab_year + 1; m < tab_year + 13; m++)
        day += *m;

    return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (yearday < 1 || yearday > 365+leap) {
        printf("month_day: yearday out of range (%d)\n", yearday);
        *pmonth = *pday = -1;
        return;
    }

    char *m;

    for (m = *(daytab + leap) + 1; yearday > *m; m++)
        yearday -= *m;

    *pmonth = i;
    *pday = yearday;
}

int main()
{
    char buf[1024];

    while (printf("[YEAR YEARDAY] or [YEAR MONTH DAY]> "),
           gets(buf) != NULL) {
        int year, snd_arg, day;

        switch (sscanf(buf, "%d%d%d", &year, &snd_arg, &day)) {
        case 3: {
            int month = snd_arg, yearday;
            
            yearday = day_of_year(year, month, day);
            printf("YEAR %d MONTH %d DAY %d = YEARDAY %d\n",
                   year, month, day, yearday);
            break;
        }
        case 2: {
            int yearday = snd_arg;
            int month, day;
            
            month_day(year, yearday, &month, &day);
            printf("YEARDAY %d of YEAR %d = MONTH %d DAY %d\n",
                   yearday, year, month, day);
            break;
        }
        default:
            printf("input format error\n");
            break;
        }
    }
    return 0;
}
