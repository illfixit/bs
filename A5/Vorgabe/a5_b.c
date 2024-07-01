#include <stdio.h>
#include <stdlib.h>

int breite;
int hoehe;
int farbkomponente_rot;
int farbkomponente_gruen;
int farbkomponente_blau;
char dateiname[100];

// fopen(3), fclose(3), fseek(3), ftell(3), fscanf(3) und fprintf(3)
int main(int argc, char *argv[])
{

	/*
	In dieser Teilaufgabe soll ein C-Programm (a5_b.c) implementiert werden, bei dem ihr eine Bilddatei
	im Portable Pixmap-Format mit einer Farbe durchgehend füllt. Hierbei sollen die Pixeldaten in ASCII
	kodiert werden, der Maximalwert für die Helligkeit soll 255 sein. Die Breite, Höhe und zu verwendende
	Farbe sollen als Kommandozeilenparameter beim Aufruf übergeben werden; zusätzlich soll noch der
	Pfad, in dem das Bild abgespeichert wird, angegeben werden. Der Aufruf muss wie folgt aussehen:
	./a5_b <Breite> <Höhe> <Farbkomponente rot> <Farbkomponente grün> <Farbkomponente blau> <Dateiname>.ppm

	Beispiel
	studi@bsvm:~$ ./a5 b 10 12 120 200 50 beispiel b.ppm
	*/

	// Überprüfen ob die richtige Anzahl an Argumenten übergeben wurde
	if (argc != 7)
	{
		printf("Falsche Anzahl an Argumenten\n");
		return 1;
	}

	// Breite und Hoehe auslesen und von einem String in einen Integer umwandeln
	breite = atoi(argv[1]);
	hoehe = atoi(argv[2]);
	farbkomponente_rot = atoi(argv[3]);
	farbkomponente_gruen = atoi(argv[4]);
	farbkomponente_blau = atoi(argv[5]);
	sprintf(dateiname, "%s", argv[6]);

	// Datei öffnen	
	FILE *bild = fopen(dateiname, "w");

	// Überprüfen ob die Datei geöffnet werden konnte
	if (bild == NULL)
	{
		printf("Fehler: Datei konnte nicht geöffnet werden\n");
		return 1;
	}

	// Schreibe die Kopfzeile in die Datei
	fprintf(bild, "P3 %d %d 255 ", breite, hoehe);

	// Fuege die Farbkomponenten in die Datei ein
	for (int y = 0; y < hoehe; y++)
	{
		for (int x = 0; x < breite; x++)
		{
			fprintf(bild, "%d %d %d ", farbkomponente_rot, farbkomponente_gruen, farbkomponente_blau);
		}
		fprintf(bild, "\n"); // Neue Zeile
	}

	// Schließen der Datei mit Fehlerbehandlung
	if(fclose(bild) != 0){
		printf("Fehler: Datei konnte nicht geschlossen werden\n");
		return 1;
	} 

	printf("Breite: %d \nHoehe: %d \nFarbkomponente Rot: %d \nFarbkomponente Grün: %d \nFarbkomponente Blau: %d \nDateiname: %s\n", breite, hoehe, farbkomponente_rot, farbkomponente_gruen, farbkomponente_blau, dateiname);

	return 0;
}