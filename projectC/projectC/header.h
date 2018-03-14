#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRIJAVA_IZLASKA_NA_ISPIT 1
#define PREGLED_PRIJAVLJENIH_STUDENATA 2
#define RAZVRSTAVANJE_PRIJAVLJENIH_STUDENATA 3
#define DIN_MEM 4
#define IZLAZ_IZ_PROGRAMA 0

#define MAT3 1
#define PJ 2
#define ELK1 3
#define EN3 4
#define TEK1 5
#define EM 6

char nazivi_predmeta[][5] = {
	{"MAT3"},
	{"PJ"},
	{"ELK1"},
	{"EN3"},
	{"TEK1"},
	{"EM"}
};

typedef struct
{
	char ime[25];
	char prezime[25];
	int broj_indexa;
	char smjer[50];
	int godina_studija;
	char datum_rodjenja[30];
	char datum_upisa[30];
	int broj_polozenih_ispita;
	char ocijene[48];
	float projek_osnovne_studije;
	float projsek_strukovne_studije;
	float prosjek;
}student;

typedef struct
{
	student student_info;
	int sifra_predmeta;
	int dio_ispita;
}prijava;

typedef struct
{
	char ime[25];
	char prezime[25];
	char funkcija[30];
	float staz;
	char JMBG[14];
}radnik;

typedef struct
{
	int h;
	int m;
	int s;
}vrijeme;

typedef struct
{
	int dan;
	int mjesec;
	int godina;
}datum;

void Test();

vrijeme TrenutnoVrijeme(datum *danasnji_datum);

FILE *OtvoriiliKreirajFajl(char lokacija[], char argumenti[]);

void Test()
{
	FILE *test;
	printf("Ova funkcija je pozvana iz header fajla PJ.h\n\n");
	test = fopen("test123.txt", "w");
	fprintf(test, "Zdravo");
	fclose(test);
}

vrijeme TrenutnoVrijeme(datum *danasnji_datum)
{
	time_t t;
	struct tm *v;
	vrijeme rez;

	time(&t);
	v = localtime(&t);
	
	rez.h = v->tm_hour;
	rez.m = v->tm_min;
	rez.s = v->tm_sec;
	danasnji_datum->dan = v->tm_mday;
	danasnji_datum->mjesec = v->tm_mon;
	danasnji_datum->godina = 1900 + v->tm_year;

	return rez;
}

FILE *OtvoriiliKreirajFajl(char lokacija[], char argumenti[])
{
	FILE *baza;
	baza = fopen(lokacija, argumenti);
	if(baza == NULL)
	{
		baza = fopen(lokacija, "w");
		if(baza == NULL)
		{
			printf("\n\n\t\tGRESKA: Problem prilikom otvaranja fajla. Vjerovatno putanja:\n\t\t\t%s\n\t\tne postoji.\n\n", lokacija);
			return(NULL);
		}
		fclose(baza);
		baza = fopen(lokacija, argumenti);
	}
	return(baza);
}