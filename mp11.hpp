/*

Copyright (c) 2025 Elias Aebi

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef MP11_HPP
#define MP11_HPP

#include <cstddef>

namespace mp11 {

template <class T>
class Type {
public:
	constexpr Type() {}
	using type = T;
};

template <class T, T V>
class Value {
public:
	constexpr Value() {}
	static constexpr T value = V;
	constexpr operator T() const noexcept {
		return V;
	}
	constexpr T operator ()() const noexcept {
		return V;
	}
};

template <std::size_t I>
using Index = Value<std::size_t, I>;
template <int I>
using Int = Value<int, I>;
template <bool B>
using Bool = Value<bool, B>;
using False = Bool<false>;
using True = Bool<true>;

// operators for Type
template <class T, class U>
constexpr auto operator ==(Type<T>, Type<U>)
-> False {
	return {};
}
template <class T>
constexpr auto operator ==(Type<T>, Type<T>)
-> True {
	return {};
}

// arithmetic operators for Value
template <class T, class U, T x, U y>
constexpr auto operator +(Value<T, x>, Value<U, y>)
-> Value<decltype(x + y), (x + y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator -(Value<T, x>, Value<U, y>)
-> Value<decltype(x - y), (x - y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator *(Value<T, x>, Value<U, y>)
-> Value<decltype(x * y), (x * y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator /(Value<T, x>, Value<U, y>)
-> Value<decltype(x / y), (x / y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator %(Value<T, x>, Value<U, y>)
-> Value<decltype(x % y), (x % y)> {
	return {};
}

// relational operators for Value
template <class T, class U, T x, U y>
constexpr auto operator ==(Value<T, x>, Value<U, y>)
-> Value<decltype(x == y), (x == y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator !=(Value<T, x>, Value<U, y>)
-> Value<decltype(x != y), (x != y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator <(Value<T, x>, Value<U, y>)
-> Value<decltype(x < y), (x < y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator >(Value<T, x>, Value<U, y>)
-> Value<decltype(x > y), (x > y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator <=(Value<T, x>, Value<U, y>)
-> Value<decltype(x <= y), (x <= y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator >=(Value<T, x>, Value<U, y>)
-> Value<decltype(x >= y), (x >= y)> {
	return {};
}

// logical operators for Value
template <class T, class U, T x, U y>
constexpr auto operator &&(Value<T, x>, Value<U, y>)
-> Value<decltype(x && y), (x && y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator ||(Value<T, x>, Value<U, y>)
-> Value<decltype(x || y), (x || y)> {
	return {};
}
template <class T, T x>
constexpr auto operator !(Value<T, x>)
-> Value<decltype(!x), (!x)> {
	return {};
}

// bitwise operators for Value
template <class T, class U, T x, U y>
constexpr auto operator &(Value<T, x>, Value<U, y>)
-> Value<decltype(x & y), (x & y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator |(Value<T, x>, Value<U, y>)
-> Value<decltype(x | y), (x | y)> {
	return {};
}
template <class T, class U, T x, U y>
constexpr auto operator ^(Value<T, x>, Value<U, y>)
-> Value<decltype(x ^ y), (x ^ y)> {
	return {};
}
template <class T, T x>
constexpr auto operator ~(Value<T, x>)
-> Value<decltype(~x), (~x)> {
	return {};
}

// decrement and increment
template <class T, T x>
constexpr auto dec(Value<T, x>)
-> Value<T, (x - 1)> {
	return {};
}
template <class T, T x>
constexpr auto inc(Value<T, x>)
-> Value<T, (x + 1)> {
	return {};
}

template <class... T>
class Types;

template <class, std::size_t I>
struct TypesAt;
template <class T0, class... T>
struct TypesAt<Types<T0, T...>, 0> {
	using type = T0;
};
template <class T0, class... T, std::size_t I>
struct TypesAt<Types<T0, T...>, I> {
	using type = typename TypesAt<Types<T...>, I - 1>::type;
};

template <class, class U>
struct TypesFind;
template <class T0, class... T>
struct TypesFind<Types<T0, T...>, T0> {
	static constexpr std::size_t index = 0;
};
template <class T0, class... T, class U>
struct TypesFind<Types<T0, T...>, U> {
	static constexpr std::size_t index = 1 + TypesFind<Types<T...>, U>::index;
};

template <class... T>
class Types {
public:
	constexpr Types() {}
	constexpr auto size() const
	-> Index<sizeof...(T)> {
		return {};
	}
	template <std::size_t I>
	constexpr auto operator [](Index<I>) const
	-> Type<typename TypesAt<Types, I>::type> {
		return {};
	}
	template <std::size_t I>
	constexpr auto at(Index<I>) const
	-> Type<typename TypesAt<Types, I>::type> {
		return {};
	}
	template <class U>
	constexpr auto find(Type<U>) const
	-> Index<TypesFind<Types, U>::index> {
		return {};
	}
};

template <class T, T... V> class Values {
public:
	using types = Types<Value<T, V>...>;
	constexpr Values() {}
	constexpr auto size() const
	-> Index<sizeof...(V)> {
		return {};
	}
	template <std::size_t I>
	constexpr auto operator [](Index<I>) const
	-> typename TypesAt<types, I>::type {
		return {};
	}
	template <std::size_t I>
	constexpr auto at(Index<I>) const
	-> typename TypesAt<types, I>::type {
		return {};
	}
};

template <std::size_t... I>
using Indices = Values<std::size_t, I...>;
template <int... I>
using Ints = Values<int, I...>;

// operators for Types
template <class... T, class... U>
constexpr auto operator ==(Types<T...>, Types<U...>)
-> False {
	return {};
}
template <class... T>
constexpr auto operator ==(Types<T...>, Types<T...>)
-> True {
	return {};
}
template <class... T, class... U>
constexpr auto operator +(Types<T...>, Types<U...>)
-> Types<T..., U...> {
	return {};
}

// operators for Values
template <class T, class U, T... x, U... y>
constexpr auto operator ==(Values<T, x...>, Values<U, y...>)
-> False {
	return {};
}
template <class T, T... x>
constexpr auto operator ==(Values<T, x...>, Values<T, x...>)
-> True {
	return {};
}
template <class T, T... x, T... y>
constexpr auto operator +(Values<T, x...>, Values<T, y...>)
-> Values<T, x..., y...> {
	return {};
}

}

#endif
