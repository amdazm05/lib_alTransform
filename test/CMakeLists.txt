cmake_minimum_required(VERSION 3.0)

project(test)

IF(GPU_ACCELERATION)
    message("GPU Benchmarks")
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/benchmark_gpu.cc)
    target_link_libraries(${PROJECT_NAME} PUBLIC  alTran benchmark::benchmark)
ELSE(GPU_ACCELERATION)
    message("CPU Benchmarks")
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/benchmark_cpu.cc)
    target_link_libraries(${PROJECT_NAME} PUBLIC  alTran benchmark::benchmark)
ENDIF(GPU_ACCELERATION)