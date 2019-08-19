CREATE DATABASE cloud_disk2 charset=utf8;

CREATE TABLE user (
	id BIGINT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR (128) NOT NULL,
	nickname VARCHAR (128) NOT NULL,
	password VARCHAR (128) NOT NULL,
	phone VARCHAR (15) NOT NULL,
	createtime VARCHAR (128),
	email VARCHAR (100),
	CONSTRAINT uq_nickname UNIQUE (nickname),
	CONSTRAINT uq_name UNIQUE (NAME)
);

-- CONSTRAINT uq_nickname UNIQUE (nickname),   表级唯一约束 给约束起名字 方便以后根据名字操作约束  uq_nickname 别名


--文件信息
CREATE TABLE file_info (
	md5 VARCHAR (200) NOT NULL PRIMARY KEY,
	file_id VARCHAR (256) NOT NULL,
	url VARCHAR (512) NOT NULL,
	size BIGINT,
	type VARCHAR (20),
	count INT
);

--用户文件列表
CREATE TABLE user_file_list (
	user VARCHAR (128) NOT NULL,
	md5 VARCHAR (200) NOT NULL,
	createtime VARCHAR (128),
	filename VARCHAR (128),
	shared_status INT,
	pv INT
);

--用户文件数量
CREATE TABLE user_file_count (
	user VARCHAR (128) NOT NULL PRIMARY KEY,
	count INT
);

--共享文件列表
CREATE TABLE share_file_list (
	user VARCHAR (128) NOT NULL,
	md5 VARCHAR (200) NOT NULL,
	createtime VARCHAR (128),
	filename VARCHAR (128),
	pv INT
);


INSERT INTO user VALUES (0, %s, %s, %s, %s, now(), %s);

alter table  user  AUTO_INCREMENT =1
