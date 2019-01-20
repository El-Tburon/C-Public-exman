#pragma once

#include "pch.h"
#include <iostream>
#include <math.h>

using namespace std;

double objectiveFunction(double PMT, int n, double PV, double r) {

	double tmp;

	tmp = (PMT / PV) - r * (1 + (1 / (pow((1 + r), n) - 1)));

	return tmp;

}

double computeR() {

	double PMT, PV, r, rNext, tmp;
	int n;

	//Providiing values
	cout << "Please provide:" << endl;
	cout << "Loan Present Value:"; cin >> PV;
	if (PV <= 0) 
	{
		throw invalid_argument("Loan Present Value must be positive");
	}
	cout << "Instalment Value :"; cin >> PMT;
	if (PMT <= 0) 
	{
		throw invalid_argument("Instalmen Value must be positive");
	}
	cout << "Periods Per Year:"; cin >> n;
	if (n < 0)
	{
		throw invalid_argument("Number of periods should be non negative");
	}

	//We take for r a random realistic value, here 10%
	r = 0.1;
	rNext = 0.95 * r;

	while (abs(objectiveFunction(PMT, n, PV, rNext)) > 0.001) 
	{
		tmp = rNext;
		rNext = rNext - (objectiveFunction(PMT, n, PV, rNext) * (rNext - r)) / (objectiveFunction(PMT, n, PV, rNext) - objectiveFunction(PMT, n, PV, r));
		r = tmp;
	}

	cout << "Objective Function: " << objectiveFunction(PMT, n, PV, rNext) << endl;
	cout << "Periodic Rate: " << rNext * 100 << "% ." << endl;
}




double computePMT(int n, double PV, double r) {

	int result;
	result = 0;

	//Realistic constraints
	if (PV <= 0)
	{
		throw invalid_argument("Received a negative present value");
	}

	else if (n < 0)
	{
		throw invalid_argument("Received a negative number of period");
	}

	else if (r < 0)
	{
		throw invalid_argument("Received a negative interest rate");
	}

	else
	{
		//Applying closed formula 
		result = (r * PV) * (1 + (1 / (pow((1 + r), n) - 1)));
	}

	return result;
}

double computePV(double PMT, double r, int n) {

	double result;
	result = 0;

	//Realistic constraints
	if (PMT <= 0)
	{
		throw invalid_argument("Received a negative instalment value");
	}

	else if (n < 0)
	{
		throw invalid_argument("Received a negative number of period");
	}

	else if (r < 0)
	{
		throw invalid_argument("Received a negative interest rate");
	}

	else
	{
		//Applying closed formula 
		result = PMT / (r * (1 + (1 / (pow((1 + r), n) - 1))));
	}

	return result;
}

int computePeriods(double PMT, double r, double PV) 
{

	double result;
	result = 0;

	//Realistic constraints
	if (PMT <= 0)
	{
		throw invalid_argument("Received a negative instalment value");
	}

	else if (r < 0)
	{
	throw invalid_argument("Received a negative interest rate");
	}

	else if (PV <= 0)
	{
		throw invalid_argument("Received a negative present value");
	}

	else
	{
		//Applying closed formula 
		result = log(((r * PV) / (PMT - (r * PV))) + 1) / log(1 + r);

		result = round(result); //Round up to the integer
	}

	return result;
}