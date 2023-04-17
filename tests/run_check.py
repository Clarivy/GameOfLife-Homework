import os
from pathlib import Path
import glob

COMIPLE_COMMAND = "g++ -Wall -Wextra -o run_testcase ../GameManager.cpp ../GameWorld.cpp ../LifeCell.cpp ../LifeRule.cpp ./run_testcase.cpp"
RUN_COMMAND = lambda rule_type, testcase, output: f"./run_testcase {rule_type} {testcase} {output}"

test_task = [ "base", "colorised", "extended", "weighted", "generations"]

os.system(COMIPLE_COMMAND)

for rule_type in test_task:
    testcases = list(glob.glob(f"./testcases/{rule_type}_*.in"))
    for testcase in testcases:
        output = Path(testcase).with_suffix(".out")
        std_output = Path(testcase).with_suffix(".ans")
        os.system(RUN_COMMAND(rule_type, testcase, output))
        if os.system(f"diff {output} {std_output}") != 0:
            print(f"Testcase {testcase} failed.")
            break
    print(f"Rule {rule_type} passed.")
        # print(RUN_COMMAND(rule_type, testcase, output))