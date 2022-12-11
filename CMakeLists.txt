cmake_minimum_required(VERSION 3.24)
project(Lab2_3sem_final)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Lab2_3sem_final
        ../model/array/DynamicArray.h
        ../model/array/ArraySequence.h
        ../model/array/Sequence.h
        ../model/tests/Tests.cpp
        ../model/tests/Tests.h
        ../presenter/Presenter.cpp
        ../presenter/Presenter.h
        ../view/chart/Chartcontrol.cpp
        ../view/chart/Chartcontrol.h
        ../view/App.cpp
        ../view/App.h
        ../view/MainFrame.cpp
        ../view/MainFrame.h
        main.cpp
        #model/HashTable.h
        model/IMap.h
        #presenter/Presenter1.h
        #presenter/Presenter1.cpp
        model/HashTable1.h
        model/BinaryTree1.h model/Person.h)

find_package(wxWidgets REQUIRED core base)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Lab2_3sem_final PROPERTY CXX_STANDARD 20)
endif()

if (wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(Lab2_3sem_final ${wxWidgets_LIBRARIES})
endif()
