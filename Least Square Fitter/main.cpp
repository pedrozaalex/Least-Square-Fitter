// Least Square Fitter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include "inputOutput.h"


int main()
{
	std::fstream table{};

	do
	{
		std::string fileName{};
		std::cout << "What is the file name?" << std::endl;
		std::cin >> fileName;
		table.open(fileName, std::ios::in);

		// If table is already open, no need to further inquiry about filename
		if (table.is_open())
			break;

		std::cout << "Couldn't open file!" << std::endl;
		std::cout << "Want to try again? (y/n)" << std::endl;
	} while (yesNoReader());

	std::vector<double> xValues{}, yValues{};

	double num{ 0.0 };

	int numberMeasurements{ 0 };

	// This loop will both read the values in the file and store the number
	// of measurements collected
	while (table >> num)
	{
		xValues.push_back(num);

		table >> num;
		yValues.push_back(num);

		++numberMeasurements;
	}

	long double delta{}, aaa{}, bbb{}, sigmaA{}, sigmaY{};
	long double sigmaB{};

	double sumXSquared{}, sumX{}, sumXY{}, sumY{};

	// This loop will calculate all the summations at once for posterior use
	for (int nnn = 0; nnn < numberMeasurements; ++nnn)
	{
		sumXSquared += pow(xValues[nnn], 2);
		sumX += xValues[nnn];
		sumXY += xValues[nnn] * yValues[nnn];
		sumY += yValues[nnn];
	}
	

	// Now we calculate the values for the least squares fitting

	delta = numberMeasurements*sumXSquared;
	delta -= pow(sumX, 2);

	aaa = (((sumXSquared*sumY) - (sumX*sumXY)) / delta);

	//std::cout << "number of measurements = " << numberMeasurements << std::endl;
	bbb = (((numberMeasurements*sumXY) - (sumX*sumY)) / delta);

	// Now, to calculate the errors in the found coefficients

	double summation{};
	for (int nnn = 0; nnn < numberMeasurements; ++nnn)
	{
		double square{};
		square = (yValues[nnn] - aaa - (bbb*xValues[nnn]));
		square = pow(square, 2);
		summation += square;
	}

	sigmaY = (summation / (numberMeasurements - 2));
	sigmaY = sqrt(sigmaY);

	sigmaA = (sigmaY*sqrt(sumXSquared / delta));

	sigmaB = sqrt(numberMeasurements / delta);
	sigmaB *= sigmaY;

	// Printing the found values
	std::cout << "The results are:\n" << "\tA = " << aaa << "\n\tB = "
		<< bbb << "\n\tsigmaA = " << sigmaA << "\n\tsigmaB = " << sigmaB
		<< "\nsumXSquared = " << sumXSquared << "\nsumX = " << sumX
		<< "\nsumXY = " << sumXY << "\nsumY = " << sumY << "\ndelta = "
		<< delta << std::endl << "number of measurements = " << numberMeasurements 
		<< std::endl;

	system("pause");

	return 0;
}