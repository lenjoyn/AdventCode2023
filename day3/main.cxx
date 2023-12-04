#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<chrono>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

struct dim
{
    dim(int x, int y, int z): line(x), start(y), end(z){}
    int line;
    int start;
    int end;
};

bool isSymbol(char c)
{
        return (!isdigit(c) && c!='.' && c!='\0') ? true : false;
}

int main()
{
    auto t1 = high_resolution_clock::now();

    std::ifstream myfile("inputs.txt");
    std::string myline;
    std::vector<string> lines;
    
    vector<dim> dims;
    vector<int> nums;
    int num;
    while (myfile)
    {
        std::getline(myfile, myline);
        lines.push_back(myline);
        num = 0;
        int begin = -1;
        for (int i = 0; i< myline.length(); ++i)
        {
            char c = myline[i];
           
            if (isdigit(c))
            {
                num = num*10 + int(c&0xf);
                if (begin == -1)
                    begin = i;

                if (i == myline.length()-1)
                {
                    nums.push_back(num);
                    dims.push_back(dim(lines.size()-1, begin, i));
                }
            }
            else if (begin != -1)
            {
                nums.push_back(num);
                dims.push_back(dim(lines.size()-1, begin, i-1));
                begin = -1;
                num = 0;
            }
        }
    }

    int sum = 0;
    for (int i =0; i < dims.size(); ++i)
    {
        bool a_part = false;
        int z = dims[i].line;
        int x = dims[i].start == 0 ? 0: dims[i].start - 1;
        int y = dims[i].end == 139 ? 139 : dims[i].end + 1;
       
        for (int j = z-1 ; j <= z+1 ; ++j)
        {
            if (j < 0)
                continue;
            if (j == lines.size() - 1)
                break;

            for (int k = x; k <= y ; ++k)
            {
                
                if (!isSymbol(lines[j][k]))
                    continue;

                
                a_part = true;
            }
        }
        if (a_part)
        {
            sum += nums[i];    
        }
    }
    std::cout<<sum<<std::endl;
    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;
}
