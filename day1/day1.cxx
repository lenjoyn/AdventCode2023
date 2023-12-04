#include<iostream>
#include<fstream>
#include<string>
#include <ctype.h>
#include <unordered_map>
#include <memory>
#include <chrono>


class trie
{
    class Node
    {
    public:
        Node() = default;
        ~Node() = default;

        int value{-1};
        std::unordered_map<char, Node> next;

        int getNext(std::string c, int order)
        {
            if (value != -1)
                return value;

            ++order;
            if ( next.find(c[order]) == next.end() )
                return value;
 
            return next[c[order]].getNext(c, order);
        }

        void put(std::string s, int value_, int order)
        {
            if (s.length() == order + 1)
            {
                value = value_;
                return;
            }
            ++order;
            if (next.find(s[order]) == next.end())
                next[s[order]] = Node();

            next[s[order]].put(s, value_, order);        
        }
    };

public:
    trie()
    {
    }
    ~trie() = default;

    void put(std::string s, int value_)
    {
        ordered_root.put(s, value_, -1);
        std::reverse(s.begin(),s.end());     
        reverse_root.put(s, value_, -1);
    }

    int find_ordered(std::string s)
    {
        return ordered_root.getNext(s, -1);
    }

    int find_reverse(std::string s)
    {
        return reverse_root.getNext(s, -1);
    }
private:
    Node ordered_root;
    Node reverse_root;
};

int main(int argc, char* argv[])
{

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    trie trie;

    trie.put("one",1);
    trie.put("two",2);
    trie.put("three",3);
    trie.put("four",4);
    trie.put("five",5);
    trie.put("six",6);
    trie.put("seven",7);
    trie.put("eight",8);
    trie.put("nine",9);
    trie.put("1",1);
    trie.put("2",2);
    trie.put("3",3);
    trie.put("4",4);
    trie.put("5",5);
    trie.put("6",6);
    trie.put("7",7);
    trie.put("8",8);
    trie.put("9",9);

    std::ifstream myfile("inputs.txt");
    std::string myline;
    int count = 0;

    while ( myfile ) 
    {
        std::getline (myfile, myline);
        if (myline == "endoffile")
            break;

        std::string myline_reverse = myline;
        std::reverse(myline_reverse.begin(), myline_reverse.end());
        int first = -1;
        int last  = -1;
        int front_id = 0;
        int last_id = 0;

        while (true)
        {
            if (first == -1)
            {
                int num = trie.find_ordered(&myline[front_id]);
                if (num != -1)
                    first = num;
                else
                    front_id += 1;
            }

            if (last == -1)
            {
                int num = trie.find_reverse(&myline_reverse[last_id]);
                if (num != -1)
                    last = num;
                else
                    last_id += 1;
            }
            
            if (first != -1 && last != -1)
                break;
        }
        count += first*10 + last;
    }
    std::cout<<count<<std::endl;
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;

}
