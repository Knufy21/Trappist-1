#pragma once

// Zusammenfassung vieler pseudozufälligen Funktionen.
namespace Randomf
{
	// Setzt den Seed für den Pseudozufallsgenerator mit der aktuellen Zeit.
	void seed();

	// Setzt den Seed für den Pseudozufallsgenerator mit dem angegebenen Seed.
	void seed(unsigned int seed);

	// Erzeugt einen pseudozufälligen Wahrheitswert, der mit angegebener Warscheinlichkeit wahr ist.
	bool randomBool(float chancePercentage = 50.0f);

	// Erzeugt eine pseudozufällige Ganzzahl, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	int randomInt(int inclStart, int inclEnd);

	// Erzeugt eine pseudozufällige Gleitkommazahl, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	float randomFloat(float inclStart, float inclEnd);

	// Erzeugt eine pseudozufällige Präzisionsgleitkommazahl, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	double randomDouble(double inclStart, double inclEnd);

	// Erzeugt einen Block an pseudozufälligen Ganzzahlen mit angegebener Größe, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	int *randomIntBlock(int inclStart, int inclEnd, unsigned int blockSize);

	// Erzeugt einen Block an pseudozufälligen Gleitkommazahlen mit angegebener Größe, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	float *randomFloatBlock(float inclStart, float inclEnd, unsigned int blockSize);

	// Erzeugt einen Block an pseudozufälligen Präzisionsgleitkommazahlen mit angegebener Größe, die im angegebenen Bereich liegt(Anfangs - &Endwert inklusive).
	double *randomDoubleBlock(double inclStart, double inclEnd, unsigned int blockSize);
}