#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>


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

// What happens to mother and the murderer? How do we know if they are still alive?
struct Rabbit
{
	int Age;
	EGender Gender;
	EColor Color;
	bool Vampire;

	Rabbit* Mother;

	const static int MaxAge = 10;
	const static int MinAdulthoodAge = 2;
	const static int VampireMaxAge = 50;

	Rabbit() : Age(0), Gender(static_cast<EGender>(rand() % 2)),
		Color(static_cast<EColor>(rand() % static_cast<int>(EColor::Count)))
	{}

	Rabbit(EColor color) : Age(0), Gender(static_cast<EGender>(rand() % 2))
	{}

	Rabbit(EColor color, bool vampire) : Age(0), Gender(static_cast<EGender>(rand() % 2)),
		Color(color), Vampire(vampire)
	{}

	// SendAnalytics("New Rabbit");
	
	/*~Rabbit()
	{
		cout << "destruct ";
	}
	*/
};


class World* GWorld;

struct World
{
	std::vector<Rabbit> RabbitColony;
	int Turn;
	const int MaxRabbits = 1000;

	World() : Turn(0)
	{
	}

	void IncreaseAnimalsAge()
	{
		for (Rabbit& rabbit : GWorld->RabbitColony)
		{
			rabbit.Age++;
		}
	}

	bool CheckForMaleRabbit() const
	{
		for (const Rabbit& rabbit : GWorld->RabbitColony)
		{
			if (rabbit.Gender == EGender::Male && !rabbit.Vampire)
				return true;
		}
		return false;
	}

	bool CheckForVampireRabbit() const 
	{
		for (const Rabbit& rabbit : GWorld->RabbitColony) 
		{
			if (rabbit.Vampire)
			{
				return true;
			}
			
		}
		return false;
		cout << "No Vampire rabbit";

	}
	void Infection() 
	{
		if (CheckForVampireRabbit())
		{
			//Check for Vampire Rabbit Number
			int VampireRabbit = 0;
			for (const Rabbit& rabbit : GWorld->RabbitColony)
			{
				if (rabbit.Vampire)
				{
					VampireRabbit++;
				}
			}

			int TotalRabbitInfected = 0;
			for (int x=0; x <= VampireRabbit; x++)
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
				int RandomRabbitIndex = RandomRabbitIndex = (rand() % GWorld->RabbitColony.size());
				
				if (!GWorld->RabbitColony[RandomRabbitIndex].Vampire)
				{
					GWorld->RabbitColony[RandomRabbitIndex].Vampire = true;
					TotalRabbitInfected++;
				}

			}
			cout << TotalRabbitInfected << " Rabbit infected!";
		}
	}
	
	void KillHalfColony() 
	{
		cout << "\nTotal rabbit: " << GWorld->RabbitColony.size() << "\n";
		cout << "\nToo much rabbits, low food. Killing half colony.. \n";
		
		int HalfColony = GWorld->RabbitColony.size() / 2;
		for (int i = 0; i < HalfColony; i++)
		{
			GWorld->RabbitColony.erase(GWorld->RabbitColony.begin() + (rand() % GWorld->RabbitColony.size()));
		}
		cout << "\nTotal rabbit: " << GWorld->RabbitColony.size() << "\n";

	}


	void OnRabbitDied(Rabbit)
	{
	}

	

	void Tick()
	{
		// Check if colony is empty
		if (GWorld->RabbitColony.empty()) {

			cout << "The rabbit colony is dead!";
			exit;
		}

		const bool isThereAMaleRabbit = CheckForMaleRabbit();
		Infection();
		IncreaseAnimalsAge();
		
		// Checking for MaxRabbits
		if (GWorld->RabbitColony.size() >= MaxRabbits) 
		{
			KillHalfColony();
		}

		for (int i = 0; i < GWorld->RabbitColony.size(); ++i)
		{
			const Rabbit& rabbit = GWorld->RabbitColony[i];

			// Rabbits death
			const bool ShouldDie =
				(rabbit.Age >= Rabbit::MaxAge && !rabbit.Vampire) ||
				(rabbit.Age >= Rabbit::VampireMaxAge && rabbit.Vampire);

			if (ShouldDie)
			{
				GWorld->RabbitColony.erase(GWorld->RabbitColony.begin() + i);
				i--;
				cout << "A rabbit is dead! Vampire? " << rabbit.Vampire << "\n";
			}

			// Rabbits breeding

			const bool ShouldGiveBirth = isThereAMaleRabbit &&
				rabbit.Age >= Rabbit::MinAdulthoodAge &&
				rabbit.Gender == EGender::Female &&
				!rabbit.Vampire;

			if (ShouldGiveBirth)
			{
				const bool ShouldSpawnVampire = (rand() % 100) + 1 <= 2;
				GWorld->RabbitColony.push_back(Rabbit(rabbit.Color, ShouldSpawnVampire));
				cout << "A baby rabbit is born! Vampire? " << ShouldSpawnVampire << "\n";
			}
			
		}

		// TODO: Don't increase the age of the newborn babies - they should stay at 0 - DONE


		Turn++;

	}

	void Print() const
	{
		// TODO: Print in a table -- DONE
		/*
		| Age |  Gender   |  Color |
		| --- |  ------   | ------ |
		| 1   |   Male    | White  |

		*/

		const char* GenderNames[] = { "Male", "Female" };
		const char* ColorNames[static_cast<int>(EColor::Count)] = { "White", "Black", "Brown", "Red", "Blue" };

		cout << "Total Colony: " << GWorld->RabbitColony.size() << "\n\n";
		cout << "\n\nNormal Rabbits\n";
		cout << "| Age |  Gender  |  Color |\n";
		cout << "| --- |  ------  | ------ |\n";

		for (const Rabbit& rabbit : GWorld->RabbitColony)
		{
			if (!rabbit.Vampire) {
				// Male Print
				if (rabbit.Gender == EGender::Male)
				{
					cout << "|  " << rabbit.Age << "  "
						<< "| " << GenderNames[static_cast<int>(rabbit.Gender)] << "     " // Just more space then Female
						<< "| " << ColorNames[static_cast<int>(rabbit.Color)] << "  | \n";
				}
				else
				{
					// Female Print
					cout
						<< "|  " << rabbit.Age << "  "
						<< "| " << GenderNames[static_cast<int>(rabbit.Gender)] << "   "
						<< "| " << ColorNames[static_cast<int>(rabbit.Color)] << "  | \n";
				}
			}


		}

		cout << "\n\nRadioactive Mutant Vampire Rabbits\n";
		for (const Rabbit& rabbit : GWorld->RabbitColony)
		{
			
			if (rabbit.Vampire)
			{
				
				if (rabbit.Gender == EGender::Male)
				{
					cout << "|  " << rabbit.Age << "  "
						<< "| " << GenderNames[static_cast<int>(rabbit.Gender)] << "     " // Just more space then Female
						<< "| " << ColorNames[static_cast<int>(rabbit.Color)] << "  | \n";
				}
				else
				{
					// Female Print
					cout
						<< "|  " << rabbit.Age << "  "
						<< "| " << GenderNames[static_cast<int>(rabbit.Gender)] << "   "
						<< "| " << ColorNames[static_cast<int>(rabbit.Color)] << "  | \n";
				}
			}
		}
		cout << "\n\n";
	}
};


int main()
{
	//srand(static_cast<unsigned>(time(0))); // Born all females??

	char inputkey = 'a';

	// Populating Colony
	GWorld = new World();


	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false));
	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false));
	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false));
	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false));
	GWorld->RabbitColony.push_back(Rabbit((static_cast<EColor>(rand() % 2)), false));

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
		// Cout for first Turn
		if (GWorld->Turn == 0) {
			cout << "\n Start a new colony pressing 'n'";
		}
		// Cout for Turns
		else {
			cout << "\n Press 'n' to move to the next turn";
		}
		inputkey = _getch();

		if (inputkey == 'n')
		{
			cout << "\n\nTurn number: " << GWorld->Turn << "\n";


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
