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
from scrapy.spider import BaseSpider
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
import sys

class FlipkartSpider(scrapy.Spider):
	name = "flip1"
	allowed_domains = ["snapdeal.com"]
	def __init__(self, category=''):
		f = open(category)
		self.start_urls = [url.strip() for url in f.readlines()]
		f.close()
        #self.start_urls = ['http://www.example.com/categories/%s' % category]
        #self.domain = domain
	'''start_urls = ["http://www.snapdeal.com/product/iball-slide-2g-7236-tablet/1238133516#bcrumbSearch:tablet|bcrumbLabelId:133"
	,"http://www.snapdeal.com/product/zync-dual-7i-dual-core/669828179559#bcrumbSearch:tablet|bcrumbLabelId:133",
	"http://www.snapdeal.com/product/micromax-p470/1507564950#bcrumbSearch:tablet|bcrumbLabelId:133",
	"http://www.snapdeal.com/product/vox-177-cm-android-442/621151916466#bcrumbSearch:vox%20102",
	"http://www.snapdeal.com/product/iball-slide-wq32-with-keyboard/620528839485?",
	"http://www.snapdeal.com/product/blackberry--playbook-wifi-/53050#bcrumbSearch:tablet|bcrumbLabelId:175"]'''
	def parse(self, response):
		x="[u'3.5']"
		model="Model"
		hmodel=""
		f = open("data2.txt", "a")
		item = FlipkartItem()
		item['company'] = response.xpath('//*[@class="productTitle"]//img/@alt').extract()
		item['image'] = response.xpath('//*[@id="product-slider"]/li[1]/img/@src').extract()[0]
		item['rating'] = response.xpath('//*[@id="ratingOverReview"]/div[2]/span[1]/text()').extract()
		item['title'] = response.xpath('//*[@class="productTitle"]//h1[@itemprop="name"]/text()').extract()
		item['price'] = response.xpath('//*[@id="selling-price-id"]/text()').extract()
		item['price_del'] = response.xpath('//*[@id="Ship_charges"]/text()').extract()
		item['stock'] = response.xpath('//*[@class="notifyMe-soldout"]/text()').extract()
		item["link"] = response.request.url
		'''yield item
		item = FlipkartItem()'''
		sites = response.xpath('//*[@class="product-spec"]')
		item['model'] = None
		item['ram'] = None
		'''if item['ram']==None:
			print "yessdysdaiydsiaydsiuyadsduyiadsyidsyayaiudsyi"'''
		for site in sites:
			#print site
			table = site.xpath('tr/td/text()').extract()
			#f.write(table+"\n")
			for index,tab in enumerate(table):
				#f.write(str(table[index]).lower()+"\n")
				try:
					x = str(table[index]).lower().strip()
					#f.write(x+"\n")
					if x.find("model") != -1:
						item['model']=str(table[index+1]).strip()
						#f.write("yes\n")
					elif x=="ram" and item['ram']==None:
						item['ram']=str(table[index+1]).strip()
					elif x=="internal memory" and item['ram']==None:
						item['ram']=str(table[index+1]).strip()		
					elif x=="memory" and item['ram']==None:
						item['ram']=str(table[index+1]).strip()	
				except IndexError:
					break
			#item['rating']= str(site.xpath('tr/td/text()').extract())
			'''
				f.write("found\n")'''
			#print table	
		yield item
		f.close();
		'''item = FlipkartItem()
		rating = response.xpath('//*[@id="ratingOverReview"]/div[2]/span[1]/text()').extract()
		x=str(rating)
		print x
		if x=="[u'3.5']":
			item['rating']=rating
		yield item'''
		#company = response.xpath('//*[@class="productTitle"]//img/@alt').extract()
		#print company