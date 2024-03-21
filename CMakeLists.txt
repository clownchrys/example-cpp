cmake_minimum_required(VERSION 3.23)
project(example_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        example_cpp
        main.cpp
        utils/func.cpp
        utils/func.h
        part/dtypes/dtypes.cpp
        part/dtypes/dtypes.h
        part/ops/ops.h
        part/ops/trinary_op.cpp
        part/ops/arithmetic_op.cpp
        part/ops/logical_op.cpp
        part/ops/bit_op.cpp
        part/statements/statements.h
        part/statements/condition.cpp
        part/statements/loop.cpp
        part/collections/collections.h
        part/collections/array.cpp
        part/collections/struct.cpp
        part/var/var.cpp
        part/var/var.h
        part/interface/interface.cpp
        part/interface/interface.h
        part/pointer/pointer.cpp
        part/pointer/pointer.h
        part/collections/string.cpp
        part/collections/vector.cpp
        part/dynamic_alloc/dynamic_alloc.cpp
        part/dynamic_alloc/dynamic_alloc.h
        part/collections/linked_list.cpp
        part/cls/cls.cpp
        part/cls/cls.h
        part/collections/vector.h
        part/collections/linked_list.h
        part/collections/tree.cpp
        part/collections/tree.h
        part/cls/inherit.cpp
        part/exception/exception.cpp
        part/exception/exception.h
        part/cast/cast.cpp
        part/cast/cast.h
        part/threading/threading.cpp
        part/threading/threading.h
        part/threading/consumer_producer.cpp part/pointer/smart_ptr.cpp part/pointer/smart_ptr.h)

#file(GLOB APP_SOURCES */*.h)
#
#foreach(file ${APP_SOURCES})
#    get_filename_component(name ${file} NAME_WLE)
#    get_filename_component(dir ${file} DIRECTORY)
#    add_executable(${name} main.cpp ${dir}/${name}.cpp ${dir}/${name}.h)
#endforeach(file ${APP_SOURCES})
