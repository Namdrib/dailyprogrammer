#include <bits/stdc++.h>
#include <unistd.h>
#include "../helpers.cpp"
using namespace std;

// https://www.reddit.com/r/dailyprogrammer/comments/8xzwl6/20180711_challenge_365_intermediate_sales/

int main(int argc, char** argv)
{
	double COMmission = 0.062; // amount of commission. 1 is 100%, 0 is 0%

	// ignore heading
	string dummy;
	cin >> dummy;
	getline(cin, dummy);
	cin.ignore();

	// read names
	string names_string;
	vector<string> names;
	getline(cin, names_string);
	stringstream ss1(names_string);
	for (string temp; ss1 >> temp; )
	{
		names.push_back(temp);
	}

	// cerr << "names: " << names << endl;

	// revenue[i][j] is the revenue for the jth person in the ith product
	vector<vector<double>> revenues;
	vector<string> product_names;

	// read the products and the corresponding prices
	string line;
	getline(cin, line);
	do
	{
		// read the product name
		stringstream ss2(line);
		string product_name;
		ss2 >> product_name;
		product_names.push_back(product_name);

		// read the revenue figures
		vector<double> product_revenue(names.size());
		for (size_t i=0; i<names.size(); i++)
		{
			ss2 >> product_revenue[i];
		}
		revenues.push_back(product_revenue);

		getline(cin, line);
	} while (line != "");

	// cerr << "product_names: " << product_names << endl;
	// cerr << "revenues: " << revenues << endl;

	// Skip the next few lines
	getline(cin, dummy);
	getline(cin, dummy);
	getline(cin, dummy);

	// read the expenses
	// subtract the expense figures from the revenue
	for (int prod_id=0; getline(cin, line); prod_id++)
	{
		stringstream ss3(line);
		string product_name;
		ss3 >> product_name;

		for (size_t person_id=0; person_id<names.size(); person_id++)
		{
			double temp;
			ss3 >> temp;
			revenues[prod_id][person_id] -= temp;
		}
	}
	// cerr << "profits: " << revenues << endl;

	// calculate commission
	vector<double> commission(names.size(), 0);

	for (auto v : revenues)
	{
		for (size_t i=0; i<v.size(); i++)
		{
			if (v[i] > 0)
			{
				commission[i] += v[i];
			}
		}
	}
	transform(commission.begin(), commission.end(), commission.begin(), [COMmission](double d){return d * COMmission;});

	// perform output
	cerr << endl;
	string commission_str = "Commission";

	// output names
	cout << string(commission_str.size() + 5, ' ');
	for (auto name : names)
	{
		cout << name << setfill(' ') << setw(10);
	}
	cout << endl;

	// output commission
	cout << commission_str << setfill(' ') << setw(commission.size());
	cout << fixed << setprecision(2);
	for (size_t i=0; i<names.size(); i++)
	{
		cout << "" << commission[i] << setfill(' ') << setw(5);
	}
	cout << endl;
}
