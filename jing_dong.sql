/*
Navicat MySQL Data Transfer

Source Server         : evil
Source Server Version : 50561
Source Host           : 192.168.0.113:3306
Source Database       : jing_dong

Target Server Type    : MYSQL
Target Server Version : 50561
File Encoding         : 65001

Date: 2018-10-10 16:15:48
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for goods
-- ----------------------------
DROP TABLE IF EXISTS `goods`;
CREATE TABLE `goods` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(150) NOT NULL,
  `cate_id` int(10) unsigned NOT NULL,
  `brand_id` int(10) unsigned NOT NULL,
  `price` decimal(10,3) NOT NULL DEFAULT '0.000',
  `is_show` bit(1) NOT NULL DEFAULT b'1',
  `is_saleoff` bit(1) NOT NULL DEFAULT b'0',
  PRIMARY KEY (`id`),
  KEY `cate_id` (`cate_id`),
  CONSTRAINT `goods_ibfk_1` FOREIGN KEY (`cate_id`) REFERENCES `goods_cates` (`id`),
  CONSTRAINT `goods_ibfk_2` FOREIGN KEY (`cate_id`) REFERENCES `goods_cates` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of goods
-- ----------------------------
INSERT INTO `goods` VALUES ('1', 'r510vc 15.6英寸笔记本', '5', '2', '3399.000', '', '\0');
INSERT INTO `goods` VALUES ('2', 'y400n 14.0英寸笔记本电脑', '5', '7', '4999.000', '', '\0');
INSERT INTO `goods` VALUES ('3', 'g150th 15.6英寸游戏本', '4', '9', '8499.000', '', '\0');
INSERT INTO `goods` VALUES ('4', 'x550cc 15.6英寸笔记本', '5', '2', '2799.000', '', '\0');
INSERT INTO `goods` VALUES ('5', 'x240 超极本', '7', '7', '4880.000', '', '\0');
INSERT INTO `goods` VALUES ('6', 'u330p 13.3英寸超极本', '7', '7', '4299.000', '', '\0');
INSERT INTO `goods` VALUES ('7', 'svp13226scb 触控超极本', '7', '6', '7999.000', '', '\0');
INSERT INTO `goods` VALUES ('8', 'ipad mini 7.9英寸平板电脑', '2', '8', '1998.000', '', '\0');
INSERT INTO `goods` VALUES ('9', 'ipad air 9.7英寸平板电脑', '2', '8', '3388.000', '', '\0');
INSERT INTO `goods` VALUES ('10', 'ipad mini 配备 retina 显示屏', '2', '8', '2788.000', '', '\0');
INSERT INTO `goods` VALUES ('11', 'ideacentre c340 20英寸一体电脑 ', '1', '7', '3499.000', '', '\0');
INSERT INTO `goods` VALUES ('12', 'vostro 3800-r1206 台式电脑', '1', '5', '2899.000', '', '\0');
INSERT INTO `goods` VALUES ('13', 'imac me086ch/a 21.5英寸一体电脑', '1', '8', '9188.000', '', '\0');
INSERT INTO `goods` VALUES ('14', 'at7-7414lp 台式电脑 linux ）', '1', '3', '3699.000', '', '\0');
INSERT INTO `goods` VALUES ('15', 'z220sff f4f06pa工作站', '3', '4', '4288.000', '', '\0');
INSERT INTO `goods` VALUES ('16', 'poweredge ii服务器', '3', '5', '5388.000', '', '\0');
INSERT INTO `goods` VALUES ('17', 'mac pro专业级台式电脑', '3', '8', '28888.000', '', '\0');
INSERT INTO `goods` VALUES ('18', 'hmz-t3w 头戴显示设备', '6', '6', '6999.000', '', '\0');
INSERT INTO `goods` VALUES ('19', '商务双肩背包', '6', '6', '99.000', '', '\0');
INSERT INTO `goods` VALUES ('20', 'x3250 m4机架式服务器', '3', '1', '6888.000', '', '\0');
INSERT INTO `goods` VALUES ('21', '商务双肩背包', '6', '6', '99.000', '', '\0');
INSERT INTO `goods` VALUES ('22', 'adk10英寸笔记本', '5', '2', '4399.000', '', '\0');

-- ----------------------------
-- Table structure for goods_brands
-- ----------------------------
DROP TABLE IF EXISTS `goods_brands`;
CREATE TABLE `goods_brands` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(40) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of goods_brands
-- ----------------------------
INSERT INTO `goods_brands` VALUES ('1', 'ibm');
INSERT INTO `goods_brands` VALUES ('2', '华硕');
INSERT INTO `goods_brands` VALUES ('3', '宏碁');
INSERT INTO `goods_brands` VALUES ('4', '惠普');
INSERT INTO `goods_brands` VALUES ('5', '戴尔');
INSERT INTO `goods_brands` VALUES ('6', '索尼');
INSERT INTO `goods_brands` VALUES ('7', '联想');
INSERT INTO `goods_brands` VALUES ('8', '苹果');
INSERT INTO `goods_brands` VALUES ('9', '雷神');
INSERT INTO `goods_brands` VALUES ('16', '海尔');
INSERT INTO `goods_brands` VALUES ('17', '清华同方');
INSERT INTO `goods_brands` VALUES ('18', '神舟');

-- ----------------------------
-- Table structure for goods_cates
-- ----------------------------
DROP TABLE IF EXISTS `goods_cates`;
CREATE TABLE `goods_cates` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(40) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of goods_cates
-- ----------------------------
INSERT INTO `goods_cates` VALUES ('1', '台式机');
INSERT INTO `goods_cates` VALUES ('2', '平板电脑');
INSERT INTO `goods_cates` VALUES ('3', '服务器/工作站');
INSERT INTO `goods_cates` VALUES ('4', '游戏本');
INSERT INTO `goods_cates` VALUES ('5', '笔记本');
INSERT INTO `goods_cates` VALUES ('6', '笔记本配件');
INSERT INTO `goods_cates` VALUES ('7', '超级本');
INSERT INTO `goods_cates` VALUES ('8', '路由器');
INSERT INTO `goods_cates` VALUES ('9', '交换机');
INSERT INTO `goods_cates` VALUES ('10', '网卡');
