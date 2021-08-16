#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace ft
{
	template<typename T>
	class vector
	{

	private:
		template<typename S>
		class VectorIterator
		{
		private:
			S* it;
			VectorIterator() : it(nullptr) {};
			friend class vector<T>;
		public:
			VectorIterator(S* p) : it(p) {};
			VectorIterator(VectorIterator<S> const & src)
			{
				*this = src;
			};
			VectorIterator<S> & operator=(VectorIterator<S> const & src)
			{
				if (this != &src)
					it = src.it;
				return *this;
			}

			bool operator==(VectorIterator<S> const & src)
			{
				return it == src.it;
			}
			bool operator!=(VectorIterator<S> const & src)
			{
				return it != src.it;
			}

			S & operator*()
			{
				return *it;
			}
			S * operator->()
			{
				return it;
			}

			VectorIterator & operator++()
			{
				it++;
				return (*this);
			}
			VectorIterator & operator--()
			{
				it--;
				return (*this);
			}
			VectorIterator operator++(int)
			{
				VectorIterator<S> temp = *this;
				it++;
				return (temp);
			}
			VectorIterator operator--(int)
			{
				VectorIterator<S> temp = *this;
				it--;
				return (temp);
			}
		};

		template<typename S>
		class ReverseVectorIterator
		{
		private:
			S* it;
			ReverseVectorIterator() : it(nullptr) {};
			friend class vector<T>;
		public:
			ReverseVectorIterator(S* head) : it(head) {};
			ReverseVectorIterator(ReverseVectorIterator<S> const & src)
			{
				*this = src;
			};
			ReverseVectorIterator<S> & operator=(ReverseVectorIterator<S> const & src)
			{
				if (this != &src)
					it = src.it;
				return *this;
			}

			bool operator==(ReverseVectorIterator<S> const & src)
			{
				return it == src.it;
			}
			bool operator!=(ReverseVectorIterator<S> const & src)
			{
				return it != src.it;
			}

			S & operator*()
			{
				return *it;
			}
			S * operator->()
			{
				return it;
			}

			ReverseVectorIterator & operator++()
			{
				it--;
				return (*this);
			}
			ReverseVectorIterator & operator--()
			{
				it++;
				return (*this);
			}
			ReverseVectorIterator operator++(int)
			{
				VectorIterator<S> temp = *this;
				it--;
				return (temp);
			}
			ReverseVectorIterator operator--(int)
			{
				VectorIterator<S> temp = *this;
				it++;
				return (temp);
			}
		};

	public:
		typedef	std::allocator<T>						allocator_type;
		typedef size_t									size_type;
		typedef	T										value_type;
		typedef	value_type&								reference;
		typedef const value_type&						const_reference;
		typedef	std::ptrdiff_t							difference_type;
		typedef typename allocator_type::pointer		pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		typedef VectorIterator<T> 						iterator;
		typedef VectorIterator<const T> 				const_iterator;
		typedef ReverseVectorIterator<T>				reverse_iterator;
		typedef ReverseVectorIterator<const T>			const_reverse_iterator;


		vector<T>() : _size(0), _capacity(0)
		{
			_elements = _allocator.allocate(1);
			_elements[0] = T();
		}

		vector(int count, const T& value = T())
		: _capacity(count), _size(count)
		{
			_elements = _allocator.allocate(count + 1);
			for (int i = 0; i < count; i++)
			{
				_allocator.construct(_elements + i, value);
			}
			_elements[count] = T();
		}

		template<typename InputIt>
		vector( InputIt first, InputIt last) : _size(0), _capacity(0)
		{
			_elements = _allocator.allocate(1);
			_elements[0] = T();
			insert(begin(), first, last);
		}

		vector (const vector& x)
		{
			*this = x;
		}

		~vector()
		{
			for (int i = 0; i < _size + 1; i++)
			{
				_allocator.destroy(_elements + i);
			}
			_allocator.deallocate(_elements, _capacity + 1);
		}

		vector& operator=(const vector& x)
		{
			if (this == &x)
				return *this;
			for (int i = 0; i < _size + 1; i++)
			{
				_allocator.destroy(_elements + i);
			}
			_allocator.deallocate(_elements, _capacity + 1);
			_elements = _allocator.allocate(x._size + 1);
			for (int i = 0; i < x._size; i++)
			{
				_allocator.construct(_elements + i, x._elements[i]);
			}
			_elements[x._size] = T();
			_size = x._size;
			_capacity = _size;
		}



		iterator begin()
		{
			return iterator(_elements);
		}

		iterator end()
		{
			return iterator(_elements + _size);
		}

		const_iterator begin() const
		{
			return const_iterator(_elements);
		}

		const_iterator end() const
		{
			return const_iterator(_elements + _size);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_elements + _size - 1);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(_elements + _size - 1);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_elements - 1);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_elements - 1);
		}


		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return (std::numeric_limits<difference_type>::max() / sizeof(T));
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n > _size)
			{
				if (n > _capacity)
					reserve(n);
				for (size_type i = _size + 1; i < n + 1; i++)
					_allocator.construct(_elements + i, val);
			}
			else if (n < _size)
			{
				_allocator.destroy(_elements + n);
				_allocator.construct(_elements + n, _elements[_size]);
				for (size_type i = n + 1; i < _size + 1; i++)
					_allocator.destroy(_elements + i);
			}
			_size = n;
		}

		size_type capacity() const
		{
			return _capacity;
		}

		bool empty() const
		{
			return _size == 0;
		}

		void reserve(size_type n)
		{
			if (n > _capacity)
			{
				_capacity = n;
				T* temp = _allocator.allocate(_capacity + 1);
				for (int i = 0; i < _size + 1; i++)
					_allocator.construct(temp + i, _elements[i]);
				for (int j = 0; j < _size + 1; j++)
					_allocator.destroy(_elements + j);
				_allocator.deallocate(_elements, _capacity + 1);
				_elements = temp;
			}
		}



		reference operator[](size_type n)
		{
			return _elements[n];
		}

		const_reference operator[](size_type n) const
		{
			return _elements[n];
		}

		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("Index out of range");
			return _elements[n];
		}

		const_reference at (size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("Index out of range");
			return _elements[n];
		}

		reference front()
		{
			return _elements[0];
		}

		const_reference front() const
		{
			return _elements[0];
		}

		reference back()
		{
			return _elements[_size - 1];
		}

		const_reference back() const
		{
			return _elements[_size - 1];
		}



		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			clear();
			insert(begin(), first, last);
		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			reserve(n);
			for (int i = 0;  i < n; i++)
				_allocator.construct(_elements + i, val);
			_allocator.construct(_elements + n, T());
			_size = n;
		}

		void push_back (const value_type& val)
		{
			if (_capacity == 0)
				reserve(1);
			else if (_size == _capacity)
				reserve(2 * _capacity);
			_elements[_size + 1] = _elements[_size];
			_allocator.construct(_elements + _size, val);
			_size++;
		}

		void pop_back()
		{
			_allocator.destroy(_elements + _size - 1);
			_elements[_size - 1] = _elements[_size];
			_size--;
		}


		iterator insert (iterator position, const value_type& val)
		{
			size_type index = 0;
			iterator it = begin();
			while (it != position)
			{
				it++;
				index++;
			}
			if (_size == _capacity)
			{
				_capacity *= 2;
				if (_capacity == 0)
					_capacity++;
				reserve(_capacity);
			}
			size_type in2 = _size + 1;
			while (in2 != index)
			{
				_elements[in2] = _elements[in2 - 1];
				in2--;
			}
			_elements[index] = val;
			_size++;
			return iterator(_elements + index);
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			size_type index = 0;
			iterator it = begin();
			while (it != position)
			{
				it++;
				index++;
			}
			if (_capacity < _size + n)
			{
				_capacity *= 2;
				if (_capacity < _size + n)
					_capacity = _size + n;
				reserve(_capacity);
			}
			size_type in2 = _size;
			while (in2 + 1 != index)
			{
				_elements[in2 + n] = _elements[in2];
				in2--;
			}
			_size += n;
			while (n > 0)
				_elements[in2 + --n] = val;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			size_type index = 0;
			iterator it = begin();
			while (it != position)
			{
				it++;
				index++;
			}
			size_type n = 0;
			InputIterator temp;
			while (temp != last)
			{
				temp++;
				n++;
			}
			if (_capacity < _size + n)
			{
				_capacity *= 2;
				if (_capacity < _size + n)
					_capacity = _size + n;
				reserve(_capacity);
			}
			size_type in2 = _size;
			while (in2 != index)
			{
				_elements[in2 + n] = _elements[in2];
				in2--;
			}
			_size += n;
			while (n > 0)
			{
				_allocator.construct(_elements + in2 + --n,  *first);
				first++;
			}
		}

		iterator erase(iterator position)
		{
			_allocator.destroy(position.it);
			for (iterator it = position; it != end(); it++)
				*it = *(it + 1);
			_size--;
			return position;
		}

		iterator erase(iterator first, iterator last)
		{
			size_type temp = _size;
			for (iterator it = first; it != last; it++, _size--)
				_allocator.destroy(it.it);
			for (iterator it = first; last != end(); last++)
				*it = *last;
			_elements[_size] = _elements[temp];
			return first;
		}



		void swap(vector& x)
		{
			size_type	temp_size = x._size;
			size_type	temp_capacity = x._capacity;
			T*			temp_els = x._elements;

			x._size = _size;
			x._capacity = _capacity;
			x._elements = _elements;

			_size = temp_size;
			_capacity = temp_capacity;
			_elements = temp_els;
		}

		void clear()
		{
			for (int i = 0; i < _size; i++)
				_allocator.destroy(_elements + i);
			_size = 0;
		}

		allocator_type get_allocator() const
		{
			return _allocator;
		}

	private:
		T*					_elements;
		std::allocator<T>	_allocator;
		size_type			_size;
		size_type			_capacity;
	};

	template <class T>
	bool operator== (const vector<T>& lhs, const vector<T>& rhs)
	{
		if (&lhs == &rhs)
			return true;
		if (lhs.size() != rhs.size())
			return false;
		typename ft::vector<T>::const_iterator lit = lhs.begin();
		typename ft::vector<T>::const_iterator rit = rhs.begin();
		for ( ; lit != lhs.end() && rit != rhs.end(); lit++, rit++)
		{
			if (*lit != *rit)
				return false;
		}
		if (lit != lhs.end() || rit != rhs.end())
			return false;
		return true;
	}

	template <class T>
	bool operator!= (const vector<T>& lhs, const vector<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T>
	bool operator< (const vector<T>& lhs, const vector<T>& rhs)
	{
		if (&lhs == &rhs)
			return false;
		typename ft::vector<T>::const_iterator lit = lhs.begin();
		typename ft::vector<T>::const_iterator rit = rhs.begin();
		for ( ; lit != lhs.end() && rit != rhs.end(); lit++, rit++)
		{
			if (*lit < *rit)
				return true;
			if (*lit > *rit)
				return false;
		}
		if (lit == lhs.end() && rit != rhs.end())
			return true;
		return false;
	}

	template <class T>
	bool operator> (const vector<T>& lhs, const vector<T>& rhs)
	{
		return rhs < lhs;
	}

	template <class T>
	bool operator<= (const vector<T>& lhs, const vector<T>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T>
	bool operator>= (const vector<T>& lhs, const vector<T>& rhs)
	{
		return !(lhs < rhs);
	}


	template <class T>
	void swap (vector<T>& x, vector<T>& y)
	{
		x.swap(y);
	}
}

#endif
