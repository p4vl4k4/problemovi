#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>

typedef struct radnici {
	int sifra;
	char imeRadnika[21];
	char prezimeRadnika[21];
	float koeficijenat;
	int radniStaz;
}tipRadnika;


void unosRadnika(tipRadnika* pradnik) {
	puts("Unesi podatke o radniku:");
	printf("Unesi sifru radnika:\n");
	scanf("%d", &pradnik->sifra);
	puts("Unesi ime radnika:");
	scanf("%s", &pradnik->imeRadnika);
	puts("Unesi prezime radnika:");
	scanf("%s", &pradnik->prezimeRadnika);
	puts("Unesi koeficijenat radnika:");
	scanf("%f", &pradnik->koeficijenat);
	printf("Unesi radni staz:\n");
	scanf("%d", &pradnik->radniStaz);
}

void prikaziRadnika(tipRadnika radnik)
{
	puts("\nPodaci o radniku:");
	printf("Sifra radnika: %d\n", radnik.sifra);
	printf("Ime radnika: %s\n", radnik.imeRadnika);
	printf("Prezime radnika: %s\n", radnik.prezimeRadnika);
	printf("Koeficijenat radnika: %.2f\n", radnik.koeficijenat);
	printf("Radni staz radnika: %d\n", radnik.radniStaz);
}

void brisiRadnika(int* n, tipRadnika radnici[], int redniBr) {
	int i, j = 0;
	for (i = redniBr - 1; i < *n - 1; i++)
	{
		radnici[i] = radnici[i + 1];
	}
	(*n)--;
}

void upisiRadnike(tipRadnika radnik[], int brRadnika) {
	FILE* fpr = fopen("radnici.txt", "w");
	if (fpr == NULL) {
		printf("Greska pri otvaranju fajla\n");
		return;
	}
	for (int i = 0; i < brRadnika; i++) {
		fprintf(fpr, "%d %s %s %.2f %d\n", radnik[i].sifra, radnik[i].imeRadnika, radnik[i].prezimeRadnika, radnik[i].koeficijenat, radnik[i].radniStaz);
	}
	fclose(fpr);
}

void procitajRadnike(FILE* pfradnik, tipRadnika* radnik)
{
	fscanf(pfradnik, "%d", &radnik->sifra);
	fscanf(pfradnik, "%s", radnik->imeRadnika);
	fscanf(pfradnik, "%s", radnik->prezimeRadnika);
	fscanf(pfradnik, "%.2f", &radnik->koeficijenat);
	fscanf(pfradnik, "%d", &radnik->radniStaz);
}

void kopiraj_u_fajl(FILE* pftxt, tipRadnika radnik)
{
	fprintf(pftxt, "%d\n", radnik.sifra);
	fprintf(pftxt, "%s\n", radnik.imeRadnika);
	fprintf(pftxt, "%s\n", radnik.prezimeRadnika);
	fprintf(pftxt, "%f\n", radnik.koeficijenat);
	fprintf(pftxt, "%d\n", radnik.radniStaz);
}

void izmeniRadnika(tipRadnika* radnik, int odredjenaSifra) {

	printf("Izmena podataka za radnika sa sifrom %d\n", radnik->sifra);
	printf("Unesi novo ime radnika: \n");
	scanf("%s", radnik->imeRadnika);
	printf("Unesi novo prezime radnika: \n");
	scanf("%s", radnik->prezimeRadnika);
	printf("Unesi novi koeficijenat radnika: \n");
	scanf("%f", &radnik->koeficijenat);
	printf("Unesi novi radni staz radnika: \n");
	scanf("%d", &radnik->radniStaz);

}

bool trazeniKoeficijenat(tipRadnika radnik, float trazeniKoef) {
	return radnik.koeficijenat == trazeniKoef;
}

float izracunajTrenutnuZaradu(tipRadnika radnik, float trenutnaCenaRada) {
	return radnik.koeficijenat * trenutnaCenaRada * (1 + radnik.radniStaz * 0.5 / 100);
}

int prebrojRadnikeSaTrazenimKoeficijentom(tipRadnika radnici[], int n, float trazeniKoef) {
	int brojac = 0;
	for (int i = 0; i < n; i++) {
		if (radnici[i].koeficijenat == trazeniKoef)
			brojac++;
	}
	return brojac;
}

int main()
{

	FILE* pr;
	int brRadnika, izbor, redniBroj;
	tipRadnika radnici[100];
	char imeFajla[80];
	int i, odaberiSifru, trazenaSifra;
	float trazeniKoef, trenutnaCenaRada, trenutnaZarada;




	while (1) {
		puts("****************************************************");
		puts("* MENI ");
		puts("* 1 - Otvaranje tekstualnog fajla");
		puts("* 2 - Snimanje radnika u tekstualni fajl");
		puts("* 3 - Unos novog radnika");
		puts("* 4 - Prikaz radnika(sa unetog rednog broja)");
		puts("* 5 - Prikaz svih radnika");
		puts("* 6 - Brisanje podataka o nekom radniku");
		puts("* 7 - Izmena podataka o nekom radniku");
		puts("* 8 - Provera da li radnik sa datim rednim brojem ima trazeni koeficijenat");
		puts("* 9 - Izracunavanje zarade radnika sa datim rednim brojem");
		puts("* 10 - Prebrojavanje radnika sa datim koeficijentom");
		puts("* 0 - Kraj programa");


		printf("Odaberi: \n");
		scanf("%d", &izbor);

		switch (izbor)
		{

		case 0:
			//kraj fajla
			pr = fopen("radnici.txt", "r");
			if (pr != NULL)
				return 0;
			fclose(pr);
			break;
		case 1:
			// 1 - Otvaranje tekstualnog fajla
			pr = fopen("radnici.txt", "r");
			if (pr == NULL)
				puts("Greska pri otvaranju fajla!");
			else
			{
				i = 0;
				while (!feof(pr))
				{
					procitajRadnike(pr, &radnici[i]);
					i++;
				}
				int n = i;
				fclose(pr);
				printf("Fajl je otvoren, procitano je %d radnika!\n", n / 2);
			}
			break;
		case 2:
			// snimanje radnika u fajl
			pr = fopen("radnici.txt", "w");
			if (pr == NULL)
				puts("Greska pri kreiranju fajla!");
			else
			{
				for (i = 0; i < brRadnika; i++)
					kopiraj_u_fajl(pr, radnici[i]);
				fclose(pr);
				puts("Fajl je kreiran!");
			}
			break;
		case 3:
			//unos novog radnika
			printf("Koliko radnika unosis: \n");
			scanf("%d", &brRadnika);
			for (i = 0; i < brRadnika; i++) {
				unosRadnika(&radnici[i]);
			}
			break;
		case 4:
			//prikaz radnika sa rednim brojem
			printf("Unesi redni broj radnika za prikaz:\n");
			scanf("%d", &redniBroj);
			prikaziRadnika(radnici[redniBroj - 1]);
			break;
		case 5:
			//prikaz svih radnika
			for (i = 0; i < brRadnika; i++)
				if (brRadnika > 0)
					prikaziRadnika(radnici[i]);
				else
					printf("Do sada nije unet ni jedan radnik");
			break;
		case 6:
			//brisanje podataka o radniku sa datim rednim brojem
			printf("Unesi redni broj:\n");
			scanf("%d", &redniBroj);//scanf_s
			brisiRadnika(&brRadnika, radnici, redniBroj);
			break;
		case 7:
			//izmena podataka o radniku sa datom sifrom
			printf("Unesi sifru radnika za koga zelis da izmenis podatke:\n");
			scanf("%d", &odaberiSifru);
			for (i = 0; i < brRadnika; i++) {
				if (radnici[i].sifra == odaberiSifru)
					izmeniRadnika(&radnici[i], odaberiSifru);
			}
			break;
		case 8:
			//provera da li radnik sa datim rednim brojem ima trazeni koeficijenat
			printf("Unesi trazeni koeficijenat: \n");
			scanf("%f", &trazeniKoef);
			for (i = 0; i < brRadnika; i++) {
				if (trazeniKoeficijenat(radnici[i], trazeniKoef)) {
					printf("Radnik sa trazenim koeficijentom je sa rednim brojm %d.\n", i + 1);
				}
				else
				{
					printf("Nije pronadjen radnik sa trazenim koeficijentom\n");
				}
			}
			break;
		case 9:
			printf("Unesi sifru radnika za koga zelis da izracunas zaradu:\n");
			scanf("%d", &trazenaSifra);
			for (i = 0; i < brRadnika; i++) {
				if (radnici[i].sifra == trazenaSifra) {
					printf("Unesi trenutnu cenu rada: \n");
					scanf("%f", &trenutnaCenaRada);
					trenutnaZarada = izracunajTrenutnuZaradu(radnici[i], trenutnaCenaRada);
					printf("Trenutna zarada datog radnika je: %.2f\n", trenutnaZarada);
				}
				else
					printf("Radnik sa datom sifrom nije pronadjen");
			}
			break;
		case 10:
			int brojRadnikaSaTrazenimKoeficijentom;
			printf("Unesi trazeni koeficijenat: \n");
			scanf("%f", &trazeniKoef);
			brojRadnikaSaTrazenimKoeficijentom = prebrojRadnikeSaTrazenimKoeficijentom(radnici, brRadnika, trazeniKoef);
			printf("Broj radnika sa trazenim koeficijenotm: %d\n", brojRadnikaSaTrazenimKoeficijentom);
			break;
		default:
			puts("pogresan izbor, pokusajte ponovo!");
		}
	}
}

