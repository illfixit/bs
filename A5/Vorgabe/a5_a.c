#include <stdio.h>

int breite;
int hoehe;
long dateigroesse;

int main( int argc, char *argv[] )  {

	// fopen(3), fclose(3), fseek(3), ftell(3), fscanf(3) und fprintf(3)

	// Überprüfen ob die richtige Anzahl an Argumenten übergeben wurde
	if(argc != 2) {
		printf("Falsche Anzahl an Argumenten\n");
		return 1;
	}

	// Datei öffnen
	FILE *bild = fopen(argv[1],"r");

	// Überprüfen ob die Datei geöffnet werden konnte
	if(bild == NULL) {
		printf("Fehler: Datei konnte nicht geöffnet werden\n");
		return 1;
	}

	// Breite und Höhe auslesen
	if(fscanf(bild,"P3%d %d",&breite,&hoehe) != 2) {
		printf("Fehler: Datei konnte nicht gelesen werden\n");
		return 1;
	}

	// Dateigröße auslesen
	fseek(bild, 0, SEEK_END); 
	long dateigroesse = ftell(bild); 
	fseek(bild, 0, SEEK_SET);

	// Datei schließen
	printf("Breite: %d \nHoehe: %d \nDateigroesse: %ld bytes\n",breite,hoehe,dateigroesse);
	return 0;
	
}