# from pynput.mouse import Button, Controller
from pynput.keyboard import Key, Controller
import time

# Configuration for splits
# n_horizontal = int(input("Enter number of horizontal splits: "))
# n_vertical = int(input("Enter number of vertical splits: "))
n_horizontal = 3
n_vertical = 8

keyboard = Controller()

# Delay for screen commands to register
def press_key(key, delay=0.1):
    keyboard.press(key)
    keyboard.release(key)
    time.sleep(delay)
    
time.sleep(5)




# with keyboard.pressed(Key.ctrl):
#     keyboard.press('a')
#     keyboard.release('a')

# keyboard.press('|')
# keyboard.release('|')

keyboard.press('S')
keyboard.release('S')
