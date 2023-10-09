#include "interface.h"

void encode(const vector<pair<string, string>>& codes)
{
	vector<string> encoded_symbols, decoded_symbols;
	ifstream decoded_sequence;
	ofstream encoded_sequence;
	decoded_sequence.open("to_encode.txt");

	while (!decoded_sequence.eof())
	{
		string s;
		decoded_sequence >> s;
		decoded_symbols.push_back(s);
	}

	decoded_sequence.close();

	for (string& s : decoded_symbols)
	{
		string code = (*find_if(codes.begin(), codes.end() - 1, [&s](const pair<string, string>& p) {return p.first == s;})).second;
		encoded_symbols.push_back(code);
	}

	encoded_sequence.open("encoded.txt");

	for (string& s : encoded_symbols)
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

void interface(const vector<pair<string, string>>& codes)
{
	int option;
	cout << "Выберите опцию: " << endl;
	cout << "1. Кодировать последовательность" << endl;
	cout << "2. Декодировать последовательность" << endl;
	cin >> option;
	option == 1 ? encode(codes) : decode(codes);
}