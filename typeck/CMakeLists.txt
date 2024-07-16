SET(
    SRC
    src/HTypeck.cxx
    src/HSymbolTable.cxx
    include/typeck/HPrimitiveTypes.hxx
    include/typeck/HTypeck.hxx
    include/typeck/HSymbolTable.hxx
    include/typeck/HSymbol.hxx
    include/typeck/HSymbolType.hxx
    include/typeck/HType.hxx
    include/typeck/symbols/HContractSymbol.hxx
    include/typeck/symbols/HEnumSymbol.hxx
    include/typeck/symbols/HFunctionSymbol.hxx
    include/typeck/symbols/HPropertySymbol.hxx
    include/typeck/symbols/HStructSymbol.hxx
    include/typeck/symbols/HVariableSymbol.hxx
    include/typeck/symbols/HWithAccessLevelSymbol.hxx
)

add_library(Typeck STATIC ${SRC})

target_include_directories(Typeck PUBLIC include)
target_include_directories(Typeck PUBLIC ${CMAKE_SOURCE_DIR}/parser/include)
target_include_directories(Typeck PUBLIC ${CMAKE_SOURCE_DIR}/ast/include)
target_include_directories(Typeck PUBLIC ${CMAKE_SOURCE_DIR}/core/include)

target_link_libraries(Typeck PUBLIC Parser AST Core)