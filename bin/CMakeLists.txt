add_executable(tise tise.cpp)

# if TISEExactDiagonalize is not used, one can safely comment
# -llapack -lgfortran and -lblas
# target_link_libraries(tise cntdse1d stdc++fs -llapack -lgfortran -lblas)
target_link_libraries(tise cntdse1d stdc++fs -L/home/tianmin/Downloads/tRecX-master/LIBRARIES/LAPACK/lib/ -llapack -lgfortran -lblas)


add_executable(tdse tdse.cpp)
target_link_libraries(tdse cntdse1d stdc++fs)
