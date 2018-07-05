# -*- coding: utf-8 -*-
from scrapy.crawler import CrawlerProcess
from scrapy.utils.project import get_project_settings
import sys

process = CrawlerProcess(get_project_settings())
# param is the name of the spider.
process.crawl('BusinessWire')
process.start() # the script will block here until the crawling is finished

