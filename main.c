#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

struct maszyny
{
    int id;
    int praca;
    int blad;
    int rok;
    int smieci;
    struct maszyny* nastepny;
};
struct wylaczone
{
    int id;
    int praca;
    int blad;
    int rok;
    int smieci;
    struct wylaczone* nastepny;
};
typedef struct maszyny MASZYNY;
typedef MASZYNY* maszyny1;
typedef struct wylaczone WYLACZONE;
typedef WYLACZONE* wylaczone1;

int zdolnosc=0;
int chwilowo;
void wypisywanie(maszyny1 pierwszy)
{
    printf("ID PRACA BLAD ROK SMIECI\n");
    maszyny1 obecny=pierwszy;
    while(obecny)
    {
        printf("%d ", obecny->id);
        printf("%d ", obecny->praca);
        printf("%d ", obecny->blad);
        printf("%d ", obecny->rok);
        printf("%d \n", obecny->smieci);
        obecny = obecny->nastepny;
    }
}
void wypisywanie2(wylaczone1 wylpierwszy)
{
    printf("ID PRACA BLAD ROK SMIECI\n");
    wylaczone1 wylobecny=wylpierwszy;
    while(wylobecny)
    {
        printf("%d ", wylobecny->id);
        printf("%d ", wylobecny->praca);
        printf("%d ", wylobecny->blad);
        printf("%d ", wylobecny->rok);
        printf("%d \n", wylobecny->smieci);
        wylobecny = wylobecny->nastepny;
    }
}
void bombelek(struct maszyny *pierwszy)
{
    int zmienione, k;
    struct maszyny *pom1;
    struct maszyny *pom2 = NULL;
    if (pierwszy == NULL)
        return;

    do
    {
        zmienione=0;
        pom1 = pierwszy;
        while(pom1->nastepny != pom2)
        {
            if (pom1->smieci < pom1->nastepny->smieci || (pom1->smieci == pom1->nastepny->smieci && pom1->rok > pom1->nastepny->rok))
            {
                zamien(pom1, pom1->nastepny);
                     zmienione = 1;
            }
            pom1 = pom1->nastepny;
        }
        pom2 = pom1;
    }
    while (zmienione);
}

void push(maszyny1 obecny1)
{
        obecny1->id = obecny1->nastepny->id;
        obecny1->praca = obecny1->nastepny->praca;
        obecny1->blad = obecny1->nastepny->blad;
        obecny1->rok = obecny1->nastepny->rok;
        obecny1->smieci = obecny1 ->nastepny->smieci;
    }


void zamien(struct maszyny *a, struct maszyny *b)
{
    int tmp = a->id;
    a->id = b->id;
    b->id = tmp;

    int tmp2 = a->praca;
    a->praca = b->praca;
    b->praca = tmp2;

    int tmp3 = a->blad;
    a->blad = b->blad;
    b->blad = tmp3;

    int tmp4 = a->rok;
    a->rok = b->rok;
    b->rok = tmp4;

    int tmp5 = a->smieci;
    a->smieci = b->smieci;
    b->smieci = tmp5;
}

int suma_produkcji(struct maszyny *pierwszy )
{
    zdolnosc = 0;
    maszyny1 help=pierwszy;
    if(help->nastepny == NULL)
        printf("Lista jest pusta");


    while(help->nastepny != NULL)
    {
        zdolnosc += help->praca;
        help = help->nastepny;
    }
    zdolnosc+=help->praca;
    return zdolnosc;
}

int main()
{
    maszyny1 pierwszy = NULL, ostatni = NULL,obecny;
    wylaczone1 wylpierwszy = NULL, wylostatni = NULL,wylobecny;

    FILE *plik = fopen("dane.txt", "r");
     if (plik==NULL)
    {
        printf("Blad otwarcia pliku.\n");
        return 1;
    }
        int x,y,z,w;
        while(fscanf(plik,"%d %d %d %d",&x,&y,&w,&z)!=EOF)
        {
        obecny =(maszyny1)malloc(sizeof(MASZYNY));
        obecny->id = x;
        obecny->praca = y;
        obecny->blad = w;
        obecny->rok = z;
        obecny->smieci =ceil(((float)(obecny->blad)/100)*(obecny->praca));
        obecny->nastepny = NULL;
        if(pierwszy==NULL)
            {
                pierwszy=obecny;
                ostatni=obecny;
            }
            else
            {
                ostatni->nastepny=obecny;
                ostatni=obecny;
            }
        }
    printf("Lista poczatkowa z danych z pliku:\n");
    wypisywanie(pierwszy);
    printf("Posortowana lista poczatkowa:\n");
    bombelek(pierwszy);
    wypisywanie(pierwszy);
    int LIM=0, miejsca=0;
    printf("Wprowadz limit produkcyjny (LIM):\n");
    scanf("%d", &LIM);
    printf("Wprowadz limit miejsc konserwacyjnych:\n");
    scanf("%d", &miejsca);
    printf("Podany limit produkcyjny to: %d, a limit miejsc to: %d\n", LIM, miejsca);
    suma_produkcji(pierwszy);
    printf("Suma produkcji: %d\n", zdolnosc);


    int licznik = 0;
    obecny=pierwszy;
    while(zdolnosc-(obecny->praca) >= LIM && licznik < miejsca)
        {
        wylobecny =(wylaczone1)malloc(sizeof(WYLACZONE));
        wylobecny->id = obecny->id;
        wylobecny->praca = obecny->praca;
        wylobecny->blad = obecny->blad;
        wylobecny->rok = obecny->rok;
        wylobecny->smieci = obecny->smieci;
        wylobecny->nastepny = NULL;
        zdolnosc=zdolnosc-(obecny->praca);
        licznik++;
        printf("%d\n", zdolnosc);
        if(wylpierwszy==NULL)
            {
                wylpierwszy=wylobecny;
                wylostatni=wylobecny;
            }
            else
            {
                wylostatni->nastepny=wylobecny;
                wylostatni=wylobecny;
            }
           push(obecny);
           obecny=obecny->nastepny;
        }
        if(licznik==miejsca)
        {
            printf("Wszystkie miejsca zapelnione. \n");
        }

        if((zdolnosc-(obecny->praca) <= LIM)&&(licznik!=miejsca))
        {
            printf("Wylaczenie maszyny doprowadzi do zbyt niskiej zdolnosci produkcyjnej. \n");
        }
        int h=0;
        while(h<=0 || h>3)
        {
            printf("Aby wypisac liste maszyn do konserwacji wcisnij 1. Aby wypisac liste maszyn po wylaczeniu wymagajacych konserwacji wcisnij 2. Aby zakonczyc dzialanie programu w tym momencie wcisnij 3. \n");
            scanf("%d,", &h);
            switch (h)
            {
                case 1:
                    wypisywanie2(wylpierwszy);
                    break;
                case 2:
                    wypisywanie(obecny);
                    break;
                case 3:
                    return 0;
                default:
                    printf("Nieprawidlowy wybor, wybierz jeszcze raz.\n");
            }
        }

        return 0;
}
