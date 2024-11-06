# from pynput.mouse import Button, Controller
from pynput.keyboard import Key, KeyCode, Controller as KeyboardController
from pynput.mouse import Button, Controller as MouseController

import time

# Configuration for splits
# n_horizontal = int(input("Enter number of horizontal splits: "))
# n_vertical = int(input("Enter number of vertical splits: "))

# screen -S grid_session bash
# screen -X -S grid_session quit

n_horizontal = 3
n_vertical = 8

delay=0.05

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

def write_move(n_hor, n_ver):
  nopa_n=1
  nopa_n1=0
  nopa_n2=1
  for i in range(n_hor):
    for ii in range(n_ver):
      press_key('s')
      press_key('s')
      press_key('h')
      keyboard.press(Key.space)
      keyboard.release(Key.space)
      press_key('n')
      press_key('o')
      press_key('p')
      press_key('a')
      if nopa_n < 10:
        press_key(KeyCode.from_char(nopa_n1))
        press_key(KeyCode.from_char(nopa_n2))
        # print(nopa_n1, nopa_n2)
        nopa_n = nopa_n + 1
        nopa_n2 = nopa_n2 + 1
      elif nopa_n == 10:
        nopa_n1 = 1
        nopa_n2 = 0
        # print(nopa_n1, nopa_n2)
        press_key(KeyCode.from_char(nopa_n1))
        press_key(KeyCode.from_char(nopa_n2))
        nopa_n = nopa_n + 1
        nopa_n2 = nopa_n2 + 1
      elif nopa_n == 20:
        nopa_n2 = 0
        nopa_n1 = 2
        # print(nopa_n1, nopa_n2)
        press_key(KeyCode.from_char(nopa_n1))
        press_key(KeyCode.from_char(nopa_n2))
        nopa_n = nopa_n + 1
        nopa_n2 = nopa_n2 + 1
      elif nopa_n > 10 and nopa_n < 20:
        nopa_n1 = 1
        # print(nopa_n1, nopa_n2)
        press_key(KeyCode.from_char(nopa_n1))
        press_key(KeyCode.from_char(nopa_n2))
        nopa_n = nopa_n + 1
        nopa_n2 = nopa_n2 + 1
      elif nopa_n > 20:
        nopa_n1 = 2
        # print(nopa_n1, nopa_n2)
        press_key(KeyCode.from_char(nopa_n1))
        press_key(KeyCode.from_char(nopa_n2))
        nopa_n = nopa_n + 1
        nopa_n2 = nopa_n2 + 1

      keyboard.press(Key.enter)
      keyboard.release(Key.enter)
      move(1)
  
time.sleep(5)
write_move(n_horizontal,n_vertical)



# keyboard.press('|')
# keyboard.release('|')

# keyboard.press('S')
# keyboard.release('S')
