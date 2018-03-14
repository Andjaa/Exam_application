/*Program za prijavljivanje ispita na fakultetu*/
#include "header.h"
char zvijezdice[]="*************************************************";
char opcije[]="Na raspolaganju su vam sledece opcije:\n\t1 - Unos novog zahtjeva\n\t2 - Pregled svih zahtjeva\n\t3 - Rang lista\n\t4 - Statistika\n\t0 - Izlaz iz programa";
char lokacija[]="EVIDENCIJA.RTF ";
char crtice[]="-------------------------------------------------";
void interfejs();
void prijava_izlaska(FILE *studenti);
void pregled(FILE *studenti);
void razvrstavanje(FILE *studenti);
main()
{
  int opcija;
  FILE *studenti=OtvoriiliKreirajFajl(lokacija,"r+b");
  while(1)
  {
	  interfejs();
	  printf("\n%s\n%s\n\nUnesite broj opcije koju zelite:\n\t:> ",opcije,zvijezdice);
	  scanf("%d",&opcija);
	  system("cls");
	  switch(opcija)
	  {
	  case PRIJAVA_IZLASKA_NA_ISPIT:
		prijava_izlaska(studenti);
		  break;
      case PREGLED_PRIJAVLJENIH_STUDENATA:
         pregled(studenti);
		  break;
	  case RAZVRSTAVANJE_PRIJAVLJENIH_STUDENATA:
		razvrstavanje(studenti);
		  break;
 	  case DIN_MEM:
		  break;
	  case IZLAZ_IZ_PROGRAMA:
		  return;

	   }
	  system("pause");
	  system("cls");
  
  }
}
void interfejs()
{
	datum trenutni_d;
	vrijeme trenutno_v;
	trenutno_v=TrenutnoVrijeme(&trenutni_d);

	printf("%s\n\n\t  PRIJAVA IZLASKA NA ISPIT\n\n%02d:%02d - %02d/%02d/%d	  by Andjela Rajic\n%s",zvijezdice,trenutno_v.h,trenutno_v.m,trenutni_d.dan,trenutni_d.mjesec,trenutni_d.godina,zvijezdice);
}

void prijava_izlaska(FILE *studenti)
{
	int broj_studenata=0;
	prijava pom;
	interfejs();
	fseek(studenti,0,0);
	fread(&broj_studenata,sizeof(int),1,studenti);
	broj_studenata++;
	fseek(studenti,0,0);
	fwrite(&broj_studenata,sizeof(int),1,studenti);
	printf("\nUnesite vase ime:\> ");
	scanf("%s",pom.student_info.ime);
	printf("\nUnesite vase prezime:\>");
	scanf("%s",pom.student_info.prezime);
	printf("\nUnesite vas broj indeksa:\>");
	scanf("%d",&pom.student_info.broj_indexa);
	printf("\nIzaberite predmet koji zelite da polazete (1 - MAT3, 2 - PJ, 3 - ELK1, 4 - EN3, \n5 - TEK1, 6 - EM):\>");
	scanf("%d",&pom.sifra_predmeta);
	printf("\nSta polazete (1 - zadatke, 2 - teoriju, 3 - oboje):\>");
	scanf("%d",&pom.dio_ispita);
	fseek(studenti,0,2);
    fwrite(&pom,sizeof(prijava),1,studenti);
	printf("\n\nUspjesno ste se prijavili za izlazak na ispit.\n");
}
void pregled(FILE *studenti)
{
	int broj_studenata,i,j;
	prijava pom,niz_prijava[100];
	interfejs();
	fseek(studenti,0,0);
	fread(&broj_studenata,sizeof(int),1,studenti);
	for(i=0;i<broj_studenata;i++)
	{
		fread(&niz_prijava[i],sizeof(prijava),1,studenti);
	}

	for(i=0;i<broj_studenata-1;i++)
		for(j=i;j<broj_studenata;j++)
		{
			if(niz_prijava[i].sifra_predmeta<niz_prijava[j].sifra_predmeta)
			{
				pom=niz_prijava[i];
			    niz_prijava[i]=niz_prijava[j];
				niz_prijava[j]=pom;
			}
        }
		fseek(studenti,sizeof(int),0);
		for(i=0;i<broj_studenata;i++)
		{
		 fwrite(&niz_prijava[i],sizeof(prijava),1,studenti);
		}
	printf("\nIme i prezime\t\tPredmet\n%s",crtice);
	for(i=0;i<broj_studenata;i++)
	{
	 if(niz_prijava[i].sifra_predmeta==1)
	 printf("\n%c.  %-20s MAT3",niz_prijava[i].student_info.ime[0],niz_prijava[i].student_info.prezime);
	 else if(niz_prijava[i].sifra_predmeta==2)
      printf("\n%c.  %-20s PJ",niz_prijava[i].student_info.ime[0],niz_prijava[i].student_info.prezime);
	 else if(niz_prijava[i].sifra_predmeta==3)
      printf("\n%c.  %-20s ELK1",niz_prijava[i].student_info.ime[0],niz_prijava[i].student_info.prezime);
	 else if(niz_prijava[i].sifra_predmeta==4)
      printf("\n%c.  %-20s EN3",niz_prijava[i].student_info.ime[0],niz_prijava[i].student_info.prezime);
	 else if(niz_prijava[i].sifra_predmeta==5)
      printf("\n%c.  %-20s TEK1",niz_prijava[i].student_info.ime[0],niz_prijava[i].student_info.prezime);
	 else if(niz_prijava[i].sifra_predmeta==6)
      printf("\n%c.  %-20s EM",niz_prijava[i].student_info.ime[0],niz_prijava[i].student_info.prezime);

	}
}

void razvrstavanje(FILE *studenti)
{
	int broj_studenata,i,brojac_sifri=1,indikator=1,j;
	char niz_lokacija[][13]={
		{"MAT3_zadaci"},
		{"MAT3_teorija"},
		{"PJ_zadaci"},
		{"PJ_teorija"},
		{"ELE1_zadaci"},
		{"ELE1_teorija"},
		{"EN3_zadaci"},
		{"EN3_teorija"},
		{"TEK_zadaci"},
		{"TEK_teorija"},
		{"EM_zadaci"},
		{"EM_teorija"}
			
	};
	FILE *stampanje;
	prijava pom;
   for(j=0;j<12;j++)
   {    printf("\n\n%s:\n",niz_lokacija[j]);
		stampanje=fopen(niz_lokacija[j],"w+");
		fprintf(stampanje,"\nIspit:%s:\nStudenti koji su se prijavili:\n",niz_lokacija[j]);
		fseek(studenti,0,0);
		fread(&broj_studenata,sizeof(int),1,studenti);
		for(i=0;i<broj_studenata;i++)
		{
			fread(&pom,sizeof(prijava),1,studenti);
			if(pom.sifra_predmeta==brojac_sifri && (pom.dio_ispita==indikator || pom.dio_ispita==3) )
			{
				printf("\n%c.  %-20s%d",pom.student_info.ime[0],pom.student_info.prezime,pom.student_info.broj_indexa);
				fprintf(stampanje,"\n%c.  %-20s%d",pom.student_info.ime[0],pom.student_info.prezime,pom.student_info.broj_indexa);
			}
		}
		if(indikator==1)
			indikator=2;
		else if(indikator==2)
			indikator=1;
		if(j%2!=0)
		brojac_sifri++;
		fclose(stampanje);
   }

}