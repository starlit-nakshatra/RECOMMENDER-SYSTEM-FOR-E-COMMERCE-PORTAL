from extract import extract
import unittest
import csv,re,os

class TestProductinfoExtractor(unittest.TestCase):
   
   def setUp(self):
      pass
   
   def testCheckUrl(self):
     '''
       Validates the url check incorporated in the extract function
     '''
     urls_for_validation = ['google.com','https://flipkart.com/ayush','https://amazon.com']
     with self.assertRaises(NameError) as context:
         for url in urls_for_validation:
           extract(url)
     self.assertEqual(context.exception.message , 'Invalid URL given')
    
   def testCheckFlipkart(self):
     '''
       The extract function should return a dict on execution with 
       urls having the xpath in the website_csv list
     '''
     item_name = "Brica Pop Open Cling Sun Shade"
     item_name_extracted = str(extract('http://www.flipkart.com/brica-pop-open-cling-sun-shade/p/itme2znucyhn7un2?pid=SUDE2ZNUDUFMJ36M&srno=b_1&offer=DOTDOnAutomotive_Jan21.&ref=75afa3e4-e5b7-425a-92f1-745b4f6b7f99')['name']).replace("\n","").replace(" ","")
     self.assertEqual(item_name.replace(" ","") , item_name_extracted)
  
   def testCheckAmazon(self):

     item_name = "MIDLAND WR300 Weather Radio"
     item_name_extracted = str(extract('http://www.amazon.com/Midland-WR-300-MIDLAND-WR300-Weather/dp/B00009V2YV/ref=sr_1_1?m=A21C4U5X700J66&s=aht&ie=UTF8&qid=1399984417&sr=1-1')['name']).replace('\n',"").replace(' ','')
    
     self.assertEqual(item_name.replace(" ","") , item_name_extracted)

   def testCheckCsvContent(self):
     '''
       Check if the contents in the csv files are in proper way 
     '''
     input_file = open(os.path.join(os.path.dirname(__file__),'webpage_xpath.csv'), 'rb')
     reader = csv.reader(input_file)
     row = list(reader)
     for r in range(len(row)):
       for p in range(1,4):
         if re.match('//',row[r][p]):
            pass
 
if __name__ == '__main__':
  unittest.main()
