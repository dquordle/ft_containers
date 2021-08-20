#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key> >
	class map
	{

	private:
		template <typename V>
		class MapIterator
		{

		};

		template <typename V>
		class ReverseMapIterator
		{

		};

	public:
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef pair<const Key, T>								value_type;
		typedef Compare											key_compare;
		typedef	std::allocator<value_type>						allocator_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef value_type*										pointer;
		typedef const value_type*								const_pointer;
		typedef	MapIterator<value_type>							iterator;
		typedef MapIterator<const value_type>					const_iterator;
		typedef	std::reverse_iterator<iterator>					reverse_iterator;
		typedef	std::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef ptrdiff_t										difference_type;
		typedef size_t											size_type;





	};
}

#endif
