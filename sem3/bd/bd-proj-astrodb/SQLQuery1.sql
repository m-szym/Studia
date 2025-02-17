USE AstroDB
GO


SELECT *
FROM AstroSchema.AstroObjects
WHERE AstroObjectID NOT IN (SELECT DISTINCT AnomalyLocation 
                            FROM AstroSchema.Anomalies)
GO

-- ZnajdŸ 3 galaktyki spoœród znajduj¹cych siê w bazie, co do których 
-- znane jest najwiêcej systemów gwidznych do nich nale¿¹cych
SELECT TOP 3 G.GalaxyName, COUNT(S.SystemName) AS NumberOfSystems
FROM AstroSchema.Galaxies G
JOIN AstroSchema.Systems S ON G.GalaxyName = S.GalaxyName
GROUP BY G.GalaxyName
ORDER BY NumberOfSystems DESC
GO

-- ZnajdŸ znane planety typu oko³o-ziemskiego znajduj¹ce siê nie dalej ni¿ 
-- 2.000.000.000 lat œwietlnych od Ziemi
SELECT A.AstroObjectName, A.DistanceYL
FROM AstroSchema.Planets P
JOIN AstroSchema.AstroObjects A ON P.PlanetID = A.AstroObjectID
WHERE P.PlanetType = 'Terrestrial'
	AND A.DistanceYL < 2000000000
ORDER BY A.DistanceYL ASC
GO

-- Przeanalizuj liczbê znanych systemów gwiezdnych zale¿nie od ich typu
-- (wg. podzia³u opieraj¹cego siê na liczbie gwiazd tworz¹cych dany system)
-- oraz znajdŸ œredni¹ liczbê gwiazd w znanych systemach gwiezdnych
SELECT StarType, COUNT(*) AS NumberOfSystems
FROM AstroSchema.Systems
GROUP BY StarType
ORDER BY 
	CASE StarType
		WHEN 'Mono' THEN 1
		WHEN 'Binary' THEN 2
		WHEN 'Trinary' THEN 3
		WHEN 'Quaternary' THEN 4
		WHEN 'Multiple' THEN 5
		ELSE 6
	END

SELECT AVG(CAST(StarCount AS FLOAT)) AS AverageStarsPerSystem
FROM (
    SELECT COUNT(StarID) AS StarCount
    FROM AstroSchema.Systems
    JOIN AstroSchema.Stars ON Systems.SystemName = Stars.InSystem
    GROUP BY Systems.SystemName
) AS StarCounts
GO

-- Zlicz w ilu misjach bra³ udzia³ pracownik X 
-- (tutaj pracownik o numerze 40.045)
-- oraz liczbê misji, w których bra³ udzia³ najbardziej 
-- 'aktywny' pracownik
IF OBJECT_ID('tempdb..#temp', 'U') IS NOT NULL
DROP TABLE #temp

SELECT EmployeeID, COUNT(*) AS NumberOfAssignments
INTO #temp
FROM AstroSchema.StudyAssignments
GROUP BY EmployeeID
HAVING COUNT(*) > 1

SELECT '40045', *
FROM #temp
WHERE EmployeeID = 40045
UNION 
SELECT 'best', *
FROM (
		SELECT TOP 1 *
		FROM #temp
		ORDER BY NumberOfAssignments DESC) AS subquery
GO

-- Przygotuj do póŸniejszego u¿ycia (przygotuj widok zawieraj¹cy) dane dotycz¹ce
-- przydzia³ów poszczególnych pracowników do misji.
-- Zestaw powinien pozwalaæ na wskazanie prze³o¿onego ka¿dej misji
IF EXISTS (SELECT * FROM sys.views WHERE name = 'EmployeeAssignmentsView')
DROP VIEW AstroSchema.EmployeeAssignmentsView;
GO

CREATE VIEW AstroSchema.EmployeeAssignmentsView
AS SELECT *
	FROM (
		SELECT 
			S.StudyID, S.StudyStartDate, S.StudyEndDate,  
			E.*, 
			'No' AS Supervisor
		FROM AstroSchema.Studies AS S
		JOIN AstroSchema.StudyAssignments AS SA ON S.StudyID = SA.StudyID
		JOIN AstroSchema.Employees AS E ON SA.EmployeeID = E.EmployeeID
		UNION
		SELECT 
			S.StudyID, S.StudyStartDate, S.StudyEndDate,  
			E.*, 
			'Yes' AS Supervisor
		FROM AstroSchema.Studies AS S
		JOIN AstroSchema.Employees AS E ON S.StudySupervisor = E.EmployeeID) AS subquey
GO

SELECT * FROM AstroSchema.EmployeeAssignmentsView
GO

-- ZnajdŸ wszystkie uk³ady wchodz¹ce w sk³ad konstelacji Andromedy
-- oraz wszystkie (jeœli s¹ takie) galaktyki wchodz¹ce w sk³ad tej samej konstelacji
SELECT GalaxyName, 'Galaxy' AS 'Type'
FROM AstroSchema.Galaxies
WHERE ConstellationName = 'Andromeda'
UNION
SELECT SystemName, 'StarSystem' AS 'Type'
FROM AstroSchema.Systems
WHERE ConstellationName = 'Andromeda'
GO

-- ZnajdŸ znane anomalie, które nie zosta³y jeszcze przebadane 
-- i ¿adna misja nie ma na celu ich zbadania
-- TODO: dodaæ odp. inserty
SELECT A.*
FROM AstroSchema.Anomalies AS A
WHERE 
	AnomalyStatus = 'Open' AND
	AnomalyID NOT IN (SELECT AnomalyID
					  FROM AstroSchema.StudyStages)
GO

-- ZnajdŸ planety o masie przekraczj¹cej œredni¹ masê znanych planet
SELECT Planets.*, MassEM
FROM AstroSchema.Planets
JOIN AstroSchema.AstroObjects ON AstroObjectID = PlanetID
WHERE MassEM > (SELECT AVG(MassEM)
				FROM AstroSchema.AstroObjects
				WHERE AstroObjectID IN (SELECT PlanetID
										FROM AstroSchema.Planets)
				)
GO


USE master
GO
