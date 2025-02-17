import random
import string

with open('namelist.txt', 'r') as f:
    names = f.read().splitlines()
f.close()

for name in names:
    name.lstrip()


galaxies = [
        'Andromeda',
        'Messier 110',
        'Maffei 1',
        'Maffei 2',
        'Triangulum',
        'IC 10',
        'IC 1613',
        'Sextans A',
        'Sextans B',
        'NGC 185',
        'NGC 147',
        'Barnards Galaxy',
        'Milky Way',
        'Large Magellanic Cloud',
        'Small Magellanic Cloud',
        'Leo I',
        'Leo II',
        'Segue 1',
        'Draco Dwarf',
        'Fornax Dwarf',
        'Wolf-Lundmark-Melotte'
]
constellations = [
        'Andromeda', 
        'Aquarius', 
        'Aquila',
        'Ara', 
        'Aries',
        'Auriga',
        'Bootes',
        'Caelum',
        'Camelopardalis',
        'Cancer', 
        'Canes Venatici', 
        'Canis Major', 
        'Canis Minor', 
        'Capricornus', 
        'Carina', 
        'Cassiopeia', 
        'Centaurus', 
        'Cepheus', 
        'Cetus', 
        'Chamaeleon', 
        'Circinus', 
        'Columba', 
        'Coma Berenices', 
        'Corona Australis', 
        'Corona Borealis', 
        'Corvus', 
        'Crater', 
        'Crux', 
        'Cygnus', 
        'Delphinus', 
        'Dorado', 
        'Draco', 
        'Equuleus', 
        'Eridanus', 
        'Fornax', 
        'Gemini', 
        'Grus', 
        'Hercules', 
        'Horologium', 
        'Hydra', 
        'Hydrus', 
        'Indus', 
        'Lacerta', 
        'Leo', 
        'Triangulum', 
        'Tucana', 
        'Ursa Major', 
        'Ursa Minor', 
        'Vela', 
        'Virgo', 
        'Volans', 
        'Vulpecula', 
        'Saggittarius', 
        'Scorpius', 
        'Sculptor', 
        'Scutum', 
        'Serpens', 
        'Sextans',
]
anomalies = [
    'Strange sattaellite of unknown origin',
    'Huge asteroid, possibly rich in minerals',
    'Unknown object, possibly an automated probe or a ship spotted nearby',
    'Abnormal energy readings',
    'Unusual gravitational readings',
    'Unique electromagnetic readings',
    'Unidentified electromagnetic sygnals detected',
    'Automated probe lost contact with the base, reason unknown',
    'Possible subsurface ocean detected',
    'Huge imapct crater left by unknown source detected',
    'Unusual magnetic field detected',
    'This body has a very eccentric orbit',
    'This body has a very unusual composition',
    'A distress signal was detected form this location',
    'Contact with exploration team was lost, reason unknown',
    'What may possibly be an aritificial structure was detected orbiting the body',
    'Stange waves of unknown origin sweep surface of this body regularly',
    'Unusually low temperature detected',
    'Unusually high temperature detected',
    'Unusually low amount of minerals detected',
]


astro_objects = []

def rand_prefix():
    prefix = ''
    for i in range(3):
        prefix += random.choice(string.ascii_lowercase)
    prefix += '-'
    return prefix


def rand_sytem(out_file):
    name = random.choice(names)
    names.pop(names.index(name))
    stype = random.choice(['Mono', 'Binary','Mono', 'Binary','Mono', 'Binary', 'Trinary','Mono', 'Binary', 'Trinary', 'Mono', 'Binary', 'Trinary', 'Quaternary', 'Multiple'])

    r = random.randint(0, 100)
    if r == 0:
        galaxy = 'NULL'
        const = 'NULL'
    elif r <= 10:
        galaxy = 'NULL'
        const = '(SELECT ConstellationName FROM AstroSchema.Constellations WHERE ConstellationName = \'' + random.choice(constellations) + '\')'
    elif r <= 40:
        galaxy = '(SELECT GalaxyName FROM AstroSchema.Galaxies WHERE GalaxyName = \'' + random.choice(galaxies) + '\')'
        const = 'NULL'
    else:
        real_galaxy = random.choice(galaxies)
        galaxy = '(SELECT GalaxyName FROM AstroSchema.Galaxies WHERE GalaxyName = \'' + real_galaxy + '\')'
        const = '(SELECT ConstellationName FROM AstroSchema.Galaxies WHERE GalaxyName = \'' + real_galaxy + '\')'
        
    system_insert = 'INSERT INTO AstroSchema.Systems VALUES (\'' + name + '\', \'' + stype + '\', ' + galaxy + ', ' +  const + ');\n'
    #print(system_insert, end='')
    out_file.write(system_insert)

    if stype == 'Mono':
        rand_star(out_file, name, -1)
    elif stype == 'Binary':
        for i in range(2):
            rand_star(out_file, name, i)
    elif stype == 'Trinary':
        for i in range(3):
            rand_star(out_file, name, i)
    elif stype == 'Quaternary':
        for i in range(4):
            rand_star(out_file, name, i)
    elif stype == 'Multiple':
        for i in range(random.randint(2, 7)):
            rand_star(out_file, name, i)


def rand_star_obj(out_file, id, name):
    astro_objects.append(name)

    dist = round(random.uniform(1, 46000000000), 1)
    mass = round(random.uniform(26000, 99000000), 1)

    star_obj_insert = 'INSERT INTO AstroSchema.AstroObjects VALUES (\'' + id + '\', \'' + name + '\', ' + str(dist) + ', ' + str(mass) + ');\n'
    #print(star_obj_insert, end='')
    out_file.write(star_obj_insert)


def rand_star(out_file, system, n):
    id = rand_prefix() + str(random.randint(1000, 9999))
    name = system
    if n != -1:
        name += '-' + string.ascii_uppercase[n]
    stype = random.choice(['Ia-O', 'Ia', 'Ib', 'II', 'III', 'IV', 'V', 'VI', 'D'])

    rand_star_obj(out_file, id, name)

    star_insert = 'INSERT INTO AstroSchema.Stars VALUES (\'' + id + '\', \'' + stype + '\', \'' + system + '\');\n'
    #print(star_insert, end='')
    out_file.write(star_insert)

    if random.randint(0,3) != 0:
        for i in range(random.choice((1,1,1,1,2,2,2,3,3,3,4,4,5,5,6,7,8,9,10))):
            rand_planet(out_file, name, id, i)


def rand_planet_obj(out_file, id, name):
    astro_objects.append(name)

    dist = round(random.uniform(1, 46000000000), 1)
    mass = round(random.uniform(0.01, 1500), 1)

    planet_obj_insert = 'INSERT INTO AstroSchema.AstroObjects VALUES (\'' + id + '\', \'' + name + '\', ' + str(dist) + ', ' + str(mass) + ');\n'
    #print(planet_obj_insert, end='')
    out_file.write(planet_obj_insert)


def rand_planet(out_file, star_name, star_id=None, n=-1):
    id = rand_prefix() + str(random.randint(1000, 9999))
    name = star_name
    if n != -1:
        name += '-' + str(n)
    mtype = random.choice(('Gas Giant', 'Ice Giant', 'Mini-Neptune', 'Super-Earth', 'Super-Jupiter', 'Sub-Earth'))   
    ptype = random.choice(('Chtonian', 'Carbon', 'Coreless', 'Desert', 'Gas dwarf', 'Gas giant', 'Helium', 'Hycean', 'Ice', 'Ocean', 'Protoplanet', 'Puffy', 'Silicate', 'Terrestrial'))

    rand_planet_obj(out_file, id, name)

    if star_id is not None:
        galaxy = '(SELECT GalaxyName FROM AstroSchema.Systems, AstroSchema.Stars WHERE StarID = \'' + star_id + '\' AND SystemName = InSystem)'     
    else:
        galaxy = 'NULL'

    star = '(SELECT StarID FROM AstroSchema.Stars WHERE StarID = \'' + star_id + '\')'

    planet_insert = 'INSERT INTO AstroSchema.Planets VALUES (\'' + id + '\', \'' + mtype + '\', \'' + ptype + '\', ' + star + ', ' + galaxy + ');\n'
    #print(planet_insert, end='')
    out_file.write(planet_insert)


with open('fnames.txt', 'r') as f:
    fnames = f.read().split()
f.close()

with open('snames.txt', 'r') as f:
    snames = f.read().split()
f.close()

emps = []

def rand_employee(out_file):
    fname = random.choice(fnames)
    lname = random.choice(snames)
    emps.append((fname, lname))

    emp_insert = 'INSERT INTO AstroSchema.Employees (EmployeeName, EmployeeSurname) VALUES (\'' + fname + '\', \'' + lname + '\');\n'
    #print(emp_insert, end='')
    out_file.write(emp_insert)

def select_rand_employee():
    emp = random.choice(emps)
    emp_select = '(SELECT EmployeeID FROM AstroSchema.Employees WHERE EmployeeName = \'' + emp[0] + '\' AND EmployeeSurname = \'' + emp[1] + '\')'
    #print(emp_select, end='')
    return emp_select


def rand_date():
    year = random.randint(2120, 2150)
    month = random.randint(1, 12)
    day = random.randint(1, 28)

    year = str(year)

    if month < 10:
        month = str(month).zfill(2)
    else:
        month = str(month)
    
    if day < 10:
        day = str(day).zfill(2)
    else:
        day = str(day)

    return year + '-' + month + '-' + day


def date_greater(date1, date2):
    d1 = date1.split('-')
    d2 = date2.split('-')
    for i in range(3):
        d1[i] = int(d1[i])
        d2[i] = int(d2[i])
    if d1[0] > d2[0]:
        return True
    elif d1[0] == d2[0]:
        if d1[1] > d2[1]:
            return True
        elif d1[1] == d2[1]:
            if d1[2] > d2[2]:
                return True
    return False


def rand_not_lower_date(date):
    d = rand_date()
    while date_greater(date, d):
        d = rand_date()
    return d

def rand_not_greater_date(date):
    d = rand_date()
    while date_greater(d, date):
        d = rand_date()
    return d

def rand_study(out_file):
    sdate = rand_date()
    edate = rand_not_lower_date(sdate)
    supervisor_select = select_rand_employee()

    study_insert = 'INSERT INTO AstroSchema.Studies (StudyStartDate, StudyEndDate, StudySupervisor) VALUES (\'' + sdate + '\', \'' + edate + '\', ' + supervisor_select + ');\n'
    #print(study_insert, end='')
    out_file.write(study_insert)
    #print(update_id_var('@studyID'), end='')
    out_file.write(update_id_var('@studyID'))

    for i in range(random.randint(1, 5)):
        rand_study_stage(out_file, sdate, edate)
        # rand_study_assingment(out_file)

    for i in range(random.randint(1, 5)):
        rand_study_assingment(out_file)

# DECLARE @studyID INT;
# DECLARE @anomalyID INT;
    
def update_id_var(var_name):
    update_str = 'SET ' + var_name + ' = SCOPE_IDENTITY();\n'
    #print(update_str, end='')
    return update_str

def rand_study_assingment(out_file):
    employee_select = select_rand_employee()
    study_assignment_insert = 'INSERT INTO AstroSchema.StudyAssignments (StudyID, EmployeeID) VALUES (@studyID, ' + employee_select + ');\n'
    #print(study_assignment_insert, end='')
    out_file.write(study_assignment_insert)


def rand_anomaly(out_file):
    obj_select = '(SELECT AstroObjectID FROM AstroSchema.AstroObjects WHERE AstroObjectName = \'' + random.choice(astro_objects) + '\')'
    status = random.choice(('Open', 'Closed', 'In Progress'))
    desc = random.choice(anomalies)
    anomaly_insert = 'INSERT INTO AstroSchema.Anomalies (AnomalyStatus, AnomalyDescription, AnomalyLocation) VALUES (\'' + status + '\', \'' + desc + '\', ' + obj_select + ');\n'
    #print(anomaly_insert, end='')
    out_file.write(anomaly_insert)


def rand_study_stage(out_file, ssdate, sedate):
    sdate = rand_not_greater_date(ssdate)
    edate = rand_not_lower_date(sedate)

    rand_anomaly(out_file)

    #print(update_id_var('@anomalyID'), end='')
    out_file.write(update_id_var('@anomalyID'))
    study_stage_insert = 'INSERT INTO AstroSchema.StudyStages (StudyID, AnomalyID, StageStartDate, StageEndDate) VALUES (@studyID, @anomalyID, \'' + sdate + '\', \'' + edate + '\');\n'
    #print(study_stage_insert, end='')
    out_file.write(study_stage_insert)



#big test
#print('\t\t--SYSTEM++')
#rand_sytem('systems.txt') 
#print('\n\n')   
#print('\n\n\t\t--EMPLOYEES')
#for i in range(10):
#    rand_employee('employees.txt')
#print('\n\n\t\t--STUDIES++')
#print('\n\n')
#print('DECLARE @studyID INT;')
#print('DECLARE @anomalyID INT;')
#rand_study('studies.txt')

#dump 
out_f = open('insert6.txt', 'w')

for i in range(200):
    rand_sytem(out_f)

for i in range(300):
    rand_employee(out_f)

out_f.write('DECLARE @studyID INT;')
out_f.write('DECLARE @anomalyID INT;')

for i in range(100):
    rand_study(out_f)