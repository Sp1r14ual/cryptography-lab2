#include "interface.h"

int main()
{
	setlocale(LC_ALL, "ru");

	const vector<string> alphabet = { "a", "b", "c", "d", "e", "f" };
	const vector<double> p = { 0.10, 0.20, 0.10, 0.10, 0.35, 0.15 };

	const vector<pair<string, string>> codes = shannon(alphabet, p);

	interface(codes);
}