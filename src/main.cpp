#include <iostream>
using std::cout;
using std::endl;
using std::string;
#include "database/saveShard.hpp"
int main() {
    string content = "T001|Abdo|Cairo University|5|Smart Traffic System|4.5|12|\nT002|ByteMasters|Ain Shams University|4|AI Healthcare Assistant|4.8|3|\nT003|CodeStorm|Alexandria University|6|Cloud-Based LMS|4.2|18|\n";;
    saveTeams(content);
    return 0;
}