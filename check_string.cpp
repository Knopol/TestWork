#include <string>
#include "check_string.h"
using namespace std;

bool check_string(string line1, string line2)
{
	bool follow = false;
	bool rule = true;
	bool facts = false;
	for (int i = 0; line1[i] != '\0'; i++)
	{
		if ((((int)line1[i] > 90) || ((int)line1[i] < 65)) && ((int)line1[i] != 95) && ((int)line1[i] != 34) && ((int)line1[i] != 44) && ((int)line1[i] != 124))
		{
			return false;
		}
	}
	for (int i = 0; line2[i] != '\0'; i++)
	{
		if ((i == 0) && (line2[i] != '"'))
		{
			return false;
		}
		else
		{
			rule = true;
		}

		if (((line2[i] == '"') && (i != 0) && (line2[i + 1] != '\0') && (((int)line2[i - 1] <= 90) && ((int)line2[i - 1] >= 65))) && ((line2[i + 1] != ',') || (line2[i + 2] != '"') || (((int)line2[i + 3] > 90) || ((int)line2[i + 3] < 65)) || (follow == false)))
		{
			return false;
		}

		if ((line2[i] == '"') && (i != 0) && (line2[i + 1] != '\0') && (((int)line2[i - 1] <= 90) && ((int)line2[i - 1] >= 65)) && (line2[i + 1] == ',') && (line2[i + 2] == '"') && (((int)line2[i + 3] <= 90) || ((int)line2[i + 3] >= 65)))
		{
			facts = false;
			follow = false;
			rule = true;
		}

		if ((line2[i] == '-') && (((int)line2[i - 1] > 90) || ((int)line2[i - 1] < 65)))
		{
			return false;
		}

		if ((line2[i] == '-') && ((line2[i + 1] != '>') || (((int)line2[i + 2] > 90) || ((int)line2[i + 2] < 65))))
		{
			return false;
		}

		if ((line2[i] == '-') && (follow == true))
		{
			return false;
		}

		if ((line2[i] == '|') && (facts == true))
		{
			return false;
		}

		if ((rule == true) && (line2[i] == '-') && (line2[i+1] == '>'))
		{
			if (((int)line2[i + 2] <= 90) && ((int)line2[i + 2] >= 65))
			{
				rule = false;
				facts = true;
				follow = true;
			}
			else
			{
				return false;
			}
		}

		if ((i == 1) && (((int)line2[i] > 90) || ((int)line2[i] < 65)))
		{
			return false;
		}

		if ((((int)line2[i] > 90) || ((int)line2[i] < 65)) && ((int)line2[i] != 95) && ((int)line2[i] != 34) && ((int)line2[i] != 44) && ((int)line2[i] != 124) && ((int)line2[i] != 45) && ((int)line2[i] != 62))
		{
			return false;
		}
	}
	return true;
}