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


USE master
GO
