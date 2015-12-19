from scrapy.spider import Spider
from scrapy.selector import Selector
from flipkart.items import FlipkartItem
from selenium import selenium
from scrapy.contrib.spiders.init import InitSpider
from scrapy.http import Request, FormRequest
from scrapy.contrib.linkextractors.sgml import SgmlLinkExtractor
from scrapy.contrib.spiders import CrawlSpider, Rule
class FlipkartSpider(InitSpider):
    name = "flip"
    allowed_domains = ["flipkart.com"]
    start_urls = [
		"http://www.flipkart.com/beauty-and-personal-care/personal-care-appliances/hair-dryers/pr?sid=t06,79s,mh8&otracker=nmenu_sub_electronics_0_Hair%20Dryers",
		"http://www.flipkart.com/laptops/hp~brand/pr?sid=6bo,b5g",
		"http://www.flipkart.com/books/cooking-food-wine/pr?sid=bks%2C43p&ref=6216ce54-d429-4959-a53d-d3ffe9d5522b",
		"http://www.flipkart.com/mobiles/~new-releases/pr?sid=tyy%2C4io&otracker=ch_vn_mobile_main_NEW%20ARRIVALS%20IN%20MOBILE%20PHONES_View_All"
	]
    def __init__(self):
		InitSpider.__init__(self)
		self.selenium = selenium("localhost", 4444, "*chrome", "http://www.flipkart.com")
		self.log("nnn Starting the Selenium Server! nnn")
		self.selenium.start()
		self.log("nnn Successfully, Started the Selenium Server! nnn")
			
    def parse(self, response):
		sel = Selector(response)
		sele = self.selenium
		sele.open(response.url)
		time.sleep(2.5)
		sites = sele.xpath('//div[@class="gd-col gu12 browse-product fk-inf-scroll-item"] | //div[@class="pu-details lastUnit"]')
		#x= site.xpath('//span[@class="fk-font-17 fk-bold"]')
		for site in sites:
			item = FlipkartItem()
			hxs = Selector(response)
			
			item['title'] = site.xpath('div//a[@class="lu-title"]/text() | div[1]/a/text()').extract()
			""""x= site.xpath('/*div[@class="pu-final"]')
			for xx in x:
				item['price'] = xx.xpath('span/text()').extract()
				break"""
			
			item['price'] = site.xpath('div//div[@class="pu-price"]/div/text() | div//div[@class="pu-final"]/span/text()').extract()
			yield item
	