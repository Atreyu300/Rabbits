
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <thread>

#include "Gender.h"
#include "Names.h"
#include "Fox.h"
#include "Color.h"
#include "Grass.h"
#include "World.h"
#include "Rabbit.h"

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


enum class DataType
{
	Fox,
	Rabbit,
	Grass
};

// What happens to mother and the murderer? How do we know if they are still alive?






void GameOver(string message)
{
	cout << "Game Over! " << message;
}


class World* GWorld;



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
