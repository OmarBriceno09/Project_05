cmake_minimum_required(VERSION 3.14)
project(Project_05)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_05 main.h main.cpp DatalogProgram.h DatalogProgram.cpp Parameter.h Parameter.cpp Predicate.h
        Predicate.cpp Rule.h Rule.cpp state_transitions.cpp tokenizer.cpp Relation.cpp Relation.h Tuple.cpp Tuple.h
        union_test.cpp join_test.cpp Node.h Node.cpp main_2.cpp Graph.cpp Graph.h)