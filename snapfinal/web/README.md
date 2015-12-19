python-web-extractor
====================

Scrapes data from various e-coomerce websites that do load their data by javascript .
Till now ,it extracts from online marketting websites namely - amazon ,flipkart, jabong and myntra .

It contains 2 main scripts , namely `extract.py` and `webkit_product_info.py` 
The 1st one provides data with cache which can be used later .

To get the product info , just give a call to the fuction in the module.For example - 
     `from extract import *`
     `info = extract('http://www.flipkart.com/wills-lifestyle-men-s-printed-casual-shirt/p/itmduesu6zf6hrzn?pid=SHTDUESURJDHFWVB&srno=b_3&ref=dce83d46-bb86-4fd3-8000-140be7fc60d5')`
     `print info`

or use the info as per your wish .

#Contributors

[Ayush Tiwari](https://github.com/tiwariayush)

#Dependencies

- Python
- Webscraping(http://docs.webscraping.com/index.html)
- csv
- For `webkit_product_info.py` , you need to install PyQt4 `sudo apt-get install python-pyqt4`

#Installation/Usage

- Fork and clone the repository.
- Move the files `extract.py` and `webpage_xpath.csv` to your app directory .
- Pass the function `extract(url)` to get the data and use as per your wish.
- For extracting more data from other websites , just add the xpaths in `webpage_xpath.csv` .

#License

`python-web-extractor` is licensed under the [MIT license.]
