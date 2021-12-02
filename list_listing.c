#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list_listing.h"
#include "list_functions.h"
#include "list_others.h"

void list_by_day(Action *newHead, int year, int month, int day)
{
    Action *temp = newHead;

    if(year < 2017)
    {
        printf("Mar 2017-et irunk!\n");
        return;
    }

    if(getWeekNumber(month) == 0) //0 �s 12 k�z�tt kell lennie a h�napnak
    {
        printf("Rosszul adta meg a honapot!\n");
        return;
    }

    if(day < 1 && day > 31)
    {
        printf("Rosszul adta meg a napot!\n");
        return;
    }

    while(temp != NULL)
    {
        if(temp->date->year == year && temp->date->month == month && temp->date->day == day)
        {
            Print_element(temp);
        }
        temp = temp->next;
    }
    return;
}

void list_by_week(Action *newHead, int year, int month, int weeknum)
{
    Action *temp = newHead;

    if(year < 2017)
    {
        printf("Mar 2017-et irunk!\n");
        return;
    }

    if(getWeekNumber(month) == 0)
    {
        printf("Rosszul adta meg a honapot!\n");
        return;
    }

    if(weeknum < 1 && weeknum > 4)
    {
        printf("Rosszul adta meg a hetet!\n");
        return;
    }

    int i = 0;
    int sum = 0;
    for(i=1;i<=weeknum;i++) //kisza�molja a h�t kezdet�nek napj�t
    {
        sum += 7;
    }
    if(weeknum == 4)
    {
        sum += getWeekNumber(month) - sum; //ez pedig a h�t v�ge, a h�napok v�ltoz� napsz�ma miatt kell a getweeknumber f�ggv�ny
    }

    while(temp != NULL)
    {
        if(temp->date->year == year && temp->date->month == month && temp->date->day >= sum-6 && temp->date->day <= sum)
        {
            Print_element(temp);
        }
        temp = temp->next;
    }
    return;
}

void list_by_month(Action *newHead, int year, int month)
{
    Action *temp = newHead;

    if(year < 2017)
    {
        printf("Mar 2017-et irunk!\n");
        return;
    }

    if(getWeekNumber(month) == 0)
    {
        printf("Rosszul adta meg a honapot!\n");
        return;
    }

    while(temp != NULL)
    {
        if(temp->date->year == year && temp->date->month == month)
            Print_element(temp);
        temp = temp->next;
    }
}

//teljes strukt�ra list�z� f�ggv�ny
void list_structure(Action *head)
{
    if(head == NULL)
        return;

    int counter = 1;

    Action *temp = head;

    while(temp != NULL)
    {
        printf("%d:\n", counter);
        puts(temp->name);
        printf("\n%d.%d.%d %d:%d\n", temp->date->year, temp->date->month, temp->date->day, temp->date->hour, temp->date->minute);
        puts(temp->place);
        puts(temp->comment);
        printf("\n");
        counter++;
        temp = temp->next;
    }
}
