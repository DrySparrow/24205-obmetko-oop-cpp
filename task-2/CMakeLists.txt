cmake_minimum_required(VERSION 3.14)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Список исходных файлов для основной программы
set(MAIN_SOURCES
    src/main.cpp
    src/game.cpp
    src/Universe.cpp
    src/GameOfLifeEngine.cpp
    src/CommandQualifier.cpp
    src/Commands.cpp
)

# Список исходных файлов для тестов
set(TEST_SOURCES
    tests/test_universe.cpp
    tests/test_rule.cpp
    src/Universe.cpp
)

# Основное приложение
add_executable(gameoflife ${MAIN_SOURCES})

# Для лучшей поддержки Unicode в Windows
if(WIN32)
    target_compile_definitions(gameoflife PRIVATE _UNICODE UNICODE)
endif()

# Устанавлием стандарт C++23 для основного приложения
target_compile_features(gameoflife PRIVATE cxx_std_23)

# Включаем директории
target_include_directories(gameoflife PRIVATE include)

# ============================================
# НАСТРОЙКА GTEST ДЛЯ ТЕСТОВ
# ============================================

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Путь к установленному gtest (адаптируйте под свой путь)
    set(GTEST_PATH "C:/Users/Sergey/vcpkg/installed/x64-mingw-static")
    set(GTEST_INCLUDE_DIR "${GTEST_PATH}/include")
    
    # Проверяем существование директорий
    if(NOT EXISTS ${GTEST_PATH})
        message(WARNING "Google Test not found at ${GTEST_PATH}. Tests will not be built.")
    else()
        # Создаем таргет для тестов
        add_executable(run_all_tests ${TEST_SOURCES})
        
        # Настройки компиляции
        target_include_directories(run_all_tests PRIVATE 
            ${GTEST_INCLUDE_DIR}
            include
        )
        
        # Устанавлием стандарт C++23 для тестов
        target_compile_features(run_all_tests PRIVATE cxx_std_23)
        
        # Линковка библиотек
        target_link_libraries(run_all_tests 
            ${GTEST_PATH}/lib/libgtest_main.a
            ${GTEST_PATH}/lib/libgtest.a
            pthread
        )
        
        # Дополнительные библиотеки для Windows
        if(WIN32)
            target_link_libraries(run_all_tests ws2_32)
        endif()
        
        # Добавляем цель для запуска тестов
        add_custom_target(test
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_all_tests
            DEPENDS run_all_tests
            COMMENT "Running tests..."
        )
    endif()
endif()

# ============================================
# НАСТРОЙКА ИСХОДНОЙ СТРУКТУРЫ
# ============================================

# Создаем директории, если их нет
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/src)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tests)

# Копируем заголовочные файлы в бинарную директорию
# (если нужно для out-of-source build)
configure_file(include/game.h ${CMAKE_CURRENT_BINARY_DIR}/include/game.h COPYONLY)
configure_file(include/Universe.h ${CMAKE_CURRENT_BINARY_DIR}/include/universe.h COPYONLY)

# ============================================
# ВЫВОД ИНФОРМАЦИИ
# ============================================

message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build tests: ${BUILD_TESTS}")
if(BUILD_TESTS AND EXISTS ${GTEST_PATH})
    message(STATUS "Google Test found at: ${GTEST_PATH}")
endif()