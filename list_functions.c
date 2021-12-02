#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list_functions.h"

//Lista elem hozz�ad�sa
Action *Add_element(Date *date, char *place, char *name, char *comment)
{
    Action *newAction = NULL;

    if(!(newAction = (Action*)malloc(sizeof(Action))))
    {
        printf("\nA helyfoglalas sikertelen.");
        return NULL;
    }

    newAction->date = date;
    newAction->place = (char*)calloc(strlen(place), sizeof(char));
    strcpy(newAction->place, place);
    newAction->name = (char*)calloc(strlen(name), sizeof(char));
    strcpy(newAction->name, name);
    newAction->comment = (char*)calloc(strlen(comment), sizeof(char));
    strcpy(newAction->comment, comment);
    newAction->next = NULL;

    return newAction;
}

//D�tum t�pus� v�ltoz� l�trehoz�sa
Date *Build_date(int year, int month, int day, int hour, int minute)
{
    Date *date = NULL;

    if(!(date = (Date*)malloc(sizeof(Date))))
    {
        printf("\nA helyfoglalas sikertelen.");
        return NULL;
    }

    date->year = year; //year ? 0 ???
    date->month = month;
    date->day = day;
    date->hour = hour;
    date->minute = minute;

    return date;
}

Action *Search_element(Action *first, char *name)
{
    Action *temp = first;

    while(temp != NULL) //iterat�v bej�r�s a l�ncolt list�n
    {
        if(strcmp(temp->name, name) != 0)
            temp = temp->next;
        else
            return temp;
    }
    return NULL;
}

void Print_element(Action *element)
{
    puts(element->name);
    printf("\n%d.%d.%d %d:%d\n", element->date->year, element->date->month, element->date->day, element->date->hour, element->date->minute);
    puts(element->place);
    puts(element->comment);
    printf("\n");
    return;
}

bool Delete_element(Action *first, Action *element)
{
    Action *temp = first;

    if(first == NULL)
        return false;

    if(first == element) //amennyiben a head a t�rlend� elem
    {
        if(first->next != NULL) //ha van ut�na k�vetkez� elem
        {
            first = element->next; //head pointer �tk�t�se arra
            free(element);
            return true;
        }
    }

    if(first->next == NULL) //ha nincs k�vetkez� akkor head t�rl�se
    {
        free(first);
        first = NULL;
        return true;
    }

    while(temp->next != element) //iterat�v bej�r�s am�g nincs meg a t�rlend� elem
    {
        temp = temp->next;
    }

    if(element->next != NULL) //ha van ut�na k�vetkez� elem
    {
        temp->next = element->next; //akkor a t�rlend�t megel�z� elem next pointere a t�rlend� nextj�re mutasson
        free(element);
        return true;
    }
    else
    {
        temp->next = NULL; //egy�bk�nt akkor ez a lista utols� eleme, teh�t t�rl�s
        free(element);
        return true;
    }

    return true;
}

//l�ncolt lista felszabad�t�sa
void free_structure(Action *Head)
{
    Action *temp = Head;
    while (temp != NULL)
    {
       Action *tmp = temp->next;
       free(temp->date);
       free(temp);
       temp = tmp;
    }
}

//Sorting

Action *Sort_structure_by_month(Action *first)
{
    Action *tmpPtr = first;
    Action *tmpNxt = first->next;

    Date *tempDate = NULL;
    char *name = NULL;
    char *place = NULL;
    char *comment = NULL;

    while(tmpNxt != NULL) //elindul a 2. elemt�l
    {
        while(tmpNxt != tmpPtr) //az els� elemt�l indul, �gy �ssze tud hasonl�tani kett�t
        {
            if(tmpNxt->date->year <= tmpPtr->date->year && tmpNxt->date->month < tmpPtr->date->month)
            {
                tempDate = tmpPtr->date; //ment�s
                name = tmpPtr->name;
                place = tmpPtr->place;
                comment = tmpPtr->comment;

                tmpPtr->date = tmpNxt->date; //adatok felcser�l�se
                tmpPtr->place = tmpNxt->place;
                tmpPtr->name = tmpNxt->name;
                tmpPtr->comment = tmpNxt->comment;


                tmpNxt->date = tempDate; //a mentett adatok vissza�r�sa
                tmpNxt->place = place;
                tmpNxt->name = name;
                tmpNxt->comment = comment;
            }
            tmpPtr = tmpPtr->next;
        }
        tmpPtr = first;
        tmpNxt = tmpNxt->next;
    }
    return tmpPtr; //az �j, rendezett strukt�ra visszaad�sa
}

Action *Sort_month_by_day(Action *first)
{
    Action *tmpPtr = first;
    Action *tmpNxt = first->next;

    Date *tempDate = NULL;
    char *name = NULL;
    char *place = NULL;
    char *comment = NULL;

    while(tmpNxt != NULL)
    {
        while(tmpNxt != tmpPtr)
        {
            if(tmpNxt->date->day <= tmpPtr->date->day && tmpNxt->date->month == tmpPtr->date->month)
            {
                tempDate = tmpPtr->date;
                name = tmpPtr->name;
                place = tmpPtr->place;
                comment = tmpPtr->comment;

                tmpPtr->date = tmpNxt->date;
                tmpPtr->place = tmpNxt->place;
                tmpPtr->name = tmpNxt->name;
                tmpPtr->comment = tmpNxt->comment;


                tmpNxt->date = tempDate;
                tmpNxt->place = place;
                tmpNxt->name = name;
                tmpNxt->comment = comment;
            }
            tmpPtr = tmpPtr->next;
        }
        tmpPtr = first;
        tmpNxt = tmpNxt->next;
    }
    return tmpPtr;
}

Action *Sort_day_by_hour(Action *first)
{
    Action *tmpPtr = first;
    Action *tmpNxt = first->next;

    Date *tempDate = NULL;
    char *name = NULL;
    char *place = NULL;
    char *comment = NULL;

    while(tmpNxt != NULL)
    {
        while(tmpNxt != tmpPtr)
        {
            if(tmpNxt->date->day == tmpPtr->date->day && tmpNxt->date->month == tmpPtr->date->month && tmpNxt->date->hour < tmpPtr->date->hour)
            {
                tempDate = tmpPtr->date;
                name = tmpPtr->name;
                place = tmpPtr->place;
                comment = tmpPtr->comment;

                tmpPtr->date = tmpNxt->date;
                tmpPtr->place = tmpNxt->place;
                tmpPtr->name = tmpNxt->name;
                tmpPtr->comment = tmpNxt->comment;


                tmpNxt->date = tempDate;
                tmpNxt->place = place;
                tmpNxt->name = name;
                tmpNxt->comment = comment;
            }
            tmpPtr = tmpPtr->next;
        }
        tmpPtr = first;
        tmpNxt = tmpNxt->next;
    }
    return tmpPtr;
}

Action *Sort_hour_by_minute(Action *first)
{
    Action *tmpPtr = first;
    Action *tmpNxt = first->next;

    Date *tempDate = NULL;
    char *name = NULL;
    char *place = NULL;
    char *comment = NULL;

    while(tmpNxt != NULL)
    {
        while(tmpNxt != tmpPtr)
        {
            if(tmpNxt->date->day == tmpPtr->date->day && tmpNxt->date->month == tmpPtr->date->month && tmpNxt->date->hour == tmpPtr->date->hour && tmpNxt->date->minute < tmpPtr->date->minute)
            {
                tempDate = tmpPtr->date;
                name = tmpPtr->name;
                place = tmpPtr->place;
                comment = tmpPtr->comment;

                tmpPtr->date = tmpNxt->date;
                tmpPtr->place = tmpNxt->place;
                tmpPtr->name = tmpNxt->name;
                tmpPtr->comment = tmpNxt->comment;


                tmpNxt->date = tempDate;
                tmpNxt->place = place;
                tmpNxt->name = name;
                tmpNxt->comment = comment;
            }
            tmpPtr = tmpPtr->next;
        }
        tmpPtr = first;
        tmpNxt = tmpNxt->next;
    }
    return tmpPtr;
}
