#include <iostream>
#include "build/feedforward.pb.h"
#include "absl/strings/str_cat.h"

int main() {
    Message msg;
    msg.set_text("Hello, World!");

    std::string output;
    absl::StrAppend(&output, "Message: ", msg.text());
    std::cout << output << std::endl;

    return 0;
}
