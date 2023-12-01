#include<iostream>
#include<fstream>
#include<string>
#include <ctype.h>

unsigned convertCharToInt(char c)
{
    return 0xF & c;
}

int main(int argc, char* argv[])
{
    std::ifstream myfile("inputs.txt");
    std::string myline;
    int count = 0 ;
    while ( myfile ) 
    {
        ++ count;
        std::getline (myfile, myline);
        
        size_t length = myline.size() - 1;
        int first = 0;
        int last  = 0;
        for ( int i = 0; i <= length; ++i)
        {
            if (first == 0 && std::isdigit(myline[i]))
            {
                std::cout<<myline[i]<<std::endl;
                first = convertCharToInt(myline[i]);
                first = first == 0 ? -1 : first;
                std::cout<<first<<std::endl;
            }

            if (last == 0 && std::isdigit(myline[length]))
            {
                std::cout<<myline[length]<<std::endl;
                last = convertCharToInt(myline[length]);
                last = last == 0 ? -1 : last;
            }

            --length;
        }
        
        std::cout<<myline<<" " <<first<< " " << last <<std::endl;

        if (count == 10)
        break;
    }
   
    return 0;
}
