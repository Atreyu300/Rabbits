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

struct Rabbit
{
	int Age;
	EGender Gender;
	EColor Color;

	const static int MaxAge = 10;
	const static int MinAdulthoodAge = 2;

	Rabbit() : Age(0), Gender(static_cast<EGender>(rand() % 2)),
		Color(static_cast<EColor>(rand() % static_cast<int>(EColor::Count)))
	{
		cout << "";
		// SendAnalytics("New Rabbit");
	}

	Rabbit(EColor color) : Age(0), Gender(static_cast<EGender>(rand() % 2)),
		Color(color)
	{
		cout << "";
		// SendAnalytics("New Rabbit");
	}

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
			if (rabbit.Gender == EGender::Male)
				return true;
		}
		return false;
	}

	void OnRabbitDied(Rabbit)
	{
	}

	void Tick()
	{
		const bool isThereAMaleRabbit = CheckForMaleRabbit();

		for (int i = 0; i < GWorld->RabbitColony.size(); ++i)
		{
			const Rabbit& rabbit = GWorld->RabbitColony[i];

			if (rabbit.Age >= Rabbit::MaxAge)
			{
				GWorld->RabbitColony.erase(GWorld->RabbitColony.begin() + i);
				i--;
			}
			if (isThereAMaleRabbit)
			{
				if (rabbit.Age >= Rabbit::MinAdulthoodAge && rabbit.Gender == EGender::Female)
				{
					GWorld->RabbitColony.push_back(Rabbit(rabbit.Color));
				}
			}
		}

		// TODO: Don't increase the age of the newborn babies - they should stay at 0
		IncreaseAnimalsAge();
		Turn++;
	}

	void Print() const
	{
		// TODO: Print in a table
		/*
		| Age | Gender |  Color |
		| --- | ------ | ------ |
		| 1   | Male   | White  |

		*/
		const char* GenderNames[] = { "Male", "Female" };
		const char* ColorNames[static_cast<int>(EColor::Count)] = { "White", "Black", "Brown", "Red", "Blue" };

		for (const Rabbit& rabbit : GWorld->RabbitColony)
		{
			cout
				<< "Age: " << rabbit.Age
				<< ", Gender: " << GenderNames[static_cast<int>(rabbit.Gender)]
				<< ", Colour: " << ColorNames[static_cast<int>(rabbit.Color)];
		}
	}
};


int main()
{
	char inputkey = 'a';

	// Populating Colony
	GWorld = new World();
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());

	// Timer Next Turn
	while (true)
	{
		cout << "\n Press 'n' to move to the next turn";
		inputkey = _getch();

		if (inputkey == 'n')
		{
			cout << "\n\nTurn number: " << GWorld->Turn << "\n";

			GWorld->Print();
			GWorld->Tick();
			// std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		}
	}

	delete GWorld;
	return 0;
}
