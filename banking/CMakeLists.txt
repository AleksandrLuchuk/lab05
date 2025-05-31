add_library(banking STATIC
    Account.cpp
    Transaction.cpp
)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(TARGET gmock_main)
    target_link_libraries(banking PUBLIC gmock_main)
endif()
