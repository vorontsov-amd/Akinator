#include "BinaryTree.h"

std::string tab(int n)
{
	if (n == 0)
		return "";
	else
	{
		std::string tabulate = "\t";
		for (int i = 0; i < n; ++i)
		{
			tabulate += tabulate;
		}
		return tabulate;
	}
}



namespace iLab
{
	using std::string;
	class Akinaor: private Tree<string>
	{
	public:
		Akinaor();
		~Akinaor();

	private:

	};

	Akinaor::Akinaor()
	{
	}

	Akinaor::~Akinaor()
	{
	}
}