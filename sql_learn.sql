create table areas(
	aid int primary key,
	atitle varchar(20),
	pid int
);

select p.* from areas as p inner join areas c on p.pid=c.aid having c.atitle="四川省";
select * from areas where areas.pid=(select aid from areas where atitle="四川省");

select name, price from goods where cate_name="超级本";