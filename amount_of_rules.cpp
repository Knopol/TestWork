#include <string>
#include "amount_of_rules.h"
using namespace std;

int amount_of_rules(string s)
{
	int i{ 0 }, l{ 0 };
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			++l;
		}
		++i;
	}
	l = l / 2;
	return l;
}