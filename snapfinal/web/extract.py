#!usr/bin/python
#-*- coding: utf-8 -*-

import sys
import os
import csv
import re

class InvalidurlError(Exception):
    pass

try:
    # Checking for module import exceptions
    from webscraping import download, xpath, webkit
except ImportError:
    print('No webscraping module found , try installing it ')
    sys.exit()


def extract(url):
    '''
    Function that extracts product info from websites
    listed in the csv page . It takes the url as an argument.
    '''
    try:
        url = url.encode('utf-8')

        D = download.Download()

        try:
            xpath_input_file = open(os.path.join(os.path.dirname(__file__),
                                                 'webpage_xpath.csv'), 'rb')
            # Joining absolute path so that the function can be anywhere
        except IOError:
            # Checking for IO exceptions, i.e if the file exists or not
            print("An error occured while reading the csv file,\
                  check your Directory again")
            sys.exit()

        reader = csv.reader(xpath_input_file)
        row = list(reader)
        item_info = {}
        for r in range(0, len(row)):
            if url.find(row[r][0]) >= 0 and url.find(row[r][4]) >= 0:
            # Checks if the url fiven is correct or not
            # Fails in the case the url is of given site but not a prduct url
                xpath1 = row[r][1]
                xpath2 = row[r][2]
                xpath3 = row[r][3]

                html = D.get(url)
                # Webpage downloads after validation
                item_info['name'] = xpath.get(html, '%s//text()' % xpath1).strip()
                item_info['price'] = xpath.get(html, '%s//text()' % xpath2)
                item_info['image'] = xpath.get(html, '%s' % xpath3).strip()
                return item_info

            else:
                continue

        if item_info == {}:
            raise InvalidurlError("Enter a valid product url")
            sys.exit()

        xpath_input_file.close()
        sys.exit()

    except KeyboardInterrupt:
        raise
        sys.exit()

if __name__ == '__main__':
    url = "".join(sys.argv[1:])
    extract(url)
    sys.exit()
