#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<chrono>
#include<cmath>

#include<climits>

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

void part2()
{
    std::ifstream myfile("test.txt");
    std::string myline;

    std::map<unsigned, unsigned> ranges;
    std::map<unsigned, bool>     matched;

    std::getline(myfile, myline);
    stringstream ss(myline);

    ss.ignore(myline.length(),':');

    unsigned seed_begin;
    unsigned seed_range;
    while(ss>>seed_begin>>seed_range)
    {
        ranges[seed_begin] = seed_range;
    }

    getline(myfile, myline);
    unsigned dst, src, num;
    while(getline(myfile, myline))
    {
        if (myline[myline.size()-1] == ':')
        {
            for (auto& entry:matched)
                 entry.second = false;
        }

        if (myline == "" || myline[myline.size()-1] == ':')
            continue;

        std::cout<<myline<<std::endl;
        stringstream sss(myline);
        sss>>dst>>src>>num;

        vector<unsigned> erase_entries;
        for (auto it = ranges.begin(); it != ranges.end(); ++it)
        {
            auto range = *it;
            std::cout<<"==="<<range.first<<" "<<range.second<<"==="<<std::endl;
            if (matched[range.first] == true)
                continue;

            signed diff = range.first - src;
            unsigned abs_diff = abs(diff);
            if (abs_diff > num  && abs_diff > range.second)
                continue;

            if (diff < 0)
            {
                diff = abs(diff);
                if (range.first + range.second <= src + num)
                {
                    std::cout<<"case 1:"<<dst<<" "<<(range.second-diff)<<std::endl;
                    std::cout<<"case 1:"<<range.first<<" "<<diff<<std::endl;
                    ranges[dst]         = range.second - diff;
                    matched[dst]        = true;
                }
                else
                {
                    std::cout<<"case 2:"<<(range.first+diff+num)<<" "<<(range.second - diff - num)<<std::endl;
                    std::cout<<"case 2:"<<dst<<" "<<num<<std::endl;
                    std::cout<<"case 2:"<<dst<<" "<<diff<<std::endl;
                    ranges[range.first+diff+num] = range.second - diff - num;
                    matched[range.first+diff+num]    = false;

                    ranges[dst] = num;
                    matched[dst]    = true;
                }
                ranges[range.first] = diff;
            }
            else if (diff >= 0)
            {

                if (range.first + range.second <= src + num)
                {
                    std::cout<<"case 3:"<<(dst+diff)<<" "<<range.second<<std::endl;
                    ranges[dst+diff] = range.second;
                }
                else
                {
                    int new_range = num - diff;
                    std::cout<<"case 4:"<<range.first+new_range<<" "<<range.second - new_range<<std::endl;
                    std::cout<<"case 4:"<<dst+diff<<" "<<new_range<<std::endl;
                    ranges[range.first+new_range] = range.second - new_range;
                    ranges[dst+diff] = new_range;
                }
                erase_entries.push_back(range.first);
                ++it;
                matched[dst+diff] = true;
                if (it == ranges.end())
                break;
            }
            std::cout<<"size: "<<ranges.size()<<std::endl;
        }
        for (auto entry:erase_entries)
        {
            ranges.erase(entry);
            matched.erase(entry);
        }
    }

    unsigned lowest_location = UINT_MAX;
    std::cout<<" ==== "<<std::endl;
    for (auto range:ranges)
    {
        std::cout<<range.first<<" "<<range.second<<std::endl;
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
