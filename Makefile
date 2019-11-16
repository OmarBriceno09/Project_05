all:
	g++ main.cpp tokenizer.cpp state_transitions.cpp DatalogProgram.cpp Parameter.cpp Predicate.cpp Rule.cpp Relation.cpp Tuple.cpp -o lab4
project:
	g++ project_test.cpp Relation.cpp Tuple.cpp -o lab4_project
rename:
	g++ rename_test.cpp Relation.cpp Tuple.cpp -o lab4_rename
select:
	g++ select_test.cpp Relation.cpp Tuple.cpp -o lab4_select
union:
	g++ union_test.cpp Relation.cpp Tuple.cpp -o lab4_union