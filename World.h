#pragma once
#include "Fox.h"
#include "Rabbit.h"
#include "Gender.h"
#include "Names.h"
#include "Grass.h"


using namespace std;


class World
{
public:
	std::vector<Rabbit*> RabbitColony;
	std::vector<Fox*> FoxColony;
	std::vector<Rabbit*>RabbitGhostColony;
	Grass Grass;

	int Turn;
	const int MaxRabbits = 50;

	World() : Turn(0)
	{
	}

	void IncreaseAnimalsAge();

	bool CheckForMaleRabbit() const;

	bool CheckForVampireRabbit() const;

	void VampireRabbitInfection();

	void CheckForMaxRabbit();

	void FoxesHaveLowFood();


	void RabbitEat();



	void DecreasingRabbitGhostTurn();

	void GrassGrown();

	void CheckForEnoughGrass();

	int TotalVampireRabbit() const;

	int TotalGhostRabbit() const;

	int RandomChance(int chance);
	void TransferRabbitToGhost(Fox* fox, Rabbit* rabbit);;

	void FoxEat();

	void FoxBreed();


	void DecreaseInfection();
	void RabbitDie();

	void RabbitBreed();

	//  Unused?
	int RabbitColonyWithoutGhosts();

	void Tick();

	void Print() const;
};

