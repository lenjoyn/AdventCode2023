#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<chrono>
#include<cmath>
#include<map>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


void part1()
{
    std::ifstream myfile("inputs.txt");
    std::string myline;
    
    vector<unsigned> seeds;
    vector<bool>     matched;
    std::getline(myfile, myline);
    stringstream ss(myline);

    ss.ignore(myline.length(),':');
  
    unsigned seed_num;
    while(ss>>seed_num)
    {
            seeds.push_back(seed_num);
            matched.push_back(false);
    }

    getline(myfile, myline);
    unsigned dst, src, num;
    while(getline(myfile, myline))
    {
        if (myline[myline.size()-1] == ':')
        {
            std::fill(matched.begin(), matched.end(), false);
        }

        if (myline == "" || myline[myline.size()-1] == ':')
            continue;

        stringstream sss(myline);
        sss>>dst>>src>>num;
        for (int i=0; i < seeds.size(); ++i)
        {
            unsigned diff = seeds[i] - src;
            if ((diff < 0 || diff > num-1) || matched[i] )
                continue;
            seeds[i] = dst + diff;
            matched[i] = true;
        }
    }

    unsigned lowest_location = UINT_MAX;
    for (auto seed:seeds)
    {
        if (seed > lowest_location)
            continue;
        lowest_location = seed;
    }
    std::cout<<lowest_location<<std::endl;
}

void part2()
{
    std::ifstream myfile("inputs.txt");
    std::string myline;

    std::map<unsigned, unsigned> ranges;
    std::map<unsigned, bool>     matched;
    std::getline(myfile, myline);
    stringstream ss(myline);

    ss.ignore(myline.length(),':');

    unsigned seed_num;
    unsigned range;
    while(ss>>seed_num>>range)
    {
        ranges[seed_num] = range;
        matched[seed_num] = false;
    }

    getline(myfile, myline);
    unsigned dst, src, num;
    while(getline(myfile, myline))
    {
        if (myline[myline.size()-1] == ':')
        {
            std::fill(matched.begin(), matched.end(), false);
        }

        if (myline == "" || myline[myline.size()-1] == ':')
            continue;

        stringstream sss(myline);
        sss>>dst>>src>>num;

        for (auto range: ranges)
        {
            if (matched[range.first] == true)
                continue;
            
            signed diff = range.first - src;
            if (abs(diff) > num )
                continue;
            
            if (diff < 0)
            {
                diff = abs(diff);
                if (range.first + range.second <= src + num)
                {
                    ranges[dst]         = range.second - abs(diff);
                    ranges[range.first] = diff;
                    matched[dst]        = true;
                }
                else
                {
                    ranges[range.first+diff+num] = range.second - diff - num;
                    ranges[dst]                  = num;
                    ranges[range.first]          = diff;
                }  
            }
            else if (diff >= 0)
            {
                int new_range = num - diff;
                ranges[ranges.first+new_range] = ranges[ranges.first] - new_range; 
                ranges[dst] = new_range;
                matched[dst] = true; 
            }
            
        }
    }

    unsigned lowest_location = UINT_MAX;
    for (auto seed:seeds)
    {
        if (seed > lowest_location)
            continue;
        lowest_location = seed;
    }
    std::cout<<lowest_location<<std::endl;

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
