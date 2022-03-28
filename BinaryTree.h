#pragma once


namespace iLab
{
	template <class T> class BinaryTree;

	template <class T>
	class Node
	{
		friend BinaryTree<T>;
	public:
		Node();
		Node(const T& data);
		Node(const Node& node);
		~Node();

		Node<T>& operator=(const Node<T>& node);

	private:
		T __data__;
		BinaryTree<T>* __left__;
		BinaryTree<T>* __right__;
	};

	template <class T>
	Node<T>::Node()
	{
		__left__ = nullptr;
		__right__ = nullptr;
	}

	template<class T>
	Node<T>::Node(const T& data)
	{
		__data__ = data;
		__left__ = nullptr;
		__right__ = nullptr;
	}

	template<class T>
	Node<T>::Node(const Node& node)
	{
		__data__ = *node.__data__;
		__left__  = node.__left__;
		__right__ = node.__right__;
	}

	template <class T>
	Node<T>::~Node()
	{
	}

	template<class T>
	Node<T>& Node<T>::operator=(const Node<T>& node)
	{
		__data__  = node.__data__;
		__left__  = node.__left__;
		__right__ = node.__right__;

		return *this;
	}
	
	//---------------------------------------------------------------------------------------------
	
	template <class T>
	class BinaryTree
	{
		friend Node<T>;
	public:
		BinaryTree();
		~BinaryTree();

		int Incert(const T& data);

	private:
		size_t __size__;
		unsigned __lvl__;
		Node<T>* __root__;
	};


	template <class T>
	BinaryTree<T>::BinaryTree()
	{
		__size__ = 0;
		__lvl__  = 0;
		__root__ = new Node<T>;
	}

	template <class T>
	BinaryTree<T>::~BinaryTree()
	{
		delete __root__;
	}

	template <class T>
	int BinaryTree<T>::Incert(const T& data)
	{
		Node<T>* node = __root__;
		
		while (node->__left__ != nullptr or node->__right__ != nullptr)
		{
			if (data < node->__data__)
				node = node->__left__->__root__;
			else
				node = node->__right__->__root__;
		}

		Node<T> element(data);
		if (data < node->__data__)
		{
			node->__left__ = element;
			return 0;
		}
		else if (data > node->__data__)
		{
			node->__right__ = element;
			return 0;
		}
		return -1;
		
	}

}