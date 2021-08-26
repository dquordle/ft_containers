#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key> >
	class map
	{

	private:

		typedef struct Node
		{
			ft::pair<const Key, T>	pair;
			Node*					left;
			Node*					right;
			Node*					parent;

			Node() : pair(pair()), left(nullptr), right(nullptr), parent(nullptr) {}
			Node(ft::pair<Key, T> newPair, Node* newLeft, Node* newRight, Node* newParent) :
			pair(newPair), left(newLeft), right(newRight), parent(newParent) {}
		}	TreeNode;

		template <typename V>
		class MapIterator
		{
		private:
			TreeNode* it;
			friend class map<Key, T, Compare>;
		public:
			MapIterator() : it(nullptr) {};
			MapIterator(TreeNode* p) : it(p) {};
			MapIterator(MapIterator<V> const & src)
			{
				*this = src;
			};
			MapIterator<V> & operator=(MapIterator<V> const & src)
			{
				if (this != &src)
					it = src.it;
				return *this;
			}

			bool operator==(MapIterator<V> const & src)
			{
				return it == src.it;
			}
			bool operator!=(MapIterator<V> const & src)
			{
				return it != src.it;
			}

			V & operator*() const
			{
				return it->pair;
			}
			V * operator->() const
			{
				return &(it->pair);
			}

			MapIterator & operator++()
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

			MapIterator & operator--()
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

			MapIterator operator++(int)
			{
				MapIterator<V> temp = *this;
				++(*this);
				return temp;
			}

			MapIterator operator--(int)
			{
				MapIterator<V> temp = *this;
				--(*this);
				return temp;
			}
		};

		template <typename V>
		class ReverseMapIterator
		{
		private:
			TreeNode* it;
			friend class map<Key, T>;
		public:
			ReverseMapIterator() : it(nullptr) {};
			ReverseMapIterator(TreeNode* p) : it(p) {};
			ReverseMapIterator(ReverseMapIterator<V> const & src)
			{
				*this = src;
			};
			ReverseMapIterator<V> & operator=(ReverseMapIterator<V> const & src)
			{
				if (this != &src)
					it = src.it;
				return *this;
			}

			bool operator==(ReverseMapIterator<V> const & src)
			{
				return it == src.it;
			}
			bool operator!=(ReverseMapIterator<V> const & src)
			{
				return it != src.it;
			}

			V & operator*()
			{
				return it->pair;
			}
			V * operator->()
			{
				return &(it->pair);
			}

			ReverseMapIterator & operator++()
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

			ReverseMapIterator & operator--()
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

			ReverseMapIterator operator++(int)
			{
				ReverseMapIterator<V> temp = *this;
				++(*this);
				return temp;
			}

			ReverseMapIterator operator--(int)
			{
				ReverseMapIterator<V> temp = *this;
				--(*this);
				return temp;
			}

		};

	public:
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef pair<const Key, T>								value_type;
		typedef Compare											key_compare;
		typedef	std::allocator<TreeNode>						allocator_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef value_type*										pointer;
		typedef const value_type*								const_pointer;
		typedef	MapIterator<value_type>							iterator;
		typedef MapIterator<const value_type>					const_iterator;
		typedef	ReverseMapIterator<value_type>					reverse_iterator;
		typedef	ReverseMapIterator<const value_type>			const_reverse_iterator;
		typedef ptrdiff_t										difference_type;
		typedef size_t											size_type;

	private:
		TreeNode*			_head;
		TreeNode*			_last;
		size_type			_size;
		allocator_type		_allocator;
		key_compare			_comp;


	public:
		explicit map(const key_compare& comp = key_compare()) :
		_head(nullptr), _last(nullptr), _size(0), _comp(comp) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare()) :
		_head(nullptr), _last(nullptr), _size(0), _comp(comp)
		{
			insert(first, last);
		}

		map(const map& x) :
		_head(nullptr), _last(nullptr), _size(0), _comp(x._comp)
		{
			for (const_iterator it = x.begin(); it != x.end(); it++)
				insert(end(), *it);
		}

		~map()
		{
			clear();
		}

		map& operator= (const map& x)
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
			TreeNode* temp = _head;
			if (temp)
			{
				while (temp->left)
					temp = temp->left;
			}
			return iterator(temp);
		}

		const_iterator begin() const
		{
			TreeNode* temp = _head;
			if (temp)
			{
				while (temp->left)
					temp = temp->left;
			}
			return const_iterator(temp);
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


		mapped_type& operator[] (const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
		}

		pair<iterator,bool> insert (const value_type& val)
		{
			TreeNode* node = _head;
			if (!node)
			{
				_head = _allocator.allocate(1);
				_allocator.construct(_head, TreeNode(val, nullptr, nullptr, nullptr));
				_size++;
				_last = _head;
				return ft::make_pair(iterator(_head), true);
			}
			while (true)
			{
				if (_comp(val.first, node->pair.first))
				{
					if (!node->left)
					{
						node->left = _allocator.allocate(1);
						_allocator.construct(node->left, TreeNode(val, nullptr, nullptr, node));
						_size++;
						return ft::make_pair(iterator(node->left), true);
					}
					node = node->left;
				}
				else if (_comp(node->pair.first, val.first))
				{
					if (!node->right)
					{
						node->right = _allocator.allocate(1);
						_allocator.construct(node->right, TreeNode(val, nullptr, nullptr, node));
						_size++;
						if (node == _last)
							_last = node->right;
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
			if (position == end() && _head && _comp(_last->pair.first, val.first))
			{
				_last->right = _allocator.allocate(1);
				_allocator.construct(_last->right, TreeNode(val, nullptr, nullptr, _last));
				_size++;
				_last = _last->right;
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
			if (!node->right && !node->left)
			{
				if (node->parent)
				{
					TreeNode *temp = node;
					node = node->parent;
					if (temp == node->right)
						node->right = nullptr;
					else
						node->left = nullptr;
				}
				else
					_head = nullptr;
			}
			else if (node == _head)
			{
				if (node->left)
					_head = node->left;
				else
					_head = node->right;
				_head->parent = nullptr;
			}
			else if (!node->left)
			{
				TreeNode *temp = node;
				node = node->parent;
				if (temp == node->right)
					node->right = temp->right;
				else
					node->left = temp->right;
				temp->right->parent = node;
			}
			else if (!node->right)
			{
				TreeNode *temp = node;
				node = node->parent;
				if (temp == node->right)
					node->right = temp->left;
				else
					node->left = temp->left;
				temp->left->parent = node;
			}
			else
			{
				TreeNode *temp = node->right;
				while (temp->left)
					temp = temp->left;
				if (node->right == temp)
					temp->parent->right = temp->right;
				else
					temp->parent->left = temp->right;
				if (temp->right)
					temp->right->parent = temp->parent;
				TreeNode *par = node->parent;
				temp->parent = par;
				if (par->right == node)
					par->right = temp;
				else
					par->left = temp;
				temp->right = node->right;
				if (node->right)
					node->right->parent = temp;
				temp->left = node->left;
				node->left->parent = temp;
			}
			_allocator.destroy(position.it);
			_allocator.deallocate(position.it, 1);
			_size--;
		}

		size_type erase (const key_type& k)
		{
			iterator it = find(k);
			if (it != end())
			{
				erase(it);
				return 1;
			}
			return 0;
		}

		void erase (iterator first, iterator last)
		{
			for (iterator it = first; it != last; )
			{
				iterator temp = it++;
				erase(temp);
			}
		}

		void swap (map& x)
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

		class value_compare
		{
			friend class map;
		protected:
			Compare comp;
			explicit value_compare(Compare c) : comp(c) {}
		public:
			value_compare() : comp(key_compare()) {}
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		value_compare value_comp() const
		{
			return value_compare();
		}

		iterator find(const key_type& k)
		{
			TreeNode* node = _head;
			while (node)
			{
				if (_comp(k, node->pair.first))
					node = node->left;
				else if (_comp(node->pair.first, k))
					node = node->right;
				else
					break;
			}
			return iterator(node);
		}

		const_iterator find (const key_type& k) const
		{
			TreeNode* node = _head;
			while (node)
			{
				if (_comp(k, node->pair.first))
					node = node->left;
				else if (_comp(node->pair.first, k))
					node = node->right;
				else
					break;
			}
			return const_iterator(node);
		}

		size_type count (const key_type& k) const
		{
			if (find(k) != end())
				return 1;
			return 0;
		}

		iterator lower_bound (const key_type& k)
		{
			iterator it = begin();
			while (it != end())
			{
				if (!_comp(it.it->pair.first, k))
					return it;
				it++;
			}
			return it;
		}

		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator it = begin();
			while (it != end())
			{
				if (!_comp(it.it->pair.first, k))
					return it;
				it++;
			}
			return it;
		}

		iterator upper_bound (const key_type& k)
		{
			iterator it = begin();
			while (it != end())
			{
				if (_comp(k, it.it->pair.first))
					return it;
				it++;
			}
			return it;
		}

		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator it = begin();
			while (it != end())
			{
				if (_comp(k, it.it->pair.first))
					return it;
				it++;
			}
			return it;
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			const_iterator end = lower_bound(k);
			const_iterator start = end;
			if (!_comp(k, end.it->pair.first) && !_comp(end.it->pair.first, k))
				end++;
			return ft::make_pair(start, end);
		}

		pair<iterator,iterator> equal_range (const key_type& k)
		{
			iterator end = lower_bound(k);
			iterator start = end;
			if (!_comp(k, end.it->pair.first) && !_comp(end.it->pair.first, k))
				end++;
			return ft::make_pair(start, end);
		}

		allocator_type get_allocator() const
		{
			return _allocator;
		}
	};
}

#endif
