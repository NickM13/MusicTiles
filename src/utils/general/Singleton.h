#pragma once

template <typename T>
class Singleton
{
	public:
		inline static T& getInstance()
		{
			static T t_pointer;
			return t_pointer;
		}

	protected:
		Singleton(){};
		Singleton(const T&){};
		Singleton& operator=(const T&){};
		virtual ~Singleton(){};
};
