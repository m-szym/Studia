USE AstroDB
GO

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
ALTER TABLE AstroSchema.Planets NOCHECK CONSTRAINT FK__Planets__Orbitin__52593CB8;
DELETE
FROM AstroSchema.Systems
WHERE SystemName = @systemName
ALTER TABLE AstroSchema.Planets CHECK CONSTRAINT FK__Planets__Orbitin__52593CB8;

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

USE master
GO