#pragma once
#include "BinaryTree.h"
enum class script
{
	game,
	settings,
	exit,
	error_script,
};
enum class answer
{
	is_true,
	is_false,
	parrent,
};

using std::string;

script Greeting();
void ClearBuffer();
void Game();
void AddNewPerson(iLab::Akinator& aki);
void LoadGame(script scr);
void Settings();
char* StrToCh(string& str);
char* CreateDiffStr(string& new_person, string person);
char* CreateShowStr(string person);

namespace iLab
{
	typedef Node_t<string> node_t;
	typedef Tree<string> tree_t;

	using std::string;

	class Akinator : public tree_t
	{
	public:
		Akinator();
		~Akinator();

		int Scan(const char* filename = "DataBase");
		void Incert(const string& new_person, const string& different);

		node_t& ShowCurrent();
		node_t* UpdateCurrent(answer ans);

	private:
		node_t* current_node;
		void Delete();
	};

	Akinator::Akinator()
	{
		current_node = root;
	}

	Akinator::~Akinator()
	{

	}



	int Akinator::Scan(const char* filename)
	{
		int ret = Tree::Scan(filename);
		current_node = root;
		return ret;
	}

	node_t& Akinator::ShowCurrent()
	{
		return *current_node;
	}
	node_t* Akinator::UpdateCurrent(answer ans)
	{
		if (ans == answer::is_true)
		{
			if (current_node->rigth) current_node = current_node->rigth;
			else return nullptr;
		}
		else if (ans == answer::is_false)
		{
			if (current_node->left) current_node = current_node->left;
			else return nullptr;
		}
			return current_node;
	}

	void Akinator::Delete()
	{
		return;
	}

	void Akinator::Incert(const string& new_person, const string& different)
	{		
		string current_person = current_node->data;
		current_node->data = different;
		CreateNode(new_person, current_node, current_node->rigth);
		CreateNode(current_person, current_node, current_node->left);
	}
}
