import random
import os
import shutil

upper_bound_of_edge_weight = 100
number_of_test = 20
tests_dimension = [(15,35), (20, 40), (25, 50), (30, 60)]
test_directory_name = "graphs"

if os.path.isdir(test_directory_name):
    shutil.rmtree(test_directory_name, ignore_errors=False, onerror=None)
os.mkdir(test_directory_name)

for test in tests_dimension:
    current_test_directory = "%s/(%d,%d)" % (test_directory_name, test[0], test[1])
    os.mkdir(current_test_directory)
    for count_of_test in range(0, number_of_test):
        successfull_generated = []
        while len(successfull_generated) < test[1]:
            new_edge = (random.randint(0, test[0]), random.randint(0, test[0]))
            if new_edge[0] != new_edge[1]:
                unique = True
                for edge in successfull_generated:
                    if edge[0] == new_edge[0] and edge[1] == new_edge[1] or edge[0] == new_edge[1] and edge[1] == new_edge[0]:
                        unique = False
                        break
                if unique:
                    successfull_generated.append(new_edge)
        test_file = open(current_test_directory + "/%d.txt" % (count_of_test), "w")
        test_file.write("%d %d \n" % (test[0], test[1]))
        for edge in successfull_generated:
            test_file.write("%d %d %d \n" % (edge[0], edge[1], random.randint(1, upper_bound_of_edge_weight)))
        test_file.close()

print("Done")
