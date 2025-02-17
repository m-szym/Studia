USE AstroDB
GO

SELECT * 
FROM AstroSchema.Stars
INNER JOIN AstroSchema.AstroObjects ON AstroObjectID = StarID
GO

SELECT COUNT(*) AS obj
FROM AstroSchema.AstroObjects
GO

SELECT COUNT(*) AS st
FROM AstroSchema.Stars
GO


ALTER TABLE AstroSchema.Planets NOCHECK CONSTRAINT FK__Planets__Orbitin__52593CB8;
DELETE
FROM AstroSchema.Stars
WHERE StarID = 'cok-1035'
ALTER TABLE AstroSchema.Planets CHECK CONSTRAINT FK__Planets__Orbitin__52593CB8;
GO



SELECT * 
FROM AstroSchema.Stars
INNER JOIN AstroSchema.AstroObjects ON AstroObjectID = StarID

GO


SELECT COUNT(*) AS obj
FROM AstroSchema.AstroObjects
GO

SELECT COUNT(*) AS st
FROM AstroSchema.Stars
GO



USE master
GO
