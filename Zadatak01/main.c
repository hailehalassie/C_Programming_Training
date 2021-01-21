#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPRIM 15
#define MAXIME 25

typedef struct racun
{
    int broj;
    char primalac[MAXPRIM];
    char uplatilac[MAXIME];
    float iznos;
    int indikator;
    struct racun *sled;
} Racun;

Racun *kreiranjeRacuna();
Racun *insertAtHead(Racun *head, Racun *novi);
Racun *pretragaRacuna(Racun *head, int br);
void placanjeRacuna(Racun *rac);
void prikaz(Racun *lst);
Racun *brisanjeRacuna(Racun *head,int br);
Racun *pretragaPoImenu(Racun *head, char primalac[]);
void prikazOdredjen(Racun *rac);
void prikazNeplacenih(Racun *head);
Racun *brisanjeSvihRacuna(Racun *head);
Racun *testPodaci();

int main()
{
    Racun *temp;
    Racun *head = NULL;
    int izbor;
    char primalac[15];
    int brRacuna;
    int testIzbor;

    printf("Da li zelite da radite sa test podacima?\n");
    printf("1. DA\n2. NE\n\n");
    scanf("%d",&testIzbor);
    if(testIzbor==1)
    {
        head = testPodaci();
    }
    do
    {
        printf(" 1. Dodavanje racuna\n 2. Placanje postojeceg racuna\n 3. Prikaz\n 4. Brisanje\n 5. Prikaz odredjenog racuna\n 6. Prikaz neplacenih racuna\n 7. Brisanje svih racuna\n 8. Izlaz\n\n");
        scanf("%d",&izbor);
        printf("****************\n\n");
        switch(izbor)
        {
            case 1 : temp = kreiranjeRacuna();
                     head = insertAtHead(head,temp);
                     printf("\n");
                     break;
            case 2 : printf("Unesite broj racuna: ");
                     scanf("%d",&brRacuna);
                     printf("\n");
                     if(pretragaRacuna(head,brRacuna)!=NULL)
                     {
                        placanjeRacuna(pretragaRacuna(head,brRacuna));
                     }
                     else
                        printf("nema takvog!\n\n");
                     break;
            case 3 : prikaz(head);
                     printf("\n");
                     break;
            case 4 : printf("unesite broj racuna: ");
                     scanf("%d",&brRacuna);
                     head = brisanjeRacuna(head,brRacuna);
                     printf("\n");
                     break;
            case 5 : printf("Unesite primaoca: ");
                     scanf("%s", primalac);
                     prikazOdredjen(pretragaPoImenu(head,primalac));
                     printf("\n");
                     break;
            case 6 : prikazNeplacenih(head);
                     printf("\n");
                     break;
            case 7 : head = brisanjeSvihRacuna(head);
                     printf("\n");
                     break;
            case 8 : printf("GOODBYE!\n"); break;
            default : printf("ponovo!\n\n"); break;
        }
    } while(izbor!=8);

    return 0;
}

Racun *kreiranjeRacuna()
{
    Racun *r = malloc(sizeof(Racun));
    int br;
    int ind = 0;
    float iznos;
    char buff; //koristim ovu varijablu u koju smestam ono sto ostane u bufferu posle inputa

    printf("Unesite broj racuna: ");
    scanf("%d",&br);
    r->broj = br;

    printf("Unesite primaoca: ");
    scanf("%c",&buff);
    scanf("%[^\n]",r->primalac);

    printf("Unesite uplatioca: ");
    scanf("%c",&buff);
    scanf("%[^\n]",r->uplatilac);

    printf("Unesite iznos: ");
    scanf("%f",&iznos);
    r->iznos = iznos;

    r->indikator = ind;

    r->sled = NULL;

    return r;
}

Racun *insertAtHead(Racun *head, Racun *novi)
{
    novi->sled = head;
    return novi;
}

void prikaz(Racun *lst)
{
    Racun *temp = lst;
    char stanje[20];
    char placeno[] = "PLACEN";
    char neplaceno[] = "NIJE PLACEN";

    while(temp!=NULL)
    {
        if(temp->indikator==1)
            strcpy(stanje,placeno);
        else
            strcpy(stanje,neplaceno);

        printf("%d %10s %20s\t %0.2f %20s\n",temp->broj, temp->primalac,temp->uplatilac,temp->iznos,stanje);
        temp = temp->sled;
    }
}

Racun *pretragaRacuna(Racun *head, int br)
{
    Racun *temp = head;
    while(temp!=NULL)
    {
  /*      if(strcasecmp(temp->primalac,racun)==0)
                return temp;
        temp = temp->sled;    */
        if(temp->broj==br)
            return temp;
        else
            temp = temp->sled;
    }
    return NULL;
}

void placanjeRacuna(Racun *rac)
{
    int placen = 1;
    rac->indikator = placen;
    printf("Racun je uplacen!\n\n");

}

Racun *brisanjeRacuna(Racun *head,int br)
{
    Racun *temp = head, *pret = NULL, *stari;
    while(temp)
    {
        if(temp->broj!=br)
        {
            pret = temp;
            temp = temp->sled;
        }
        else
        {
            stari = temp;
            temp = temp->sled;
            if(!pret)
                head = temp;
            else
                pret->sled = temp;

            free(stari);
            printf("Racun je obrisan!\n\n");
        }
    }
    return head;
}

Racun *pretragaPoImenu(Racun *head, char primalac[])
{
    Racun *temp = head;
    while(temp!=NULL)
    {
        if(strcasecmp(temp->primalac,primalac)==0)
            return temp;

        temp = temp->sled;
    }
    return NULL;
}

void prikazOdredjen(Racun *rac)
{
    Racun *temp = rac;
    char stanje[20];
    char placeno[] = "PLACEN";
    char neplaceno[] = "NIJE PLACEN";


    if(temp->indikator==1)
        strcpy(stanje,placeno);
    else
        strcpy(stanje,neplaceno);

    printf("%d %10s %10s\t %0.2f %10s\n",temp->broj, temp->primalac,temp->uplatilac,temp->iznos,stanje);
}

void prikazNeplacenih(Racun *head)
{
    Racun *temp = head;


    while(temp!=NULL)
    {
        if(temp->indikator==0)
        {
            printf("%d %10s %10s\t %0.2f\t\n",temp->broj, temp->primalac,temp->uplatilac,temp->iznos);
        }

        temp = temp->sled;
    }
}

Racun *brisanjeSvihRacuna(Racun *head)
{
    Racun *stari;
    while(head)
    {
        stari = head;
        head = head->sled;
        free(stari);
    }
    printf("SVI RACUNI SU OBRISANI!\n\n");
    return head;
}


Racun *testPodaci()
{
    Racun *r1 = malloc(sizeof(Racun));
    Racun *r2 = malloc(sizeof(Racun));
    Racun *r3 = malloc(sizeof(Racun));
    Racun *r4 = malloc(sizeof(Racun));
    Racun *r5 = malloc(sizeof(Racun));
    Racun *head;

    head = r1;

    r1->broj = 123;

    strcpy(r1->primalac,"Struja");

    strcpy(r1->uplatilac,"Petar Petrovic");
    r1->iznos = 2305.56;
    r1->indikator = 0;
    r1->sled = r2;
    r2->broj = 234;

    strcpy(r2->primalac,"Voda");

    strcpy(r2->uplatilac,"Petar Petrovic");
    r2->iznos = 1200.51;
    r2->indikator = 1;
    r2->sled = r3;
    r3->broj = 345;

    strcpy(r3->primalac, "Info");

    strcpy(r3->uplatilac,"Petar Petrovic");
    r3->iznos = 1206.16;
    r3->indikator = 0;
    r3->sled = r4;
    r4->broj = 456;

    strcpy(r4->primalac,"Telefon");

    strcpy(r4->uplatilac,"Petar Petrovic");
    r4->iznos = 301.50;
    r4->indikator = 0;
    r4->sled = r5;
    r5->broj = 567;

    strcpy(r5->primalac,"Internet");

    strcpy(r5->uplatilac,"Petar Petrovic");
    r5->iznos = 3000.0;
    r5->indikator = 0;
    r5->sled = NULL;
    return head;
}
