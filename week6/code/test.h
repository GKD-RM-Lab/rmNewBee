#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

// 一个测试用例的描述和函数指针
struct TestCase {
  std::string name;
  std::function<void()> func;
};

// 全局注册表
inline std::vector<TestCase> &GetTests() {
  static std::vector<TestCase> tests;
  return tests;
}

// 辅助拼接名字
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b)        CONCAT_IMPL(a, b)

// 定义 TEST(suite_name, test_name) 宏
#define TEST(suite, name)                                             \
  void CONCAT(test_, CONCAT(suite, CONCAT(_, name)))();               \
  struct CONCAT(_registrar_, CONCAT(suite, CONCAT(_, name))) {        \
    CONCAT(_registrar_, CONCAT(suite, CONCAT(_, name)))() {           \
      GetTests().push_back(                                           \
          {#suite "." #name, &CONCAT(test_, CONCAT(suite, CONCAT(_, name)))}); \
    }                                                                 \
  } CONCAT(_registrar_instance_, CONCAT(suite, CONCAT(_, name)));     \
  void CONCAT(test_, CONCAT(suite, CONCAT(_, name)))()

// 断言宏：如果失败就打印文件、行号、表达式，然后直接 return
#define ASSERT_TRUE(cond)                                                   \
  do {                                                                       \
    if (!(cond)) {                                                           \
      std::cerr << __FILE__ << ":" << __LINE__                               \
                << ": Failure in " << __FUNCTION__                          \
                << ": ASSERT_TRUE(" #cond ") failed\n";                     \
      return;                                                                \
    }                                                                        \
  } while (0)

#define ASSERT_EQ(lhs, rhs)                                                  \
  do {                                                                       \
    auto _l = (lhs);                                                         \
    auto _r = (rhs);                                                         \
    if (!(_l == _r)) {                                                       \
      std::cerr << __FILE__ << ":" << __LINE__                               \
                << ": Failure in " << __FUNCTION__                          \
                << ": ASSERT_EQ(" #lhs ", " #rhs ") failed: "                \
                << _l << " != " << _r << "\n";                              \
      return;                                                                \
    }                                                                        \
  } while (0)

  #define RUN_ALL_TESTS()                                                         \
  int main() {                                                                  \
    int passed = 0, failed = 0;                                                 \
    auto &tests = GetTests();                                                   \
    for (auto &t : tests) {                                                     \
      std::cout << "[ RUN      ] " << t.name << "\n";                           \
      try {                                                                     \
        t.func();                                                               \
        std::cout << "[       OK ] " << t.name << "\n";                         \
        ++passed;                                                               \
      } catch (const std::exception &e) {                                       \
        std::cerr << "[  FAILED  ] " << t.name                                  \
                  << " threw exception: " << e.what() << "\n";                  \
        ++failed;                                                               \
      } catch (...) {                                                           \
        std::cerr << "[  FAILED  ] " << t.name                                  \
                  << " threw unknown exception\n";                              \
        ++failed;                                                               \
      }                                                                         \
    }                                                                           \
    std::cout << "\n[  PASSED  ] " << passed << " tests.\n";                    \
    if (failed > 0) {                                                           \
      std::cout << "[  FAILED  ] " << failed << " tests.\n";                    \
    }                                                                           \
    return failed;                                                              \
  }
