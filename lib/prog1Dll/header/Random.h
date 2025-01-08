#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <random>
#include <iostream>
#include <string>   
#include <conio.h>
using namespace std;

typedef unsigned int u_int;

namespace Tools
{
    static int RandomInt(const int _min, const int _max)
    {
        random_device _rSeed;
        mt19937 _gen(_rSeed());
        uniform_int_distribution<> distr(_min, _max);

        return distr(_gen);
    }

    /// <summary>
     /// Renvoie une valeur random selon un type
     /// </summary>
     /// <typeparam name="Type"> Disponible avec les double, floats et longs double</typeparam>
     /// <param name="_min">Minimum</param>
     /// <param name="_max">Maximum</param>
     /// <returns>Valeur random</returns>
    template<typename Type>
    Type RandomValue(const Type& _min, const Type& _max)
    {
        random_device _rSeed;
        mt19937 _gen(_rSeed());
        uniform_real_distribution<Type> distr(_min, _max);

        return distr(_gen);
    }

    template<typename Type>
    Type GetRandomObjectInArray(Type* _array, const u_int& _arraySize)
    {
        int _randomIndex = RandomInt(0, _arraySize - 1);
        return _array[_randomIndex];
    }

    template<template<typename, typename> typename Collection, typename Type, typename Alloc = allocator<Type>()>
    Type GetRandomObjectInCollection(Collection<Type, Alloc> _collection)
    {
        int _randomIndex = RandomInt(0, _collection.size() - 1);
		typedef typename Collection<Type, Alloc>::iterator Iterator;
		Iterator _it = _collection.begin();

        for (int _i = 0; _i < _randomIndex; _i++)
        {
            _it++;
        }

        return *_it;
    }
}