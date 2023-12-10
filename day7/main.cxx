#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<chrono>
#include<cmath>
#include <cassert> 

#include<map>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;




void part1()
{
    std::unordered_map<char, int> converter;

    converter['2'] = 2;
    converter['3'] = 3;
    converter['4'] = 4;
    converter['5'] = 5;
    converter['6'] = 6;
    converter['7'] = 7;
    converter['8'] = 8;
    converter['9'] = 9;
    converter['T'] = 10;
    converter['J'] = 11;
    converter['Q'] = 12;
    converter['K'] = 13;
    converter['A'] = 14;

    std::ifstream myfile("input.txt");
    std::string myline;
    std::map<long int, int> money;
    std::map<long int, string> rank_record;
    std::map<long int, int> modes;
    int i = 0;
    while(getline(myfile, myline))
    {
        stringstream s(myline);
        string hand;
        int    bid;
        ++i;
        std::cout<<dec<<i<<std::endl;
        s>>hand>>bid;
        std::map<long int, int> card_num;
        for (char c: hand)
        {
            long int ch = static_cast<long int>(converter[c]);
            if (card_num.find(ch) == card_num.end())
                card_num[ch] = 1;
            else
                ++card_num[ch];
        }

        long int card_power = 0;
        int  mode = 0;
        long int one =   0;
        long int three = 0;
        long int two   = 0;

        for (auto it = card_num.rbegin(); it != card_num.rend(); ++it)
        {
            switch(it->second)
            {
                case 5:
                {
                    card_power |= (it->first << 40);
                    mode = 6;
                    break;
                }
                case 4:
                {
                    card_power |= (it->first << 36);
                    mode = 5;
                    break;
                }
                case 3:
                {
                    if (two != 0)
                    {
                        three = (it->first << 28);
                        mode = 4;
                    }
                    else
                    {
                        mode = 3;
                        three = (it->first << 24);
                    }
                    break;
                }

                case 2:
                {
                    if (three != 0)
                    {
                        three = three << 4;
                        mode = 4;
                    }
                    
                    mode = ( mode > 2 ) ? mode : (mode == 1) ? 2 : 1; 
                    two = (two << 4) | (it->first << 20);
                    std::cout<<"two:"<<two<<std::endl;
  
                    break;
                }

                case 1:
                {
                    one = ((one << 4) | it->first);
                    break;
                }
            }
        }
        card_power |= (one | two | three);
        //std::cout<<hex<<card_power<<" "<<one<<" "<<two<<" "<<three<<std::endl;
        modes.push_back(mode);
        money.emplace(card_power,bid);
        assert(money.find(card_power) != money.end());
        rank_record[card_power] = hand;
        std::cout<<hand<<" "<<std::hex<<card_power<<" "<<one<<" "<<two<<" "<<three<<" "<<dec<<money.size()<<std::endl;
    }

    int rank = 1;
    int total_money = 0;
    std::cout<<money.size()<<std::endl;
    for (auto win:money)
    {
        std::cout<<std::dec<<rank<<" "<<rank_record[win.first]<<" "<<win.second<<std::endl;
        total_money += win.second*rank;
        ++rank;
    }
    std::cout<<total_money<<std::endl;
}


int main()
{
    auto t1 = high_resolution_clock::now();
    part1();
    //part2();
    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;
}
