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
};

struct Rabbit
{
	int Age;
	EGender Gender;
	EColor Color;

	// Why is necessary to have a cast on Ecolor when is not necessary on EGeneder?
	Rabbit() : Age(0), Gender(rand() % 2 == 0 ? EGender::Male : EGender::Female), 
		Color(static_cast<EColor>(rand() % 2))
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

struct World
{
	std::vector<Rabbit> RabbitColony;
};


World* GWorld;
int Turn;

void Tick()
{
	cout << "";
}




void IncreaseAnimalsAge() {

	for (Rabbit& Rabbit : GWorld->RabbitColony) {
		Rabbit.Age++;
	}
}

bool CheckForMaleRabbit() {
	for (const Rabbit& rabbit : GWorld->RabbitColony) {
		if (rabbit.Gender == EGender::Male)
			
		return true;
			else
				return false;
	}
}

void RabbitDeath(Rabbit) {
	for (Rabbit& rabbit : GWorld->RabbitColony) {
		{

		}
	}
}

void RabbitLifeCycle() 
{

	for (int i = 0; i < GWorld->RabbitColony.size(); ++i) 
	{
		Rabbit& rabbit = GWorld->RabbitColony[i];

		if (rabbit.Age >= 10) 
		{ 
			GWorld->RabbitColony.erase(GWorld->RabbitColony.begin()+i);
		}
		if (bool malerabbit = CheckForMaleRabbit) 
		{
			if (rabbit.Age >= 2 && rabbit.Gender == EGender::Female) 
			{
				EColor BabyColor = rabbit.Color;
				GWorld->RabbitColony.push_back(Rabbit()); 
				// how to sets mom color in constructor?? 
				// work around
				Rabbit& RabbitToChangeColor = GWorld->RabbitColony.back();
				RabbitToChangeColor.Color = BabyColor;
													
			}
		}
	}

}
	



int NextTurn() {
	Turn++;

	IncreaseAnimalsAge();
	
	return Turn;
}



void StampRabbitColony() {

	for (const Rabbit& Rabbit : GWorld->RabbitColony) {
		cout << "Age: " << Rabbit.Age << ", Gender: " << (Rabbit.Gender == EGender::Male ? "Maschio" : "Femmina") << ", Colore: " << (Rabbit.Color == EColor::White ? "Bianco" : "Marrone") << std::endl;
	}
}

int main()
{
	//InitAnalytics();


	char inputkey = 'a';



	// Populating Colony
	GWorld = new World();
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());

	// First Turn
	//cout << "Turn number: " << Turn << "\n\n";
	//StampRabbitColony();



	// Timer Next Turn
	while (true)
	{
		cout << "\n Press 'n' to move to the next turn";
		inputkey = _getch();

		if (inputkey == 'n') {


			int TurnNumber = 0;
			cout << "\n\nTurn number: " << TurnNumber << "\n";


			RabbitLifeCycle();
			StampRabbitColony();
			TurnNumber = NextTurn();


			// std::this_thread::sleep_for(std::chrono::milliseconds(2000));


		}
	}






	/*
	while (true)
	{
		Tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	}
	*/





	delete GWorld;
	return 0;

}
