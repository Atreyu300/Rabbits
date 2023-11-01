#include <algorithm>
#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <chrono>
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
	int MaxGhostTurn = 5;

	// TODO: Use a pointer to check if the mother is still alive
	string MotherName = "TempName";

	const static int MaxAge = 10;
	const static int MinAdulthoodAge = 2;
	const static int VampireMaxAge = 50;
	
	int Hungry = ((Vampire) ? 2 : 4);

	const static int VampireHungry = 4;

	// Constructors 
	Rabbit() = delete;


	Rabbit(EColor color, bool vampire, string motherName) : Age(0), Gender(static_cast<EGender>(rand() % 2)),
		Color(color), Vampire(vampire), MotherName(motherName)
	{
		SetRandomName(); // Only females??
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
	
	/*~Rabbit()
	{
		cout << "destruct ";
	}
	*/
};

struct Fox 

{
	int Age;
	EGender Gender;

	Fox() : Age(0), Gender(static_cast<EGender>(rand()% 2))
	{}

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
	std::vector<Rabbit> RabbitColony;
	std::vector<Fox> FoxColony;
	std::vector<Rabbit>RabbitGhostColony;
	Grass Grass; // Should i use the same name for struct and variable?

	int Turn;
	const int MaxRabbits = 1000;

	World() : Turn(0)
	{
	}

	
	void IncreaseAnimalsAge()
	{
		for (Rabbit& rabbit : RabbitColony)
		{
			rabbit.Age++;
		}
		for (Fox& fox : FoxColony) {

			fox.Age++;
		}
	}

	bool CheckForMaleRabbit() const
	{
		return std::any_of(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit& rabbit)
			{
				return rabbit.Gender == EGender::Male && !rabbit.Vampire;
			});
	}
	// My first lambda
	bool CheckForVampireRabbit() const
	{
		return std::any_of(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit& rabbit)
			{
				return rabbit.Vampire;
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
				
				if (!RabbitColony[RandomRabbitIndex].Vampire)
				{
					RabbitColony[RandomRabbitIndex].Vampire = true;
					TotalRabbitInfected++;
				}

			}
			cout << TotalRabbitInfected << " Rabbit infected!";
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
				RabbitColony.erase(RabbitColony.begin() + (rand() % RabbitColony.size()));
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
			FoxColony.erase(FoxColony.begin() + CasualFox);
			cout << "\nA Fox is dead by starving..";
		}
	}
	

	void RabbitEating() 
	{
		for (Rabbit& rabbit : RabbitColony)
		{
			Grass.Quantity = std::max(0, Grass.Quantity - rabbit.Hungry);
		}
		
	}
	void DecreasingRabbitGhostTurn()
	{
		auto removalIt = std::remove_if(RabbitGhostColony.begin(), RabbitGhostColony.end(), [](Rabbit& rabbit)
			{
				if (rabbit.IsGhost())
				{
					rabbit.GhostTurn--;
					return rabbit.GhostTurn == 0;
				}
				return false;
			});
		RabbitGhostColony.erase(removalIt, RabbitGhostColony.end());

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
		std::vector<Rabbit>& Colony = RabbitColony;
		// TODO: Turn into lambda; std::accumulate
		for (const Rabbit& rabbit : Colony)
		{
			NecessaryFood = NecessaryFood + rabbit.Hungry;
		}

		if (NecessaryFood >= Grass.Quantity)
		{
			return;
		}

		cout << "\nNot enough grass for rabbits. Some rabbit will die.";
		int FoodDifference = NecessaryFood - Grass.Quantity;
		int FoodToEat = 0;
		for (int i = 0; i < FoodDifference && !Colony.empty(); i++, FoodDifference -= FoodToEat)
		{
			int RandomRabbitIndex = rand() % Colony.size();

			const Rabbit& Rabbit = Colony[RandomRabbitIndex];
			FoodToEat = Rabbit.Hungry;
			Colony.erase(Colony.begin() + RandomRabbitIndex);
			cout << "\nA Rabbit is dead for starving..";
		}
	}
	 
	void OnRabbitDied(Rabbit)
	{
	}

	int TotalVampireRabbit() const
	{
		return std::count_if(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit& rabbit)
			{
				return rabbit.Vampire;
			});
	}

	int TotalGhostRabbit() const
	{
		return std::count_if(RabbitColony.begin(), RabbitColony.end(), [](const Rabbit& rabbit)
			{
				return rabbit.IsGhost();
			});
	}

	void KillRabbit(Fox&, Rabbit&)
	{
	}

	int RandomChance(int chance)
	{
		int randomvalue = rand() % 100 < chance;
		return randomvalue;
	}

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
			Rabbit& rabbit = RabbitColony[RandomRabbitIndex];
			
			const bool IsFoxHuntingGhostRabbit = FoxColony[i].Age >= FoxColony[i].HuntAge && rabbit.IsGhost();
			if (!IsFoxHuntingGhostRabbit)
			{
				continue;
			}
			if (Grass.Quantity < Grass.MaxQuantity*20/100 && RandomChance(50))
			{
				// TODO: Make a new function KillRabbit(Fox&, Rabbit&) and call it twice instead of copy/pasting code
				// TODO: Move chance code to a function - RandomChance(50), RandomChance(30) <--  DONE
				int RandomRabbitIndex2 = rand() % RabbitColony.size();
				Rabbit& rabbit2 = RabbitColony[RandomRabbitIndex2];
				rabbit2.GhostTurn = rabbit2.MaxGhostTurn;
				RabbitGhostColony.push_back(rabbit2);// <-- what i'm doing here? moving from vector to vector o coping it? There are two same rabbit in two different vector?
				//RabbitColony.erase(RabbitColony.begin() + RandomRabbitIndex2); <-- causing crash!
				cout << "\nA Rabbit is turned to ghost.";
			}

			rabbit.GhostTurn = rabbit.MaxGhostTurn;
			RabbitGhostColony.push_back(rabbit);
			//RabbitColony.erase(RabbitColony.begin() + RandomRabbitIndex); <-- like the prev comment
			cout << "\nA Rabbit is turned to ghost.";

			FoxColony[i].HauntedTurn = FoxColony[i].MaxHauntedTurn;
			if (rabbit.Vampire && RandomChance(30))
			{
				FoxColony.erase(FoxColony.begin() + i);
			}
		}
	}

	void FoxBreeding() 
	{
		for (Fox& malefox : FoxColony)
		{
			// TODO: Invert condition to save indent
			if ((malefox.Gender == EGender::Male) 
				&& (!malefox.Breeded) 
				&& (malefox.HauntedTurn!=0)
				&& (malefox.Age >=malefox.MinAdulthoodAge))
			{
				for (Fox& femalefox : FoxColony)
				{
					if ((femalefox.Gender == EGender::Female) 
						&& (!femalefox.Breeded)
						&& (femalefox.HauntedTurn!=0)
						&& (femalefox.Age >= femalefox.MinAdulthoodAge))
					{
						malefox.Breeded = true;
						femalefox.Breeded = true;
						FoxColony.push_back(Fox());
					}
				}
			}
		}
		for (Fox& fox : FoxColony) 
		{
			fox.Breeded = false;
		}
		
	}


	void DecreaseInfection()
	{
		for (Rabbit& rabbit : RabbitColony)
		{
			rabbit.GhostTurn = std::min(rabbit.GhostTurn - 1, 0);
		}

		for (Fox& fox : FoxColony)
		{
			fox.HauntedTurn = std::min(fox.HauntedTurn - 1, 0);
		}
		
	}

	
	void RabbitLifeCycle() 
	{
		const bool isThereAMaleRabbit = CheckForMaleRabbit();
		for (int i = 0; i < RabbitColony.size(); ++i)
		{
			const Rabbit& parentRabbit = RabbitColony[i];

			// Rabbits death
			const bool ShouldDie =
				(parentRabbit.Age >= Rabbit::MaxAge && !parentRabbit.Vampire) ||
				(parentRabbit.Age >= Rabbit::VampireMaxAge && parentRabbit.Vampire);

			if (ShouldDie)
			{
				const string& Name = parentRabbit.Name;
				
				cout << "A rabbit named " << Name << " is dead!Vampire ? " << parentRabbit.Vampire << "\n";
				RabbitColony.erase(RabbitColony.begin() + i);
				i--;
			}

			// Rabbits breeding

			const bool ShouldGiveBirth = !ShouldDie && isThereAMaleRabbit &&
				parentRabbit.Age >= Rabbit::MinAdulthoodAge &&
				parentRabbit.Gender == EGender::Female &&
				!parentRabbit.Vampire;

			if (ShouldGiveBirth)
			{
				const bool ShouldSpawnVampire = RandomChance(2);
				RabbitColony.push_back(Rabbit(parentRabbit.Color, ShouldSpawnVampire, parentRabbit.Name));
				// cout << "\nMom Rabbit name " << rabbit.Name;

				const Rabbit& babyRabbit = RabbitColony[RabbitColony.size() - 1];

				cout << "\bA baby rabbit named "  << babyRabbit.Name << " is born!Vampire ? " << ShouldSpawnVampire << "\n"; // crash?!
			}
		}
	}

	// Unused// Unused?
	int RabbitColonyWithoutGhosts() 
	{
		int x = 0;
		for (Rabbit& rabbit : RabbitColony)
			if (rabbit.GhostTurn>=1)
			{
				x++;
			}

		return x;
	} 

	void Tick()
	{
		


		// Check if Rabbit colony is empty
		if (RabbitColony.empty()) {

			cout << "The rabbit colony is dead!";
			exit;
		}
		
		DecreaseInfection();
		
		CheckForMaxRabbit();

		GrassGrown();
		CheckForEnoughGrass();

		RabbitLifeCycle();
		RabbitEating();
				
		FoxBreeding();
		FoxEat();

		VampireRabbitInfection();
		IncreaseAnimalsAge();
		

		// TODO: Don't increase the age of the newborn babies - they should stay at 0 - DONE


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

	
	
	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false, "God"));
	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false, "God"));
	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false, "God"));
	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false, "God"));
	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false, "God"));

	GWorld->FoxColony.push_back(Fox());
	GWorld->FoxColony.push_back(Fox());
	GWorld->FoxColony.push_back(Fox());
	GWorld->FoxColony.push_back(Fox());
	GWorld->FoxColony.push_back(Fox());

	
	/*

	// | Rabbit0 | Rabbit1 | Rabbit 2 | Rabbit3
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
		// Print for first Turn
		if (GWorld->Turn == 0) {
			cout << "\n Start a new colony pressing 'n'";
		}
		// Print for next Turns
		else {
			cout << "\n Press 'n' to move to the next turn";
		}
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
