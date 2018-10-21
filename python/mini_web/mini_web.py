import mini_web
import mini_mysql
import re

path_list = dict()
DB = mini_mysql.Mini_mysql("asd123", "stock_db")

def route(path):
	def call_fun(func):
		print("="*10, "以装饰")
		path_list[path] = func
		# func()

	return call_fun



@route("/center.html")
def center():
	data = get_file_data("./templates/center.html")
	# re.sub(r"\{%content%\}", , data)
	db_data = DB.execute("select * from info order by id;")
	print('查询成功')
	tmp = data.decode("utf-8")
	print(type(tmp))
	content = str()
	if db_data:
		print("==============center1===============")
		for item in db_data: 
			content += '''
		    <tr>
			    <th>%s</th>
			    <th>%s</th>
			    <th>%s</th>
			    <th>%s</th>
			    <th>%s(元)</th>
			    <th>%s</th>
			    <th style="color:red">hehe</th>
			    <th>nono</th>
			    <th>del</th>
			</tr>
			''' %(item[1], item[2], item[3], item[4], item[5], item[6])

		print(content)
		print("==============center2===============")
		tmp = re.sub(r"content1", content, tmp)
		# tmp.replace("content1", content)
		print("==============center3===============")

	print(tmp)
	data = bytes(tmp, encoding='utf8')
	print("==============center4===============")
	return data


@route("/index.html")
def index():
	data = get_file_data("./templates/index.html")
	db_data = DB.execute("select * from info order by id;")
	content = str()
	tmp = data.decode("utf-8")
	if db_data:
		for item in db_data:
			content += ''' 
			<tr>
		        <th>%s</th>
		        <th>%s</th>
		        <th>%s</th>
		        <th>%s</th>
		        <th>%s</th>
		        <th>%s(元)</th>
		        <th>%s</th>
		        <th>%s</th>
		        <th>添加自选</th>
		    </tr>
			''' %(item[0] ,item[1], item[2], item[3], item[4], item[5], item[6], item[7])

		tmp = re.sub(r"\{%content%\}", content, tmp)
		data = bytes(tmp, encoding='utf8')

	return data

def get_file_path(file):
	file_name = file
	if file == "/":
		file_name = "/index.html"
	# elif file == '/index.html':
	# 	return index()

	# elif file == '/center.html':
	# 	return center()

	# else:
	# 	return None
	try:
		data = path_list[file_name]()
	except Exception as e:
		print(e)
		return None
	else:
		return data
	


def get_file_data(file_path):
	try:
		file = open(file_path, "rb")
	except Exception as e:
		return None
	else:
		data = file.read()
		return data

def application(evn, call_fun):
	print(evn)
	data = get_file_path(evn['FILE_INFO'])
	status = ''
	if data:
		status = "200 OK"
	else:
		status = "403 ERROR"
		data = "没有该资源"
		data = bytes(data, encoding = "utf8")

	call_fun(status, "")
	return data