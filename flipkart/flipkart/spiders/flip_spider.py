from scrapy.spider import Spider
from scrapy.selector import Selector
from flipkart.items import FlipkartItem
from scrapy.spider import BaseSpider
from selenium import webdriver
import scrapy
import time
from selenium.common.exceptions import NoSuchElementException
from selenium.common.exceptions import NoSuchFrameException
from selenium.common.exceptions import StaleElementReferenceException
from selenium.common.exceptions import WebDriverException
from selenium.common.exceptions import NoAlertPresentException
from scrapy.http import TextResponse 
from selenium.common.exceptions import NoSuchElementException 
from selenium.webdriver.support.ui import Select 
#from items import EbayItem
from scrapy.spider import BaseSpider
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC


class FlipkartSpider(BaseSpider):
    name = "flip1"
    allowed_domains = ["flipkart.com"]
    start_urls = [
		"http://www.flipkart.com/tablets/pr?sid=tyy%2Chry&q=mobile&ref=b8b64676-065a-445c-a6a1-bc964d5ff938"
	]
    '''def is_element_present(self, finder, selector, wait_time=None):
        wait_time = wait_time or self.wait_time
        end_time = time.time() + wait_time
        while time.time() < end_time:
            if finder(selector):
                return True
        return False
		def is_element_present_by_xpath(self, xpath, wait_time=None):
        return self.is_element_present(self.find_by_xpath, xpath, wait_time)
		'''
    def __init__(self):
        self.driver = webdriver.Firefox()
 

    def parse(self, response):
		sel = Selector(response) 
		self.driver.get(response.url)
		block="block"
		hyper="http://www.flipkart.com"
		print hyper
		#i=0
		while True:
			self.driver.execute_script("window.scrollTo(10000000,10000000)")
			self.driver.set_page_load_timeout(10000)
			try:
				show = self.driver.find_element_by_xpath('//div[@id="show-more-results"]').value_of_css_property('display')
				if show==block:
					self.driver.find_element_by_xpath('//div[@id="show-more-results"]').click()
				no_more = self.driver.find_element_by_xpath('//*[@id="no-more-results" and @class="dont-show"]').value_of_css_property('display')
				if no_more==block:
					break;
				time.sleep(5)
				self.driver.execute_script("window.scrollTo(10000000,10000000)")
				
				self.driver.set_page_load_timeout(10000)
				#if i==7:
				#	break
			except NoSuchElementException:
				print "pungi"
				break
		#down = self.driver.find_element_by_xpath('//div[@id="show-more-results"]')
		#location = down.location
		#self.((JavascriptExecutor) driver).executeScript("window.scrollBy(10000,10000);");
		#next = self.driver.find_element_by_xpath('//div[@id="show-more-results"]')
		response = TextResponse(url=response.url, body=self.driver.page_source, encoding='utf-8')
		try:
			#self.driver.set_page_load_timeout(10000)
			#driver.execute_script("window.scrollTo(0, location.get('y')")
			sites = response.xpath('//div[@class="gd-col gu12 browse-product fk-inf-scroll-item"] | //div[@class="pu-details lastUnit"] |  //div[@class="pu-visual-section"]')
			for site in sites:
				item = FlipkartItem()
				item['title'] = site.xpath('div//a[@class="lu-title"]/text() | div[1]/a/text()').extract()
				item['price'] = site.xpath('div//div[@class="pu-price"]/div/text() | div//div[@class="pu-final"]/span/text()').extract()
				item['rating'] = site.xpath('div[@class="pu-rating"]/div/@title').extract()
				item['image'] = site.xpath('a/img/@src').extract()
				data = site.xpath('a/@href').extract()
				print data
				item['link'] = data
				
				#print rating
				yield item
			'''for site in sites:
				item = FlipkartItem()
				item['title'] = site.xpath('div//a[@class="lu-title"]/text() | div[1]/a/text()').extract()
				item['price'] = site.xpath('div//div[@class="pu-price"]/div/text() | div//div[@class="pu-final"]/span/text()').extract()
				item['rating'] = site.xpath('div[@class="pu-rating"]/div/@title').extract()
				#print rating
				yield item'''
			#next.click()
			#self.driver.execute_script("window.scrollTo(10000000,10000000)")
		except:
			#break
			a=10
		self.driver.close()
		