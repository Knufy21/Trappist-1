#pragma once

// Zusammenfassung vieler pseudozuf�lligen Funktionen.
namespace Randomf
{
	// Setzt den Seed f�r den Pseudozufallsgenerator mit der aktuellen Zeit.
	void seed();

	// Setzt den Seed f�r den Pseudozufallsgenerator mit dem angegebenen Seed.
	void seed(unsigned int seed);

	// Erzeugt einen pseudozuf�lligen Wahrheitswert, der mit angegebener Warscheinlichkeit wahr ist.
	bool randomBool(float chancePercentage = 50.0f);

	// Erzeugt eine pseudozuf�llige Ganzzahl, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	int randomInt(int inclStart, int inclEnd);

	// Erzeugt eine pseudozuf�llige Gleitkommazahl, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	float randomFloat(float inclStart, float inclEnd);

	// Erzeugt eine pseudozuf�llige Pr�zisionsgleitkommazahl, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	double randomDouble(double inclStart, double inclEnd);

	// Erzeugt einen Block an pseudozuf�lligen Ganzzahlen mit angegebener Gr��e, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	int *randomIntBlock(int inclStart, int inclEnd, unsigned int blockSize);

	// Erzeugt einen Block an pseudozuf�lligen Gleitkommazahlen mit angegebener Gr��e, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	float *randomFloatBlock(float inclStart, float inclEnd, unsigned int blockSize);

	// Erzeugt einen Block an pseudozuf�lligen Pr�zisionsgleitkommazahlen mit angegebener Gr��e, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	double *randomDoubleBlock(double inclStart, double inclEnd, unsigned int blockSize);
}