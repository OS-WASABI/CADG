-- MySQL Script generated by MySQL Workbench
-- Sat Jan 19 11:11:47 2019
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema admin_db
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `admin_db` ;
-- -----------------------------------------------------
-- Schema admin_db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `admin_db` ;
-- -----------------------------------------------------
-- Schema cadg
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `cadg` ;
-- -----------------------------------------------------
-- Schema cadg
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `cadg` ;
-- -----------------------------------------------------
-- Schema test_db
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `test_db` ;
-- -----------------------------------------------------
-- Schema test_db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `test_db` ;

USE `admin_db` ;

-- -----------------------------------------------------
-- Table `admin_db`.`admin`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `admin_db`.`admin` ;

CREATE TABLE IF NOT EXISTS `admin_db`.`admin` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `first_name` VARCHAR(45) NOT NULL,
  `last_name` VARCHAR(45) NOT NULL,
  `username` VARCHAR(45) NOT NULL,
  `password` CHAR(64) NULL,
  `email` VARCHAR(100) NOT NULL,
  `phone` VARCHAR(45) NULL,
  `address` VARCHAR(255) NULL,
  `country` VARCHAR(45) NULL,
  `state_region` VARCHAR(45) NULL,
  `zip` VARCHAR(45) NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `userID_UNIQUE` (`id` ASC),
  UNIQUE INDEX `username_UNIQUE` (`username` ASC))
ENGINE = InnoDB
COMMENT = '				';

-- -----------------------------------------------------
-- Table `cadg`.`disseminator`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `cadg`.`disseminator` ;

CREATE TABLE IF NOT EXISTS `cadg`.`disseminator` (
  `disseminator_id` INT NOT NULL,
  `disseminator_name` VARCHAR(45) NULL,
  `disseminator_type` ENUM('CMSP') NULL,
  `message_format` ENUM('CMAC') NULL,
  `ip` VARCHAR(45) NULL,
  `port` INT NULL,
  `status` ENUM('ACTIVE', 'DISABLED') NULL,
  PRIMARY KEY (`disseminator_id`))
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `cadg`.`alert`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `cadg`.`alert` ;

CREATE TABLE IF NOT EXISTS `cadg`.`alert` (
  `alert_id` INT NOT NULL AUTO_INCREMENT,
  `identifier` VARCHAR(255) NOT NULL,
  `originator_id` INT NOT NULL,
  `message_type` ENUM('ACTUAL', 'EXERCISE', 'SYSTEM', 'TEST', 'DRAFT') NOT NULL,
  `scope` ENUM('PUBLIC', 'RESTRICTED', 'PRIVATE') NOT NULL,
  `status` ENUM('ACTIVE', 'CANCELED', 'EXPIRED') NOT NULL,
  `urgency` ENUM('IMMEDIATE', 'EXPECTED', 'FUTURE', 'PAST', 'UNKNOWN') NOT NULL,
  `severity` ENUM('EXTREME', 'SEVERE', 'MODERATE', 'MINOR', 'UNKNOWN') NOT NULL,
  `sent_time` VARCHAR(50) NOT NULL,
  `cap_xml` TEXT NOT NULL,
  PRIMARY KEY (`alert_id`),
  CONSTRAINT `alert_originator`
    FOREIGN KEY (`originator_id`)
    REFERENCES `cadg`.`originator` (`originator_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

CREATE INDEX `alert_originator_idx` ON `cadg`.`alert` (`originator_id` ASC) VISIBLE;

-- -----------------------------------------------------
-- Table `cadg`.`originator`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `cadg`.`originator` ;
                                  
USE `cadg` ;
                                  
CREATE TABLE IF NOT EXISTS `cadg`.`originator` (
  `originator_id` INT NOT NULL AUTO_INCREMENT,
  `originator_name` VARCHAR(45) NULL,
  `status` ENUM('ACTIVE', 'DISABLED') NULL,
  `agency` VARCHAR(45) NULL,
  PRIMARY KEY (`originator_id`))
ENGINE = InnoDB;

USE `test_db` ;

-- -----------------------------------------------------
-- Table `test_db`.`test`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `test_db`.`test` ;

CREATE TABLE IF NOT EXISTS `test_db`.`test` (
  `user_id` INT NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(120) NOT NULL,
  `password` VARCHAR(120) NOT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE INDEX `userID_UNIQUE` (`user_id` ASC),
  UNIQUE INDEX `username_UNIQUE` (`username` ASC))
ENGINE = InnoDB
COMMENT = '				';
       
SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
