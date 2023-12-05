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
    std::ifstream myfile("inputs.txt");
    std::string myline;
    bool nums[100] = {0};
    int read_num;
    char dummy;
    int winning_points = 0;
    int winning_time;
    

    while (std::getline(myfile, myline))
    {
        stringstream ss(&myline[9]);
        winning_time = 0;
        memset(nums, 0, sizeof(nums));

        while(ss >> read_num || !ss.eof())
        {
            if (ss.fail())
            {
                ss.clear();
                ss>>dummy;
                break;
            }
            nums[read_num] = 1;
        }

        while(ss >> read_num || !ss.eof())
        {
            if (nums[read_num])
            {   
                ++winning_time;            
            }
        }
        if (winning_time != 0)
            winning_points += (0x1 << (winning_time-1));

        
    }
    std::cout<<winning_points<<std::endl;
}

void part2()
{
    std::ifstream myfile("test.txt");
    std::string myline;
    bool nums[100] = {0};
    int read_num;
    char dummy;
    int card_num[999] = {1};
    int card_no;

    while (std::getline(myfile, myline))
    {
        stringstream ss(&myline[3]);
        
        std::getline(ss, nums, ":");
        card_no = stoi(nums);

        int cards_i_have = card_num[card_no];
        std::cout<<card_no<<" "<<cards_i_have<<std::endl;
        memset(nums, 0, sizeof(nums));
        while(ss >> read_num || !ss.eof())
        {
            if (ss.fail())
            {
                ss.clear();
                ss>>dummy;
                break;
            }
            nums[read_num] = 1;
        }

        while(ss >> read_num || !ss.eof())
        {
            if (nums[read_num])
            {
                ++card_no;
                card_num[card_no] += cards_i_have;
            }
        }
    } 
}

int main()
{
    auto t1 = high_resolution_clock::now();
   
 //   part1();
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
