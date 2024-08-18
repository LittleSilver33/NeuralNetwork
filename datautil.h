
#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include <random>

// Chooses a random stock from the train folder, then chooses 101 random adjacent days and returns the closing price of each day
std::vector<double> GetData();
