# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html

import pymysql
import businessWire.config

class BusinesswirePipeline(object):

    def process_item(self, item, spider):
        self.cursor.execute(
            """INSERT INTO articles (ID, title, content, company, ticker, hashtag, cashtag, contact, xdate, pdate, url) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"""
            % (
                ((item['ID'],
                  item['title'],
                 item['content'],
                 item['company'],
                 item['ticker'],
                 item['hashtag'],
                 item['cashtag'],
                 item['contact'],
                 item['xdate'],
                 item['pdate'],
                 item['url']))))

        self.connection.commit()
        self.cpt_insert += 1
        return item

    def open_spider(self, spider):
        self.cpt_insert = 0
        self.connection = pymysql.connect(host=businessWire.config.HOST, user=businessWire.config.USER, passwd=businessWire.config.PASSWD, db=businessWire.config.DBNAME,charset=businessWire.config.CHARSET)
        self.cursor = self.connection.cursor()

    def close_spider(self, spider):
        # Control process
        self.connection.close()

