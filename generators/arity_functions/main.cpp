
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std::string_literals;

void write_function(std::ostream& header, int arity) {

    std::string tag = "value_tag<int, " + std::to_string(arity) + ">";

    header << "\n        template <class Aggregate>";
    header << "\n        auto as_tuple(Aggregate& aggregate, " << tag << ") {";
    if (arity == 0) {
        header << "\n            return std::make_tuple();";
    }
    else {
        header << "\n            auto& [v1";
        for (int i = 2; i <= arity; ++i) header << ", v" << i;
        header << "] = aggregate;";
        header << "\n            return std::forward_as_tuple(v1";
        for (int i = 2; i <= arity; ++i) header << ", v" << i;
        header << ");";
    }
    header << "\n        }";

    header << "\n        template <class Aggregate>";
    header << "\n        auto to_tuple(Aggregate&& aggregate, " << tag << ") {";
    if (arity == 0) {
        header << "\n            return std::make_tuple();";
    }
    else {
        header << "\n            constexpr auto tag = type_tag<Aggregate>{};";
        header << "\n            auto&& [v1";
        for (int i = 2; i <= arity; ++i) header << ", v" << i;
        header << "] = aggregate;";
        header << "\n            return std::make_tuple(fwd(v1, tag)";
        for (int i = 2; i <= arity; ++i) header << ", fwd(v" << i << ", tag)";
        header << ");";
    }
    header << "\n        }";
    header << "\n";
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage : make_arity_functions <max_arity>\n";
        return 0;
    }
    try {
        int max_arity = std::stoi(argv[1]);
        if (max_arity < 1) {
            std::cout << "The max_arity given must be superior to zero.\n";
            return 1;
        }

        std::ofstream header{ TARGET_DIRECTORY + "arity_functions.inl"s };
        
        header << "\n/// ----- Arity functions -----";
        header << "\n///";
        header << "\n/// max_arity = " << max_arity << '.';
        header << "\n/// Auto-generated file which writes functions which convert aggregates to tuples.";
        header << "\n";
        header << "\nnamespace att {";
        header << "\n";
        header << "\n    /// Defines the max arity (the number of member variables) that an aggregate can have.";
        header << "\n    constexpr int max_arity = " << max_arity << ';';
        header << "\n";
        header << "\n    namespace detail {";
        header << "\n";
        header << "\n        /// Forward the reference depending on the 'Aggregate' type.";
        header << "\n";
        header << "\n        template <class Aggregate, class T>";
        header << "\n        auto fwd(T&& val, type_tag<Aggregate>) {";
        header << "\n            if constexpr (std::is_reference_v<Aggregate>) {";
        header << "\n                return val;";
        header << "\n            }";
        header << "\n            else {";
        header << "\n                return std::move(val);";
        header << "\n            }";
        header << "\n        }";
        header << "\n";
        header << "\n        /// as_tuple and to_tuple implementation for each arity supported.";
        header << "\n";
        for (int arity = 0; arity <= max_arity; ++arity) {
            write_function(header, arity);
        }
        header << "\n    }";
        header << "\n}";
        header << "\n";
    }
    catch (std::exception& e) {
        std::cout << "Error : " << e.what() << '\n';
        return 1;
    }
    std::cout << "The file '" << TARGET_DIRECTORY << "arity_functions.inl' has been generated.";
}
