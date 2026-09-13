#include <iostream>
#include <argparse/argparse.hpp>

const std::string PROGRAM_NAME = ProgramName;
const std::string PROGRAM_DESCRIPTION = ProgramDescription;
const std::string PROGRAM_VERSION = VERSION;

int main(int argc, char* argv[]) {
    argparse::ArgumentParser program(PROGRAM_NAME,PROGRAM_VERSION);
    program.add_description(PROGRAM_DESCRIPTION);

    program.parse_args(argc, argv);
    return 0;
}