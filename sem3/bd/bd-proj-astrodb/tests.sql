USE master
GO

IF DB_ID('AstroDB') IS NOT NULL
BEGIN
    USE AstroDB

    -- Test table creation
    SELECT * FROM AstroSchema.Constellations;
    SELECT * FROM AstroSchema.Galaxies;
    SELECT * FROM AstroSchema.Systems;
    SELECT * FROM AstroSchema.AstroObjects;
    SELECT * FROM AstroSchema.Stars;
    SELECT * FROM AstroSchema.Planets;
    SELECT * FROM AstroSchema.Anomalies;
    SELECT * FROM AstroSchema.Employees;
    SELECT * FROM AstroSchema.Studies;
    SELECT * FROM AstroSchema.StudyStages;
    SELECT * FROM AstroSchema.StudyAssignments;

END
GO

use master
GO