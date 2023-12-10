#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<chrono>
#include<cmath>
#include <iomanip>
#include<climits>

#include<map>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

inline bool isInt(double f)
{
    int i = f;

    return i == f;
}
void part1()
{
    std::ifstream myfile("inputs.txt");
    std::string myline;

    vector<double> distances;
    vector<double> times;
    string dummy;


    std::getline(myfile, myline);
    std::cout<<myline<<std::endl;
    stringstream sss(myline);
    sss>>dummy;
    int time;
    while(sss>>time)
    {
        times.push_back(time);
    }

    std::getline(myfile, myline);
    std::cout<<myline<<std::endl;
    stringstream ss(myline);

    ss>>dummy;
    int distance;
    while(ss>>distance)
    {
        distances.push_back(distance);
    }


    int res = 1;
    for (int i = 0; i<times.size(); ++i)
    {
        double det = sqrt(times[i]*times[i] - 4*distances[i]);
        double begin = (times[i]-det)/2.0;
        double end   = (times[i]+det)/2.0;

        int begin_limit = isInt(begin) ? begin + 1: begin;
        std::cout<<begin<<" "<<end<<std::endl;
        res *= (end-begin_limit);
    }

    std::cout<<res<<std::endl;
}

void part2()
{
    float time     = 41667266;
    float distance = 244104712281040;


    double det = sqrt(time*time - 4*distance);
    std::cout<< std::setprecision(15)<<det<<std::endl;
    double begin = (time - det)/2;
    double   end = (time+det)/2.;

    int begin_limit = isInt(begin) ? begin + 1: begin;
    std::cout<< std::setprecision(15)<<begin<<" "<<end<<std::endl;
    std::cout<<end-begin_limit<<std::endl;
}

int main()
{
    auto t1 = high_resolution_clock::now();
    //part1();
    part2();
    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;
}
