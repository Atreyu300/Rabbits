#include "Rabbit.h"


void Rabbit::SetRandomName()
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

bool Rabbit::IsGhost() const
{
	return GhostTurn != 0;
}

// SendAnalytics("New Rabbit");

void Rabbit::OnGhostRabbitDeath() const
{
	if (!Mother)
	{
		return;
	}
	std::cout << "\nMother " << Mother->Name << " finally accepts the death of " << Name;
	if (std::cout.bad())
	{
		std::cout.clear();
	}

};
