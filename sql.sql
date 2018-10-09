create table areas(
	aid int primary key,
	atitle varchar(20),
	pid int
);

select p.* from areas as p inner join areas c on p.pid=c.aid having c.atitle="四川省";