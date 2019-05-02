# Host: localhost  (Version: 5.5.53)
# Date: 2018-11-22 22:40:41
# Generator: MySQL-Front 5.3  (Build 4.234)

/*!40101 SET NAMES utf8 */;

#
# Structure for table "users"
#

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `password` varchar(255) DEFAULT NULL,
  `username` varchar(255) DEFAULT NULL,
  `follower` varchar(255) DEFAULT NULL,
  `following` varchar(255) DEFAULT NULL,
  `popularity` varchar(255) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

#
# Data for table "users"
#

/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'123456','yxr0168',NULL,NULL,0),(3,'123456','xinruiy2',NULL,NULL,0);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
