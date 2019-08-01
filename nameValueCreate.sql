CREATE TABLE `namevalue` (
  `Name` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Value` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
CREATE TABLE `timedNameValue` (
  `TimedNameValue_id` datetime NOT NULL,
  `Name` nvarchar(64) DEFAULT NULL,
  `Value` nvarchar(64) DEFAULT NULL,
  PRIMARY KEY (`TimedNameValue_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;