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

void list_structure(Action *head);
void list_by_day(Action *newHead, int year, int month, int day);
void list_by_week(Action *newHead, int year, int month, int weeknum);
void list_by_month(Action *newHead, int year, int month);
