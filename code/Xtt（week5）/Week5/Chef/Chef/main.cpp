#include"chef.h"



int main()
{

	Chef chef;
	chef.getMenu();
	chef.FillStore();
	while (1)
	{
		chef.cooking();
	}


	return 0;
}