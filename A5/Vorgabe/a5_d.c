#include <stdio.h>
#include <stdlib.h>

int breite;
int hoehe;
int radius;
int rot;
int gruen;
int blau;
char *dateiname;

int inKreis(int x, int y, int x0, int y0, int r);

/*
d) Zusatzaufgabe: Kreis zeichnen (2 Sonderpunkte)
Für die Zusatzaufgabe soll ein C-Programm (a5_d.c) erstellt werden, das ein Bild mit einem Kreis
zeichnet und in einer Datei im Portable Pixmap-Format abspeichert. Die Breite und Höhe des Bildes,
sowie der Radius des Kreises in Pixeln und dessen Farbe sollen als Kommandozeilenparameter beim
Aufruf übergeben werden; zusätzlich soll noch der Pfad an dem das Bild abgespeichert wird angegeben
werden. Der Aufruf muss wie folgt aussehen:
./a5_d <Breite> <Höhe> <Radius> <Farbkomponente rot> <Farbkomponente grün> <Farb-
komponente blau> <Dateiname>.ppmBeispiel
studi@bsvm:~$ ./a5_d 20 20 5 20 10 200 beispiel_kreis.ppm
Breite
H ̈ohe Radius
Farbkomponente Rot
Farbkomponente Gr ̈un
Farbkomponente Blau
Dateiname
Die Ausgabedatei beispiel_kreis.ppm finden Sie in der Vorlage.
Der Kreis soll zentriert im Bild gezeichnet werden, die Mitte des Kreises ist also die Mitte des Bildes.
Denken Sie an eine ordentliche Fehlerbehandlung, zum Beispiel bei falscher Nutzereingabe, und
achten Sie darauf, dass Ihr Programm ordnungsgemäß hinter sich aufräumt.*/

int main( int argc, char *argv[] )  {

	// Überprüfen ob die richtige Anzahl an Argumenten übergeben wurde
	if(argc != 8){
		printf("Falsche Anzahl an Argumenten\n");
		return 1;
	}

	// Breite, Höhe, Radius, Farbkomponenten rot, grün, blau, Dateiname	
	breite = atoi(argv[1]);
	hoehe = atoi(argv[2]);
	radius = atoi(argv[3]);
	rot = atoi(argv[4]);
	gruen = atoi(argv[5]);
	blau = atoi(argv[6]);
	dateiname = argv[7];

	FILE *datei = fopen(dateiname, "w");

	if(datei == NULL){
		printf("Datei konnte nicht geöffnet werden\n");
		return 1;
	}

	fprintf(datei, "P3 %d %d 255", breite, hoehe);

	int x, y;
	for(y = 0; y < hoehe; y++){
		for(x = 0; x < breite; x++){
			// Kreisgleichung (x - x0)^2 + (y - y0)^2 = r^2
			if(inKreis(x, y, breite/2, hoehe/2, radius)){
			// alle Punkte die in dem Kreis liegen
				fprintf(datei, "%d %d %d ", rot, gruen, blau);
			}else{
				// alle Punkte die nicht in dem Kreis liegen
				fprintf(datei, "0 0 0 ");
			}
		}
		fprintf(datei, "\n");
	}

	if(fclose(datei) != 0){
		printf("Datei konnte nicht geschlossen werden\n");
		return 1;
	}

	return 0;
	
}

int inKreis(int x, int y, int x0, int y0, int r){
	int toleranz = 4;
	return ( (x-x0)*(x-x0) + (y-y0)*(y-y0) >= r*r - toleranz && 
		(x-x0)*(x-x0) + (y-y0)*(y-y0) <= r*r + toleranz);
}