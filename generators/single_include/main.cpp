
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std::string_literals;

std::vector<std::string> standard_headers = {
    "tuple",
    "type_traits",
    "functional",
    "iostream" };
std::vector<std::string> att_headers = {
    "tools.hpp",
    "arity_functions.inl",
    "core.hpp",
    "loops.hpp",
    "comparisons.hpp",
    "hash.hpp",
    "serialization.hpp" };

std::string clean_file(std::string const& file) {
    std::ifstream tools{ INCLUDES_DIRECTORY + file };
    std::stringstream text;
    text << tools.rdbuf();

    std::string line;
    bool reachedNamespace = false;
    while (!reachedNamespace) {
        std::getline(text, line);
        if (line.empty()) continue;
        if (line.front() == 'n') reachedNamespace = true;
    }

    std::string content;
    content.reserve(text.str().size());
    content += "/// Auto-merge of " + file + '\n';
    do {
        content += line;
        content += '\n';
    } while (std::getline(text, line));
    return content;
}

int main() {
    try {
        std::ofstream header{ TARGET_DIRECTORY + "aggregates_to_tuples.hpp"s };
        
        header << "\n/// ----- Aggregates to Tuples -----";
        header << "\n///";
        header << "\n/// Auto-generated header which glues :";
        for (auto& h : att_headers) header << "\n///   - " << h;
        header << "\n";
        header << "\n#pragma once";
        header << "\n";
        for (auto& h : standard_headers) header << "\n#include <" << h << '>';
        header << "\n";
        header << "\n";
        for (auto& h : att_headers) header << clean_file(h);
    }
    catch(std::exception& e) {
        std::cout << "Error : " << e.what();
        return 1;
    }
    std::cout << "The file '" << TARGET_DIRECTORY << "aggregates_to_tuples.hpp' has been generated.\n";
}
