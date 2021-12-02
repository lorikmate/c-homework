#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list_functions.h"
#include "list_listing.h"
#include "list_others.h"

void menu();
void clearScreen();

int main()
{
    menu();

    char *input;

    Action *HEAD = NULL; //A lista elsõ pointere

    Action *temp = NULL;

    int year = 0, month = 0, day = 0, hour = 0, minute = 0;
    char *place = NULL;
    char *name = NULL;
    char *comment = NULL;
    char *crit = NULL;

    while(strcmp(input, "quit") != 0) //quit without saving
    {
        input = getString();
        if(strcmp(input, "add") == 0)
        {
            clearScreen();

            printf("Kerem adja meg a datumot YYYY.MM.DD. formatumban!\n");
            scanf("%d.%d.%d", &year, &month, &day);
            fflush(stdin);
            if(year < 2017 || month < 1 || month > 12 || day < 1 || day > 31)
            {
                printf("A datum formatuma nem megfelelo!\n");
                clearScreen();
                menu();
                continue;
            }
            printf("Kerem adja meg az idot HH:MM formatumban!\n");
            scanf("%d:%d", &hour, &minute);
            fflush(stdin);
            if(hour < 0 || hour > 23 || minute < 0 || minute > 59)
            {
                printf("Az ido formatuma nem megfelelo!\n");
                clearScreen();
                menu();
                continue;
            }
            printf("Kerem adja meg az idopont nevet!\n");
            name = getString();
            if(strcmp(name, "") == 0)
            {
                printf("A megadott nev nem megfelelo!\n");
                clearScreen();
                menu();
                continue;
            }
            printf("Kerem adja meg az idopont helyet!\n");
            place = getString();
            printf("Kerem adja meg az idoponthoz fuzodo megjegyzest!\n");
            comment = getString();

            if(HEAD == NULL) //Ha még nincs elem, vegye fel oda
            {
                HEAD = Add_element(Build_date(year, month, day, hour, minute), place, name, comment);
            }
            else //egyébként keresse meg a lista végét, és kösse oda
            {
                temp = HEAD;
                while(temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = Add_element(Build_date(year, month, day, hour, minute), place, name, comment);
            }

            clearScreen();

            printf("\nSikeresen felvett egy rekordot!\n");

            menu();
        }
        else if(strcmp(input, "edit") == 0)
        {
            clearScreen();

            if(HEAD == NULL)
            {
                printf("Ures a lista!\n");
                menu();
                continue;
            }

            list_structure(HEAD); //Listázza a struktúrát, amelyhez sorszámokat rendel, ez alapján tud választani a felhasználó

            int id = 0;
            int counter = 1;
            temp = HEAD;
            bool flag = false;

            printf("\nMelyik elemet szeretne modositani? Kerem adja meg a sorszamat!\nSorszam: ");
            scanf("%d", &id);
            fflush(stdin);

            while(temp != NULL)
            {
                if(counter == id)
                {
                    printf("\nMelyik elemet szeretne modositani (name, place, comment, date, time)\n");
                    fflush(stdin);
                    crit = getString();
                    printf("(Date:YYYY.MM.DD | Time:HH:MM)");
                    printf("\nMire?\n");
                    if(strcmp(crit, "name") == 0)
                    {
                        name = getString();
                        temp->name[0] = '\0';
                        temp->name = (char*)malloc(strlen(name) * sizeof(char)+1); //Dinamikusan újra helyet foglal a memóriában, mert a string hossza változhat
                        strcpy(temp->name, name);
                        flag = true;
                    }
                    else if(strcmp(crit, "place") == 0)
                    {
                        place = getString();
                        temp->place[0] = '\0';
                        temp->place = (char*)malloc(strlen(place) * sizeof(char));
                        strcpy(temp->place, place);
                    }
                    else if(strcmp(crit, "comment") == 0)
                    {
                        comment = getString();
                        temp->comment[0] = '\0';
                        temp->comment = (char*)malloc(strlen(comment) * sizeof(char));
                        strcpy(temp->comment, comment);
                        flag = true;
                    }
                    else if(strcmp(crit, "date") == 0)
                    {
                        scanf("%d.%d.%d.", &year, &month, &day);
                        fflush(stdin);
                        hour = temp->date->hour;
                        minute = temp->date->minute;
                        free(temp->date);
                        temp->date = NULL;
                        temp->date = Build_date(year, month, day, hour, minute);
                        flag = true;
                    }
                    else if(strcmp(crit, "time") == 0)
                    {
                        scanf("%d:%d", &hour, &minute);
                        fflush(stdin);
                        year = temp->date->year;
                        month = temp->date->month;
                        day = temp->date->day;
                        free(temp->date);
                        temp->date = NULL;
                        temp->date = Build_date(year, month, day, hour, minute);
                        flag = true;
                    }
                    break;
                }
                else
                {
                    temp = temp->next;
                    counter++;
                }
            }
            if(!flag)
            {
                clearScreen();
                printf("A modositas sikertelen volt!\n");
                menu();
                continue;
            }
            clearScreen();
            printf("Sikeres modositas!\n");
            free(crit);
            menu();
        }
        else if(strcmp(input, "delete") == 0)
        {
            clearScreen();

            if(HEAD == NULL)
            {
                printf("Nincsenek megadott idopontok!\n");
                menu();
                continue;
            }

            printf("Kerlek add meg az idopont nevet, amit torolni szeretnel!\n");
            name = getString();

            if(Search_element(HEAD, name))
            {
                if(Delete_element(HEAD, Search_element(HEAD, name)))
                    printf("Sikeresen torolted az idopontot!\n");
                else
                    printf("Idopont torlese sikertelen!\n");
            }
            else
                printf("Nem letezik a megadott idopont!\n");

            menu();
        }
        else if(strcmp(input, "list") == 0)
        {
            clearScreen();

            if(HEAD == NULL)
            {
                printf("Nincsenek megadott idopontok!\n");
                menu();
                continue;
            }

            int num = 0;

            Action *newHead = Sort_structure_by_month(HEAD); //Elõször évek és  hónapok szerint rendezi sorba

            newHead = Sort_month_by_day(newHead); //utána a hónapokat napok alapján
            newHead = Sort_day_by_hour(newHead); //majd a napokat óra alapján
            newHead = Sort_hour_by_minute(newHead); //és végül percek alapján

            printf("Egy napot, hetet vagy honapot szeretne kilistazni?(nap, het, honap)\n");
            crit = getString();

            if(strcmp(crit, "nap") == 0)
            {
                printf("A nap datuma YYYY.MM.DD. alakban?\n");
                scanf("%d.%d.%d", &year, &month, &day);
                list_by_day(newHead, year, month, day);
                fflush(stdin);
            }
            else if(strcmp(crit, "het") == 0)
            {
                printf("A het datuma YYYY.MM. alakban?\n");
                scanf("%d.%d.", &year, &month);
                fflush(stdin);
                printf("A honap hanyadik hetet?\n");
                scanf("%d", &num);
                list_by_week(newHead, year, month, num);
                fflush(stdin);
            }
            else if(strcmp(crit, "honap") == 0)
            {
                printf("A honap datuma YYYY.MM. alakban?\n");
                scanf("%d.%d.", &year, &month);
                fflush(stdin);
                list_by_month(newHead, year, month);
                fflush(stdin);
            }
            else
            {
                printf("Rosszul adta meg a listazasi feltetelt!\n");
                continue;
            }
            menu();
        }
        else if(strcmp(input, "search") == 0)
        {
            clearScreen();

            if(HEAD == NULL)
            {
                printf("Nincsenek megadott idopontok!\n");
                menu();
                continue;
            }

            printf("Kerlek ird be az idopont nevet, amit meg szeretnel talalni!\n");
            name = getString();

            if(Search_element(HEAD, name))
                Print_element(Search_element(HEAD, name));
            else
                printf("\nNincs ilyen esemeny megadva.\n");

            menu();
        }
        else if(strcmp(input, "save") == 0)
        {
            clearScreen();

            if(HEAD == NULL)
            {
                printf("Nincsenek megadott idopontok!\n");
                menu();
                continue;
            }

            temp = HEAD;
            FILE *Fs = NULL;

            printf("Kerem adja meg a fajl nevet!\n");
            name = getString();

            if(!(Fs = fopen(name, "w+")))
            {
                printf("Fajl nyitas sikertelen!\n");
                continue;
            }
            while(temp != NULL)
            {
                fprintf(Fs, "%d.%d.%d\n%d:%d\n%s\n", temp->date->year, temp->date->month, temp->date->day, temp->date->hour, temp->date->minute, temp->name, temp->place, temp->comment);
                if(strcmp(temp->place, "") == 0)
                    fprintf(Fs, "-\n");
                else
                    fprintf(Fs, "%s\n", temp->place);
                if(strcmp(temp->comment, "") == 0)
                    fprintf(Fs, "-");
                else
                    fprintf(Fs, "%s", temp->comment);
                if(temp->next != NULL)
                    fprintf(Fs, "\n");
                temp = temp->next;
            }
            printf("Sikeres fajlbairas!\n");

            fclose(Fs);
            menu();
        }
        else if(strcmp(input, "open") == 0)
        {
            clearScreen();

            if(HEAD != NULL)
            {
                printf("Epp dolgozol egy rekordlistan!\n");
                menu();
                continue;
            }

            FILE *Fs = NULL;

            printf("Kerem adja meg a fajl nevet!\n");
            name = getString();

            if(!(Fs = fopen(name, "r+")))
            {
                printf("Fajl nyitas sikertelen!\n");
                clearScreen();
                menu();
                continue;
            }

            char ignore[2] = {0};
            char name[50] = {0};
            char place[50] = {0};
            char comment[256] = {0};

            while(!feof(Fs))
            {
                fscanf(Fs, "%d.%d.%d", &year, &month, &day);
                fgets(ignore, 2, Fs);
                fscanf(Fs, "%d:%d", &hour, &minute);
                fgets(ignore, 2, Fs);
                fscanf(Fs, "%[^\n]s", &name);
                fgets(ignore, 2, Fs);
                fscanf(Fs, "%[^\n]s", &place);
                fgets(ignore, 2, Fs);
                fscanf(Fs, "%[^\n]s", &comment);
                if(HEAD == NULL)
                {
                    HEAD = Add_element(Build_date(year, month, day, hour, minute), place, name, comment);
                }
                else
                {
                    temp = HEAD;
                    while(temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->next = Add_element(Build_date(year, month, day, hour, minute), place, name, comment);
                }
            }
            printf("Sikeres beolvasas!\n");

            fclose(Fs);
            menu();
        }
        else if(strcmp(input, "quit") == 0)
        {
            break;
        }
        else
        {
            printf("Nem megfelelo menupontot adott meg!");
        }
    }
    free(crit);
    free(input);
    free(name);
    free(place);
    free(comment); //a stringeknek szinte mindenhol dinamikusan foglal helyet a program, a használat végén felszabadítás
    free_structure(HEAD);
    return 0;
}

void menu()
{
    printf("Menu:\n");
    printf("Kerem valasszon az alabbi lehetosegek kozul:\n");
    printf("add: uj rekord letrehozasa.\n");
    printf("edit: meglevo rekord modositasa.\n");
    printf("delete: meglevo rekord torlese.\n");
    printf("list: egy adott naphoz, hethez vagy honaphoz tartozo esemeny naptarszeru (idorendes) kilistazasa.\n");
    printf("search: esemeny nev szerinti keresese.\n");
    printf("save: az adatbazis fajlba mentese.\n");
    printf("open: az adatbazis fajlbol betoltese.\n");
    printf("quit: kilepes a modositasok mentese nelkul.\n");
    return;
}

/* A console ablakról töröl minden eddig kiírt infót,
 * az átláthatóság végett kényelmes.
 */

void clearScreen()
{
    system("cls");
}



