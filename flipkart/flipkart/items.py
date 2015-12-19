# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy

class FlipkartItem(scrapy.Item):
	rating = scrapy.Field()
	title = scrapy.Field()
	price = scrapy.Field()
	image = scrapy.Field()
	link = scrapy.Field()
	
