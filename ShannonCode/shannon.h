#pragma once
#include "lib.h"

string toBinary(double n);

bool sort_assembly(const pair<string, double>& a, const pair<string, double>& b);

vector<pair<string, string>> shannon(const vector<string>& alphabet, const vector<double>& p);