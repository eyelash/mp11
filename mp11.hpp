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

// arithmetic operators for Value
template <class T, class U, T t, U u>
constexpr auto operator +(Value<T, t>, Value<U, u>)
-> Value<decltype(t + u), (t + u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator -(Value<T, t>, Value<U, u>)
-> Value<decltype(t - u), (t - u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator *(Value<T, t>, Value<U, u>)
-> Value<decltype(t * u), (t * u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator /(Value<T, t>, Value<U, u>)
-> Value<decltype(t / u), (t / u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator %(Value<T, t>, Value<U, u>)
-> Value<decltype(t % u), (t % u)> {
	return {};
}

// relational operators for Value
template <class T, class U, T t, U u>
constexpr auto operator ==(Value<T, t>, Value<U, u>)
-> Value<decltype(t == u), (t == u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator !=(Value<T, t>, Value<U, u>)
-> Value<decltype(t != u), (t != u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator <(Value<T, t>, Value<U, u>)
-> Value<decltype(t < u), (t < u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator >(Value<T, t>, Value<U, u>)
-> Value<decltype(t > u), (t > u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator <=(Value<T, t>, Value<U, u>)
-> Value<decltype(t <= u), (t <= u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator >=(Value<T, t>, Value<U, u>)
-> Value<decltype(t >= u), (t >= u)> {
	return {};
}

// logical operators for Value
template <class T, class U, T t, U u>
constexpr auto operator &&(Value<T, t>, Value<U, u>)
-> Value<decltype(t && u), (t && u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator ||(Value<T, t>, Value<U, u>)
-> Value<decltype(t || u), (t || u)> {
	return {};
}
template <class T, T t>
constexpr auto operator !(Value<T, t>)
-> Value<decltype(!t), (!t)> {
	return {};
}

// bitwise operators for Value
template <class T, class U, T t, U u>
constexpr auto operator &(Value<T, t>, Value<U, u>)
-> Value<decltype(t & u), (t & u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator |(Value<T, t>, Value<U, u>)
-> Value<decltype(t | u), (t | u)> {
	return {};
}
template <class T, class U, T t, U u>
constexpr auto operator ^(Value<T, t>, Value<U, u>)
-> Value<decltype(t ^ u), (t ^ u)> {
	return {};
}
template <class T, T t>
constexpr auto operator ~(Value<T, t>)
-> Value<decltype(~t), (~t)> {
	return {};
}

// decrement and increment
template <class T, T t>
constexpr auto dec(Value<T, t>)
-> Value<T, (t - 1)> {
	return {};
}
template <class T, T t>
constexpr auto inc(Value<T, t>)
-> Value<T, (t + 1)> {
	return {};
}

template <std::size_t I>
using Index = Value<std::size_t, I>;
template <int I>
using Int = Value<int, I>;
template <bool B>
using Bool = Value<bool, B>;
using False = Bool<false>;
using True = Bool<true>;

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
	constexpr std::size_t size() const {
		return sizeof...(T);
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

template <class... T, class... U>
constexpr auto operator +(Types<T...>, Types<U...>)
-> Types<T..., U...> {
	return {};
}

template <class T, T... V> class Values {
public:
	using types = Types<Value<T, V>...>;
	constexpr Values() {}
	constexpr std::size_t size() const {
		return sizeof...(V);
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

template <class T, T... x, T... y>
constexpr auto operator +(Values<T, x...>, Values<T, y...>)
-> Values<T, x..., y...> {
	return {};
}

template <std::size_t... I>
using Indices = Values<std::size_t, I...>;
template <int... I>
using Ints = Values<int, I...>;

}

#endif
