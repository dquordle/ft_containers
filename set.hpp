#ifndef SET_HPP
#define SET_HPP

#include "pair.hpp"

#define BLACK	0
#define RED		1

namespace ft
{
	template < class T,	class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
	private:

		typedef struct Node
		{
			T			value;
			Node*		left;
			Node*		right;
			Node*		parent;
			int			color;

			Node() : value(T()), left(nullptr), right(nullptr), parent(nullptr), color(BLACK) {}
			Node(T newValue, Node* newLeft, Node* newRight, Node* newParent, int newColour) :
			value(newValue), left(newLeft), right(newRight), parent(newParent), color(newColour) {}
		}	TreeNode;


		template <typename V>
		class SetIterator
		{
		private:
			TreeNode* it;
			friend class set<T, Compare, Alloc>;

		public:
			SetIterator() : it(nullptr) {};
			SetIterator(TreeNode* p) : it(p) {};
			SetIterator(SetIterator<V> const & src)
			{
				*this = src;
			};

			SetIterator<V> & operator=(SetIterator<V> const & src)
			{
				if (this != &src)
					it = src.it;
				return *this;
			}

			bool operator==(SetIterator<V> const & src)
			{
				return it == src.it;
			}

			bool operator!=(SetIterator<V> const & src)
			{
				return it != src.it;
			}

			V & operator*() const
			{
				return it->value;
			}

			V * operator->() const
			{
				return &(it->value);
			}

			SetIterator & operator++()
			{
				if (it->right)
				{
					it = it->right;
					while (it->left)
						it = it->left;
				}
				else
				{
					TreeNode *temp = it;
					it = it->parent;
					while (it && temp == it->right)
					{
						temp = it;
						it = it->parent;
					}
				}
				return *this;
			}

			SetIterator & operator--()
			{
				if (it->left)
				{
					it = it->left;
					while (it->right)
						it = it->right;
				}
				else
				{
					TreeNode *temp = it;
					it = it->parent;
					while (it && temp == it->left)
					{
						temp = it;
						it = it->parent;
					}
				}
				return *this;
			}

			SetIterator operator++(int)
			{
				SetIterator<V> temp = *this;
				++(*this);
				return temp;
			}

			SetIterator operator--(int)
			{
				SetIterator<V> temp = *this;
				--(*this);
				return temp;
			}
		};

		template <typename V>
		class ReverseSetIterator
		{
		private:
			TreeNode* it;
			friend class set<T, Compare, Alloc>;

		public:
			ReverseSetIterator() : it(nullptr) {};
			ReverseSetIterator(TreeNode* p) : it(p) {};
			ReverseSetIterator(ReverseSetIterator<V> const & src)
			{
				*this = src;
			};

			ReverseSetIterator<V> & operator=(ReverseSetIterator<V> const & src)
			{
				if (this != &src)
					it = src.it;
				return *this;
			}

			bool operator==(ReverseSetIterator<V> const & src)
			{
				return it == src.it;
			}

			bool operator!=(ReverseSetIterator<V> const & src)
			{
				return it != src.it;
			}

			V & operator*() const
			{
				return it->value;
			}

			V * operator->() const
			{
				return &(it->value);
			}

			ReverseSetIterator & operator++()
			{
				if (it->left)
				{
					it = it->left;
					while (it->right)
						it = it->right;
				}
				else
				{
					TreeNode *temp = it;
					it = it->parent;
					while (it && temp == it->left)
					{
						temp = it;
						it = it->parent;
					}
				}
				return *this;
			}

			ReverseSetIterator & operator--()
			{
				if (it->right)
				{
					it = it->right;
					while (it->left)
						it = it->left;
				}
				else
				{
					TreeNode *temp = it;
					it = it->parent;
					while (it && temp == it->right)
					{
						temp = it;
						it = it->parent;
					}
				}
				return *this;
			}

			ReverseSetIterator operator++(int)
			{
				SetIterator<V> temp = *this;
				++(*this);
				return temp;
			}

			ReverseSetIterator operator--(int)
			{
				SetIterator<V> temp = *this;
				--(*this);
				return temp;
			}
		};

	public:

		typedef T												key_type;
		typedef T												value_type;
		typedef Compare											key_compare;
		typedef Compare											value_compare;
		typedef	std::allocator<TreeNode>						allocator_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef value_type*										pointer;
		typedef const value_type*								const_pointer;
		typedef	SetIterator<value_type>							iterator;
		typedef SetIterator<const value_type>					const_iterator;
		typedef	ReverseSetIterator<value_type>					reverse_iterator;
		typedef	ReverseSetIterator<const value_type>			const_reverse_iterator;
		typedef ptrdiff_t										difference_type;
		typedef size_t											size_type;


	private:
		TreeNode*			_head;
		TreeNode*			_last;
		size_type			_size;
		allocator_type		_allocator;
		key_compare			_comp;

	public:
		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_head(nullptr), _last(nullptr), _size(0), _allocator(alloc), _comp(comp) {}

		template <class InputIterator>
		set(InputIterator first, InputIterator last,
				 const key_compare& comp = key_compare(),
				 const allocator_type& alloc = allocator_type()) :
		 _head(nullptr), _last(nullptr), _size(0), _allocator(alloc), _comp(comp)
		 {
			insert(first, last);
		 }

		set (const set& x) :
		_head(nullptr), _last(nullptr), _size(0)
		{
			for (const_iterator it = x.begin(); it != x.end(); it++)
				insert(end(), *it);
		}

		~set()
		{
			clear();
		}

		set& operator= (const set& x)
		{
			if (this != &x)
			{
				clear();
				for (const_iterator it = x.begin(); it != x.end(); it++)
					insert(end(), *it);
			}
			return *this;
		}


		iterator begin()
		{
			TreeNode* node = _head;
			if (node)
			{
				while (node->left)
					node = node->left;
			}
			return iterator(node);
		}

		const_iterator begin() const
		{
			TreeNode* node = _head;
			if (node)
			{
				while (node->left)
					node = node->left;
			}
			return const_iterator(node);
		}

		iterator end()
		{
			return iterator(nullptr);
		}

		const_iterator end() const
		{
			return const_iterator(nullptr);
		}

		reverse_iterator rbegin()
		{
			TreeNode* temp = _head;
			if (temp)
			{
				while (temp->right)
					temp = temp->right;
			}
			return reverse_iterator(temp);
		}

		const_reverse_iterator rbegin() const
		{
			TreeNode* temp = _head;
			if (temp)
			{
				while (temp->right)
					temp = temp->right;
			}
			return const_reverse_iterator(temp);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(nullptr);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(nullptr);
		}


		bool empty() const
		{
			return _size == 0;
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return (std::numeric_limits<difference_type>::max() / sizeof(TreeNode));
		}

		pair<iterator,bool> insert (const value_type& val)
		{
			TreeNode* node = _head;
			if (!node)
			{
				_head = _allocator.allocate(1);
				_allocator.construct(_head, TreeNode(val, nullptr, nullptr, nullptr, BLACK));
				_size++;
				_last = _head;
				return ft::make_pair(iterator(_head), true);
			}
			while (true)
			{
				if (_comp(val, node->value))
				{
					if (!node->left)
					{
						node->left = _allocator.allocate(1);
						_allocator.construct(node->left, TreeNode(val, nullptr, nullptr, node, RED));
						_size++;
						insert_case1(node->left);
						return ft::make_pair(iterator(node->left), true);
					}
					node = node->left;
				}
				else if (_comp(node->value, val))
				{
					if (!node->right)
					{
						node->right = _allocator.allocate(1);
						_allocator.construct(node->right, TreeNode(val, nullptr, nullptr, node, RED));
						_size++;
						if (node == _last)
							_last = node->right;
						insert_case1(node->right);
						return ft::make_pair(iterator(node->right), true);
					}
					node = node->right;
				}
				else
					return ft::make_pair(iterator(node), false);
			}
		}

		iterator insert (iterator position, const value_type& val)
		{
			if (position == end() && _head && _comp(_last->value, val))
			{
				_last->right = _allocator.allocate(1);
				_allocator.construct(_last->right, TreeNode(val, nullptr, nullptr, _last, RED));
				_size++;
				_last = _last->right;
				insert_case1(_last);
				return iterator(_last);
			}
			return insert(val).first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for (InputIterator temp = first; temp != last; temp++)
				insert(*temp);
		}

		void erase (iterator position)
		{
			TreeNode* node = position.it;

			if (_last == node)
			{
				iterator newLast = position;
				newLast--;
				_last = newLast.it;
			}

			if (node->right && node->left)
			{
				TreeNode *temp = node->right;
				while (temp->left)
					temp = temp->left;
				node->value = temp->value;
				node = temp;
			}

			if (node == _head && _size == 1)
				_head = nullptr;
			else
			{
				delete_one_child(node);
				if (_head == node)
					_head = node->right ? node->right : node->left;
			}
			_allocator.destroy(node);
			_allocator.deallocate(node, 1);
			_size--;
		}

		size_type erase (const value_type& val)
		{
			iterator it = find(val);
			if (it != end())
			{
				erase(it);
				return 1;
			}
			return 0;
		}

		void erase (iterator first, iterator last)
		{
//			for (iterator it = first; it != last; )
//			{
//				iterator temp = it++;
//				erase(temp);
//			}
			while (_size > 0)
				erase(begin());
		}

		void swap (set& x)
		{
			TreeNode*	temp_head = _head;
			TreeNode*	temp_last = _last;
			size_type	temp_size = _size;
			_head = x._head;
			_last = x._last;
			_size = x._size;
			x._head = temp_head;
			x._last = temp_last;
			x._size = temp_size;
		}

		void clear()
		{
			erase(begin(), end());
		}

		key_compare key_comp() const
		{
			return _comp;
		}

		value_compare value_comp() const
		{
			return _comp;
		}

		iterator find (const value_type& val) const
		{
			TreeNode* node = _head;
			while (node)
			{
				if (_comp(val, node->value))
					node = node->left;
				else if (_comp(node->value, val))
					node = node->right;
				else
					break;
			}
			return iterator(node);
		}

		size_type count (const value_type& val) const
		{
			if (find(val) == end())
				return 0;
			return 1;
		}

		iterator lower_bound (const value_type& val) const
		{
			iterator it = begin();
			while (it != end())
			{
				if (!_comp(it.it->value, val))
					return it;
				it++;
			}
			return it;
		}

		iterator upper_bound (const value_type& val) const
		{
			iterator it = begin();
			while (it != end())
			{
				if (_comp(val, it.it->value))
					return it;
				it++;
			}
			return it;
		}

		pair<iterator,iterator> equal_range (const value_type& val) const
		{
			const_iterator start = lower_bound(val);
			const_iterator end = upper_bound(val);
			return ft::make_pair(start, end);
		}

		allocator_type get_allocator() const
		{
			return _allocator;
		}

		////////////////////////////////////
//		void test()
//		{
//			if (_size == 0)
//			{
//				std::cout << "Set is empty" << std::endl;
//				return ;
//			}
//			TreeNode* node = _head;
//			std::cout << "HEAD : " << node->value << std::endl;
//			std::cout << "Left side:" << std::endl;
//			int count = 0;
//			while (node)
//			{
//				std::cout << node->value << std::endl;
//				node = node->left;
//				count++;
//			}
//			std::cout << "Left height: " << count << std::endl;
//			std::cout << "/////////////////////////////" << std::endl;
//			std::cout << "Right side:" << std::endl;
//			node = _head;
//			count = 0;
//			while (node)
//			{
//				std::cout << node->value << std::endl;
//				node = node->right;
//				count++;
//			}
//			std::cout << "Right height: " << count << std::endl;
//		}
		///////////////////////////////


	private:

		TreeNode* grandparent(TreeNode* n)
		{
			if ((n != nullptr) && (n->parent != nullptr))
				return n->parent->parent;
			else
				return nullptr;
		}

		TreeNode* uncle(TreeNode *n)
		{
			TreeNode *g = grandparent(n);
			if (g == nullptr)
				return nullptr;
			if (n->parent == g->left)
				return g->right;
			else
				return g->left;
		}

		TreeNode* sibling(TreeNode *n)
		{
			if (n == n->parent->left)
				return n->parent->right;
			else
				return n->parent->left;
		}

		//////////////////////////////////////
		void rotate_left(TreeNode *n)
		{
			TreeNode *pivot = n->right;

			pivot->parent = n->parent;
			if (n->parent != NULL)
			{
				if (n->parent->left==n)
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			}

			n->right = pivot->left;
			if (pivot->left != NULL)
				pivot->left->parent = n;

			n->parent = pivot;
			pivot->left = n;
			if (_head == n)
				_head = pivot;
		}

		void rotate_right(TreeNode *n)
		{
			TreeNode *pivot = n->left;

			pivot->parent = n->parent;
			if (n->parent != NULL)
			{
				if (n->parent->left==n)
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			}
			n->left = pivot->right;
			if (pivot->right != NULL)
				pivot->right->parent = n;
			n->parent = pivot;
			pivot->right = n;
			if (_head == n)
				_head = pivot;
		}


		////////////////////////////////
		void insert_case1(TreeNode *n)
		{
			if (n->parent == NULL)
				n->color = BLACK;
			else
				insert_case2(n);
		}

		void insert_case2(TreeNode *n)
		{
			if (n->parent->color == BLACK)
				return;
			else
				insert_case3(n);
		}
		
		void insert_case3(TreeNode *n)
		{
			TreeNode *u = uncle(n), *g;

			if ((u != NULL) && (u->color == RED))
			{
				n->parent->color = BLACK;
				u->color = BLACK;
				g = grandparent(n);
				g->color = RED;
				insert_case1(g);
			}
			else
				insert_case4(n);
		}
		
		void insert_case4(TreeNode *n)
		{
			TreeNode *g = grandparent(n);

			if ((n == n->parent->right) && (n->parent == g->left))
			{
				rotate_left(n->parent);
				n = n->left;
			}
			else if ((n == n->parent->left) && (n->parent == g->right))
			{
				rotate_right(n->parent);
				n = n->right;
			}
			insert_case5(n);
		}
		
		void insert_case5(TreeNode *n)
		{
			TreeNode *g = grandparent(n);

			n->parent->color = BLACK;
			g->color = RED;
			if ((n == n->parent->left) && (n->parent == g->left))
				rotate_right(g);
			else
				rotate_left(g);
		}

		////////////////////////////////////

		void replace_node(TreeNode* n, TreeNode* child)
		{
			if (child)
				child->parent = n->parent;
			if (n->parent)
			{
				if (n == n->parent->left)
					n->parent->left = child;
				else
					n->parent->right = child;
			}
		}

		void delete_one_child(TreeNode *n)
		{
			TreeNode *child = n->left ? n->left : n->right;

			if (child)
				replace_node(n, child);
			if (n->color == BLACK)
			{
				if (child && child->color == RED)
					child->color = BLACK;
				else
				{
					if (!child)
						delete_case1(n);
					else
						delete_case1(child);
				}
			}
			if (!child)
				replace_node(n, child);
		}

		void
		delete_case1(TreeNode *n)
		{
			if (n->parent)
				delete_case2(n);
		}

		void delete_case2(TreeNode *n)
		{
			TreeNode *s = sibling(n);

			if (s->color == RED)
			{
				n->parent->color = RED;
				s->color = BLACK;
				if (n == n->parent->left)
					rotate_left(n->parent);
				else
					rotate_right(n->parent);
			}
			delete_case3(n);
		}

		void delete_case3(TreeNode *n)
		{
			TreeNode *s = sibling(n);

			if ((n->parent->color == BLACK) && (!s ||
				((s->color == BLACK) &&
				(!s->left || s->left->color == BLACK) &&
				(!s->right || s->right->color == BLACK))))
			{
				s->color = RED;
				delete_case1(n->parent);
			}
			else
				delete_case4(n);
		}

		void delete_case4(TreeNode *n)
		{
			TreeNode *s = sibling(n);

			if ((n->parent->color == RED) &&
				(s->color == BLACK) &&
				(!s->left || s->left->color == BLACK) &&
				(!s->right || s->right->color == BLACK))
			{
				s->color = RED;
				n->parent->color = BLACK;
			}
			else
				delete_case5(n);
		}

		void delete_case5(TreeNode *n)
		{
			TreeNode *s = sibling(n);

			if  (s->color == BLACK)
			{
				if ((n == n->parent->left) &&
					(!s->right || s->right->color == BLACK) &&
					(s->left && s->left->color == RED))
				{
					s->color = RED;
					s->left->color = BLACK;
					rotate_right(s);
				}
				else if ((n == n->parent->right) &&
					(!s->left || s->left->color == BLACK) &&
					(s->right && s->right->color == RED))
				{
					s->color = RED;
					s->right->color = BLACK;
					rotate_left(s);
				}
			}
			delete_case6(n);
		}
		
		void delete_case6(TreeNode *n)
		{
			TreeNode *s = sibling(n);

			s->color = n->parent->color;
			n->parent->color = BLACK;

			if (n == n->parent->left)
			{
				if (s->right)
					s->right->color = BLACK;
				rotate_left(n->parent);
			}
			else
			{
				if (s->left)
					s->left->color = BLACK;
				rotate_right(n->parent);
			}
		}
	};
}

#endif
