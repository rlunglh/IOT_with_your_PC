CREATE TABLE `timedNameValue` (
  `TimedNameValue_id` datetime NOT NULL,
  `Name` nvarchar(64) DEFAULT NULL,
  `Value` nvarchar(64) DEFAULT NULL,
  PRIMARY KEY (`TimedNameValue_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;