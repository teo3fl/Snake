#pragma once

#ifdef _DEBUG
#define resourcesPath std::string("../External/Resources/")
#else
#define resourcesPath std::string("./Resources/")
#endif

// std
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <utility>
#include <random>
#include <sstream>
#include <cstdint>
#include <iostream>
#include <filesystem>

// SFML
#include <SFML/Graphics.hpp>