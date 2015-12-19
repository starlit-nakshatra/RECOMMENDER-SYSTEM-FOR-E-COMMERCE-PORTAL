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


class FlipkartSpider(BaseSpider):
    name = "flip1"
    allowed_domains = ["snapdeal.com"]
    start_urls = [
		"http://www.snapdeal.com/search?keyword=mobile&santizedKeyword=mobile&catId=12&categoryId=133&suggested=false&vertical=p&noOfResults=20&clickSrc=searchOnSubCat&lastKeyword=mobile&prodCatId=175&changeBackToAll=false&foundInAll=false&categoryIdSearched=&cityPageUrl=&url=&utmContent=&catalogID=&dealDetail=#bcrumbSearch:mobile|bcrumbLabelId:175",
		"http://www.snapdeal.com/search?keyword=tablet&santizedKeyword=tablet&catId=12&categoryId=29&suggested=false&vertical=p&noOfResults=20&clickSrc=searchOnSubCat&lastKeyword=tablet&prodCatId=133&changeBackToAll=false&foundInAll=false&categoryIdSearched=&cityPageUrl=&url=&utmContent=&catalogID=&dealDetail=#bcrumbSearch:tablet|bcrumbLabelId:133"
	]

    def __init__(self):
        self.driver = webdriver.Firefox()
 

    def parse(self, response):
		sel = Selector(response) 
		self.driver.get(response.url)
		block="none"
		hyper="http://www.snapdeal.com"
		print hyper
		i=0
		while True:
			self.driver.set_page_load_timeout(10000)
			self.driver.execute_script("window.scrollTo(10000000,10000000)")
			self.driver.set_page_load_timeout(10000)
			try:
				show = self.driver.find_element_by_xpath('//*[@id="seemore"]').value_of_css_property('display')
				print show
				'''if show==block:
					self.driver.find_element_by_xpath('//div[@id="show-more-results"]').click()'''
				no_more = self.driver.find_element_by_xpath('//*[@class="mar_20per_left ajax-loader-icon hidden"]').value_of_css_property('display')
				print no_more
				if no_more==block and show==block:
					break;
				time.sleep(5)
				self.driver.execute_script("window.scrollTo(10000000,10000000)")
				self.driver.set_page_load_timeout(10000)
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
			sites = response.xpath('//*[@class="product_grid_box"]')
			#print sites
			for site in sites:
				item = FlipkartItem()
				check = site.xpath('div[@class="productWrapper"]//div[@class="soldout-tag prod-grid-sold-out-lang"]/div/text()').extract()
				if check=='SOLD OUT':
					continue
				item['price'] =  site.xpath('div[@class="productWrapper"]//div[@class="product-price"]/div/text()').extract()[0]
				data = site.xpath('div[@class="productWrapper"]//div[@class="product-title"]/a/text()').extract()
				item['title'] = data
				item['rating'] = site.xpath('div[@class="productWrapper"]//div[@class="ratingStarsSmall"]/@style | div[@class="productWrapper"]//div[@class="ratingStarsSmall corrClass8"]/@ratings').extract()
				item['image'] = site.xpath('div[@class="productWrapper"]//div[@class=" product-image "]/a/img/@src').extract()
				item['link'] = site.xpath('div[@class="productWrapper"]//div[@class="product-title"]/a/@href').extract()
				yield item
		except:
			print "Loop error"
			a=10
		self.driver.close()
		