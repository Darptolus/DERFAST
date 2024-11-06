# from pynput.mouse import Button, Controller
from pynput.keyboard import Key, Controller as KeyboardController
from pynput.mouse import Button, Controller as MouseController

import time

# Configuration for splits
# n_horizontal = int(input("Enter number of horizontal splits: "))
# n_vertical = int(input("Enter number of vertical splits: "))

# screen -S grid_session bash
# screen -X -S grid_session quit

n_horizontal = 3
n_vertical = 8

delay=0.1

keyboard = KeyboardController()
mouse = MouseController()

# Delay for screen commands to register
def press_key(key):
  keyboard.press(key)
  keyboard.release(key)
  time.sleep(delay)

def press_ca_key(key):
  with keyboard.pressed(Key.ctrl):
    keyboard.press('a')
    keyboard.release('a')
  keyboard.press(key)
  keyboard.release(key)
  time.sleep(delay)

def create_vertical_splits(count):
  for _ in range(count - 1):
    press_ca_key("|")
    
def create_horizontal_splits(count):
  for _ in range(count - 1):
    press_ca_key("S")

def move(count):
  for _ in range(count):
    with keyboard.pressed(Key.ctrl):
      keyboard.press('a')
      keyboard.release('a')
    keyboard.press(Key.tab)
    keyboard.release(Key.tab)

def paste_move(n_hor, n_ver):
  for i in range(n_hor):
    for ii in range(n_ver):
      if ((i + 1) * (ii + 1) < n_ver * n_hor):
        press_key('i')
        mouse.press(Button.right)
        mouse.release(Button.right)
        keyboard.press(Key.esc)
        keyboard.release(Key.esc)
        press_key(':')
        press_key('w')
        press_key('q')
        keyboard.press(Key.enter)
        keyboard.release(Key.enter)
        move(1)
  
time.sleep(5)
paste_move(n_horizontal,n_vertical)



# keyboard.press('|')
# keyboard.release('|')

# keyboard.press('S')
# keyboard.release('S')
