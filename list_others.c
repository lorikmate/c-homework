int getWeekNumber(int month) //hónap alapján visszaadja a napok számát
{
    if(month > 12 || month < 1)
        return 0;
    if(month == 1 || month == 3 || month ==  5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    if(month == 2)
        return 28;
    return 30;
}

//tetszõleges számú karakter bekérõ függvény, enter karakter terminálja, dinamikusan foglal helyet, forrás: infoc, illetve laboron
//önállóan is el kellett készíteni.

char *getString()
{
    int db = 0;

    char *sor = (char*) malloc(sizeof(char) * 1); //kezdeti helyfoglalás
    sor[0] = '\0';

    char ujkar;

    while (scanf("%c", &ujkar) == 1 && ujkar != '\n') //karakterek bekérése, enternél ciklus vége
    {
        int i;
        char *ujtomb = (char*) malloc(sizeof(char) * (db+1+1)); //új helyfoglalás, melyben elfér az eddigi adat, az új karakter + a lezáró \0
        for (i = 0; i < db; ++i)
            ujtomb[i] = sor[i]; //elõzõ másolása az újonnan foglalt helyre
        free(sor); //korábbi felszabadítása
        sor = ujtomb;
        ujtomb[db] = ujkar; //új karakter  hozzáadása
        ujtomb[db+1] = '\0'; //sor lezárása
        ++db; //darabszám növelése
    }

    return sor;
}
