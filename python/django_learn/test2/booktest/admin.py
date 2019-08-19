from django.contrib import admin
from booktest import models

# Register your models here.


class BookInfoAdmin(admin.ModelAdmin):
    list_display = ['b_tittle']


class HeroInfoAdmin(admin.ModelAdmin):
    '''在管理后台显示详细数据'''
    list_display = ['id', 'h_name', 'h_comment', 'h_book']
    # inlines = [BookInfoAdmin]


admin.site.register(models.HeroInfo, HeroInfoAdmin)
