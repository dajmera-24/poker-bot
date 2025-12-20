import numpy as np
import yfinance as yf
import scipy as sp
import pandas as pd

def ticker_data(ticker):
    return yf.download(ticker)
