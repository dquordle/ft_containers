#ifndef PAIR_HPP
#define PAIR_HPP


namespace ft
{
	template <typename T1, typename T2>
	struct pair
	{
	public:
		typedef T1	first_type;
		typedef T2	second_type;

		first_type first;
		second_type second;

		pair() : first(first_type()), second(second_type()) {}

		template<class U, class V>
		pair(const pair<U,V>& pr)
		{
			first = first_type(pr.first);
			second = second_type(pr.second);
		}

		pair(const first_type& a, const second_type& b)
		{
			first = first_type(a);
			second = second_type(b);
		}

		pair& operator= (const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		if (lhs.first < rhs.first)
			return true;
		if (lhs.first == rhs.first && lhs.second < rhs.second)
			return true;
		return false;
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}
}
#endif
