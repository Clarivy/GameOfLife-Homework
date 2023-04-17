MAX_WIDTH = 25
MAX_HEIGHT = 25

import random
random.seed(0)

def generate_base_cell(p=0.1) -> str:
    value = random.random()
    if value < p:
        return 'O'
    else:
        return '.'

def generate_color_cell(p=0.1) -> str:
    value = random.random()
    if value < p:
        return random.choice(['R', 'B'])
    else:
        return '.'