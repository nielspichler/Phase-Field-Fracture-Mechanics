# define a function to implement test
function(PFFE_add_test TEST_NAME)
  add_simulation(${TEST_NAME})
  add_test(${TEST_NAME} ${TEST_NAME})
endfunction()

  
PFFE_add_test(model_constructor_tests)
PFFE_add_test(model_assembly_tests)
PFFE_add_test(model_assembly_tests_multiple_el)
PFFE_add_test(model_applyBC_tests)
PFFE_add_test(full_run_test)
PFFE_add_test(matrix_operations_test)
PFFE_add_test(Resisues_tests)
PFFE_add_test(solver_tests)

configure_file(input_tests.inp input_tests.inp COPYONLY)
configure_file(input_2_el_tests.inp input_2_el_tests.inp COPYONLY)
configure_file(input_4_el_tests.inp input_4_el_tests.inp COPYONLY)
