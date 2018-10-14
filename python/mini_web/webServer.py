import re
import socket
import threading
import mini_web

class webServer(object):
	"""docstring for webServer"""
	def __init__(self):
		print("=====服务器创建成功==========")
		listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		listen_socket.bind(("", 9999))
		listen_socket.listen(128)
		self.client_num = 0
		self._listen_socket = listen_socket
		self.evn = dict()


	def __del__(self):
		try:
			self._listen_socket.close()
		except Exception as e:
			print("释放服务器失败")


	def work_deal(self, client_socket, c_addr):
		# print(client_socket)
		print("==============work_deal ==============");
		

		recv_data = client_socket.recv(1024).decode("utf-8")
		lines = recv_data.splitlines()
		print(lines)
		# print(recv_data)
		if recv_data == '':
			print("==========客户端关闭============")
			client_socket.close()

		requre = re.match(r"[^/]+(/[^ ]*)", lines[0])
		# print(requre)	
		data = None

		if requre:
			data = requre.group(1)
			print(data)


		body = None
		if data.endswith(".html") or data == '/':
			self.evn["FILE_INFO"] = data
			body =  mini_web.application(self.evn, self.call_fun)
			header = "HTTP/1.1 %s OK\r\n" %self._status
			# header += self._header + "\r\rn"
			header += "Content-Type: text/html; charset=utf-8\r\n"
			header += "\r\n"
		else:
			print("=============./static%s" %data)
			header = "HTTP/1.1 %s OK\r\n" %200
			header += "\r\n"
			try:
				data = './static' + data
				file = open(data, "rb")
			except Exception as e:
				header = "HTTP/1.1 %s OK\r\n" %403
				header += "Content-Type: text/html; charset=utf-8\r\n"
				header += "\r\n"
				
				body = "没有该资源"
				body = bytes(body, encoding = "utf8")  
				print(e)
			else:
				print("=============./static%s" %data)
				body = file.read()

			
			# header += self._header + "\r\rn"
			
		

		# print(header + body)

		client_socket.send(header.encode("utf-8") + body)
		client_socket.close()


	def call_fun(self, status, header):
		self._status = status
		self._header = header
		print("="*10, "call back succuss")



	def run(self):
		print("=======服务器启动==========")
		while True:
			listen_socket = self._listen_socket
			client_socket, c_addr = listen_socket.accept()
			thread = threading.Thread(target=self.work_deal, args=(client_socket, c_addr))
			thread.start()

		



def main():
	server = webServer()
	server.run()


if __name__ == '__main__':
	main()