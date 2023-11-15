
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <chrono>
#include <functional>
#include <string>
#include <numeric>
#include <thread>

// TODO:
// - Read on lambdas
// - Read on pointers
// - Read on vectors - how would you write your own vector if I asked you?
// class vector
// {
//		???
// }
// - rename all functions to have verbs as names (e.g. "FeedFoxes", "BreedFoxes", etc.)
// - do the todos in the code
// - [optional] use <algorithm> functions and lambdas to make code simpler


using namespace std;

enum class EGender
{
	Male,
	Female
};

enum class EColor
{
	White,
	Black,
	Brown,
	Red,
	Blue,
	Count
};

enum class ENamesMale // 20 Male Names
{
	Michael, Joe, Nick, Stephen, Henry, William, Levi, Jack, Owen, Leo, Ethan, Lucas, Benjamin, Liam, Samuel, Luke, Elia, Thomas, Brad, Jake
}; 

enum class ENamesFemale // 20 Female Names 
{
	Olivia, Emma, Charlotte, Amelia, Sophia, Isabella, Ava, Mia, Evelyn, Luna, Harper, Camila, Sofia, Scarlett, Elizabeth, Elanor, Emily, Aria, Nami, 

};

vector<string>NamesMale = { "Michael", "Joe", "Nick", "Stephen", "Henry", "William", "Levi", "Jack", "Owen", "Leo", "Ethan", "Lucas", "Benjamin", "Liam", "Samuel", "Luke", "Elia", "Thomas", "Brad", "Jake"};
vector<string>NamesFemale = { "Olivia", "Emma", "Charlotte", "Amelia", "Sophia", "Isabella", "Ava", "Mia", "Evelyn", "Luna", "Harper", "Camila", "Sofia", "Scarlett", "Elizabeth", "Elanor", "Emily", "Aria", "Nami"};

enum class DataType
{
	Fox,
	Rabbit,
	Grass
};

// What happens to mother and the murderer? How do we know if they are still alive?
struct Rabbit
{
	int Age;
	EGender Gender;
	EColor Color;
	bool Vampire;
	
	int randomindex;
	string Name = "TempName";
	
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

	void SetRandomName()
	{
		if (Gender == EGender::Male) // there is a way to check what's value has this Gender on runtime wihtout cout?
		{
			randomindex = rand() % NamesMale.size();
			Name = NamesMale[randomindex];
			//cout << "\n" << Name;
		}
		else
		{
			randomindex = rand() % NamesFemale.size();
			Name = NamesFemale[randomindex];
			//cout << "\n" << Name;
		}
	}

	bool IsGhost() const
	{
		return GhostTurn != 0;
	}

	// SendAnalytics("New Rabbit");
	
	void OnGhostRabbitDeath() const
	{
		if (!Mother)
		{
			return;
		}
		cout << "\nMother " << Mother->Name << " finally accepts the death of " << Name;
		if (cout.bad())
		{
			cout.clear();
		}
	}

	~Rabbit()
	{

	}
};

struct Fox 

{
	int Age;
	EGender Gender;

	Fox() : Age(0), Gender(static_cast<EGender>(rand()% 2))
	{
		SetRandomName();
	}

	const static int MaxAge = 20;
	const static int HuntAge = 2;
	// TODO: Add names
	// TODO: For haunted foxes, keep a pointer to their ghost
	// - what happens if the pointer to the rabbit becomes invalid before the fox has died?
	// 1. ...
	// 2. ...
	// 3. ...
	int HauntedTurn = 0;
	const static int MaxHauntedTurn = 5;
	bool Breeded = false;
	const static int MinAdulthoodAge = 2;
	int randomindex;
	string Name;

	bool GetIsHuntingAge() const
	{
		return Age >= HuntAge;
	}

	void SetRandomName()
	{
		if (Gender == EGender::Male) // there is a way to check what's value has this Gender on runtime wihtout cout?
		{
			randomindex = rand() % NamesMale.size();
			Name = NamesMale[randomindex];
			//cout << "\n" << Name;
		}
		else
		{
			randomindex = rand() % NamesFemale.size();
			Name = NamesFemale[randomindex];
			//cout << "\n" << Name;
		}
	}

};

struct Grass 
{
	int Quantity = 500;
	const int MaxQuantity = 500;
};

void GameOver(string message)
{
	cout << "Game Over! " << message;
}


class World* GWorld;

struct World
{
	std::vector<Rabbit*> RabbitColony;
	std::vector<Fox*> FoxColony;
	std::vector<Rabbit*>RabbitGhostColony;
	Grass Grass;								

	int Turn;
	const int MaxRabbits = 50;

	World() : Turn(0)
	{
	}

	void IncreaseAnimalsAge()					
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

	bool CheckForMaleRabbit() const
	{
		return std::any_of(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit* rabbit)
			{
				return rabbit->Gender == EGender::Male && !rabbit->Vampire;
			});
	}
	
	bool CheckForVampireRabbit() const
	{
		return std::any_of(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit* rabbit)
			{
				return rabbit->Vampire;
			});
	}

	void VampireRabbitInfection() 
	{
		if (CheckForVampireRabbit())
		{
			//Check for Vampire Rabbit Number
			const int VampireRabbitCount = TotalVampireRabbit();

			int TotalRabbitInfected = 0;
			for (int i=0; i <= VampireRabbitCount; i++)
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
	
	void CheckForMaxRabbit() 
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

	void FoxesHaveLowFood()
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
	

	void RabbitEat() 
	{
		for (Rabbit* rabbit : RabbitColony)
		{
			if (&rabbit->GhostTurn != 0) 
			{
				Grass.Quantity = std::max(0, Grass.Quantity - rabbit->Hungry);
			}
		}
	}



	void DecreasingRabbitGhostTurn()
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
	
	void GrassGrown() 
	{
		Grass.Quantity = std::min(Grass.Quantity + 10, Grass.MaxQuantity);
	}

	void CheckForEnoughGrass() 
	{
		int NecessaryFood = 0;
		std::vector<Rabbit*>& Colony = RabbitColony;
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
	
	int TotalVampireRabbit() const
	{
		return std::count_if(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit* rabbit)
			{
				return rabbit->Vampire;
			});
	}

	int TotalGhostRabbit() const
	{
		return RabbitGhostColony.size();
	}

	void KillRabbit(Fox&, Rabbit&)
	{
	}

	int RandomChance(int chance)
	{
		int randomvalue = rand() % 100 < chance;
		return randomvalue;
	}
	void TransferRabbitToGhost(Fox* fox, Rabbit* rabbit)
	{
		rabbit->GhostTurn = rabbit->MaxGhostTurn;
		auto it = std::find(RabbitColony.begin(), RabbitColony.end(), rabbit);
		RabbitColony.erase(it);
		RabbitGhostColony.push_back(rabbit);
		Rabbit* RabbitGhost = RabbitGhostColony[RabbitGhostColony.size() - 1];

		cout << "\nA Rabbit named " << RabbitGhost->Name << " is turned to ghost. ";
		if (RabbitGhost->Mother!=nullptr)
		{
			cout << RabbitGhost->Mother->Name << " is looking for revenge!";
			return;
		}
		cout << "No one is looking for revenge!";
	};

	void FoxEat()
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

			if (Grass.Quantity < Grass.MaxQuantity*20/100 && RandomChance(50))
			{
				// TODO: Make a new function KillRabbit(Fox&, Rabbit&) and call it twice instead of copy/pasting code ********DONE**********
				
				int RandomRabbitIndex2 = rand() % RabbitColony.size();
				Rabbit* rabbit2 = RabbitColony[RandomRabbitIndex2];
				TransferRabbitToGhost(fox, rabbit2);
				/*rabbit2.GhostTurn = rabbit2.MaxGhostTurn;
				RabbitGhostColony.push_back(rabbit2);
				cout << "\nA Rabbit is turned to ghost.";
				*/
			}
			/*rabbit.GhostTurn = rabbit.MaxGhostTurn;
			RabbitGhostColony.push_back(rabbit);
			cout << "\nA Rabbit is turned to ghost.";
			*/
			FoxColony[i]->HauntedTurn = FoxColony[i]->MaxHauntedTurn;
			if (rabbit->Vampire && RandomChance(30))
			{
				FoxColony.erase(FoxColony.begin() + i);
			}
		}
	}

	void FoxBreed()
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


	void DecreaseInfection()
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
	void RabbitDie()
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
	
	void RabbitBreed() 
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
				
				cout << "\nA baby rabbit named "  << babyRabbit.Name << " is born from mother " << babyRabbit.Mother->Name << " !Vampire ? " << ShouldSpawnVampire;
				if (cout.bad())
				{
					cout.clear();
				}
			}
		}
	}

	//  Unused?
	int RabbitColonyWithoutGhosts() 
	{
		int x = 0;
		for (Rabbit* rabbit : RabbitColony)
			if (rabbit->GhostTurn>=1)
			{
				x++;
			}

		return x;
	} 

	void Tick()
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

	void Print() const
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
};



int main()
{
	/*
	std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
	std::sort(v.begin(), v.end());
	std::vector<int> squaredV;
	std::transform(v.begin(), v.end(), squaredV.begin(), [](const int& num)
		{
			return num * num;
		});


	int base = 10;
	auto add = [&](int x, int y)
	{
		return base + x + y;
	};

	for (int i = 0; i < 10; i++)
	{
		cout << add(2, 3) << " "; // 15 16...
		base++;
	}

	*/

	//srand(static_cast<unsigned>(time(0))); // Born all females??

	char inputkey = 'a';

	// Populating Colony
	GWorld = new World();

	GWorld->RabbitColony.push_back(new Rabbit((static_cast<EColor>(rand() % 2)), false));
	GWorld->RabbitColony.push_back(new Rabbit((static_cast<EColor>(rand() % 2)), false));
	GWorld->RabbitColony.push_back(new Rabbit((static_cast<EColor>(rand() % 2)), false));
	GWorld->RabbitColony.push_back(new Rabbit((static_cast<EColor>(rand() % 2)), false));
	GWorld->RabbitColony.push_back(new Rabbit((static_cast<EColor>(rand() % 2)), false));

	GWorld->FoxColony.push_back(new Fox());
	GWorld->FoxColony.push_back(new Fox());
	GWorld->FoxColony.push_back(new Fox());
	GWorld->FoxColony.push_back(new Fox());
	GWorld->FoxColony.push_back(new Fox());


	/*
	for (Fox* fox : GWorld->FoxColony)
	{
		cout << fox->Gender;
	}

	*/
	/*


	// b.Mother = &GWorld->RabbitColony[1];
	Rabbit r1;
	Rabbit r2;
	Rabbit r3;
	// | r1|r2|r3|
	std::vector<Rabbit> rs;
	rs.push_back(Rabbit());
	rs.push_back(Rabbit()); // rs1
	rs.push_back(Rabbit());
	// | rs_0 | rs_1 | rs_2 |
	Rabbit* rs1p = &rs[1]; // 110
	rs.erase(rs.begin() + 1);
	rs1p->Age = 5; // modifying rs2!

	*/

	// Timer Next Turn
	while (true)
	{
		if (GWorld->Turn == 0) {
			cout << "\nStart a new colony pressing 'n'";
		}
		else {
			cout << "\n\nPress key 'n' to move to the next turn..";
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		//inputkey = 'n';
		inputkey = _getch();

		if (inputkey == 'n')
		{

			cout << "\n\n\n\n\n\nTurn number: " << GWorld->Turn << "\n";


			GWorld->Print();
			GWorld->Tick();
			// std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			
			
		}

		if (inputkey == 'q') {
			delete GWorld;
			return 0;
		}
	}
		delete GWorld;
		return 0;
}
