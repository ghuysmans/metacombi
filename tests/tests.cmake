#inspired from http://www.cmake.org/pipermail/cmake/2009-July/030788.html

macro(expect test cmd args)
	add_test(${test}
		${CMAKE_COMMAND}
		-Dcmd=${cmd}
		-Dargs:string=${args}
		-Dresult=tests/${test}.res
		-Dexpected=tests/${test}.exp
		-P tests/do_test.cmake)
endmacro(expect)

if (UNIX)
	enable_testing()
	#CuTest
	file(GLOB UnitTests tests/U*.cpp)
	execute_process(
		COMMAND "tests/make-tests.sh" ${UnitTests}
		OUTPUT_FILE "tests/UAll.cpp")
	#TODO append tested libraries
	add_executable(UAll ${UnitTests} tests/CuTest.cpp)
	add_test(UAll UAll)
	#TODO other tests?
	#add_executable(buffer tests/buffer.c src/buffer.c src/socket.c)
	#expect(buffer/a tests/buffer.sh a)
endif (UNIX)
