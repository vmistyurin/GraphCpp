import random
import os
import shutil

lower_bound_of_edge_weight = 100
upper_bound_of_edge_weight = 1000
number_of_tests = 10
tests_dimension = [(12, 14)]
test_directory_name = "random_graphs"

if os.path.isdir(test_directory_name):
    shutil.rmtree(test_directory_name, ignore_errors=False, onerror=None)
os.mkdir(test_directory_name)

for test in tests_dimension:
    current_test_directory = "%s/(%d,%d)" % (test_directory_name, test[0], test[1])
    os.mkdir(current_test_directory)
    for count_of_test in range(0, number_of_tests):
        successfull_generated = []
        while len(successfull_generated) < test[1]:
            new_edge = (random.randint(0, test[0] - 1), random.randint(0, test[0] - 1))
            if new_edge[0] != new_edge[1]:
                unique = True
                for edge in successfull_generated:
                    if edge[0] == new_edge[0] and edge[1] == new_edge[1] or edge[0] == new_edge[1] and edge[1] == new_edge[0]:
                        unique = False
                        break
                if unique:
                    successfull_generated.append(new_edge)
        test_file = open(current_test_directory + "/%d.txt" %
                         (count_of_test), "w")
        test_file.write("%d %d \n" % (test[0], test[1]))
        for edge in successfull_generated:
            test_file.write("%d %d %d %f \n" % (edge[0], edge[1], random.randint(
                lower_bound_of_edge_weight, upper_bound_of_edge_weight), random.random()))
        test_file.close()

print("Done")
