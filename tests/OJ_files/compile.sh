mv foo.cc submission.zip

unzip -nq submission.zip

g++ run_testcase.cpp GameWorld.cpp GameManager.cpp LifeCell.cpp LifeRule.cpp -o foo -std=c++17 -Wall -Wpedantic -Wextra -Wzero-as-null-pointer-constant -Werror -fsanitize=undefined -fsanitize=address -DONLINE_JUDGE