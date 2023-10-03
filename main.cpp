#include <iostream>
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

struct Rabbit
{
	int Age;
	EGender Gender;

	Rabbit() : Age(0), Gender(rand() % 2 == 0 ? EGender::Male : EGender::Female)
	{
		cout << "default ctor ";
		// SendAnalytics("New Rabbit");
	}

	Rabbit(EGender Gender) : Age(0), Gender(Gender)
	{}

	Rabbit(const Rabbit& other) :
		Age(other.Age),
		Gender(other.Gender)
	{
		cout << "copy ctor ";
	}

	Rabbit& operator=(const Rabbit& other)
	{
		cout << "assignment op ";
		Age = other.Age;
		Gender = other.Gender;

		return *this;
	}

	~Rabbit()
	{
		cout << "destruct ";
	}
};

struct World
{
	std::vector<Rabbit> RabbitColony;
};


World* GWorld;

void Tick()
{
	cout << "tick tack ";
}

int main()
{
	//InitAnalytics();
	Rabbit r;
	r.Gender = EGender::Female;

	{
		Rabbit r2(r);
		Rabbit r3 = r;
	}

	Rabbit r4;
	r4 = r;


	GWorld = new World();
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());
	GWorld->RabbitColony.push_back(Rabbit());

	while (true)
	{
		Tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	delete GWorld;
	return 0;
}