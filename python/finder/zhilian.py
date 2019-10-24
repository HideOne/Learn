# coding:utf-8
import re
import urllib

import selenium
import selenium.webdriver as webdriver

zhiLianRe = """<div class="totalnum inlineblock" data-a-29bcac4f="">为您优选<span style="color:#5183FF;" data-a-29bcac4f="">1186</span>个放心职位</div>"""

reStr     = """为您优选<span style="color:#5183FF;" data-a-29bcac4f="">(\d+)</span>个放心职位"""

jobStr = """ <i>(\d+)</i> """


def main():
    # regex = re.compile(reStr, re.IGNORECASE)

    # # url1 = 'http://zhaopin.baidu.com/quanzhi'
    # ret = regex.findall(zhiLianRe, re.IGNORECASE)
    # print ret
    url = 'https://cd.58.com/lvyouguwen/?utm_source=market&ClickID=2'
    driver = webdriver.Chrome()
    driver.get(url)
    data = driver.page_source
    print data
    regex = re.compile(jobStr, re.IGNORECASE)
    ret = regex.findall(data)

    print(ret)
    print(ret[0])
    pass


if __name__ == '__main__':
    main()
