# 添加自定义目标
add_custom_target(CBEUnitTests)
set_target_properties(CBEUnitTests PROPERTIES FOLDER "Tests")

# 查找并包含 Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if (NOT USE_SYSTEM_LLVM)
  set(LLVM_LINK_COMPONENTS
    Analysis
    CBackendCodeGen
    CBackendInfo
    CodeGen
    Core
    MC
    ScalarOpts
    Support
    Target
    TransformUtils
  )
endif()

# 添加单元测试目标
add_unittest(CBEUnitTests CWriterTest
  TypeNameTest.cpp
)

if(USE_SYSTEM_LLVM)
  llvm_map_components_to_libnames(llvm_libs
    CBackendCodeGen
    CBackendInfo
  )
  target_link_libraries(CWriterTest PRIVATE LLVM ${llvm_libs} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
else()
  target_link_libraries(CWriterTest PRIVATE LLVM ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
endif()

