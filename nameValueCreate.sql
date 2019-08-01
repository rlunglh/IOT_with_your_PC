CREATE TABLE `namevalue` (
  `Name` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Value` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;