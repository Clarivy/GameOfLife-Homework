import os
import utils

output_dir = "./testcases/"

case_num = 5

def generate_map(cell_gen):
    map = ''
    for i in range(utils.MAX_HEIGHT):
        for j in range(utils.MAX_WIDTH):
            map += cell_gen()
        map += '\n'
    return map

test_task = [
    ("base", utils.generate_base_cell),
    ("colorised", utils.generate_color_cell),
    ("extended", utils.generate_base_cell),
    ("weighted", utils.generate_base_cell),
    ("generations", utils.generate_base_cell),
]

for rule_type, cell_gen in test_task:
    for i in range(case_num):
        with open(os.path.join(output_dir, f"{rule_type}_{i:02d}.in"), 'w') as f:
            f.write(generate_map(cell_gen))