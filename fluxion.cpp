#include <iostream>
#include "fluxion.h"
#include "internals/debug.h"
#include "internals/Parser.h"
#include "internals/Compiler.h"
#include "internals/Expression.h"

std::string fluxion::interpret(const char *source) {
    Parser parser {source};
    ParsingStatus status = parser.parse();
    std::vector<Token*> tokens = parser.getTokens();
    if (status != PARSING_FAILED) {
        Compiler compiler {tokens};
        CompilationStatus cStatus = compiler.compile();
        if (cStatus != COMPILATION_FAILED) {
            Expression *expression = compiler.getRoot();
            return expression->evaluate()->getString();
        } else {
            std::cerr << "CompilationException: Compilation Failed.\n";
        }
    } else {
        std::cerr << "ParsingException: Parsing failed.\n";
    }
    return "";
}
