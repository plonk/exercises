#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
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
