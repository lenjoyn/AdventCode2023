#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <chrono>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

    static unordered_map<string, int> cubes;




int main()
{
    auto t1 = high_resolution_clock::now();
    unordered_map<string, int> cubes;

    std::ifstream myfile("inputs.txt");
    std::string myline;

    int game_sum = 0;

    int power = 0;
    string catch_phrase;
    string colour;
    int cube_num;

    cubes["blue"] = 0;
    cubes["green"] =0;
    cubes["red"]  =0;
    while ( myfile )
    {
        std::getline(myfile, myline);
        if (myline == "endoffile")
            break;

        stringstream s(&myline[5]);
        
        int game_num;
        s>>game_num;
        s.ignore(300, ':');

        cubes["blue"] = 0;
        cubes["green"] =0;
        cubes["red"]  =0;

        bool pass = true;
        while(getline(s, catch_phrase, ';') && pass)
        {
            stringstream ss(catch_phrase);
            while(getline(ss, catch_phrase, ','))
            {
                stringstream sss(catch_phrase);
                sss>>cube_num>>colour;
                if (cube_num > cubes[colour])
                    cubes[colour] = cube_num;
            }         
        }
        power += cubes["green"]* cubes["red"]* cubes["blue"];
    }
    std::cout<<power<<std::endl;
    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;
}
