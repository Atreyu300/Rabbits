#include "Fox.h"
#include "Names.h"



bool Fox::GetIsHuntingAge() const
{
	return Age >= HuntAge;
}

void Fox::SetRandomName()
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