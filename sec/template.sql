-- phpMyAdmin SQL Dump
-- version 4.7.4
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le :  ven. 13 avr. 2018 à 13:52
-- Version du serveur :  5.7.19
-- Version de PHP :  5.6.31

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `database_test`
--

-- --------------------------------------------------------

--
-- Structure de la table `scraping`
--

DROP TABLE IF EXISTS `scraping`;
CREATE TABLE IF NOT EXISTS `scraping` (
  `ID` varchar(100) NOT NULL,
  `filing_date` varchar(100) DEFAULT NULL,
  `accepted` varchar(100) DEFAULT NULL,
  `period_of_report` varchar(100) DEFAULT NULL,
  `owner_cik` varchar(100) DEFAULT NULL,
  `url` varchar(1000) DEFAULT NULL,
  `date_extract` datetime DEFAULT NULL,
  `issuerCik` varchar(100) DEFAULT NULL,
  `issuerName` varchar(100) DEFAULT NULL,
  `issuerTradingSymbol` varchar(100) DEFAULT NULL,
  `name1` varchar(100) DEFAULT NULL,
  `name2` varchar(100) DEFAULT NULL,
  `rptOwnerName` varchar(100) DEFAULT NULL,
  `isDirector` varchar(100) DEFAULT NULL,
  `isTenPercentOwner` varchar(100) DEFAULT NULL,
  `isOfficer` varchar(100) DEFAULT NULL,
  `isOther` varchar(100) DEFAULT NULL,
  `officerTitle` varchar(100) DEFAULT NULL,
  `rptOwnerStreet1` varchar(100) DEFAULT NULL,
  `rptOwnerCity` varchar(100) DEFAULT NULL,
  `rptOwnerState` varchar(100) DEFAULT NULL,
  `rptOwnerZipCode` varchar(100) DEFAULT NULL,
  `derivative` varchar(100) DEFAULT NULL,
  `securityTitle` varchar(100) DEFAULT NULL,
  `transactionDate` varchar(100) DEFAULT NULL,
  `transactionCode` varchar(100) DEFAULT NULL,
  `transactionAcquiredDisposedCode` varchar(100) DEFAULT NULL,
  `transactionShares` varchar(100) DEFAULT NULL,
  `transactionPricePerShare` varchar(100) DEFAULT NULL,
  `sharesOwnedFollowingTransaction` varchar(100) DEFAULT NULL,
  `directOrIndirectOwnership` varchar(100) DEFAULT NULL,
  `natureOfOwnership` varchar(100) DEFAULT NULL,
  `conversionOrExercisePrice` varchar(100) DEFAULT NULL,
  `deemedExecutionDate` varchar(100) DEFAULT NULL,
  `exerciseDate` varchar(100) DEFAULT NULL,
  `expirationDate` varchar(100) DEFAULT NULL,
  `underlyingSecurityTitle` varchar(100) DEFAULT NULL,
  `underlyingSecurityShares` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
