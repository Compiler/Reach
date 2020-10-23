#include "Random.h"

std::mt19937 reach::Random::_RANDOM_ENGINE;
std::uniform_int_distribution<std::mt19937::result_type> reach::Random::_DISTRIBUTION;
uint32_t reach::Random::nLehmer = 0;