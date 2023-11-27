#include "World.h"
#include <algorithm>
#include <numeric>

void World::IncreaseAnimalsAge()
{
	std::for_each(RabbitColony.begin(), RabbitColony.end(), [](Rabbit* rabbit)
		{
			rabbit->Age++;
		});

std:for_each(FoxColony.begin(), FoxColony.end(), [](Fox* fox)
	{
		fox->Age++;
	});
}

bool World::CheckForMaleRabbit() const
{
	return std::any_of(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit* rabbit)
		{
			return rabbit->Gender == EGender::Male && !rabbit->Vampire;
		});
}

bool World::CheckForVampireRabbit() const
{
	return std::any_of(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit* rabbit)
		{
			return rabbit->Vampire;
		});
}

void World::VampireRabbitInfection()
{
	if (CheckForVampireRabbit())
	{
		//Check for Vampire Rabbit Number
		const int VampireRabbitCount = TotalVampireRabbit();

		int TotalRabbitInfected = 0;
		for (int i = 0; i <= VampireRabbitCount; i++)
		{
			// 1. Always infect the first non-vampire
			// + always finding a target to infect, no need to loop
			// - non-random, always infects the oldest rabbits first
			// 2. Keep a list of non-vampire rabbits, rand in that list
			// + always finding a target to infect, no need to loop
			// - have to make sure list is up-to-date which makes code more complex
			// 3. Just do rand, if rand index is already a vampire do nothing
			// 4. Loop until a non-vampire is found
			// + we should find in a target, but have to loop
			// + simple code
			// - what happens if there are too many vampires
			// 5. Same like option 4, but loop no more than 10 times, if no targets found give up
			//
			// Option 3:
			int RandomRabbitIndex = RandomRabbitIndex = (rand() % RabbitColony.size());

			if (!RabbitColony[RandomRabbitIndex]->Vampire)
			{
				RabbitColony[RandomRabbitIndex]->Vampire = true;
				TotalRabbitInfected++;
			}

		}
		cout << "\n" << TotalRabbitInfected << " Rabbit infected!";
	}
}

void World::CheckForMaxRabbit()
{
	if (RabbitColony.size() >= MaxRabbits)
	{
		cout << "\nTotal rabbit: " << RabbitColony.size() << "\n";
		cout << "\nToo much rabbits, low food. Killing half colony.. \n";

		int HalfColony = RabbitColony.size() / 2;
		for (int i = 0; i < HalfColony; i++)
		{
			int RandomPosition = (rand() % RabbitColony.size());
			// cout << "Killing Rabbit in position: " << RandomPosition;
			delete RabbitColony[RandomPosition];    // deleting pointer from memory
			RabbitColony[RandomPosition] = nullptr;    // set on nullptr
			RabbitColony.erase(RabbitColony.begin() + (RandomPosition)); // erase object on vector
		}
		cout << "\nTotal rabbit: " << RabbitColony.size() << "\n";
	}
}

void World::FoxesHaveLowFood()
{
	int MissingFood = FoxColony.size() - RabbitColony.size();

	for (int i = 0; i < MissingFood; i++)
	{
		int CasualFox = rand() % FoxColony.size();
		delete FoxColony[CasualFox]; // cleaning memory
		FoxColony[CasualFox] = nullptr; // set variable to nullptr
		FoxColony.erase(FoxColony.begin() + CasualFox); // erasing variable from vector
		cout << "\nA Fox is dead by starving..";
	}
}

void World::RabbitEat()
{
	for (Rabbit* rabbit : RabbitColony)
	{
		if (&rabbit->GhostTurn != 0)
		{
			Grass.Quantity = std::max(0, Grass.Quantity - rabbit->Hungry);
		}
	}
}

void World::DecreasingRabbitGhostTurn()
{
	auto removalIt = std::remove_if(RabbitGhostColony.begin(), RabbitGhostColony.end(), [](Rabbit* rabbit)
		{
			if (rabbit->IsGhost())
			{
				rabbit->GhostTurn--;
				if (rabbit->GhostTurn == 0) {
					rabbit->OnGhostRabbitDeath();
					delete rabbit;
					return true;
				}

			}
			return false;
		});


	RabbitGhostColony.erase(removalIt, RabbitGhostColony.end()); // <-- is this correct?
	/* Pointer fun times
	Rabbit* m = new Rabbit(EColor::Black, false);
	Rabbit* b = new Rabbit(EColor::Black, false);
	b->Mother = m;
	delete m;
	for (Rabbit& r : RabbitColony)
	{
	if (r.Mother == m)
	{
	r.Mother = nullptr;
	}
	}
	b->Mother = nullptr;
	if (b->Mother != nullptr)
	{
	cout << "Rabbit " << b->Name << " is mourning the loss of his mother " << b->Mother->Name;
	}
	*/

	/* CODE ABOVE EQUIVALENT TO CODE BELOW
	for (int i = 0; i < RabbitGhostColony.size(); i++)

	// (Rabbit& rabbit : RabbitGhostColony)
	{
	Rabbit& rabbit = RabbitGhostColony[i];

	if (rabbit.GhostTurn != 0)
	{
	rabbit.GhostTurn--;
	if (rabbit.GhostTurn == 0)
	{
	RabbitGhostColony.erase(RabbitGhostColony.begin() + i);
	// Be careful when modifying vectors while looping over them
	// If you must, be very careful about what happens to the indices
	i--;
	cout << "\nGhost rabbit goes to the afterlife!"; //   * When the 5 turns expire, "Ghost rabbit X goes to the afterlife!" - needs to be printed on screen. (We haven't names yet)

	// rabbit.mother
	// "Mother X finally accepts the death of Y"
	}

	}
	}
	*/
}

void World::GrassGrown()
{
	Grass.Quantity = std::min(Grass.Quantity + 10, Grass.MaxQuantity);
}

void World::CheckForEnoughGrass()
{
	int NecessaryFood = 0;
	std::vector<Rabbit*> Colony = RabbitColony;
	/*
	{
	return std::any_of(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit& rabbit)
	{
	return rabbit.Vampire;
	});
	}
	*/

	// TODO: Turn into lambda; std::accumulate									************************DONE************************

	auto NecessaryFoodSum = [](int sum, const Rabbit* rabbit)
		{
			return sum + rabbit->Hungry;
		};
	NecessaryFood = std::accumulate(Colony.begin(), Colony.end(), 0, NecessaryFoodSum);
	cout << "\nNecessaryFood: " << NecessaryFood << " ";

	if (NecessaryFood <= Grass.Quantity)
	{
		return;
	}

	cout << "\nNot enough grass for rabbits. Some rabbit will die.";
	int FoodDifference = NecessaryFood - Grass.Quantity;
	int FoodToEat = 0;
	for (int i = 0; i < FoodDifference && !Colony.empty(); i++, FoodDifference -= FoodToEat)
	{
		int RandomRabbitIndex = rand() % Colony.size();

		const Rabbit* Rabbit = Colony[RandomRabbitIndex];
		FoodToEat = Rabbit->Hungry;
		Colony.erase(Colony.begin() + RandomRabbitIndex);
		cout << "\nA Rabbit is dead for starving..";
	}
}

int World::TotalVampireRabbit() const
{
	return std::count_if(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit* rabbit)
		{
			return rabbit->Vampire;
		});
}

int World::TotalGhostRabbit() const
{
	return RabbitGhostColony.size();
}



int World::RandomChance(int chance)
{
	int randomvalue = rand() % 100 < chance;
	return randomvalue;
}

void World::TransferRabbitToGhost(Fox* fox, Rabbit* rabbit)
{
	rabbit->GhostTurn = rabbit->MaxGhostTurn;
	auto it = std::find(RabbitColony.begin(), RabbitColony.end(), rabbit);
	RabbitColony.erase(it);
	RabbitGhostColony.push_back(rabbit);
	Rabbit* RabbitGhost = RabbitGhostColony[RabbitGhostColony.size() - 1];

	cout << "\nA Rabbit named " << RabbitGhost->Name << " is turned to ghost. ";
	if (RabbitGhost->Mother != nullptr)
	{
		cout << RabbitGhost->Mother->Name << " is looking for revenge!";
		return;
	}
	cout << "No one is looking for revenge!";
}

void World::FoxEat()
{
	bool EnoughFood = RabbitColony.size() > RabbitColony.size();
	if (!EnoughFood)
	{
		FoxesHaveLowFood();
	}

	for (int i = 0; i < FoxColony.size(); i++)
	{
		int RandomRabbitIndex = rand() % RabbitColony.size();
		Rabbit* rabbit = RabbitColony[RandomRabbitIndex];
		Fox* fox = FoxColony[i];

		if (!fox->GetIsHuntingAge() || rabbit->IsGhost())
		{
			continue;
		}
		if (RandomChance(85))
		{
			continue;
		}

		TransferRabbitToGhost(fox, rabbit);

		if (Grass.Quantity < Grass.MaxQuantity * 20 / 100 && RandomChance(50))
		{
			
			int RandomRabbitIndex2 = rand() % RabbitColony.size();
			Rabbit* rabbit2 = RabbitColony[RandomRabbitIndex2];
			TransferRabbitToGhost(fox, rabbit2);
			
		}
		
		FoxColony[i]->HauntedTurn = FoxColony[i]->MaxHauntedTurn;
		if (rabbit->Vampire && RandomChance(30))
		{
			FoxColony.erase(FoxColony.begin() + i);
		}
	}
}

void World::FoxBreed()
{

	for (int i = 0; i < FoxColony.size(); i++)
	{
		Fox* malefox = FoxColony[i];

		if ((malefox->Gender == EGender::Male)
			&& (!malefox->Breeded)
			&& (malefox->HauntedTurn == 0)
			&& (malefox->Age >= malefox->MinAdulthoodAge))
		{
			for (int j = 0; j < FoxColony.size(); j++)
			{
				Fox* femalefox = FoxColony[j];
				if ((femalefox->Gender == EGender::Female)
					&& (!femalefox->Breeded)
					&& (femalefox->HauntedTurn == 0)
					&& (femalefox->Age >= femalefox->MinAdulthoodAge))
				{
					malefox->Breeded = true;
					femalefox->Breeded = true;
					FoxColony.push_back(new Fox());
					const Fox* BabyFox = FoxColony[FoxColony.size() - 1];
					cout << "\nA baby Fox named " << BabyFox->Name << " is born!";
				}
			}
		}
	}
	for (Fox* fox : FoxColony)
	{
		fox->Breeded = false;
	}
}

void World::DecreaseInfection()
{
	for (Rabbit* rabbit : RabbitColony)
	{
		rabbit->GhostTurn = std::min(rabbit->GhostTurn - 1, 0);
	}

	for (Fox* fox : FoxColony)
	{
		fox->HauntedTurn = std::min(fox->HauntedTurn - 1, 0);
	}
}

void World::RabbitDie()
{
	for (int i = 0; i < RabbitColony.size(); ++i)
	{
		Rabbit* parentRabbit = RabbitColony[i];

		const bool ShouldDie =
			(parentRabbit->Age >= Rabbit::MaxAge && !parentRabbit->Vampire) ||
			(parentRabbit->Age >= Rabbit::VampireMaxAge && parentRabbit->Vampire);
		if (ShouldDie)
		{
			const string& Name = parentRabbit->Name;
			cout << "\nA rabbit named " << Name << " is dead!Vampire ? " << parentRabbit->Vampire;
			cout << "\nis the same vampire? " << (parentRabbit == RabbitColony[i]);
			parentRabbit = nullptr;
			RabbitColony.erase(RabbitColony.begin() + i);
			i--;
		}
	}
}

void World::RabbitBreed()
{
	const bool isThereAMaleRabbit = CheckForMaleRabbit();
	for (int i = 0; i < RabbitColony.size(); ++i)
	{
		Rabbit& parentRabbit = *RabbitColony[i];

		const bool ShouldGiveBirth = isThereAMaleRabbit &&
			parentRabbit.Age >= Rabbit::MinAdulthoodAge &&
			parentRabbit.Gender == EGender::Female &&
			!parentRabbit.Vampire;

		if (ShouldGiveBirth)
		{
			const bool ShouldSpawnVampire = RandomChance(2);
			RabbitColony.push_back(new Rabbit(parentRabbit.Color, ShouldSpawnVampire));
			// cout << "\nMom Rabbit name " << rabbit.Name;


			Rabbit& babyRabbit = *RabbitColony[RabbitColony.size() - 1];

			babyRabbit.Mother = &parentRabbit;
			//babyRabbit.Mother = 
			//	cout << "\nParent name " << parentRabbit.Name;

			cout << "\nA baby rabbit named " << babyRabbit.Name << " is born from mother " << babyRabbit.Mother->Name << " !Vampire ? " << ShouldSpawnVampire;
			if (cout.bad())
			{
				cout.clear();
			}
		}
	}
}

//  Unused?

int World::RabbitColonyWithoutGhosts()
{
	int x = 0;
	for (Rabbit* rabbit : RabbitColony)
		if (rabbit->GhostTurn >= 1)
		{
			x++;
		}

	return x;
}

void World::Tick()
{
	// Check if Rabbit colony is empty
	if (RabbitColony.empty()) {

		cout << "\nThe rabbit colony is dead!";
		exit;
	}

	//DecreaseInfection();
	DecreasingRabbitGhostTurn();

	CheckForMaxRabbit();

	GrassGrown();
	CheckForEnoughGrass();

	RabbitDie();
	RabbitBreed();
	RabbitEat();

	FoxBreed();
	FoxEat();

	VampireRabbitInfection();
	IncreaseAnimalsAge();

	Turn++;
}

void World::Print() const
{


	const char* GenderNames[] = { "Male", "Female" };
	const char* ColorNames[static_cast<int>(EColor::Count)] = { "White", "Black", "Brown", "Red", "Blue" };

	int TotalRabbitVampire = TotalVampireRabbit(); // Should be outside of World..? Imho yes
	int TotalRabbitGhost = TotalGhostRabbit();

	// Print 

	//cout << "\n Total Vampire Rabbit: " << (TotalRabbitVampire == 0) ? 0 : TotalRabbitVampire;
	cout << "\nTotal Grass: " << Grass.Quantity;
	cout << "\nTotal Rabbit Colony: " << RabbitColony.size() << " Vampire: " << TotalRabbitVampire << " Ghost: " << TotalRabbitGhost;
	cout << "\nTotal Foxes: " << FoxColony.size();
	cout << "\n\n";
}
