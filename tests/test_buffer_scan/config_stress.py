"""
config_stress.py - Configuration for stress.py.
"""

problem_name = "$workspace"

if problem_name == "$workspace":
    main_correct_solution = "iostream.cpp"
    other_solutions = ["stdio.c", "buffer_scan.cpp"]

    checker_type = "token"
    external_checker = "checker.cpp"

testgen_script = "testgen --n 1e6"
time_limit = 2
test_count = 32
failed_test_data = True
cpu_workers = 4
compilation_command = "g++ -D_TPR_ -O2 -pipe -std=c++20"
