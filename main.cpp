#include "CommandLineParser.h"
#include "Zipper.h"
#include "utils.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    CommandLineParser parser(argc, argv);

    parser.setApplicationName("zipper");
    parser.setApplicationDescription("A CLI that archives and compresses a source directory into a output directory.");

    parser.addPositionalArgument("SOURCE", "The directory that will archived.", "[SOURCE]");
    parser.addPositionalArgument("OUTPUT", "The target directory that the archive will be saved.", "[OUTPUT]");

    parser.parse();

    if (! parser.isSet("SOURCE") || ! parser.isSet("SOURCE")) {
        return parser.showHelp(1);
    }

    std::string sourceDir = parser.getValue("SOURCE");
    std::string outputDir = parser.getValue("OUTPUT");
    
    Zipper zipper;
    zipper.archiveNameFromDirectory(sourceDir);
    zipper.saveAt(outputDir);
    zipper.addDirectory(sourceDir);

    try {
        zipper.make();
    } catch (const std::runtime_error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
