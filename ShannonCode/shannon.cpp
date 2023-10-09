#include "shannon.h"

string toBinary(double n)
{
	if (n == 0.0)
		return "00000000000";
	if (n >= 1 || n < 0)
		return "ERROR";

	string answer;
	answer.append("");

	while (n > 0)
	{
		double b = n * 2;
		if (b >= 1)
		{
			answer.append("1");
			n = b - 1;
		}
		else
		{
			answer.append("0");
			n = b;
		}
	}
	return answer;
}

bool sort_assembly(const pair<string, double>& a, const pair<string, double>& b)
{
	return a.second > b.second;
}

vector<pair<string, string>> shannon(const vector<string>& alphabet, const vector<double>& p)
{
	vector<pair<string, double>> assembly;
	vector<pair<string, double>> bx;
	vector<pair<string, string>> bins;
	vector<pair<string, int>> lx;
	vector<pair<string, string>> codes;

	for (int i = 0; i < alphabet.size(); i++)
		assembly.push_back(make_pair(alphabet[i], p[i]));

	sort(assembly.begin(), assembly.end(), sort_assembly);

	bx.push_back(make_pair(alphabet[0], 0.));

	for (int i = 1; i < assembly.size(); i++)
	{
		pair<string, double> pair_to_be_pushed = make_pair(assembly[i].first, bx[i - 1].second + assembly[i - 1].second);
		bx.push_back(pair_to_be_pushed);
	}

	for (int i = 0; i < bx.size(); i++)
	{
		string bin_repr = toBinary(bx[i].second);
		pair<string, string> pair_to_be_pushed = make_pair(bx[i].first, bin_repr);
		bins.push_back(pair_to_be_pushed);
	}

	for (int i = 0; i < assembly.size(); i++)
	{
		int l_x = (int)ceil(-log2(assembly[i].second));
		pair<string, int> pair_to_be_pushed = make_pair(assembly[i].first, l_x);
		lx.push_back(pair_to_be_pushed);
	}

	for (int i = 0; i < assembly.size(); i++)
	{
		string code = bins[i].second.substr(0, lx[i].second);
		pair<string, string> pair_to_be_pushed = make_pair(assembly[i].first, code);
		codes.push_back(pair_to_be_pushed);
	}

	return codes;
}