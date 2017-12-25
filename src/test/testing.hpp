#ifndef AUDIOLYSIS_TEST_TESTING_HPP__
#define AUDIOLYSIS_TEST_TESTING_HPP__

#include <iostream> // For testing

#define TEST_FINAL \
	std::cerr << "Invalid Test Id\n"; \
	return false

/**
 * If [id] = [symb], execute test_symb().
 */
#define TEST_FUNC(symb) if (id == #symb) return test_##symb();

#endif // !AUDIOLYSIS_TEST_TESTING_HPP__
