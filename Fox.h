#pragma once

#include <string>
#include <ctime>
#include "Gender.h"

using namespace std;

class Fox

{


public:
	Fox() : Age(0), Gender(static_cast<EGender>(rand() % 2))
	{
		SetRandomName();
	}


	int Age;
	EGender Gender;

	const static int MaxAge = 20;
	const static int HuntAge = 2;
	
	int HauntedTurn = 0;
	const static int MaxHauntedTurn = 5;
	bool Breeded = false;
	const static int MinAdulthoodAge = 2;
	int randomindex;
	string Name;

	bool GetIsHuntingAge() const;

	void SetRandomName();

};
