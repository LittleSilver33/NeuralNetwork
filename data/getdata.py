import requests

import pandas as pd
import json
from tqdm import tqdm
import os
import yfinance as yf

# US Publicly Traded Company Stock Tickers
url = 'https://www.sec.gov/files/company_tickers.json'

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:128.0) Gecko/20100101 Firefox/128.0'
}

response = requests.get(url, headers=headers)
data = response.json()
tickers = [company['ticker'] for company in data.values()]
#print(f"{tickers}"")

period = "max"
interval = "1d"

os.makedirs("train", exist_ok=True)

with tqdm(total=len(tickers), desc="") as pbar:
    for ticker in tickers:
        try:
            pbar.set_description(f"{ticker}")
            stock = yf.Ticker(ticker)
            hist = stock.history(period=period, interval=interval)
            
            hist.to_csv(f"train/{ticker}.csv")
        except Exception as e:
            tqdm.write(f"Failed to fetch data for {ticker}: {e}")
        finally:
            pbar.update(1)

print(f"Data from {len(tickers)} tickers fetched.")