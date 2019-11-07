import re
import urllib2


def down_load():
    url = "https://sou.zhaopin.com/?jl=%E6%88%90%E9%83%BD&sf=0&st=0&kw=python&kt=3"
    headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.70 Safari/537.36;"}
    request = urllib2.Request(url, headers=headers)
    request.add_header("Connection", "keep-alive")
    respone = urllib2.urlopen(request)
    data = respone.read()
    code = respone.code
    return data
    pass


html = down_load()
print(html)