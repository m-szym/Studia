USE master
GO
-- Create the new database if it does not exist already
IF DB_ID('AstroDB') IS NULL
CREATE DATABASE AstroDB
GO

USE AstroDB
GO


CREATE SCHEMA AstroSchema;
GO


CREATE TABLE AstroSchema.Constellations
(
    ConstellationName [NVARCHAR](30) NOT NULL PRIMARY KEY, 
    NameOrigin [NVARCHAR](250) NOT NULL,
    Declination INT 
        CHECK (Declination >= -180 AND Declination <= 180)
);
GO

CREATE TABLE AstroSchema.Galaxies
(
    GalaxyName [NVARCHAR](50) NOT NULL PRIMARY KEY, 
    GalaxyType [NVARCHAR](15) NOT NULL
        CHECK (GalaxyType IN ('Elliptical', 'Spiral', 'Lenticular', 'Irregular')),
    ConstellationName [NVARCHAR](30) NULL,
    FOREIGN KEY (ConstellationName) REFERENCES AstroSchema.Constellations(ConstellationName) 
        ON UPDATE CASCADE ON DELETE SET NULL,
    HostGalaxy [NVARCHAR](50) NULL,
    FOREIGN KEY (HostGalaxy) REFERENCES AstroSchema.Galaxies(GalaxyName) 
        ON UPDATE NO ACTION ON DELETE NO ACTION
);
GO

CREATE TRIGGER trg_UpdateHostGalaxyOnGalaxyDelete
ON AstroSchema.Galaxies
FOR DELETE
AS
BEGIN
    UPDATE AstroSchema.Galaxies
    SET HostGalaxy = NULL
    WHERE HostGalaxy IN (SELECT GalaxyName FROM deleted)
END
GO

CREATE TRIGGER trg_UpdateHostGalaxyOnUpdate
ON AstroSchema.Galaxies
FOR UPDATE
AS
BEGIN
    IF UPDATE(GalaxyName)
    BEGIN
        DECLARE @oldName NVARCHAR(50), @newName NVARCHAR(50);
        SELECT @oldName = GalaxyName FROM deleted;
        SELECT @newName = GalaxyName FROM inserted;
        UPDATE AstroSchema.Galaxies
        SET HostGalaxy = @newName
        WHERE HostGalaxy = @oldName
    END
END
GO

CREATE TABLE AstroSchema.Systems
(
    SystemName [NVARCHAR](20) NOT NULL PRIMARY KEY,
    StarType [NVARCHAR](10) NOT NULL
        CHECK (StarType IN ('Mono', 'Binary', 'Trinary', 'Quaternary', 'Multiple')),
    GalaxyName [NVARCHAR](50) NULL,
    FOREIGN KEY (GalaxyName) REFERENCES AstroSchema.Galaxies(GalaxyName) 
        ON DELETE SET NULL,
    ConstellationName [NVARCHAR](30) NULL,
    FOREIGN KEY (ConstellationName) REFERENCES AstroSchema.Constellations(ConstellationName) 
        ON DELETE SET NULL
);
GO

CREATE TABLE AstroSchema.AstroObjects
(
    AstroObjectID [NVARCHAR](10) NOT NULL PRIMARY KEY
		CHECK (AstroObjectID LIKE '[a-z][a-z][a-z]-[0-9][0-9][0-9][0-9]%'),
    AstroObjectName [NVARCHAR](20) NOT NULL,
    DistanceYL FLOAT NOT NULL 
        CHECK (DistanceYL >= 1 AND DistanceYL <= 46000000000),   
    MassEM FLOAT NOT NULL
        CHECK (MassEM >= 0.01 AND MassEM <= 99000000),
);
GO

CREATE TABLE AstroSchema.Stars
(
    StarID [NVARCHAR](10) NOT NULL PRIMARY KEY
		CHECK (StarID LIKE '[a-z][a-z][a-z]-[0-9][0-9][0-9][0-9]%'),
    FOREIGN KEY (StarID) REFERENCES AstroSchema.AstroObjects(AstroObjectID) 
        ON UPDATE CASCADE ON DELETE CASCADE,
    SpectralType [NVARCHAR](10) NOT NULL
        CHECK (SpectralType IN ('Ia-O', 'Ia', 'Ib', 'II', 'III', 'IV', 'V', 'VI', 'D')),
    InSystem [NVARCHAR](20) NOT NULL,
    FOREIGN KEY (InSystem) REFERENCES AstroSchema.Systems(SystemName) 
        ON UPDATE CASCADE ON DELETE CASCADE
);
GO

CREATE TRIGGER trg_DeleteAstroObjcetOnStarDelete
ON AstroSchema.Stars
FOR DELETE
AS
BEGIN
	DELETE
	FROM AstroObjects
	WHERE AstroObjectID IN (SELECT StarID FROM DELETED)
END
GO

CREATE TABLE AstroSchema.Planets
(
    PlanetID [NVARCHAR](10) NOT NULL PRIMARY KEY
		CHECK (PlanetID LIKE '[a-z][a-z][a-z]-[0-9][0-9][0-9][0-9]%'),
    FOREIGN KEY (PlanetID) REFERENCES AstroSchema.AstroObjects(AstroObjectID) 
        ON UPDATE CASCADE ON DELETE CASCADE,
    MassType [NVARCHAR](15) NOT NULL
        CHECK (MassType IN ('Gas Giant', 'Ice Giant', 'Mini-Neptune', 'Super-Earth', 'Super-Jupiter', 'Sub-Earth')),
    PlanetType [NVARCHAR](15) NOT NULL
        CHECK (PlanetType IN ('Chtonian', 'Carbon', 'Coreless', 'Desert', 'Gas dwarf', 'Gas giant', 'Helium', 'Hycean', 'Ice', 'Ocean', 'Protoplanet', 'Puffy', 'Silicate', 'Terrestrial')),
	OrbitingStar [NVARCHAR](10) NULL,
	FOREIGN KEY (OrbitingStar) REFERENCES AstroSchema.Stars(StarID)
		ON UPDATE NO ACTION ON DELETE NO ACTION,
    InGalaxy [NVARCHAR](50) NULL,
    CONSTRAINT FK_PlantOrbitingStar FOREIGN KEY (InGalaxy) REFERENCES AstroSchema.Galaxies(GalaxyName) 
        ON UPDATE CASCADE ON DELETE SET NULL
);
GO

CREATE TRIGGER trg_CheckPlanetNotStarOnPlanetInsert
ON AstroSchema.Planets
AFTER INSERT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM inserted WHERE PlanetID = OrbitingStar)
    BEGIN
        --RAISERROR ('PlanetID and StarID cannot be the same', 16, 1);
        ROLLBACK TRANSACTION;
        RETURN;
    END
END;
GO

CREATE TRIGGER trg_UpdateOrbitingPlanetsOnStarUpdate
ON AstroSchema.Stars
FOR UPDATE
AS
BEGIN
	IF UPDATE(StarID)
	BEGIN
        DECLARE @oldID NVARCHAR(10), @newID NVARCHAR(10);
        SELECT @oldID = StarID FROM deleted;
        SELECT @newID = StarID FROM inserted;
        UPDATE AstroSchema.Planets
        SET OrbitingStar = @newID
        WHERE OrbitingStar = @oldID
    END
END
GO


CREATE TRIGGER trg_DeleteOperation
ON AstroSchema.Stars
FOR DELETE
AS
BEGIN
    UPDATE AstroSchema.Planets
	SET OrbitingStar = NULL
    WHERE OrbitingStar IN (SELECT StarID FROM deleted)
END
GO


CREATE TRIGGER trg_DeleteAstroObjcetOnPlanetDelete
ON AstroSchema.Planets
FOR DELETE
AS
BEGIN
	DELETE
	FROM AstroObjects
	WHERE AstroObjectID IN (SELECT PlanetID FROM DELETED)
END
GO

-- Anomalies and studies

CREATE TABLE AstroSchema.Anomalies
(
    AnomalyID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    AnomalyStatus[NVARCHAR](15) NOT NULL
        CHECK (AnomalyStatus IN ('Open', 'Closed', 'In Progress')),
    AnomalyDescription [NVARCHAR](250) NOT NULL,
    AnomalyLocation [NVARCHAR](10) NULL,
    FOREIGN KEY (AnomalyLocation) REFERENCES AstroSchema.AstroObjects(AstroObjectID) 
        ON UPDATE CASCADE ON DELETE CASCADE
);


CREATE TABLE AstroSchema.Employees
(
    EmployeeID INT IDENTITY(40000,1) NOT NULL PRIMARY KEY
		CHECK (EmployeeID BETWEEN 40000 AND 50000),
    EmployeeName [NVARCHAR](50) NOT NULL,
    EmployeeSurname [NVARCHAR](50) NOT NULL
);
GO

CREATE TABLE AstroSchema.Studies
(
    StudyID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    StudyStartDate DATE NULL,
    StudyEndDate DATE NULL,
    StudySupervisor INT NULL,
    FOREIGN KEY (StudySupervisor) REFERENCES AstroSchema.Employees(EmployeeID) 
        ON UPDATE CASCADE ON DELETE SET NULL
);
GO

CREATE TABLE AstroSchema.StudyStages
(
    AnomalyID INT NOT NULL,
    FOREIGN KEY (AnomalyID) REFERENCES AstroSchema.Anomalies(AnomalyID) 
        ON UPDATE CASCADE ON DELETE CASCADE,
    StudyID INT NOT NULL,
    FOREIGN KEY (StudyID) REFERENCES AstroSchema.Studies(StudyID) 
        ON UPDATE CASCADE ON DELETE CASCADE,
    PRIMARY KEY (AnomalyID, StudyID),
    StageStartDate DATE NULL,
    StageEndDate DATE NULL
);
GO

CREATE TABLE AstroSchema.StudyAssignments
(
    StudyID INT NOT NULL,
    FOREIGN KEY (StudyID) REFERENCES AstroSchema.Studies(StudyID) 
        ON DELETE CASCADE,
    EmployeeID INT NOT NULL,
    FOREIGN KEY (EmployeeID) REFERENCES AstroSchema.Employees(EmployeeID) 
        ON UPDATE CASCADE ON DELETE CASCADE,
    PRIMARY KEY (StudyID, EmployeeID)
);

-- To avoid problems with other scripts, we switch back to master
USE master
GO

