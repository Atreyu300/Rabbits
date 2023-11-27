#pragma once


#include <string>
#include <iostream>
#include "Color.h"
#include "Gender.h"
#include "Names.h"

class Rabbit
{
public:
	int Age;
	EGender Gender;
	EColor Color;
	bool Vampire;

	int randomindex;
	std::string Name = "TempName";

	int GhostTurn = 0;
	int MaxGhostTurn = 11;

	// TODO: Use a pointer to check if the mother is still alive
	Rabbit* Mother = nullptr; // What's happen when it's born in the beginning without mother?? will be not valid? *******************
	// Not valid mother pointer can be our condition to check if mother still alive?? **********************

	const static int MaxAge = 10;
	const static int MinAdulthoodAge = 2;
	const static int VampireMaxAge = 50;

	int Hungry = ((Vampire) ? 4 : 2);

	// Constructors 
	Rabbit() = delete;


	Rabbit(EColor color, bool vampire) : Age(0), Gender(static_cast<EGender>(rand() % 2)),
		Color(color), Vampire(vampire)
	{
		SetRandomName();
	}

	// Functions 

	

	~Rabbit()
	{

	}

	void SetRandomName();

	bool IsGhost() const;
	// SendAnalytics("New Rabbit");

	void OnGhostRabbitDeath() const;

};

