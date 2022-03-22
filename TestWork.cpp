#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include "check_string.h"
#include "class.cpp"
#include "amount_of_rules.h"

using namespace std;


int main()
{
	
	List facts, rules, rules_stack, new_facts;

	Node* head_facts;
	Node* head_rules;
	Node* head_new_facts;

	string s1, s2;
	string line1, line2;

	ifstream FILE("facts_n_rules.txt");
	if (FILE.is_open())
	{
		getline(FILE, line1);
		getline(FILE, line2);
	}
	FILE.close();

	bool test_string;
	if (test_string = check_string(line1, line2) == false)
	{
		cout << "ERROR_FILE -> INCORRECT_SYMBOLS" << endl;
		system("pause");
		return 1;
	}

	int i{ 0 }, l{ 0 };

	l = amount_of_rules(line2);

	head_facts = facts.read_first_line(line1);
	rules = rules_stack.read_second_line(line2,rules_stack);
	new_facts = rules.otobr(head_facts,rules,new_facts,facts);
	head_rules = rules.get_Head();
	head_new_facts = new_facts.get_Head();
	cout << "New facts: ";
	new_facts.print_list(head_new_facts);
	system("pause");
	return 0;
}
