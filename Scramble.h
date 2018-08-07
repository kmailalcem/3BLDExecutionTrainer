#pragma once
#include <random>
#include <string>
#include <vector>
#include <cstdlib>

#include <cassert>

class UnknownOccupancyException { };
class UnknownDirectionException { };

std::string get_scramble();
