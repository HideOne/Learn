from pymysql import *	

class JD(object):
	def __init__(self):
		conn = connect(host = '192.168.0.113', port = 3306, user = 'root', passwd = 'asd123', db = 'jing_dong', charset = 'utf8')
		cursor = conn.cursor()
		self.cursor = cursor
		self.conn = conn


	def __del__(self):
		self.cursor.close()
		self.conn.close()


	@staticmethod
	def get_user_select():
		print("输入选择")
		print("1.所有商品")


	def get_all_brands(self):
		print("2.所有商品类型")
		print("3.所有商品品牌")
		print("4.退出程序")
		return input("请输入选择序号")


	def run_sql(self, sql):
		self.cursor.execute(sql)
		for item in self.cursor.fetchall():
			print(item)


	def get_all_item(self):
		sql = "select * from goods;"
		self.run_sql(sql)


	def get_all_kinds(self):
		sql = "select * from goods_cates;"
		self.run_sql(sql)	
		sql = "select * from goods_brands;"	
		self.run_sql(sql)


	def run(self):
		while True:
			num = self.get_user_select()
			if num == '1':
				self.get_all_item()

			elif num == '2':
				self.get_all_kinds()

			elif num == '3':
				self.get_all_brands()

			elif num == '4':
				print("谢谢使用!")
				break
			else:
				print("输入序号有误请重新输入")


def main():
	jd = JD()
	jd.run()


if __name__ == '__main__':
	main()