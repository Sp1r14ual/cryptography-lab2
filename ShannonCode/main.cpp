#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;


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

void encode(const vector<pair<string, string>>& codes)
{
	vector<string> encoded_symbols, decoded_symbols;
	ifstream decoded_sequence;
	ofstream encoded_sequence;
	decoded_sequence.open("to_encode.txt");

	while(!decoded_sequence.eof())
	{
		string s;
		decoded_sequence >> s;
		decoded_symbols.push_back(s);
	}

	decoded_sequence.close();

	for (string& s: decoded_symbols)
	{
		string code = (*find_if(codes.begin(), codes.end() - 1, [&s](const pair<string, string>& p) {return p.first == s;})).second;
		encoded_symbols.push_back(code);
	}

	encoded_sequence.open("encoded.txt");

	for (string& s: encoded_symbols)
		encoded_sequence << s << endl;

	encoded_sequence.close();
}

void decode(const vector<pair<string, string>>& codes)
{
	vector<string> encoded_symbols, decoded_symbols;
	ifstream encoded_sequence;
	ofstream decoded_sequence;

	encoded_sequence.open("to_decode.txt");

	while (!encoded_sequence.eof())
	{
		string s;
		encoded_sequence >> s;
		encoded_symbols.push_back(s);
	}

	encoded_sequence.close();

	for (string& s : encoded_symbols)
	{
		string symbol = (*find_if(codes.begin(), codes.end() - 1, [&s](const pair<string, string>& p) {return p.second == s; })).first;
		cout << symbol << " ";
		decoded_symbols.push_back(symbol);
	}

	decoded_sequence.open("decoded.txt");

	for (string& s : decoded_symbols)
		decoded_sequence << s << endl;

	decoded_sequence.close();

}


int main()
{
	const vector<string> alphabet = { "a", "b", "c", "d", "e", "f" };
	const vector<double> p = { 0.10, 0.20, 0.10, 0.10, 0.35, 0.15 };

	const vector<pair<string, string>> codes = shannon(alphabet, p);

	encode(codes);
	//decode(codes);

}