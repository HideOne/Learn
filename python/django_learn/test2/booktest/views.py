from django.shortcuts import render
from booktest.models import BookInfo
from django.http import HttpResponse, HttpResponseRedirect
# from django.http import HttpResponseRedirect
import datetime

# Create your views here.


def index(resquest):
    '''主页'''
    book = BookInfo.objects.all()
    return render(resquest, 'booktest/index.html', {'books': book})


def create(request):
    '''新增'''
    b = BookInfo()
    b.b_tittle = "流星蝴蝶剑"
    b.b_date = datetime.date(1999, 1, 1)
    b.save()
    # 返回应答
    # return HttpResponse('ok')
    # 从定向
    return HttpResponseRedirect('/index')


def delete(request, uid):
    '''删除'''
    # 通过id获取数据对象
    book = BookInfo.objects.get(id=uid)
    book.delete()
    return HttpResponseRedirect('/index')

