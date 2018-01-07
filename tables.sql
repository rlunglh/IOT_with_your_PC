CREATE TABLE `TimedWeather` (
  `TimedWeather_id` datetime NOT NULL,
  `AmbientIR` float DEFAULT NULL,
  `DewPoint` float DEFAULT NULL,
  `LUX` float DEFAULT NULL,
  `ObjectIR` float DEFAULT NULL,
  `PressureHg` float DEFAULT NULL,
  `RH` float DEFAULT NULL,
  `Temp` float DEFAULT NULL,
  PRIMARY KEY (`TimedWeather_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `Weather` (
  `Name` varchar(20) NOT NULL,
  `Value` varchar(64) NOT NULL DEFAULT '',
  PRIMARY KEY (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1
;