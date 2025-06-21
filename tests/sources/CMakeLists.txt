file(GLOB operatorFunctors_test_sources
     "*.cpp"
)

target_sources(operatorFunctors_test PRIVATE
    ${operatorFunctors_test_sources}
)
