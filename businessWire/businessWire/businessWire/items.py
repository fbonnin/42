# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class BusinesswireItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()

    ID = scrapy.Field()
    title = scrapy.Field()
    content = scrapy.Field()
    company = scrapy.Field()
    ticker = scrapy.Field()
    hashtag = scrapy.Field()
    cashtag = scrapy.Field()
    contact = scrapy.Field()
    xdate = scrapy.Field()
    pdate = scrapy.Field()
    url = scrapy.Field()

    pass
