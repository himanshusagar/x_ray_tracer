//
// Created by xerious on 5/10/17.
//

#ifndef ASSIGNMENT4_RANDOMGEN_H
#define ASSIGNMENT4_RANDOMGEN_H


#include <iostream>
#include <random>


class RandomGen
{
    std::uniform_real_distribution<float> distribution;
    std::mt19937 mt19937;

public:
    RandomGen()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
       std::uniform_real_distribution<float> dist(0.0, 1.0);
        distribution = dist;
        mt19937 = mt;
    }


     float getNumber()
    {
        return distribution(mt19937);
    }
};

#endif //ASSIGNMENT4_RANDOMGEN_H
