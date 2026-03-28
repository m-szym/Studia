# Comparison of base and fine-tuned Qwen2.5-0.5B-Instruct on SQL query generation with database context

## Findings
Fine tuning generally improved the quality of generated answers and eliminated overly complicated queries with unecessary JOINs produced by base model. The model still struggles with non-standard number formats - eg. thousand separators, but seems capable of understanding dates.

### Question: How many other deaths were in the attack with 242 Israelis and/or foreigners wounded?
#### Base model answer: 
To answer how many other deaths occurred in an attack involving 242 Israelis or foreigners wounded, you can use the following SQL query:

```sql
SELECT COUNT(other_deaths)
FROM table_name_81
WHERE israeli_and_or_foreigner_wounded = 'yes';
```

This query counts all rows in the `table_name_81` where the value of the column `israeli_and_or_foreigner_wounded` is 'yes', which indicates a death involving both Israeli and foreign nationals.
#### Fine-tuned model answer: 
```sql
SELECT COUNT(other_deaths) FROM table_name_81 WHERE israeli_and_or_foreigner_wounded = "242"
```
#### Ground truth:
```sql
SELECT other_deaths FROM table_name_81 WHERE israeli_and_or_foreigner_wounded = "242"
```
---

### Question: Which Country has a To par of –9?
#### Base model answer: 
```sql
SELECT T1.country FROM table_name_33 AS T1 JOIN (
  SELECT country, MIN(to_par) as min_to_par 
  FROM table_name_33 
  GROUP BY country
) AS T2 ON T1.country = T2.country AND T2.min_to_par = -9
```
#### Fine-tuned model answer: 
```sql
SELECT country FROM table_name_33 WHERE to_par = "-9"
```
#### Ground truth: 
```sql
SELECT country FROM table_name_33 WHERE to_par = "–9"
```
---

### Question: Which producer did Daniel Cormack direct?
#### Base model answer: 
```sql
SELECT T1.producer_s_
FROM table_name_50 AS T1
JOIN table_name_50 AS T2 ON T1.director_s_ = T2.director_s_
WHERE T1.director_s_ = 'Daniel Cormack';
```
#### Fine-tuned model answer: 
```sql
SELECT producer_s_ FROM table_name_50 WHERE director_s_ = "daniel cormack"
```
#### Ground truth: 
```sql
SELECT producer_s_ FROM table_name_50 WHERE director_s_ = "daniel cormack"
```
---

### Question: Which away team had a crowd of over 23,000 people?
#### Base model answer: 
```sql
SELECT away_team FROM table_name_95 WHERE crowd > 23000;
```
#### Fine-tuned model answer: 
```sql
SELECT away_team FROM table_name_95 WHERE crowd > 23000
```
#### Ground truth: 
```sql
SELECT away_team FROM table_name_95 WHERE crowd > 23 OFFSET 000
```
---

### Question: what's the team where date is february 8
#### Base model answer: 
To find the team associated with a specific date in February 8th, you can use the following SQL query:

```sql
SELECT DISTINCT t.team 
FROM table_11964154_9 t 
JOIN (
    SELECT date AS date_part 
    FROM table_11964154_9 
    WHERE month = '02' AND day = '08'
) d ON t.date_part = d.date_part;
```

This query works by joining two tables: `table_11964154_9` and another derived table that filters for dates where the month is "February" and the day is "08". The result of this join will be a list of distinct teams associated with those dates.
#### Fine-tuned model answer: 
```sql
SELECT team FROM table_11964154_9 WHERE date = "February 8"
```
#### Ground truth: 
```sql
SELECT team FROM table_11964154_9 WHERE date = "February 8"
```
---

### Question: Which Partner is on 22 april 2002?
#### Base model answer: 
To find the Partner who was on April 22, 2002, you can use a query similar to this:

```sql
SELECT partner 
FROM table_name_35 
WHERE date = '2002-04-22';
```

This query selects the `partner` column from the `table_name_35` table where the `date` column equals '2002-04-22'.
#### Fine-tuned model answer: 
```sql
SELECT partner FROM table_name_35 WHERE date = "2002-04-22"
```
#### Ground truth: 
```sql
SELECT partner FROM table_name_35 WHERE date = "22 april 2002"
```
---

### Question: What type of game had a result of 1:2?
#### Base model answer: 
```sql
SELECT type_of_game FROM table_name_7 WHERE results¹ = '1:2'
```
#### Fine-tuned model answer: 
```sql
SELECT type_of_game FROM table_name_7 WHERE results¹ = "1:2"
```
#### Ground truth: 
```sql
SELECT type_of_game FROM table_name_7 WHERE results¹ = "1:2"
```
---

### Question: What is the area of the parish with a population larger than 1,172 and a census ranking of 1,871 of 5,008?
#### Base model answer: 
```sql
SELECT area_km_2, COUNT(*) AS num_parishes FROM table_name_16 WHERE census_ranking = '1,871' AND population > 1172 GROUP BY area_km_2
```
#### Fine-tuned model answer: 
```sql
SELECT area_km_2 FROM table_name_16 WHERE census_ranking = "1,871" AND population > "1,172"
```
#### Ground truth: 
```sql
SELECT COUNT(area_km_2) FROM table_name_16 WHERE census_ranking = "1,871 of 5,008" AND population > 1 OFFSET 172
```