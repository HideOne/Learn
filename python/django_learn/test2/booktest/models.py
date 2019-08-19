from django.db import models
import datetime
# Create your models here.
class BookInfo(models.Model):
    '''图书模型类'''
    # 图书名
    b_tittle = models.CharField(max_length=20)

    # 出版日期
    b_date = models.DateField(default=datetime.date(1996, 1, 1))

    # 阅读量
    b_read_count = models.IntegerField(default=0)

    # 评论数
    b_comment = models.IntegerField(default=0)

    # 是否删除
    b_isDel = models.BooleanField(default=False)


class HeroInfo(models.Model):
    '''英雄人物模型类'''
    # 姓名
    h_name = models.CharField(max_length=20)

    # 性别 0 男 1.女 2.未知
    h_gender = models.IntegerField(default=0)

    # 备注
    h_comment = models.CharField(max_length=200)

    # 关系属性
    h_book = models.ForeignKey('BookInfo', on_delete=models.CASCADE)

    # 是否删除
    h_isDel = models.BooleanField(default=False)




