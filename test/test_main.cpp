#include "gtest/gtest.h"
#include "../inc/ver.h"
#include "../inc/CmdProcessor.h"
#include "../inc/ConsoleWriter.h"
#include "../inc/FileWriter.h"

#include <vector>
#include <string>
#include <sstream>

TEST(ver_test_case, ver_major_test) {
  EXPECT_GE(ver_major(), 1);
}

TEST(ver_test_case, ver_minor_test) {
  EXPECT_GE(ver_minor(), 1);
}

TEST(ver_test_case, ver_patch_test) {
  EXPECT_GE(ver_patch(), 1);
}

namespace bulk {

/**
 * @brief Класс для тестового вывода блока команд.
 */
class TestWriter : public IStreamWriter {
  public:
    TestWriter() = default;
    ~TestWriter() override = default;

    void write(const std::time_t& time, const std::vector<std::string>& bulk) final {
      bulk_ = bulk;
      time_ = time;
    }

    auto get_bulk() {
      return bulk_;
    }

    auto get_time() {
      return time_;
    }

  private:
    std::vector<std::string> bulk_{};
    std::time_t time_{};
};

} // namespace bulk.

TEST(cmd_processor_test_case, subscribe_test) {
  bulk::CmdProcessor cmd_processor;
  auto testWriter = std::make_shared<bulk::TestWriter>();
  cmd_processor.subscribe(testWriter);

  std::stringstream ss;
  ss << "cmd1";

  cmd_processor.process(ss);

  EXPECT_EQ(testWriter->get_bulk(), std::vector<std::string>{"cmd1"});
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
