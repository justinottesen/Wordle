#ifndef __GAME_H
#define __GAME_H

#include <cstdlib>
#include <ctime>
#include <cassert>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

class Game {
  public:
    Game(const std::string& f_ans, const std::string& f_guess);

    void guess(const std::string& guess);

    bool valid_guess(const std::string& guess) const { return std::binary_search(valid_guesses.begin(), valid_guesses.end(), guess); }
    void print(std::ostream& ostr) const { for (std::string guess : guesses) { ostr << guess << std::endl; } }
    bool get_state() const;
    std::string get_answer() const { return answer; }

  private:
    void set_answer(const std::string& f_name);
    void populate_guesses(const std::string& guess_list);
  
    std::string answer;
    std::map<char, int> ans_counts;
    std::vector<std::string> valid_guesses;
    std::vector<std::string> guesses;
};

#endif