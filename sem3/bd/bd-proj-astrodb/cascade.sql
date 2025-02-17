USE AstroDB
GO

DECLARE @systemName [NVARCHAR](20)
DECLARE @newName [NVARCHAR](20)
SET @systemName = 'Rubiz'
SET @newName = 'UPDATE'

--Before any updates
SELECT SystemName, AstroObjectName StarName, StarID
FROM AstroSchema.Systems
INNER JOIN AstroSchema.Stars ON SystemName = InSystem
INNER JOIN AstroSchema.AstroObjects ON StarID = AstroObjectID
WHERE SystemName = @systemName
ORDER BY AstroObjectName

--Updating SystemName primary key - cascade expected on stars
UPDATE AstroSchema.Systems
SET SystemName = @newName
WHERE SystemName = @systemName

--After update 
SELECT SystemName, AstroObjectName StarName, StarID
FROM AstroSchema.Systems
INNER JOIN AstroSchema.Stars ON SystemName = InSystem
INNER JOIN AstroSchema.AstroObjects ON StarID = AstroObjectID
WHERE SystemName = @newName
ORDER BY AstroObjectName
GO

-- Cascade delete

DECLARE @systemName [NVARCHAR](20)
SET @systemName = 'UPDATE'

--Before any deletes
SELECT SystemName, AstroObjectName StarName, StarID
FROM AstroSchema.Systems
INNER JOIN AstroSchema.Stars ON SystemName = InSystem
INNER JOIN AstroSchema.AstroObjects ON StarID = AstroObjectID
WHERE SystemName = @systemName
ORDER BY AstroObjectName

SELECT COUNT(*) SystemsNr
FROM AstroSchema.Systems

SELECT COUNT(*) StarsNr
FROM AstroSchema.Stars

SELECT COUNT(*) AllAstroObjects
FROM AstroSchema.AstroObjects

SELECT COUNT(*) AstroObjectsOfStars
FROM AstroSchema.AstroObjects
INNER JOIN AstroSchema.Stars ON AstroObjectID = StarID

--Deleting system with @systemName primary key
-- in order to delete Star with orbiting Planets we need to temporarily disable foreign key constraint
-- on reference to the Star we want to delete
-- then a trigger fires setting the relevant fields of affected Planets to NULL
-- finally, we reenable the foreign key constraint
ALTER TABLE AstroSchema.Planets NOCHECK CONSTRAINT FK__Planets__Orbitin__5535A963;
DELETE
FROM AstroSchema.Systems
WHERE SystemName = @systemName
ALTER TABLE AstroSchema.Planets CHECK CONSTRAINT FK__Planets__Orbitin__5535A963;

--After delete 
-- are there any stars referencing the now deleted system ? 
SELECT SystemName, AstroObjectName StarName, StarID
FROM AstroSchema.Systems
INNER JOIN AstroSchema.Stars ON SystemName = InSystem
INNER JOIN AstroSchema.AstroObjects ON StarID = AstroObjectID
WHERE SystemName = @systemName
ORDER BY AstroObjectName
-- did the total number of Systems chang ?
SELECT COUNT(*) SystemsNr
FROM AstroSchema.Systems
-- were the proper Stars deleted ?
SELECT COUNT(*) StarsNr
FROM AstroSchema.Stars
-- did the total number of AstroObjects change ?
SELECT COUNT(*) AllAstroObjects
FROM AstroSchema.AstroObjects
-- were only the proper AstroObjects of deleted Stars removed ?
SELECT COUNT(*) AstroObjectsOfStars
FROM AstroSchema.AstroObjects
INNER JOIN AstroSchema.Stars ON AstroObjectID = StarID
GO

--Alt DELETE CASCADE
DECLARE @empName [NVARCHAR](50);
DECLARE @empSurname [NVARCHAR](50);
SET @empName = 'Alec';
SET @empSurname = 'Reinhart';

SELECT * FROM AstroSchema.StudyAssignments
WHERE EmployeeID = (SELECT EmployeeID FROM AstroSchema.Employees 
					WHERE EmployeeName = @empName AND EmployeeSurname = @empSurname)

SELECT COUNT(*) AllStudyAssignments FROM AstroSchema.StudyAssignments

SELECT * FROM AstroSchema.Studies
WHERE StudySupervisor = (SELECT EmployeeID FROM AstroSchema.Employees 
					WHERE EmployeeName = @empName AND EmployeeSurname = @empSurname)

SELECT COUNT(*) AllStudies FROM AstroSchema.Studies


--=================================================================================
DELETE
FROM AstroSchema.Employees
WHERE EmployeeID = (SELECT EmployeeID FROM AstroSchema.Employees 
					WHERE EmployeeName = @empName AND EmployeeSurname = @empSurname)
--=================================================================================

SELECT * FROM AstroSchema.StudyAssignments
WHERE EmployeeID = (SELECT EmployeeID FROM AstroSchema.Employees 
					WHERE EmployeeName = @empName AND EmployeeSurname = @empSurname)

SELECT COUNT(*) AllStudyAssignments FROM AstroSchema.StudyAssignments

SELECT * FROM AstroSchema.Studies
WHERE StudySupervisor = (SELECT EmployeeID FROM AstroSchema.Employees 
					WHERE EmployeeName = @empName AND EmployeeSurname = @empSurname)

SELECT COUNT(*) AllStudies FROM AstroSchema.Studies

USE master
GO
