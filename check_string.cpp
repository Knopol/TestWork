#include <string>
#include "check_string.h"
using namespace std;

bool check_string(string line1, string line2)
{
	for (int i = 0; line1[i] != '\0'; i++)
	{
		if ((((int)line1[i] > 91) || ((int)line1[i] < 65)) && ((int)line1[i] != 95) && ((int)line1[i] != 34) && ((int)line1[i] != 44) && ((int)line1[i] != 124))
		{
			return false;
		}
	}
	for (int i = 0; line2[i] != '\0'; i++)
	{
		if ((((int)line2[i] > 91) || ((int)line2[i] < 65)) && ((int)line2[i] != 95) && ((int)line2[i] != 34) && ((int)line2[i] != 44) && ((int)line2[i] != 124) && ((int)line2[i] != 45) && ((int)line2[i] != 62))
		{
			return false;
		}
	}
	return true;
}