SET(
    SRC
    src/HTypeck.cxx
    include/typeck/HTypeck.hxx
    include/typeck/HSymbolTable.hxx
    include/typeck/HSymbol.hxx
    include/typeck/symbols/HClassSymbol.hxx
    include/typeck/symbols/HEnumSymbol.hxx
    include/typeck/symbols/HFunctionSymbol.hxx
    include/typeck/symbols/HProtocolSymbol.hxx
    include/typeck/symbols/HPrototypeSymbol.hxx
    include/typeck/symbols/HStructSymbol.hxx
    include/typeck/symbols/HVariableSymbol.hxx
)

add_library(Typeck STATIC ${SRC})

target_include_directories(Typeck PUBLIC include)
target_include_directories(Typeck PUBLIC ${CMAKE_SOURCE_DIR}/parser/include)