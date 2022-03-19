#include <string>
#include <iostream>
#include "class.h"
using namespace std;
class Node;
class List;
class Node
{
	friend List;

private:
	Node* _address = nullptr;
	string _fact;
	int _val{ 0 };
	Node* _next = nullptr;
	Node* _prev = nullptr;
	bool is_true = false;
public:

	Node()
	{

	}

	string get_fact()
	{
		return this->_fact;
	}

	int get_val()
	{
		return this->_val;
	}

};

class List
{
private:
	Node* Head = nullptr;
	Node* Tail = nullptr;
	int _size{ 0 };
public:
	Node* get_Head()
	{
		return Head;
	}
	Node* add_node()
	{
		Node* node = new Node();

		if (Head == nullptr)
		{
			Head = node;
			Tail = node;
		}
		else
		{
			Tail->_next = node;
			node->_prev = Tail;
			Tail = node;
		}
		node->_val = _size;
		++_size;
		return node;
	}

	Node* del_node(Node* node)
	{
		Node* new_node = new Node();
		Node* node_node = new Node();
		if (node->_prev == nullptr)
		{
			new_node = node->_next;
			new_node->_prev = nullptr;
			Head = new_node;
			delete node;
		}
		else if (node->_next == nullptr)
		{
			new_node = node->_prev;
			new_node->_next = nullptr;
			Tail = new_node;
			delete node;
		}
		else
		{
			node_node = node->_prev;
			new_node = node->_next;
			new_node->_prev = node_node;
			node_node->_next = new_node;
			delete node;
		}
		_size--;
		return new_node;
	}

	Node* read_first_line(string s)
	{
		Node* node = add_node();
		Head = node;
		Node* new_node = new Node();
		int i{ 1 };

		while (s[i] != '\0')
		{
			if (((s[i] == ',') || (s[i] == '"')) && (s[i + 1] != '\0'))
			{
				++i;
				++i;
				++i;
				node = add_node();
				node->_fact += s[i];
			}
			else if (((s[i] == '"') && (s[i + 1] == '\0')))
			{
				break;
			}
			else
			{
				node->_fact += s[i];
			}
			++i;
		}
		node->_next = nullptr;
		return this->Head;
	}

	List read_second_line(string s, List rules)
	{
		Node* rules_node = rules.add_node();
		Node* node = new Node();
		Node* new_node = new Node();
		bool facts = false;
		int i{ 0 };
		while (s[i] != '\0')
		{
			if ((s[i] == ',') || (s[i] == '|') || (s[i] == '"'))
			{
				if (s[i] == '"')
				{
					node = add_node();
					node->_fact += "/";
				}
				else
				{
					node = add_node();
					node->_fact += s[i];
				}
				if ((s[i + 1] != ',') && (s[i + 1] != '"') && (s[i + 1] != '\0'))
				{
					node = add_node();
				}


			}
			else if (s[i] == '-')
			{
				node = add_node();
				node->_fact += s[i];
				++i;
				node->_fact += s[i];
				node = add_node();
			}
			else
			{
				node->_fact += s[i];
			}

			++i;

		}
		node = this->Head;
		node = del_node(node);
		rules_node->_address = this->Head;
		while (node->_next != nullptr)
		{
			if (node->_fact == "->")
			{
				facts = true;
			}
			if ((node->_fact == ",") && (facts == true))
			{
				node = del_node(node);
			}
			if (node->_fact == "/")
			{
				node = del_node(node);
				node = del_node(node);
				node = del_node(node);
				new_node = node->_prev;
				new_node->_next = nullptr;
				node->_prev = nullptr;
				rules_node = rules.add_node();
				rules_node->_address = node;
				facts = false;
			}
			node = node->_next;

		}
		node = del_node(node);
		node->_next = nullptr;
		return rules;
	}

	bool find_fact(string s, Node* head_facts)
	{
		Node* node = new Node();
		node = head_facts;
		for (int i = 0; 1 != 0; ++i)
		{
			if (node->_fact == s)
			{
				return true;
			}
			if (node->_next == nullptr) break;
			node = node->_next;
		}
		return false;
	}

	List otobr(Node* head_facts, List rules, List new_facts, List facts)
	{
		int l{ 0 }, k{ 0 };
		Node* new_facts_node = new_facts.Head;
		Node* rules_node = rules.Head;
		Node* node_rules = rules.Head->_address;
		Node* node = rules.Head->_address;
		Node* next_node_rules = node_rules->_next;
		Node* check_next_oper = next_node_rules->_next;
		Node* prev_oper = next_node_rules->_prev;
		bool log_val = false;
		while (k < rules._size)
		{
			node = rules_node->_address;
			node_rules = node;
			next_node_rules = node_rules->_next;
			check_next_oper = next_node_rules->_next;
			prev_oper = next_node_rules->_prev;
			log_val = false;
			for (int i = 0; next_node_rules->_fact != "->"; i++)
			{
				if (next_node_rules->_fact == "|")
				{
					next_node_rules = next_node_rules->_next;
					next_node_rules = next_node_rules->_next;
					node_rules = next_node_rules->_prev;
					check_next_oper = next_node_rules->_next;
				}
				if (next_node_rules->_fact == ",")
				{
					next_node_rules = next_node_rules->_next;
					if (i > 0)
					{
						check_next_oper = next_node_rules->_next;
						prev_oper = node_rules->_prev;
						if ((prev_oper->is_true && find_fact(next_node_rules->_fact, head_facts)) && (prev_oper->_fact == ","))
						{
							node_rules = node_rules->_next;
							node_rules->is_true = true;
						}

						else if ((find_fact(node_rules->_fact, head_facts) && find_fact(next_node_rules->_fact, head_facts)) && (prev_oper->_fact == "|"))
						{
							node_rules = node_rules->_next;
							node_rules->is_true = true;
						}

						node_rules = check_next_oper->_prev;
						next_node_rules = node_rules->_next;
					}
					if (i == 0)
					{
						if ((find_fact(node_rules->_fact, head_facts) == true) && (find_fact(next_node_rules->_fact, head_facts) == true))
						{
							node_rules = node_rules->_next;
							node_rules->is_true = true;
						}
						else
						{
							node_rules = node_rules->_next;
						}
						node_rules = node_rules->_next;
						next_node_rules = node_rules->_next;
					}
				}
			}

			node_rules = node;
			next_node_rules = node_rules->_next;

			for (int i = 0; next_node_rules->_fact != "->"; i++)
			{
				if (next_node_rules->_fact == "|")
				{
					next_node_rules = next_node_rules->_next;
					if (i > 0)
					{
						check_next_oper = next_node_rules->_next;
						prev_oper = node_rules->_prev;
						if (check_next_oper->_fact == ",")
						{
							for (int j = 0; (check_next_oper->_fact != "|") && (check_next_oper->_fact != "->"); j++)
							{
								check_next_oper = check_next_oper->_next;
							}
							check_next_oper = check_next_oper->_prev;
							check_next_oper = check_next_oper->_prev;
							if (prev_oper->is_true || check_next_oper->is_true)
							{
								node_rules = node_rules->_next;
								check_next_oper->is_true = true;
								node_rules->is_true = true;
								log_val = true;
							}
							else log_val = false;
						}

						else if (prev_oper->is_true || find_fact(next_node_rules->_fact, head_facts))
						{

							node_rules = node_rules->_next;
							node_rules->is_true = true;
							log_val = true;
						}

						else if ((check_next_oper->_fact == "->") && (prev_oper->is_true || find_fact(next_node_rules->_fact, head_facts)))
						{
							node_rules = node_rules->_next;
							node_rules->is_true = true;
							log_val = true;
						}
						else
						{
							log_val = false;
							node_rules = node_rules->_next;
						}


						node_rules = check_next_oper->_prev;
						next_node_rules = node_rules->_next;
					}
					if (i == 0)
					{
						check_next_oper = next_node_rules->_next;
						if (check_next_oper->_fact == ",")
						{
							for (int j = 0; (check_next_oper->_fact != "|") && (check_next_oper->_fact != "->"); j++)
							{
								check_next_oper = check_next_oper->_next;
							}
							check_next_oper = check_next_oper->_prev;
							check_next_oper = check_next_oper->_prev;
							if ((find_fact(node_rules->_fact, head_facts)) || (check_next_oper->is_true))
							{
								node_rules = node_rules->_next;
								check_next_oper->is_true = true;
								node_rules->is_true = true;
								log_val = true;
							}
							else log_val = false;
						}

						else if ((find_fact(node_rules->_fact, head_facts) || find_fact(next_node_rules->_fact, head_facts)) && ((check_next_oper->_fact == "|") || (check_next_oper->_fact == "->")))
						{
							node_rules = node_rules->_next;
							node_rules->is_true = true;
							log_val = true;
						}
						else
						{
							node_rules = node_rules->_next;
							log_val = false;
						}
						node_rules = node_rules->_next;
						next_node_rules = node_rules->_next;
					}
				}
				if (next_node_rules->_fact == ",")
				{
					if (next_node_rules->is_true) log_val = true;
					else log_val = false;
					next_node_rules = next_node_rules->_next;
					next_node_rules = next_node_rules->_next;
					node_rules = next_node_rules->_prev;
					check_next_oper = next_node_rules->_next;
					check_next_oper = check_next_oper->_next;
				}
			}
			if (log_val == true)
			{
				rules_node->is_true = true;
			}

			new_facts_node = new_facts.Head;

			next_node_rules = rules_node->_address;
			while (next_node_rules->_fact != "->")
			{
				next_node_rules = next_node_rules->_next;
			}

			if (rules_node->is_true == true)
			{
				while (next_node_rules->_next != nullptr)
				{
					next_node_rules = next_node_rules->_next;
					node_rules = this->Head;
					if (find_fact(next_node_rules->_fact, this->Head) == false)
					{
						node = facts.add_node();
						node->_fact = next_node_rules->_fact;
						new_facts_node = new_facts.add_node();
						new_facts_node->_fact = next_node_rules->_fact;
					}
				}
			}

			rules_node = rules_node->_next;
			++k;
		}
		return new_facts;
	}


	void print_list(Node* node)
	{
		for (int i = 0; node->_next != nullptr; i++)
		{
			cout << node->_fact << " ";
			node = node->_next;
		}
		cout << node->_fact << " " << endl;
		cout << endl;
	}
};