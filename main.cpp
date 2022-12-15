#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <array>
#include <vector>
#include <chrono>
#include <thread>


std::string getFileName();
void saveData(std::vector<int>);
void deterministicLoop1(const size_t, const int);


std::string getFileName()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
    return oss.str().append(".csv");

    return "";
}

void saveData(std::vector<int> tVec)
{
    // Save the recorded time stamps to a csv file
    std::ofstream outputFile(getFileName());

    for (const auto& t : tVec)
        outputFile << t << std::endl;
    
    outputFile.close();
}


void deterministicLoop1(const size_t numIter, const int timeStep)
{
    typedef std::chrono::high_resolution_clock Clock;
    std::vector<int> tVec(numIter, 0);

    // Starting time of the loop
    auto t = Clock::now();
    auto tStart = t;
    auto tPrev = t;

    // Time step size for the deterministic loop
    std::chrono::duration<int, std::nano> tStep(timeStep);
    
    for (auto& ti : tVec)
    {
        ti = std::chrono::duration_cast<std::chrono::nanoseconds>(t-tStart).count();
        while (t - tPrev < tStep)
        {
            t = Clock::now();
        }
        tPrev = t;
    }

    // Save the experimen data
    saveData(tVec);
}

void deterministicLoop2(const size_t numIter, const int timeStep)
{
    typedef std::chrono::high_resolution_clock Clock;
    std::vector<int> tVec(numIter, 0);

    // Starting time of the loop
    auto t = Clock::now();
    auto tStart = t;
    auto tPrev = t;
    auto tNext = t;

    // Time step size for the deterministic loop
    std::chrono::duration<int, std::nano> tStep(timeStep);

    for (auto& ti : tVec)
    {
        t = Clock::now();

        ti = std::chrono::duration_cast<std::chrono::nanoseconds>(t-tStart).count();
        
        tNext += tStep;
        std::this_thread::sleep_until(tNext);
    }

    // Save the experimen data
    saveData(tVec);
}

int main()
{
    // Number of iterations for the deterministic loop
    const size_t numIter = 100000;

    // Time step for the loop in nanoseconds
    const int timeStep = 1000000;

    std::cout << "Test the jitter of a control loop" << std::endl;

    std::cout << "> Method 1: Using while-loop to block deterministic loop" << std::endl;
    deterministicLoop1(numIter, timeStep);

    std::cout << "> Method 2: Using std::thread to block deterministic loop" << std::endl;
    deterministicLoop2(numIter, timeStep);
 
    return 0;
}