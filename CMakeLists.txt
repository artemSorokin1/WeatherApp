cmake_minimum_required(VERSION 3.26)
project(Pet_project_1)

set(CMAKE_CXX_STANDARD 20)

set(COMPILE_FILES
        HttpSender.hpp
        Server.hpp
        Client.hpp
        ZMQ_API.hpp
        HttpParse.hpp
        DataBaseCreator.hpp
)

set(GUI_FILES
        GUI/RegisterWindow.hpp
        GUI/Enter.hpp
        GUI/MainWindow.hpp
)

find_package(Boost REQUIRED)
find_package(cppzmq CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(libpqxx REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

add_executable(Pet_project_1 main.cpp ${COMPILE_FILES})
add_executable(server Server.cpp ${COMPILE_FILES})
add_executable(client Client.cpp ${COMPILE_FILES})
add_executable(GUI GUI/App.cpp ${GUI_FILES})

target_link_libraries(Pet_project_1 PRIVATE Boost::boost cppzmq cppzmq-static nlohmann_json::nlohmann_json)
target_link_libraries(server PRIVATE cppzmq cppzmq-static nlohmann_json::nlohmann_json pqxx)
target_link_libraries(client PRIVATE cppzmq cppzmq-static nlohmann_json::nlohmann_json)
target_link_libraries(GUI PRIVATE ${wxWidgets_LIBRARIES} cppzmq cppzmq-static nlohmann_json::nlohmann_json pqxx)

