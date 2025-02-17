
--Odwraca listę liczb
reverseList :: [Int] -> [Int]
reverseList [] = []
reverseList (x:xs) = reverseList xs ++ [x]

--Generuje tablicę potęg 10 od 0 do m+1
generateTens :: Int -> Int -> [Int]
generateTens m p = zipWith (^) (replicate ((m+1)*p) 10) [ x | x<-[0..(m+1)*p-1]]

--Generuje tablicę liczb od 0 do m, gdzie kazda liczba jest powtórzona p razy.
generateDigits :: Int -> Int -> [Int]
generateDigits m p = map (`div`p) [x | x<-[0..(m+1)*p-1] ]

--Traktujac wynik 'generateDigits' jako cyfry w liczbie o podstawie 10, zwraca tę liczbę za pomoca tablicy zwroconej przez 'generateTens'
finalNumber :: Int -> Int -> Int
finalNumber m p = foldr (+) 0 (zipWith (*) (generateDigits m p) (generateTens m p))
 
--Zlicza wystąpienia liczby a w tablicy tab.
countN :: [Int] -> Int -> Int
countN tab a = length (filter (==a) tab)

--Rozbija liczbę na cyfry
rozbij :: Int -> [Int]
rozbij 0 = []
rozbij n = rozbij (n `div` 10) ++ [n `mod` 10]

--Filtruje tablicę tab, usuwając z niej wszystkie liczby, które zawierają więcej niż p wystąpień cyfry m.
filtruj :: Int  -> Int -> [Int] -> [Int]
filtruj m p tab = [x | x <- tab, countN (rozbij x) m <= p]

--Filtruje tablicę tab, usuwając z niej wszystkie liczby, które zawierają więcej niż p wystąpień cyfr od zera do m.
filtrCaly :: Int -> Int -> Int -> [Int] -> [Int]
filtrCaly a m p tab
  | a > 9 = tab
  | a < m = filtrCaly (a+1) m p (filtruj a p tab)
  | otherwise = filtrCaly (a+1) m 0 (filtruj a p tab)

--Generuje liczby o 0 do najwiekszej liczby mozliwej do uzyskania poprzez kombinacje cyfr od 0 do m, gdzie kazda cyfra jest powtórzona najwyzej p razy.
generuj :: Int -> Int -> [Int]
generuj m p = filtrCaly 0 m p [0..(finalNumber m p)]

--Wybiea n-ta liczbe z tablicy liczb wygenerowanej przez 'generuj'
final :: Int -> Int -> Int -> Int
final x m p = generuj m p !! (x-1)


main :: IO ()
main = do
    --print (generuj 2 2 ) )
    print (final 14 2 2)


