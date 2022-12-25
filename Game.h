#ifndef __GAME_H
#define __GAME_H

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

enum Colors {NONE, BLACK, YELLOW, GREEN};

class Keyboard {
  public:
    Keyboard() {
      keys =  { {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"},
                   {"A", "S", "D", "F", "G", "H", "J", "K", "L"},
                       {"Z", "X", "C", "V", "B", "N", "M"} };
      reset_colors();
    }

    void set_color(char c, Colors color) {
      char temp[2];
      temp[0] = toupper(c);
      temp[1] = '\0';
      for (unsigned int i = 0; i < keys.size(); i++) {
        for (unsigned int j = 0; j < keys[i].size(); j++) {
          if (!strcmp(temp, keys[i][j].data())) {
            if (colors[i][j] < color) { colors[i][j] = color; }
            return;
          }
        }
      }
    }

    void reset_colors() {
      colors.clear();
      colors.resize(3);
      colors[0].resize(10, NONE);
      colors[1].resize(9, NONE);
      colors[2].resize(7, NONE);
    }

    void print(std::ostream& ostr) const {
      for (unsigned int i = 0; i < keys.size(); i++) {
        if (i == 1) { ostr << " "; }
        if (i == 2) { ostr << "   "; }
        for (unsigned int j = 0; j < keys[i].size(); j++) {
          switch (colors[i][j]) {
            case GREEN:  ostr << "\033[42m" << keys[i][j]; break;
            case YELLOW: ostr << "\033[43m" << keys[i][j]; break;
            case BLACK:  ostr << " ";                      break;
            case NONE:   ostr << keys[i][j];               break;
            default:
              ostr << "AHHH BAD COLOR" << std::endl;
          }
          ostr << "\033[0m ";
        }
        ostr << std::endl;
      }
    }   

  private:
    std::vector<std::vector<std::string>> keys;
    std::vector<std::vector<Colors>> colors;
};

class Game {
  public:
    Game(const std::string& f_ans, const std::string& f_guess);

    void guess(const std::string& guess);

    bool valid_guess(const std::string& guess) const { return std::binary_search(valid_guesses.begin(), valid_guesses.end(), guess); }
    void print(std::ostream& ostr) const;
    bool get_state() const;
    std::string get_answer() const { return answer; }

  private:
    void set_answer(const std::string& f_name);
    void populate_guesses(const std::string& guess_list);
  
    std::string answer;
    std::map<char, int> ans_counts;
    std::vector<std::string> valid_guesses;
    std::vector<std::string> guesses;
    std::string display;
    Keyboard keyboard;

};

#endif