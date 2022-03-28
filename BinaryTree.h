#pragma once
#include <string>
#include <iostream>
#include <fstream>

#define LOX printf("%d\n", __LINE__);


namespace iLab
{	
	using std::string;
	using std::cout;
	using std::endl;

	template <class T> class Tree;

	template <class T>
	class Node_t
	{
		friend Tree<T>;
	public:
		Node_t();
		Node_t(const T& _data);
		~Node_t();

		Node_t<T>& operator=(Node_t<T>& node);
		friend std::ostream& operator<<(std::ostream const& stream, const Node_t<T>& node);

		void GraphDump(string filename = "dump");

	private:
		T data;

		Node_t* left;
		Node_t* rigth;

	};


	template <class T>
	Node_t<T>::Node_t()
	{
		data = 0;
		
		left = nullptr;
		rigth = nullptr;
	}

	template<class T>
	Node_t<T>::Node_t(const T& _data)
	{
		data = _data;
		left = nullptr;
		rigth = nullptr;
	}

	template <class T>
	Node_t<T>::~Node_t()
	{
	}

	template<class T>
	Node_t<T>& Node_t<T>::operator=(Node_t<T>& node)
	{
		data = node.data;
		left = node.left;
		rigth = node.rigth;

		return *this;
	}

	template <class T>
	std::ostream& operator<<(std::ostream const& stream, const Node_t<T>& node)
	{
		stream << node.data;
		return stream;
	}

	
	//----------------------------------------------------------------------------
	
	template <class T>
	class Tree
	{
	public:
		Tree();
		~Tree();

		int Incert(const T& data);

		void GraphDump(string filename = "dump");

	private:
		Node_t<T>* root;
		size_t size;

		void CreateNode(const T& data, Node_t<T>*& node);
		void DumpNode(std::ofstream& dumpfile, const Node_t<T>* node, int number_of_node = 0);
	};


	template <class T>
	Tree<T>::Tree()
	{
		root = new Node_t<T>;
		size = 0;
	}

	template <class T>
	Tree<T>::~Tree()
	{
	}

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
			Node_t<T>* father = nullptr;
			while (node != nullptr)
			{
				if (data < node->data)
				{
					father = node;
					node = node->left;
				}
				else if (data > node->data)
				{
					father = node;
					node = node->rigth;
				}
				else return -1;
			}

			if (data < father->data)
				CreateNode(data, father->left);
			else
				CreateNode(data, father->rigth);
		}
		++size;
		return 0;
	}

	template<class T>
	void Tree<T>::CreateNode(const T& data, Node_t<T>*& node)
	{
		Node_t<T>* new_node = new Node_t<T>;
		new_node->data = data;
		node = new_node;
	}

	template<class T>
	void Tree<T>::DumpNode(std::ofstream& dumpfile, const Node_t<T>* node, int number_of_node)
	{
		dumpfile << "Node" << number_of_node << "[shape=\"octagon\", label=" << node->data << "\"];\n";

		if (node->left) DumpNode(dumpfile, node->left, number_of_node + 1);
		if (node->rigth) DumpNode(dumpfile, node->rigth, number_of_node + 2);
	}


	template<class T>
	void iLab::Tree<T>::GraphDump(string filename)
	{
		std::ofstream dumpfile;
		dumpfile.open(filename);

		dumpfile << "digraph " << filename << "{\n";
		DumpNode(dumpfile, root);
	}

}