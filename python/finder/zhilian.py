# ending:utf-8
import re

zhiLianRe = '<div class="totalnum inlineblock" data-a-29bcac4f="">为您优选<span style="color:#5183FF;" data-a-29bcac4f="">1186</span>个放心职位</div>'

reStr = '<div class="totalnum inlineblock" data-a-29bcac4f="">为您优选<span style="color:#5183FF;" data-a-29bcac4f="">(\\d+)</span>个放心职位</div>'


def main():
    regex = re.compile(zhiLianRe, re.IGNORECASE)
    ret = regex.findall(reStr)
    print(ret)
    pass


if __name__ == '__main__':
    main()
