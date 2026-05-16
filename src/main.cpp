#include <iostream>
#include <string>

#include "parser.h"

class TUI {
public:
    void run()
    {
        while (true) {
            std::string input;
            std::cout << "> ";
            std::getline(std::cin, input);
            if (input.empty()) {
                continue;
            }

            try {
                ast::NodePtr ast = ast::parser::parse(input);
                std::string  outputFile;

                std::cout << "Filename of .dot: ";
                std::getline(std::cin, outputFile);
                dumpToGraphviz(outputFile, ast);
            } catch (const std::exception& e) {
                std::cerr << e.what();
            }
        }
    }
};

auto main(int argc, char const* argv[]) -> int
{
    TUI tui;
    tui.run();
}
