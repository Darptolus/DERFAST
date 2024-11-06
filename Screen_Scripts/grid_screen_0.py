# from pynput.mouse import Button, Controller
from pynput.keyboard import Key, Controller
import time

# Configuration for splits
# n_horizontal = int(input("Enter number of horizontal splits: "))
# n_vertical = int(input("Enter number of vertical splits: "))

# screen -S grid_session bash
# screen -X -S grid_session quit

n_horizontal = 3
n_vertical = 8

delay=0.1

keyboard = Controller()

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

def create_grid(n_hor, n_ver):
  create_vertical_splits(n_hor)
  move(n_hor)

  for i in range(n_hor):
    create_horizontal_splits(n_ver)
    # print(i)
    for ii in range(n_ver - 1):
      move(1)
      press_ca_key('c')
    move(1)
    # print(ii)
    # print("horizontal: ", (i + 1), "vertical: ", (ii + 2), "all: ", n_ver * n_hor)
    if ((i + 1) * (ii + 2) < n_ver * n_hor):
      press_ca_key('c')
      # print(i*ii)

time.sleep(5)
create_grid(n_horizontal,n_vertical)



# keyboard.press('|')
# keyboard.release('|')

# keyboard.press('S')
# keyboard.release('S')
