#ifndef TYPEDEF_STRUCT_DECLARED_
#define TYPEDEF_STRUCT_DECLARED_
typedef struct datum
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
}Date;

typedef struct action
{
    Date *date;
    char *place;
    char *name;
    char *comment;
    struct action *next;
}Action;
#endif

Action *Add_element(Date *date, char *place, char *name, char *comment);
Date *Build_date(int year, int month, int day, int hour, int minute);
void Print_element(Action *element);
Action *Search_element(Action *first, char *name);
bool Delete_element(Action *first, Action *element);
void free_structure(Action *Head);
Action *Sort_structure_by_month(Action *first);
Action *Sort_month_by_day(Action *first);
Action *Sort_day_by_hour(Action *first);
Action *Sort_hour_by_minute(Action *first);
