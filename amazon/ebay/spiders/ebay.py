import scrapy
from scrapy.spider import Spider
from scrapy.selector import Selector
from scrapy.http import TextResponse 
from selenium.common.exceptions import NoSuchElementException 
#from items import EbayItem
from scrapy.spider import BaseSpider
from selenium.webdriver.support.wait import WebDriverWait
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
class EbayItem(scrapy.Item):
	title = scrapy.Field()
	link = scrapy.Field()
	price = scrapy.Field()
	image = scrapy.Field()
	rating = scrapy.Field()

class ProductSpider(BaseSpider):
	name = "ebay"
	allowed_domains = ['amazon.in']
	start_urls = ['http://www.amazon.in/s/ref=sr_pg_1?fst=as%3Aoff&rh=n%3A976392031%2Cn%3A1375458031%2Ck%3Atablet&keywords=tablet&ie=UTF8&qid=1427396450']

	def __init__(self):
		
		self.driver = webdriver.Firefox()

	def parse(self, response):
		#response = TextResponse(url=response.url, body=self.driver.page_source, encoding='utf-8')
		sel = Selector(response)
		self.driver.get(response.url)
		i=0
		while True:
			#next = self.driver.find_element_by_xpath('//*[@id="pagnNextString"]')
			
			next = WebDriverWait(self.driver, 10).until(
				EC.visibility_of_element_located((By.ID, "pagnNextString"))
			)
			#next.click()
			#i=i+1
			#if(i==2):
			#	break
			#sleep(50000)
			try:
				#self.driver.set_page_load_timeout(10000) 
				response = TextResponse(url=response.url, body=self.driver.page_source, encoding='utf-8')
				sites = response.xpath('//*[@id="s-results-list-atf"]/li')
				for site in sites:
			
					'''item = EbayItem()
					item['title'] = site.xpath('//a/h2[@class="a-size-base a-color-null s-inline s-access-title a-text-normal"]/text()').extract()
					item['link'] = sel.xpath('//a/@href').extract()
					item['price'] = site.xpath('//span[@class="a-size-base a-color-price s-price a-text-bold"]/span/text()').extract()
					yield item'''
					item=EbayItem()
					#title = site.xpath('//a/h2[@class="a-size-base a-color-null s-inline s-access-title a-text-normal"]/text()').extract()
					item['title'] = site.xpath('div/div[2]/div[1]/a/h2/text()').extract()
					item['link'] = site.xpath('div/div[2]/div[1]/a/@href').extract()
					item['price'] = site.xpath('div/div[3]/div[0]/a/span[0]/text() | div/div[3]/div[1]/a/span/text() ').extract()
					item['image'] = site.xpath('div/div[1]/div/div/a/img/@src').extract()
					#item['rating'] = site.xpath('div/div[5]/span/span/a/i[1]/span/text() | div/div[4]/span/span/a/i[1]/span/text()').extract()
					item['rating'] = site.xpath('div//span[@class="a-icon-alt"]/text()').extract()
					
					#price = site.xpath('div/div[3]/div[0]/a/span[0]/text() | div/div[3]/div[1]/a/span/text() ').extract()
					#print title,link, price
					#print price
					#sleep(50000)
					yield item
				try:
					self.driver.find_element_by_xpath('//*[@id="pagnNextLink"]')
				except NoSuchElementException:
					break
				next.click()
				
				# get the data and write it to scrapy items
				
			except:
				#break
				a=10
				#next.click()
		self.driver.close()