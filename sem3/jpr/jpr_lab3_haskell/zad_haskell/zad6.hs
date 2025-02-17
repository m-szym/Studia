
--Odwraca tablice tablic liczb
reverseList :: [[Int]] -> [[Int]]
reverseList [] = []
reverseList (x:xs) = reverseList xs ++ [x]

--Sprawdza czy liczby a, b, c tworzą trójkę pitagorejską
isPythagorean :: Int -> Int -> Int -> Bool
isPythagorean a b c = a ^ 2 + b ^ 2 == c ^ 2

--Generuje wszystkie trójki liczb od 1 do n, które tworzą trójkę pitagorejską
pythagoreanTriple :: Int -> [[Int]]
pythagoreanTriple 0 = []
pythagoreanTriple 1 = []
pythagoreanTriple 2 = []
pythagoreanTriple n = [x : y : [z] | x <- [1..n], y<-[1..n], z<-[1..n], isPythagorean x y z]

--Sprawdza czy suma elementów tablicy tab jest mniejsza lub równa n
checkSum :: [Int] -> Int -> Bool
checkSum tab n = if foldr (+) 0 tab <= n then True else False

--Sprawdza czy suma elementów tablicy tab jest równa n
checkEqual :: [Int] -> Int -> Bool
checkEqual tab n = if foldr (+) 0 tab == n then True else False

--Sprawdza czy wszystkie elementy tablicy tab są podzielne przez x
checkDivide :: [Int] -> Int -> Bool
checkDivide tab x = a 
    where a = foldr (+) 0 (map (`mod`x) tab) == 0

--Filtruje tablicę trójek pitagorejskich, usuwając z niej wszystkie tablice, które maja sumę elementów większą niż n
rightSizeTriple :: Int -> [[Int]] -> [[Int]]
rightSizeTriple n x = [y | y <- x, checkSum y n]

--Filtruje tablicę trójek pitagorejskich, usuwając z niej wszystkie tablice, które maja sumę elementów rózna od n
equalSizeTriple :: Int -> [[Int]] -> [[Int]]
equalSizeTriple n x = [y | y <- x, checkEqual y n]

--Zwraca wszystkie wspolne dzielniki trojki pitagorejskiej, ktorej wszystkie elementy sa nie wieksze od n
allDividers :: [Int] -> Int -> [Int]
allDividers tab n = [x | x <- [1..n] , checkDivide tab x]

--Sprawdza czy trójka pitagorejska jest względnie pierwsza
isFirst :: [Int] -> Int -> Bool
isFirst tab n = y 
    where y = if(allDividers tab n) == [1] then True else False

--Zwraca sumę elementów tablicy tab
sum3 :: [Int] -> Int
sum3 tab = foldr (+) 0 tab

--Zwraca z tablicy trójek pitagorejskich tę, której suma elementów jest największa
max3 :: [[Int]] -> Int
max3 tab = foldr max 0 (map sum3 tab)

--Odfiltrowuje z tablicy wszystkie trójki pitagorejskie, które nie są względnie pierwsze
firstTriple :: Int -> [[Int]] -> [[Int]]
firstTriple n x = [y | y <- x, isFirst y n]

--Zwraca wzglętnie pierwsze trójkę pitagorejskie, których suma elementów jest równa n
equalTriple :: Int -> [[Int]] 
equalTriple n = firstTriple n (equalSizeTriple n (pythagoreanTriple n))

--Zwraca względnie pierwsze trójki pitagorejskie, których suma elementów jest mniejsza lub równa n
lessTriple :: Int -> [[Int]] 
lessTriple n = reverseList(firstTriple n (rightSizeTriple n (pythagoreanTriple n)))

--Sprawdza czy istnieje względnie pierwsza trójka pitagorejska, której suma elementów jest równa n i jeśli istnieje to ją zwraca, jeśli nie to zwraca pierwszą trójkę pitagorejską, której suma elementów jest rowna m, gdzie m jest jak największe i m < n
finalResult :: Int -> [Int]
finalResult n = y 
    where y = if((equalTriple n) /=[]) then head(equalTriple n)  else head(equalTriple (max3 (lessTriple n)))


main :: IO ()
main = do
    print (finalResult 12)

    