cmake_minimum_required(VERSION 3.5)

set(StdFeatures
	cxx_range_for
	cxx_noexcept
	cxx_rvalue_references
	cxx_override
	cxx_lambdas
	cxx_final
	cxx_deleted_functions
	cxx_delegating_constructors
	cxx_auto_type
	cxx_constexpr
	cxx_lambda_init_captures
	)

# Include Python

set(Python_ADDITIONAL_VERSIONS 3.5)
find_package(PythonLibs 3.5 REQUIRED)
if (${PYTHONLIBS_FOUND})
	include_directories(${PYTHON_INCLUDE_DIRS})
	link_directories(${PYTHON_LIBRARIES})
endif()

# Boost
find_package(Boost 1.61.0 COMPONENTS
	filesystem thread timer python3 program_options
	REQUIRED)
if (${Boost_FOUND})
	include_directories(${Boost_INCLUDE_DIRS})
	link_directories(${Boost_LIBRARY_DIR})
endif()

# Qt
find_package(Qt5Widgets REQUIRED)
add_definitions(-DQT_NO_KEYWORDS)

# Threads
find_package(Threads REQUIRED)

# FFTW
find_library(FFTW_LIBRARY NAMES fftw3)

set(FileSource
	main.cpp
	core/Configuration.cpp
	core/scripting.cpp
	test/test.cpp
	test/scripting/testScripting.cpp
	ui/MainWindow.cpp
	ui/DialogAbout.cpp
	ui/terminal.cpp
	ui/panels/Panel.cpp
	ui/panels/PanelControl.cpp
	ui/panels/PanelPlayback.cpp
	ui/panels/PanelResources.cpp
	)
qt5_wrap_cpp(QtMOCSourceFiles
	ui/MainWindow.hpp
	ui/DialogAbout.hpp
	ui/terminal.hpp
	ui/panels/Panel.hpp
	ui/panels/PanelControl.hpp
	ui/panels/PanelPlayback.hpp
	ui/panels/PanelResources.hpp
	)

qt5_add_resources(QtCompiledResources
	assets/resources.qrc
	)

add_executable(Audiolysis
	${FileSource}
	${QtMOCSourceFiles}
	${QtCompiledResources}
	)
target_link_libraries(Audiolysis ${PYTHON_LIBRARIES})
target_link_libraries(Audiolysis ${Boost_LIBRARIES})
target_link_libraries(Audiolysis ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(Audiolysis ${FFTB_LIBRARY})
target_link_libraries(Audiolysis Qt5::Widgets Qt5::Core)
target_compile_features(Audiolysis PRIVATE ${StdFeatures})
