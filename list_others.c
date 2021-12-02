int getWeekNumber(int month) //h�nap alapj�n visszaadja a napok sz�m�t
{
    if(month > 12 || month < 1)
        return 0;
    if(month == 1 || month == 3 || month ==  5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    if(month == 2)
        return 28;
    return 30;
}

//tetsz�leges sz�m� karakter bek�r� f�ggv�ny, enter karakter termin�lja, dinamikusan foglal helyet, forr�s: infoc, illetve laboron
//�n�ll�an is el kellett k�sz�teni.

char *getString()
{
    int db = 0;

    char *sor = (char*) malloc(sizeof(char) * 1); //kezdeti helyfoglal�s
    sor[0] = '\0';

    char ujkar;

    while (scanf("%c", &ujkar) == 1 && ujkar != '\n') //karakterek bek�r�se, entern�l ciklus v�ge
    {
        int i;
        char *ujtomb = (char*) malloc(sizeof(char) * (db+1+1)); //�j helyfoglal�s, melyben elf�r az eddigi adat, az �j karakter + a lez�r� \0
        for (i = 0; i < db; ++i)
            ujtomb[i] = sor[i]; //el�z� m�sol�sa az �jonnan foglalt helyre
        free(sor); //kor�bbi felszabad�t�sa
        sor = ujtomb;
        ujtomb[db] = ujkar; //�j karakter  hozz�ad�sa
        ujtomb[db+1] = '\0'; //sor lez�r�sa
        ++db; //darabsz�m n�vel�se
    }

    return sor;
}
