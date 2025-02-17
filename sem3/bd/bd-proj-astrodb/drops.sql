IF DB_ID('AstroDB') IS NOT NULL
BEGIN
    USE AstroDB
      

    -- Table drops
    IF OBJECT_ID('AstroSchema.StudyAssignments', 'U') IS NOT NULL
    DROP TABLE AstroSchema.StudyAssignments
      

    IF OBJECT_ID('AstroSchema.StudyStages', 'U') IS NOT NULL
    DROP TABLE AstroSchema.StudyStages
      

    IF OBJECT_ID('AstroSchema.Studies', 'U') IS NOT NULL
    DROP TABLE AstroSchema.Studies
      

    IF OBJECT_ID('AstroSchema.Employees', 'U') IS NOT NULL
    DROP TABLE AstroSchema.Employees
      

    IF OBJECT_ID('AstroSchema.Anomalies', 'U') IS NOT NULL
    DROP TABLE AstroSchema.Anomalies
      

    IF OBJECT_ID('AstroSchema.Planets', 'U') IS NOT NULL
    DROP TABLE AstroSchema.Planets
      

    IF OBJECT_ID('AstroSchema.Stars', 'U') IS NOT NULL
    DROP TABLE AstroSchema.Stars
      

    IF OBJECT_ID('AstroSchema.AstroObjects', 'U') IS NOT NULL
    DROP TABLE AstroSchema.AstroObjects
      

    IF OBJECT_ID('AstroSchema.Systems', 'U') IS NOT NULL
    DROP TABLE AstroSchema.Systems
      

    IF OBJECT_ID('AstroSchema.Galaxies', 'U') IS NOT NULL
    DROP TABLE AstroSchema.Galaxies
      

    IF OBJECT_ID('AstroSchema.Constellations', 'U') IS NOT NULL
    DROP TABLE AstroSchema.Constellations
      

    -- Schema drops
    IF SCHEMA_ID('AstroSchema') IS NOT NULL
    DROP SCHEMA AstroSchema
      

    -- Database drops
    USE master
      

    -- Set the database to single-user mode
    ALTER DATABASE AstroDB SET SINGLE_USER WITH ROLLBACK IMMEDIATE;
    -- Drop the database
    DROP DATABASE AstroDB;
    
END
  