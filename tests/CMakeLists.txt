# define a function to implement test
function(tehpc_add_test TEST_NAME)
  add_simulation(${TEST_NAME})
  add_test(${TEST_NAME} ${TEST_NAME})
endfunction()

  
tehpc_add_test(model_constructor_tests)
tehpc_add_test(model_assembly_tests)
tehpc_add_test(model_assembly_tests_multiple_el)
tehpc_add_test(full_run_test)
tehpc_add_test(matrix_operations_test)


configure_file(input_tests.inp input_tests.inp COPYONLY)
configure_file(input_2_el_tests.inp input_2_el_tests.inp COPYONLY)
configure_file(input_4_el_tests.inp input_4_el_tests.inp COPYONLY)
