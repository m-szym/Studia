

--Otrzymuje tablice liczb i łączy ją kolejno z kadą liczbą od 0 do p, otrzymując tablicę p+1 tablic liczb
permm :: [Int] -> Int -> Int -> [[Int]]
permm tab a p = ans
    where ans = if a <= p then [tab ++ [a]] ++ permm tab (a+1) p else [] 

--Otrzymuje tablicę tablic liczb i dla kadej z nich wywołuje 'permm', łącząc otrzymane wyniki w jedną tablicę tablic liczb.
d :: [[Int]] -> Int -> Int -> Int -> [[Int]]
d tab length a m = ans 
    where ans = if a<length then (permm (tab!!a) 0 m) ++ d tab length (a+1) m else []

--Generuje wszystkie size-elementowe permutacje tablic liczb otrzymanych w tablicy tab i zwraca jako tablicę tablic liczb.
n_elm_permm :: [[Int]] -> Int -> Int -> [[Int]]
n_elm_permm tab 1 a = tab
n_elm_permm tab size a = res 
    where res = if a<(size-1) then d (n_elm_permm tab size (a+1)) ((length tab)^(size-a)) 0 ((length tab)-1) else d tab ((length tab)^(size-a)) 0 ((length tab)-1)

--Generuje wszystkie permutacje rozmiaru <=size tablic liczb otrzymanych w tablicy digits i zwraca jako tablicę tablic liczb.
perm_wrapper :: [[Int]] -> [[Int]] -> Int -> Int-> [[Int]]
perm_wrapper tab digits size a = res 
    where res = if a>size then tab else tab ++ n_elm_permm digits a 1 ++ perm_wrapper tab digits size (a+1)

--Zlicza wystąpienia liczby a w tablicy tab.
countN :: [Int] -> Int -> Int
countN tab a = length (filter (==a) tab)

--Filtruje tablicę tab, usuwając z niej wszystkie tablice, które zawierają więcej niż p wystąpień liczby m.
filtruj :: Int  -> Int -> [[Int]] -> [[Int]]
filtruj m p tab = [x | x <- tab, countN x m <= p]

--Filtruje tablicę tab, usuwając z niej wszystkie tablice, które zawierają więcej niż p wystąpień liczby x, dla x nalezącego do <0, m>.
filtrCaly :: Int -> Int -> Int -> [[Int]] -> [[Int]]
filtrCaly a m p tab
  | a > 9 = tab
  | a < m = filtrCaly (a+1) m p (filtruj a p tab)
  | otherwise = filtrCaly (a+1) m 0 (filtruj a p tab)

--Odwraca tablicę tablic tab.
reverseListOfLists :: [[Int]] -> [[Int]]
reverseListOfLists [] = []
reverseListOfLists (x:xs) = reverseListOfLists xs ++ [x]

--Porównuje i zamienia miejscami dwa elementy w tablicy tab (tab jest tutaj tablicą tablic liczb, tablice porówynywane są leksykograficznie) 
--i zwraca tablicę, w której te elementy są w poprawnej kolejności
swap :: [[Int]] -> Int -> [[Int]]
swap tab a = ans
    where ans = if tab!!a > tab!!(a+1) then [tab!!(a+1), tab!!a] else [tab!!a, tab!!(a+1)]

--Odpowiednik wewenętrznej pętli sortowania bąbelkowego
inner_sort :: [[Int]] -> [[Int]] -> Int ->[[Int]]
inner_sort buffer tab a = ans
    where ans = if a>=(length tab)-1 then buffer else buffer ++ (swap tab a) ++ (inner_sort buffer tab (a+2))

--Odpowiednik zewnętrznej pętli sortowania bąbelkowego
outer_sort :: [[Int]] -> Int -> [[Int]]
outer_sort tab a = ans
    where ans = if a>=(length tab)*2 then tab else if (a`mod`2)==0 then outer_sort (inner_sort [] tab 0) (a+1) else outer_sort( [head(tab)] ++ (inner_sort [] tab 1) ++ [head(reverseListOfLists tab)])(a+1)

--Usuwa pierwszy elelment tablicy
removeHead :: [[Int]] -> [[Int]]
removeHead [] = []
removeHead tab = tail tab

--Sortuje bąbelkowo, dla tablic długości nieparzystej dodaje pusty element, poniważ nasze sortowanie bąbelkowe nie działa dla tablic nieparzystych 
--(z powodu wykonywania skoku ,,co dwa" w wewnętrznej pętli).
sort :: [[Int]] -> [[Int]]
sort tab = ans 
    where ans = if (length tab)`mod`2 == 0 then outer_sort tab 0 else removeHead (outer_sort (tab ++ [[]]) 0)


--Generuje tablicę tablic liczb, w której kazdy elemnt zawiera tylko jedną liczbę i są one kolejnymi liczbami od 0 do m.
liczby :: Int -> Int -> [[Int]] -> [[Int]]
liczby a m tab = ans
    where ans = if a>m then tab else [[a]] ++ (liczby (a+1) m tab)

--Generuje leksykograficznie posorwoawny ciąg słów zawierających zawierających tylko cyfry 
--i zawierające nie więcej niz p wystapien cyfr z zakresu od 0 do m, gdzie słowo jest reprezentowane przez tablicę liczb.
generate :: Int -> Int  -> [[Int]]
generate m p = sort (filtrCaly 0 m p (perm_wrapper [] (liczby 0 m []) ((m+1)*p) 1))

--Konwertuje tablicę liczb na stringa
itostr :: [Int] -> String
itostr tab = concat (map show tab)

--Bierze wynik z 'generate' i zwraca n-ty element
final :: Int -> Int -> Int -> String
final n m p = itostr (generate m p !! (n-1))

main :: IO ()
main = do
    print (final 3 2 2)
    