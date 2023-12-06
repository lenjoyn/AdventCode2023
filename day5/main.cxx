#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<chrono>
#include<cmath>
#include<unordered_map>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


void part1()
{
    std::ifstream myfile("test.txt");
    std::string myline;
    
    std::unordered_map<int, int> seeds;
    std::getline(myfile, myline);
    stringstream ss(myline);

    ss.ignore(myline.length(),':');
  
    int seed_num;
    std::cout<<ss.str()<<std::endl;
    while(ss>>seed_num)
    {
        seeds[seed_num] = seed_num;
        std::cout<<seed_num<<std::endl;
    }

    getline(myfile, myline);
    int dst, src, num;
    while(getline(myfile, myline))
    {
        if (myline == "" || myline[myline.size()-1] == ':')
            continue;

        stringstream sss(myline);
        sss>>dst>>src>>num;
        for (auto seed: seeds)
        {
            int diff = seed.second - src;
            if (diff < 0 || diff > num-1)
                continue;

            seed.second = dst + diff;
        }        
    }

    int lowest_location = UINT_MAX;
    for (auto seed:seeds)
    {
        if (seed.second<lowest_location)
            lowest_location = seed.second;
    }
    std::cout<<lowest_location<<std::endl;
}


int main()
{
    auto t1 = high_resolution_clock::now();
   
    part1();
    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;
}
