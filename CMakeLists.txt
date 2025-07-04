cmake_minimum_required(VERSION 3.12)

# 设置工程属性，如版本，开发语言等
project(minic VERSION 1.0.1 LANGUAGES CXX)

# 是否输出Bison语法分析时是否输出自动机， 默认输出
# 如果修改为OFF，请删除cmake_build_debug后重新build
# set(BISON_OUTPUT_GRAPH OFF CACHE BOOL "Enable/Disable output of a graph of the automaton for Bison")

# 是否使用GravphViz库
set(USE_GRAPHVIZ ON CACHE BOOL "Enable/Disable GraphViz")

# 默认设置为ON，这里可注释掉。开启时会产生compile_commands.json的文件，有了这个文件才能识别出clang-tidy的配置
# Generates a `compile_commands.json` that can be used for autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Enable/Disable output of compile commands during generation.")

# 这个目前没有用处，可删除
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 禁止MSVC编译时出现C4819警告
if(MSVC)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# graphviz查找文件
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

# 查找线程库，避免terminate called after throwing an instance of 'std::system_error'
find_package(Threads REQUIRED)

# 查找Java，若没有安装则错误。因ANTLR4需要，如果不使用ANTLR4时可删除
find_package(Java COMPONENTS Runtime REQUIRED)

# 因AST输出图片需要借助Graphviz提供的C++接口来实现，因此若Graphviz没有安装则出错
# 查找graphviz库是否在系统中安装，若安装则设置一系列的变量，如LIBGVC_INCLUDE_DIRS等
find_package(Graphviz REQUIRED)

# 设置antlr-4.12.0-complete的位置
set(ANTLR4_JAR_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/antlr4/antlr-4.12.0-complete.jar)

# 设置libsysy-runtime的位置
set(LIBSYSY_RUNTIME_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/syslib)

if(NOT EXISTS ${LIBSYSY_RUNTIME_LOCATION}/std.a)
	message(FATAL_ERROR "std.a not found at ${LIBSYSY_RUNTIME_LOCATION}/std.a")
endif()

# 查找antlr4-runtime包是否存在，若不存在则出错。目的用于本程序与Antlr4进行链接
find_package(ANTLR4 REQUIRED)
message(STATUS ${ANTLR4_INCLUDE_DIR})

# antlr4工具的输入和输出文件
set(ANTLR4_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/frontend/antlr4/autogenerated)
set(ANTLR4_INPUT
	${CMAKE_CURRENT_SOURCE_DIR}/frontend/antlr4/SysY.g4
)
set(ANTLR4_OUTPUT
	${ANTLR4_GEN_DIR}/SysYBaseVisitor.cpp
	${ANTLR4_GEN_DIR}/SysYBaseVisitor.h
	${ANTLR4_GEN_DIR}/SysYVisitor.cpp
	${ANTLR4_GEN_DIR}/SysYVisitor.h
	${ANTLR4_GEN_DIR}/SysYLexer.cpp
	${ANTLR4_GEN_DIR}/SysYLexer.h
	${ANTLR4_GEN_DIR}/SysYParser.cpp
	${ANTLR4_GEN_DIR}/SysYParser.h
)

# 前端源代码集合
set(FRONTEND_SRCS

	# 前端共性代码
	frontend/AST.cpp
	frontend/AST.h
	frontend/Graph.cpp
	frontend/Graph.h
	frontend/FrontEndExecutor.h
	frontend/AttrType.h

	# ANTLR4相关代码
	${ANTLR4_OUTPUT}
	frontend/antlr4/Antlr4CSTVisitor.cpp
	frontend/antlr4/Antlr4CSTVisitor.h
	frontend/antlr4/Antlr4Executor.cpp
	frontend/antlr4/Antlr4Executor.h
)

# 后端源代码集合
set(BACKEND_SRCS

	# 后端共性代码
	backend/CodeGenerator.cpp
	backend/CodeGenerator.h
	backend/CodeGeneratorAsm.cpp
	backend/CodeGeneratorAsm.h

	# 后端产生ARM32汇编指令
	backend/arm32/ILocArm32.cpp
	backend/arm32/ILocArm32.h
	backend/arm32/InstSelectorArm32.cpp
	backend/arm32/InstSelectorArm32.h
	backend/arm32/PlatformArm32.cpp
	backend/arm32/PlatformArm32.h
	backend/arm32/CodeGeneratorArm32.cpp
	backend/arm32/CodeGeneratorArm32.h
	backend/arm32/SimpleRegisterAllocator.cpp
	backend/arm32/SimpleRegisterAllocator.h
)

# 中间IR(ir)源代码集合
set(IR_SRCS
	ir/Generator/IRGenerator.cpp
	ir/Generator/IRGenerator.h
	ir/Instructions/ArgInstruction.cpp
	ir/Instructions/ArgInstruction.h
	ir/Instructions/BinaryInstruction.cpp
	ir/Instructions/BinaryInstruction.h
	ir/Instructions/BranchConditional.cpp
	ir/Instructions/BranchConditional.h
	ir/Instructions/CastInstruction.cpp
	ir/Instructions/CastInstruction.h
	ir/Instructions/EntryInstruction.cpp
	ir/Instructions/EntryInstruction.h
	ir/Instructions/ExitInstruction.cpp
	ir/Instructions/ExitInstruction.h
	ir/Instructions/FuncCallInstruction.cpp
	ir/Instructions/FuncCallInstruction.h
	ir/Instructions/GotoInstruction.cpp
	ir/Instructions/GotoInstruction.h
	ir/Instructions/LabelInstruction.cpp
	ir/Instructions/LabelInstruction.h
	ir/Instructions/LoadInstruction.cpp
	ir/Instructions/LoadInstruction.h
	ir/Instructions/StoreInstruction.cpp
	ir/Instructions/StoreInstruction.h
	ir/Instructions/MoveInstruction.cpp
	ir/Instructions/MoveInstruction.h
	ir/Instructions/UnaryInstruction.cpp
	ir/Instructions/UnaryInstruction.h
	ir/Instructions/GetElementPtrInstruction.cpp
    ir/Instructions/BitCastInstruction.cpp
	ir/Types/VoidType.h
	ir/Types/VoidType.cpp
	ir/Types/LabelType.h
	ir/Types/LabelType.cpp
	ir/Types/IntegerType.h
	ir/Types/IntegerType.cpp
	ir/Types/FloatType.h
	ir/Types/FloatType.cpp
	ir/Types/ArrayType.h
	ir/Types/ArrayType.cpp
	ir/Values/ConstInt.h
	ir/Values/FormalParam.h
	ir/Values/GlobalVariable.h
	ir/Values/LocalVariable.h
	ir/Values/MemVariable.h
	ir/Values/RegVariable.h
	ir/IRCode.h
	ir/IRCode.cpp
	ir/Constant.h
	ir/Function.cpp
	ir/Function.h
	ir/GlobalValue.h
	ir/Instruction.cpp
	ir/Instruction.h
	ir/IRConstant.h
	ir/Type.h
	ir/Use.cpp
	ir/Use.h
	ir/User.h
	ir/User.cpp
	ir/Value.cpp
	ir/Value.h
)

# 符号表等共通化代码集合
set(SYMBOLTABLES_SRCS

	symboltable/Module.cpp
	symboltable/Module.h
	symboltable/ScopeStack.cpp
	symboltable/ScopeStack.h
)

# 系统差异性代码集合
set(UTILS_SRCS
	utils/Common.cpp
	utils/Common.h
	utils/getopt-port.cpp
	utils/getopt-port.h
	utils/Set.h
	utils/Set.cpp
	utils/BitMap.h
)

# 优化源代码集合
# TODO 增加优化时可在这里指定源代码的相对路径
set(OPT_SRCS)

# 配置创建一个可执行程序，以及该程序所依赖的所有源文件、头文件等
add_executable(${PROJECT_NAME}

	# 主程序
	main.cpp

	# 前端源代码
	${FRONTEND_SRCS}

	# 后端源代码
	${BACKEND_SRCS}

	# 符号表代码
	${SYMBOLTABLES_SRCS}

	# 中间IR代码
	${IR_SRCS}

	# 优化代码，暂时未用
	${OPT_SRCS}

	# 操作系统差异化代码，VC编译时使用
	${UTILS_SRCS}
)

# 设置语言标准C++17，可根据需要调整
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
)

# # LLDB调试运行时string不能显示，这是由于clang默认优化时减少调试信息导致的，因此这里指定选项不要优化调试信息
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	target_compile_options(${PROJECT_NAME} PRIVATE -fstandalone-debug)
endif()

# -Wno-unused-function避免无用函数警告
# -Wno-write-strings避免c++提示字符串常量转换char*的警告
# -Werror强制警告当作错误处理
# -Wall尽可能多的让编译器提示警告和错误
# __STDC_VERSION__的目的是警告产生的flex源文件出现INT8_MAX警告等
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wno-write-strings -Wno-unused-function)

if(USE_GRAPHVIZ)
	target_compile_definitions(${PROJECT_NAME} PRIVATE USE_GRAPHVIZ)
	target_include_directories(${PROJECT_NAME} PRIVATE ${Graphviz_INCLUDE_DIRS})

	# 指定graphviz的库文件以及位置，防止链接时找不到graphviz的库函数
	target_link_libraries(${PROJECT_NAME} PRIVATE ${Graphviz_LIBRARIES})
endif()

# 引入graphviz库的头文件，防止编译时找不到graphviz的头文件
target_include_directories(${PROJECT_NAME} PRIVATE
	${ANTLR4_INCLUDE_DIR}
	utils
	symboltable
	ir
	ir/Generator
	ir/Types
	ir/Values
	ir/Instructions
	frontend
	frontend/antlr4
	frontend/antlr4/autogenerated
	${LIBSYSY_RUNTIME_LOCATION}
	backend
	backend/arm32
)

# 添加syslib静态库
add_library(sysy_runtime STATIC IMPORTED)
set_target_properties(sysy_runtime PROPERTIES
	IMPORTED_LOCATION ${LIBSYSY_RUNTIME_LOCATION}/std.a
)

# 指导antlr4的库名，防止链接时找不到antlr4-runtime
target_link_libraries(${PROJECT_NAME} PRIVATE ${ANTLR4_LIBRARY})

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

target_link_libraries(${PROJECT_NAME} PRIVATE sysy_runtime)

# 通过antlr4.12.0生成词法与语法分析源代码
# WORKING_DIRECTORY指定工作目录时Mac平台有问题，因此使用绝对地址
add_custom_command(
	OUTPUT
	${ANTLR4_OUTPUT}
	COMMAND
	${Java_JAVA_EXECUTABLE} -jar ${ANTLR4_JAR_LOCATION} -Dlanguage=Cpp -no-listener -visitor -o ${ANTLR4_GEN_DIR} SysY.g4
	DEPENDS
	${ANTLR4_INPUT}
	WORKING_DIRECTORY
	${ANTLR4_GEN_DIR}/..
)

# 源代码打包
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-src")

# 忽略不需要源代码目录或文件
set(CPACK_SOURCE_IGNORE_FILES
	"/build/;" # 忽略 build 目录
	"/cmake-build-.*/;" # cmake-build-开头的目录
	"/.git/;" # 忽略 Git 仓库
	"~$;" # 忽略临时文件（如编辑器产生的临时文件）
	"/doc/;" # 忽略 doc 目录
	"/frontend/antlr4/.antlr/;" # antlr自动产生的目录
	"/.history/;" # 本地历史文件
	"/tests/;" # 测试文件夹
)

# 二进制打包
set(CPACK_GENERATOR "ZIP;TGZ")

# 安装可执行程序，不要bin文件夹下
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)

# 设置打包的名字
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-bin")

# 设置包描述
set(CPACK_PACKAGE_DESCRIPTION "minic开发版")

include(CPack)
