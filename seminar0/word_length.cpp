#include <iostream>
#include <istream>
#include <string>
#include <fstream>
using namespace std;
string get_file_to_str(string file_name){
    // put file in str variable
    ifstream ifs;
    string str;
    ifs.open(file_name, ifstream::in);
    if (ifs.is_open()){
        while (!ifs.eof()){
            string temp_str;
            ifs >> temp_str;
            str = str + " " + temp_str;
        }

    }
    return str;
}

int get_word_count(string str){
    int word_count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' '){
            word_count++;
        }
    }
    return word_count;
}


int main(){

    string file_name = "/home/fella149/cpp/tddd38/words.txt";
    string str = get_file_to_str(file_name);
    int word_count = get_word_count(str);

    int letter_count = 0;
    int word_len = 0;
    string longest_w = "";
    string shortest_w = "";

    for (int i = 0; i < (int) str.length(); i++){

        if (str[i] == ' '){  // end of current word
            letter_count += word_len;
            string word = str.substr(i-word_len, word_len);
            if (shortest_w == "" && longest_w == ""){
                shortest_w = word;
                longest_w = word;
            }
            else if (word_len > (int) longest_w.length()){  // found new longest word
                longest_w = word;
            } else if (word_len < (int) shortest_w.length()) {  // found new shortest word
                shortest_w = word;
            }
            word_len = 0;
        } else {  //continue with current word
            word_len++;
        }
    }


    cout << "There are " << word_count << " words in the file." << endl;
    cout << "The shortest word was '" << shortest_w << "' with "
         << shortest_w.length() << " character(s)." << endl;
    cout << "The longest word was '" << longest_w << "' with "
         << longest_w.length() << " character(s)." << endl;
    cout << "The average length was " << letter_count/word_count << " character(s)." << endl;
    return 0;
}
