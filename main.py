import numpy as np
import pandas as pd
import sys
import csv

if input('This is the GUI-less interface. Type \'Y\' if you would like to proceed, and N if you would like to exit.') == 'N':
    sys.exit()

if input('Are there any new stocks you would like to add to your portfolio? (Y/N) >>> ') == 'Y':
    user_input = input('Enter these tickers in a commma-separated format >>> ')
