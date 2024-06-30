#include <stdio.h>
#include <stdlib.h>

int breite;
int hoehe;
int start_farbkomponente_rot;
int start_farbkomponente_gruen;
int start_farbkomponente_blau;
int ziel_farbkomponente_rot;
int ziel_farbkomponente_gruen;
int ziel_farbkomponente_blau;

char dateiname[100];

int calculate_color(int start, int ziel, int x, int breite);

// fopen(3), fclose(3), fseek(3), ftell(3), fscanf(3) und fprintf(3)
int main(int argc, char *argv[])
{

	/*
	In dieser Teilaufgabe soll ein C-Programm (a5_c.c) implementiert werden, das einen Farbgradienten
	in einer Datei im Portable Pixmap-Format abspeichert. Hierbei sollen die Pixeldaten in ASCII kodiert
	werden, der Maximalwert für die Helligkeit soll 255 sein. In der Mitte des Gradienten sollen Start-
	und Zielfarbe im gleichen Verhältnis vorkommen. Der Gradient soll von einer Startfarbe gleichmäßig
	in eine Zielfarbe übergehen. Der Gradient soll von links nach rechts verlaufen. Hierbei sollen Breite
	und Höhe, sowie die Start- und Zielfarben als Kommandozeilenparameter beim Aufruf übergeben
	werden; zusätzlich soll noch der Pfad, in dem das Bild abgespeichert wird, angegeben werden. Der
	Aufruf muss wie folgt aussehen:

	./a5_c <Breite> <Höhe> <Rotanteil Startfarbe> <Grünanteil Startfarbe> <Blauanteil Startfar-
	be> <Rotanteil Zielfarbe> <Grünanteil Zielfarbe> <Blauanteil Zielfarbe> <Dateiname>.ppm

	Beispiel
	studi@bsvm:~$ ./a5_c 20 10 120 200 50 20 150 200 beispiel_c.ppm
	*/

	if (argc != 10)
	{
		printf("Falsche Anzahl an Argumenten\n");
		return 1;
	}

	// Breite und Hoehe auslesen und von einem String in einen Integer umwandeln
	breite = atoi(argv[1]);
	hoehe = atoi(argv[2]);
	start_farbkomponente_rot = atoi(argv[3]);
	start_farbkomponente_gruen = atoi(argv[4]);
	start_farbkomponente_blau = atoi(argv[5]);
	ziel_farbkomponente_rot = atoi(argv[6]);
	ziel_farbkomponente_gruen = atoi(argv[7]);
	ziel_farbkomponente_blau = atoi(argv[8]);
	sprintf(dateiname, "%s", argv[6]);

	FILE *bild = fopen(dateiname, "w");

	if (bild == NULL)
	{
		printf("Fehler: Datei konnte nicht geöffnet werden\n");
		return 1;
	}

	// After opening the file and before the return statement

	// Write the PPM header
	fprintf(bild, "P3 %d %d 255 ", breite, hoehe);

	// Write the pixel data
	for (int y = 0; y < hoehe; y++)
	{
		for (int x = 0; x < breite; x++)
		{
			int rot = calculate_color(start_farbkomponente_rot, ziel_farbkomponente_rot, x, breite);
			int gruen = calculate_color(start_farbkomponente_gruen, ziel_farbkomponente_gruen, x, breite);
			int blau = calculate_color(start_farbkomponente_blau, ziel_farbkomponente_blau, x, breite);
			fprintf(bild, "%d %d %d ", rot, gruen, blau);
		}
		fprintf(bild, "\n"); // New line at the end of each row
	}

	fclose(bild); // Don't forget to close the file

	return 0;
}

int calculate_color(int start, int ziel, int x, int breite)
{
	return start + (ziel - start) * x / breite;
}