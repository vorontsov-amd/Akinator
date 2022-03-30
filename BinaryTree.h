#pragma once
#pragma warning(disable : 4996)
#include <string>
#include <iostream>
#include <fstream>

#define LOX printf("%d\n", __LINE__);
extern std::string tab(int n);

namespace iLab
{	
	using std::string;
	using std::cout;
	using std::endl;

	template <class T> class Tree;
	class Akinator;

	template <class T>
	class Node_t
	{
		friend Tree<T>;
		friend Akinator;
	public:
		Node_t();
		Node_t(const T& _data);
		Node_t(Node_t<T>& node);
		~Node_t();

		Node_t<T>& operator=(const Node_t<T>& node);

		template<class T>
		friend std::ostream& operator<<(std::ostream& stream, Node_t<T> const& node);

	private:
		T data;

		Node_t* parrent;

		Node_t* left;
		Node_t* rigth;

	};


	template <class T>
	Node_t<T>::Node_t()
	{
		parrent = nullptr;
		left = nullptr;
		rigth = nullptr;
	}

	template<class T>
	Node_t<T>::Node_t(const T& _data)
	{
		data = _data;
		parrent = nullptr;
		left = nullptr;
		rigth = nullptr;
	}

	template<class T>
	Node_t<T>::Node_t(Node_t<T>& node)
	{
		data = node.data;
		parrent = node.parrent;
		left = node.left;
		rigth = node.rigth;
	}

	template <class T>
	Node_t<T>::~Node_t()
	{
	}

	template<class T>
	Node_t<T>& Node_t<T>::operator=(const Node_t<T>& node)
	{
		data = node.data;
		return *this;
	}

	template<class T>
	std::ostream& operator<<(std::ostream& stream, Node_t<T> const& node)
	{
		return stream << node.data;
	}

	// template<class T>
	// std::ostream& operator<<(std::ostream& stream, Node_t<T> const& node)
	// {
	// 	return stream << node.data;
	// }


	
	//----------------------------------------------------------------------------
	
	template <class T>
	class Tree
	{
	public:
		Tree();
		//Tree(Tree<T>& tree);
		~Tree();

		//Tree<T>& operator=(const Tree<T>& tree);

		int Incert(const T& data);
		int Delete(const T& data);

		int Print();
		int Scan(const char* filename = "DataBase");
		void GraphDump(const char* filename = "dump");

	protected:
		Node_t<T>* root;
		size_t size;


		void CreateNode(const T& data, Node_t<T>*& parrent, Node_t<T>*& node);
		void DumpNode(std::ofstream& dumpfile, const Node_t<T>* node);

		Node_t<T>* Find(Node_t<T>* root, const T& value);
	private:
		void StabilizateLeftRoot(Node_t<T>* node);
		void StabilizateRightRoot(Node_t<T>* node);

	protected:
		void Write(std::ofstream& file, Node_t<T>* node, int n);
		void Read(std::ifstream& file, Node_t<T>*& node, Node_t<T>* parrent, T& element);

		//void Free(Node_t<T>* tree);
	};



	template <class T>
	Tree<T>::Tree()
	{
		root = new Node_t<T>;
		size = 0;
	}

	//template<class T>
	//Tree<T>::Tree(Tree<T>& tree)
	//{
	//	*root = *tree.root;
	//	size = tree.size;
	//}

	template <class T>
	Tree<T>::~Tree()
	{
		//if (root) Free(root);
	}

	//template<class T>
	//Tree<T>& Tree<T>::operator=(const Tree<T>& tree)
	//{
	//	root = tree.root;
	//	size = tree.size;
	//	return *this;
	//}

	template <class T>
	int Tree<T>::Incert(const T& data)
	{
		Node_t<T>* node = root;

		if (size == 0)
		{
			root->data = data;
		}
		else
		{
			Node_t<T>* parrent = nullptr;
			while (node != nullptr)
			{
				if (data < node->data)
				{
					parrent = node;
					node = node->left;
				}
				else if (data > node->data)
				{
					parrent = node;
					node = node->rigth;
				}
				else return -1;
			}

			if (data < parrent->data)
				CreateNode(data, parrent, parrent->left);
			else
				CreateNode(data, parrent, parrent->rigth);
		}
		++size;
		return 0;
	}

	template<class T>
	int Tree<T>::Delete(const T& data)
	{
		Node_t<T>* node = Find(root, data);
		
		if (node = node->parrent->left)
		{
			StabilizateLeftRoot(node);
		}

		else if (node = node->parrent->rigth)
		{
			StabilizateRightRoot(node);
		}

		else return -1;

		return 0;
	}

	template<class T>
	void Tree<T>::StabilizateLeftRoot(Node_t<T>* node)
	{
		if (node->left != nullptr and node->rigth != nullptr)
		{
			node->parrent->left = node->rigth;
			node->rigth->parrent = node->parrent;
			Node_t<T>* root = node->rigth;
			while (root->left != nullptr)
			{
				root = root->left;
			}
			root->left = node->left;
			node->left->parrent = root;
		}
		else if (node->rigth != nullptr)
		{
			node->rigth->parrent = node->parrent;
			node->parrent->left = node->rigth;
		}
		else
		{
			node->left->parrent = node->parrent;
			node->parrent->left = node->left;
		}
		delete node;
	}

	template<class T>
	void Tree<T>::StabilizateRightRoot(Node_t<T>* node)
	{
		if (node->left != nullptr and node->rigth != nullptr)
		{
			node->parrent->rigth = node->left;
			node->left->parrent = node->parrent;
			Node_t<T>* root = node->left;
			while (root->rigth != nullptr)
			{
				root = root->rigth;
			}
			root->rigth = node->rigth;
			node->rigth->parrent = root;
		}
		else if (node->rigth != nullptr)
		{
			node->rigth->parrent = node->parrent;
			node->parrent->rigth = node->rigth;
		}
		else
		{
			node->left->parrent = node->parrent;
			node->parrent->rigth = node->left;
		}
		delete node;
	}

	template<class T>
	void Tree<T>::CreateNode(const T& data, Node_t<T>*& parrent, Node_t<T>*& node)
	{
		Node_t<T>* new_node = new Node_t<T>;
		new_node->data = data;
		new_node->parrent = parrent;
		node = new_node;
	}

	template<class T>
	void Tree<T>::DumpNode(std::ofstream& dumpfile, const Node_t<T>* node)
	{
		dumpfile << "Node" << node << "[shape=\"record\", label=\"" << node->data << "\"];\n";

		if (node->left)
		{
			DumpNode(dumpfile, node->left);
			dumpfile << "Node" << node << "->" << "Node" << node->left << ";\n";
		}
		if (node->rigth)
		{
			DumpNode(dumpfile, node->rigth);
			dumpfile << "Node" << node << "->" << "Node" << node->rigth << ";\n";
		}
	}

	template<class T>
	Node_t<T>* Tree<T>::Find(Node_t<T>* root, const T& value)
	{
		Node_t<T>* node = root;
		while (node != nullptr)
		{
			if (node->data == value)
				return node;
			else if (node->data < value)
				node = node->rigth;
			else
				node = node->left;
		}
		return nullptr;
	}


	template<class T>
	int Tree<T>::Print()
	{
		std::ofstream out;
		out.open("DataBase");
		Write(out, root, 0);
		out.close();

		return 0;
	}

	template<class T>
	int Tree<T>::Scan(const char* filename)
	{
		std::ifstream in;
		in.open(filename);
		T element;
		Read(in, root, nullptr, element);
		in.close();
		
		return 0;
	}

	template<class T>
	void Tree<T>::Write(std::ofstream& file, Node_t<T>* node, int n)
	{
		file << tab(n) << "{ " << node->data << endl;
		if (node->rigth) Write(file, node->rigth, n + 1);
		if (node->left)  Write(file, node->left,  n + 1);
		file << tab(n) << "}\n";

	}

	template<class T>
	void Tree<T>::Read(std::ifstream& file, Node_t<T>*& node, Node_t<T>* parrent, T& element)
	{
		char test = 0;
		file >> test;
		if (test == '{')
		{
			file >> element;
			CreateNode(element, parrent, node);
			Read(file, node->rigth, node, element);
			Read(file, node->left, node, element);
		}
		else if (test == '}')
		{
			file.putback(test);
			return;
		}
		file >> test;
	}

	//template<class T>
	//void Tree<T>::Free(Node_t<T>* tree)
	//{
	//	if (tree->left)  Free(tree->left);
	//	if (tree->rigth) Free(tree->rigth);
	//	if (tree)
	//	{
	//		delete tree;
	//		tree = nullptr;
	//	}
	//}

	template<class T>
	void iLab::Tree<T>::GraphDump(const char* graphname)
	{
		size_t length = strlen(graphname) + 50;
		char* command = new char[length] {};
		strncpy(command, graphname, length);
		strncat(command, ".dot", length);

		std::ofstream dumpfile;
		dumpfile.open(command);

		dumpfile << "digraph " << graphname << "{\n";
		DumpNode(dumpfile, root);
		dumpfile << "}";

		dumpfile.close();

		strncpy(command, "iconv -f cp1251 -t utf-8 ", length);
		strncat(command, graphname, length);
		strncat(command, ".dot > ", length);
		strncat(command, graphname, length);
		strncat(command, "-utf8.dot", length);
		system(command);

		strncpy(command, "dot -Tpdf ", length);
		strncat(command, graphname, length);
		strncat(command, "-utf8.dot", length);
		strncat(command, " -o ", length);
		strncat(command, graphname, length);
		strncat(command, ".pdf", length);

		system(command);
		delete[] command;
	}
}