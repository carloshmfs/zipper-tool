#include "CommandLineParser.h"

#include <iostream>

int main(int argc, char* argv[])
{
    CommandLineParser parser(argc, argv);

    parser.setApplicationName("zipper");
    parser.setApplicationDescription("A CLI that archives and compresses a source directory into a output directory.");

    parser.addPositionalArgument("source", "Source directory.", "[source]");
    parser.addPositionalArgument("output", "Output directory.", "[output]");

    parser.parse();

    if (! parser.isSet("source") || ! parser.isSet("output")) {
        return parser.showHelp(1);
    }

    std::string sourceDir = parser.getValue("source");
    std::string outputDir = parser.getValue("output");
    
    std::cout << sourceDir << std::endl;
    std::cout << outputDir << std::endl;

    // Zipper zipper;
    // zipper.archiveName("test.zip");
    // zipper.saveAt(outputDir);
    // zipper.addDirectory(sourceDir);
    // zipper.make();

    return 0;
}
