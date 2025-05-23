cmake_minimum_required(VERSION 3.13)

project(civicc VERSION 1.0 LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

set(TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/test")
set(COMPILER "${CMAKE_CURRENT_BINARY_DIR}/civicc")

# These will only work after you received the testing framework from us.
enable_testing()
add_test(NAME "basic" COMMAND "${TEST_COMMAND}/run.bash" "${COMPILER}" basic WORKING_DIRECTORY "${TEST_DIR}")
add_test(NAME "nested_funs" COMMAND "${TEST_COMMAND}/run.bash" "${COMPILER}" nested_funs WORKING_DIRECTORY "${TEST_DIR}")
add_test(NAME "arrays" COMMAND "${TEST_COMMAND}/run.bash" "${COMPILER}" arrays WORKING_DIRECTORY "${TEST_DIR}")


find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(CivicParser src/scanparse/parser.y "${CMAKE_CURRENT_BINARY_DIR}/parser.c"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/parser.h" VERBOSE)

flex_target(CivicLexer src/scanparse/lexer.l "${CMAKE_CURRENT_BINARY_DIR}/lexer.c"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/lexer.h")
ADD_FLEX_BISON_DEPENDENCY(CivicLexer CivicParser)


include(./coconut/coconut.cmake)

# Whenever you add a file, add it here too.
add_executable(civicc ${FLEX_CivicLexer_OUTPUTS} ${BISON_CivicParser_OUTPUTS}
    src/main.c src/print/print.c src/scanparse/scanParse.c
    src/global/globals.c src/global/globals.h
    # Context Analysis traversals
    src/traversals/contextanalysis/renameforidentifiers.c
    src/traversals/contextanalysis/createvariablesymboltableentries.c 
    src/traversals/contextanalysis/createfunctionsymboltableentries.c
    src/traversals/contextanalysis/linkfuncallstostefunnode.c

    # Convert variable initializations into regular assignments traversal
    src/traversals/regularassignments.c

    # TypeChecking traversals
    src/traversals/typechecking/typematchingassignmentsfuncalls.c

    # Annotates useless typecast expressions traversal
    src/traversals/annotateuselesscastexpressions.c

    # Compiling boolean disjunction and conjunction
    src/traversals/compilingbooleandisjunctionandconjunction.c
    
    # Convert boolean arguments/results cast expressions into non-cast expressions
    src/traversals/compilingbooleancastexpressions.c

    # Convert For nodes to While nodes with exactly the same semantics
    src/traversals/convertfortowhile.c

    # Assembly Code Generation
    src/traversals/assemblycodegeneration.c
)

target_compile_options(civicc PRIVATE
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Wno-unused-function>
)

coconut_target_generate(civicc "${CMAKE_CURRENT_LIST_DIR}/src/main.ccn" dynamic)
target_include_directories(civicc 
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src" 
)

add_custom_target(dot 
    dot -Tpng ccngen/ast.dot > ast.png
    COMMENT "Generate a png of your ast based on the generated dot diagram."
)
