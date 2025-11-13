cmake_minimum_required(VERSION 3.10)

# Projekto pavadinimas 
project(_3_strategija VERSION 1.0 LANGUAGES CXX)

# Naudojamas C++17 standartas
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Optimizuota versija
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Įtraukiame antraščių failų aplanką
include_directories(${PROJECT_SOURCE_DIR})

# Pagrindinės programos failai
set(SOURCES_MAIN
    "3 strategija.cpp"
    studentas.cpp
    failai.cpp
)

# Testavimo programos failai
set(SOURCES_TEST
    studentas.cpp
    failai.cpp
    testavimas.cpp
)

# Sukuriame vykdomuosius failus
add_executable("3_strategija" ${SOURCES_MAIN})
add_executable("testavimas" ${SOURCES_TEST})
