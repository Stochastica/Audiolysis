#ifndef AUDIOLYSIS_TEST_TEST_HPP__
#define AUDIOLYSIS_TEST_TEST_HPP__

#include <string>
#include <map>

namespace al
{

/**
 * @brief Returns a map of possible test id's and their descriptions.
 */
std::map<std::string, std::string> testInfo();

/**
 * @brief Executes test [id].
 */
bool test(std::string id);

} // namespace al

#endif // !AUDIOLYSIS_TEST_TEST_HPP__
