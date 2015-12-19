import sys
import os
import csv
from webscraping import webkit, xpath
from PyQt4.QtGui import * 
from PyQt4.QtCore import *
from PyQt4.QtWebKit import *

class Render(QWebPage):
  def __init__(self,url):
    self.app = QApplication(sys.argv)  
    QWebPage.__init__(self)  
    self.loadFinished.connect(self._loadFinished)  
    self.mainFrame().load(QUrl(url))  
    self.app.exec_() 

  def _loadFinished(self, result):  
    self.frame = self.mainFrame()  
    self.app.quit()
    
   r = Render(url)
   html = r.frame.toHtml()
  
   try: 
     f = open(os.path.join(os.path.dirname(__file__),'webpage_xpath.csv'), 'rb')  #Joining absolute path so that the function can be used inside an app
   except IOError:                                                               # Checking for Input Output exceptions, i.e if the file exists or not
     print('An error occured while reading the csv file, check your Directory again')
     sys.exit()

   reader = csv.reader(f)
   row = list(reader)
   item ={}
   for r in range(0,len(row)):
     if url.find(row[r][0])>=0 and url.find(row[r][4])>=0:
        xpath1 = row[r][1]
        xpath2 = row[r][2]
        xpath3 = row[r][3]  

        item['name'] = xpath.get(html,'%s//text()' % xpath1)
        item['price'] = xpath.get(html,'%s//text()' % xpath2)
        item['image'] = xpath.get(html, '%s' % xpath3)
        return item
        sys.exit()

     else:
       continue

   if item == {}: 
     print "Invalid url given"
     sys.exit()

if __name__ =='__main__':
  url ="".join(sys.argv[1:])
  extract(url)
  sys.exit()
