-- Create a new database called 'AstroDB'
-- Connect to the 'master' database to run this snippet
USE master
GO
-- Create the new database if it does not exist already
IF NOT EXISTS (
    SELECT name
        FROM sys.databases
        WHERE name = N'AstroDB'
)
CREATE DATABASE AstroDB
GO

USE AstroDB
GO

IF SCHEMA_ID('AstroSchema') IS NOT NULL
    DROP SCHEMA AstroSchema;
GO

CREATE SCHEMA AstroSchema;
GO

-- Create the tables
IF OBJECT_ID('AstroSchema.Constellations', 'U') IS NOT NULL
DROP TABLE AstroSchema.Constellations
GO

CREATE TABLE AstroSchema.Constellations
(
    ConstellationName [NVARCHAR](30) NOT NULL PRIMARY KEY, 
    NameOrigin [NVARCHAR](250) NOT NULL,
    Declination INT CHECK (Declination >= -180 AND Declination <= 180)
);
GO

IF OBJECT_ID('AstroSchema.Galaxies', 'U') IS NOT NULL
DROP TABLE AstroSchema.Galaxies
GO

CREATE TABLE AstroSchema.Galaxies
(
    GalaxyName [NVARCHAR](50) NOT NULL PRIMARY KEY, 
    GalaxyType [NVARCHAR](15) NOT NULL
        CHECK (GalaxyType IN ('Elliptical', 'Spiral', 'Lenticular', 'Irregular')),
    ConstellationName [NVARCHAR](30) NULL,
    FOREIGN KEY (ConstellationName) REFERENCES AstroSchema.Constellations(ConstellationName) ON DELETE SET NULL,
    HostGalaxy [NVARCHAR](50) NULL,
    FOREIGN KEY (HostGalaxy) REFERENCES AstroSchema.Galaxies(GalaxyName) ON DELETE SET NULL
);
GO

IF OBJECT_ID('AstroSchema.Systems', 'U') IS NOT NULL
DROP TABLE AstroSchema.Systems
GO

CREATE TABLE AstroSchema.Systems
(
    SystemName [NVARCHAR](20) NOT NULL PRIMARY KEY,
    StarType [NVARCHAR](10) NOT NULL
        CHECK (StarType IN ('Mono', 'Binary', 'Trinary', 'Quaternary', 'Multiple')),
    GalaxyName [NVARCHAR](50) NULL,
    FOREIGN KEY (GalaxyName) REFERENCES AstroSchema.Galaxies(GalaxyName) ON DELETE SET NULL,
    ConstellationName [NVARCHAR](30) NULL,
    FOREIGN KEY (ConstellationName) REFERENCES AstroSchema.Constellations(ConstellationName) ON DELETE SET NULL
);
GO

IF OBJECT_ID('AstroSchema.AstroObjects', 'U') IS NOT NULL
DROP TABLE AstroSchema.AstroObjects
GO

CREATE TABLE AstroSchema.AstroObjects
(
    AstroObjectID [NVARCHAR](10) NOT NULL PRIMARY KEY,
    AstroObjectName [NVARCHAR](16) NOT NULL,
    DistanceYL INT NOT NULL 
        CHECK (DistanceYL >= 1 AND DistanceYL <= 100000),   -- TODO: fix ranges
    MassEM INT NOT NULL
        CHECK (MassEM >= 1 AND MassEM <= 100000),
);
GO

IF OBJECT_ID('AstroSchema.Stars', 'U') IS NOT NULL
DROP TABLE AstroSchema.Stars
GO

CREATE TABLE AstroSchema.Stars
(
    StarID [NVARCHAR](10) NOT NULL PRIMARY KEY,
    FOREIGN KEY (StarID) REFERENCES AstroSchema.AstroObjects(AstroObjectID) ON DELETE CASCADE,
    SpectralType [NVARCHAR](10) NOT NULL
        CHECK (SpectralType IN ('Ia-O', 'Ia', 'Ib', 'II', 'III', 'IV', 'V', 'VI', 'D')),
    InSystem [NVARCHAR](20) NOT NULL,
    FOREIGN KEY (InSystem) REFERENCES AstroSchema.Systems(SystemName) ON DELETE CASCADE
);
GO

IF OBJECT_ID('AstroSchema.Planets', 'U') IS NOT NULL
DROP TABLE AstroSchema.Planets
GO

CREATE TABLE AstroSchema.Planets
(
    PlanetID [NVARCHAR](10) NOT NULL PRIMARY KEY,
    FOREIGN KEY (PlanetID) REFERENCES AstroSchema.AstroObjects(AstroObjectID) ON DELETE CASCADE,
    MassType [NVARCHAR](10) NOT NULL
        CHECK (MassType IN ('Terrestrial', 'Gas Giant', 'Ice Giant', 'Dwarf', 'Exoplanet')),
    PlanetType [NVARCHAR](10) NOT NULL
        CHECK (PlanetType IN ('Rocky', 'Gas', 'Ice', 'Dwarf', 'Exoplanet')),
    InGalaxy [NVARCHAR](50) NULL,
    FOREIGN KEY (InGalaxy) REFERENCES AstroSchema.Galaxies(GalaxyName) ON DELETE SET NULL
);

-- Anomalies and studies

IF OBJECT_ID('AstroSchema.Anomalies', 'U') IS NOT NULL
DROP TABLE AstroSchema.Anomalies
GO

CREATE TABLE AstroSchema.Anomalies
(
    AnomalyID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    AnomalyStatus[NVARCHAR](10) NOT NULL
        CHECK (AnomalyStatus IN ('Open', 'Closed', 'In Progress')),
    AnomalyDescription [NVARCHAR](250) NOT NULL,
    AnomalyLocation [NVARCHAR](10) NULL,
    FOREIGN KEY (AnomalyLocation) REFERENCES AstroSchema.AstroObjects(AstroObjectID) ON DELETE CASCADE
);


IF OBJECT_ID('AstroSchema.Employees', 'U') IS NOT NULL
DROP TABLE AstroSchema.Employees
GO

CREATE TABLE AstroSchema.Employees
(
    EmployeeID INT IDENTITY(40000,1) NOT NULL PRIMARY KEY,
    EmployeeName [NVARCHAR](50) NOT NULL,
    EmployeeSurame [NVARCHAR](50) NOT NULL,
);
GO

IF OBJECT_ID('AstroSchema.Studies', 'U') IS NOT NULL
DROP TABLE AstroSchema.Studies
GO

CREATE TABLE AstroSchema.Studies
(
    StudyID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    StudyStartDate DATE NULL,
    StudyEndDate DATE NULL,
    StudySupervisor INT NULL,
    FOREIGN KEY (StudySupervisor) REFERENCES AstroSchema.Employees(EmployeeID) ON DELETE SET NULL
);
GO

IF OBJECT_ID('AstroSchema.StudyStages', 'U') IS NOT NULL
DROP TABLE AstroSchema.StudyStages
GO

CREATE TABLE AstroSchema.StudyStages
(
    AnomalyID INT NOT NULL,
    FOREIGN KEY (AnomalyID) REFERENCES AstroSchema.Anomalies(AnomalyID) ON DELETE CASCADE,
    StudyID INT NOT NULL,
    FOREIGN KEY (StudyID) REFERENCES AstroSchema.Studies(StudyID) ON DELETE CASCADE,
    PRIMARY KEY (AnomalyID, StudyID),
    StageStartDate DATE NULL,
    StageEndDate DATE NULL,
);
GO

IF OBJECT_ID('AstroSchema.StudyAssignments', 'U') IS NOT NULL
DROP TABLE AstroSchema.StudyAssignments
GO

CREATE TABLE AstroSchema.StudyAssignments
(
    StudyID INT NOT NULL,
    FOREIGN KEY (StudyID) REFERENCES AstroSchema.Studies(StudyID) ON DELETE CASCADE,
    EmployeeID INT NOT NULL,
    FOREIGN KEY (EmployeeID) REFERENCES AstroSchema.Employees(EmployeeID) ON DELETE CASCADE,
    PRIMARY KEY (StudyID, EmployeeID),
);




