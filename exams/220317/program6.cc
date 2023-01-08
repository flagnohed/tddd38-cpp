#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

/* Example output for ./a.out < lorem_ipsum.txt (might differ slightly
 * since there might be multiple different choices for the three most
 * common words:

== Replaced text: 
lorem REPLACED dolor sit amet consectetur adipiscing elit donec 
efficitur massa eget auctor convallis aenean nibh eros efficitur 
eget velit pharetra fringilla imperdiet dolor aliquam nisl justo 
scelerisque ac ex REPLACED consectetur efficitur REPLACED REPLACED placerat 
leo at tincidunt pretium risus magna ornare ante a ornare nunc elit 
vel eros donec porttitor turpis lectus sit amet dignissim REPLACED 
molestie ac cras semper sodales REPLACED ut gravida nisl pellentesque 
REPLACED vestibulum lobortis enim quis velit gravida vel faucibus magna 
ornare aliquam erat volutpat REPLACED at semper enim finibus 
consequat sem REPLACED pharetra felis REPLACED diam vestibulum 
hendrerit fusce porta urna lacus id molestie leo posuere 
quis suspendisse potenti 

*/

int main()
{
    std::vector<std::vector<std::string>> lines { };
    std::vector<std::vector<int>> word_count { };
    std::map<std::string, int> m{};
    // Your code goes here
    std::string replaced_str = "REPLACED";
    std::string line{};
    while (std::getline(std::cin, line)) {
        std::istringstream iss{line};

        std::vector<std::string> line_vector{};
        for (std::string word; std::getline(iss, word, ' ');) {
            m[word]++;
            line_vector.push_back(word);
        }
        lines.push_back(line_vector);
    }
    


    // cannot get partial_sort_copy to work
    std::vector<std::pair<std::string, int>> common(3);
    
    std::partial_sort_copy(m.begin(), m.end(), 
        common.begin(), common.end(), 
            [](auto&& l, auto&& r) { return l.second > r.second; });
    
    // check that common is alright
    for (auto&& p : common) {
        std::cout << p.first << " " << p.second << std::endl;
    }




    for (std::vector<std::string> line : lines) {
        for (std::string word : line) {
            for (auto&& p : common) {
                if (word == p.first) {
                    std::replace(line.begin(), line.end(), word, replaced_str);
                }
            }   
        }
        for (auto it{line.begin()}; it != line.end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << '\n';
    }
}