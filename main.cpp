#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <array>


std::string getFileName()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
    return oss.str().append(".csv");

    return "";
}


int main()
{
    std::cout << "Test the jitter of a control loop" << std::endl;

    const int numIter = 1000;
    std::array<double, numIter> tVec {0.0};

    for (int i = 0; i < numIter; ++i)
    {

    }

    // Save the recorded time stamps to a csv file
    std::ofstream outputFile(getFileName());

    for (const auto& i : tVec)
        outputFile << i << std::endl;
    
    outputFile.close();
    
    return 0;
}