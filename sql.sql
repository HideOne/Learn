create table areas(
	aid int primary key,
	atitle varchar(20),
	pid int
);

select p.* from areas as p inner join areas c on p.pid=c.aid having c.atitle="四川省";
select * from areas where areas.pid=(select aid from areas where atitle="四川省");

select name, price from goods where cate_name="超级本";

-- 显示商品的种类
select cate_name from goods group by cate_name;

-- 求所有电脑产品的平均价格,并且保留两位小数
select cate_name, round(avg(price), 2) from goods group by cate_name;

select max(price), min(price), avg(price), count(*) from goods;

-- 查询所有价格大于平均价格的商品，并且按价格降序排序
select * from goods where price > (select avg(price) from goods) order by price desc;

-- 查询每种类型中最贵的电脑信息

 select goods.* from goods inner join (
 	select cate_name, max(price) as max_price from goods group by cate_name
 	) 
 	as tmp on tmp.cate_name=goods.cate_name and goods.price=tmp.max_price;

 	insert into goods_cates (name) select cate_name from goods group by cate_name;

 	update goods as g inner join goods_cates on g.cate_name=goods_cates.name set g.cate_name = goods_cates.id;



alter table goods change cate_name cate_id int unsigned not null;

alter table goods add foreign key (cate_id) references goods_cates(id);

-- 外键
insert into goods values(0,'adk10英寸笔记本', 5, '华硕','4399',default,default);