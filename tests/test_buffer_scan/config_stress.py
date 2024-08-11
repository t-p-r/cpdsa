problem_name = "$workspace"

if problem_name == "$workspace":
    main_correct_solution = "iostream.cpp"
    other_solutions = [
        "iostream.cpp",
        "buffer_scan.cpp",
        "stdio.c",
        "iostream_vanilla.cpp",
    ]
    checker = "token"
    external_checker = ""

testgen_script = "testgen 1000000 1000000000"
testlib_persistent = False
time_limit = 5
test_count = 32
failed_test_data = True
cpu_count = 4
compiler = "g++"
compiler_args = "-O2"
