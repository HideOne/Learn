import mini_mysql
import pymysql


class Mini_mysql(object):
    def __init__(self, host="localhost", user="root", password="", db="", port=3306):
        print("==========创建数据库对象成功======")
        print(host, user, password, db, port)
        db = pymysql.connect(host=host, user=user, password=password,
                             db=db, port=port, charset="utf8")
        # 获得Cursor对象
        cursor = db.cursor()
        self._db = db
        self._cursor = cursor


    def __del__(self):
        print("=========数据库关闭=========")
        self._db.close()
        self._cursor.close()

    def __delattr__():
        print("=========数据库关闭=========")
        self._db.close()
        self._cursor.close()


    def execute(self, mind=""):
        print("=================1111")
        try:
            print("=================22222")
            cursor = self._cursor
            cursor.execute(mind)
        except Exception as e:
            print("=================33333")
            print(e)
            return None
        else:
            data = cursor.fetchall()
        
        return data



